/*
 * Regression test for the cut-sample source-range bug.
 *
 * Failure sequence under test, driven exactly as a user performs it:
 *   1. Import an audio sample.                    (setSampleBuffer)
 *   2. Cut/split the sample.                      (knife-mode mouse gesture)
 *   3. Select the resulting cut sample.           (mouse press)
 *   4. Stretch that cut sample.                   (right-edge drag)
 *
 * The source is deterministic and its two halves are *distinguishable*: the
 * first half carries 440 Hz on the left channel, the second half 880 Hz, and
 * the right channel carries 880 Hz throughout. So a rendered clip tells us not
 * only how long and how high it plays, but WHICH SOURCE SECTION it plays.
 *
 * Expected: stretching a cut clip stretches ONLY the source section the cut
 * retained. Neither the discarded section nor the whole original sample may be
 * squeezed into the new clip length.
 *
 * This test deliberately does NOT hand-construct a SampleClip with
 * pre-populated source boundaries: the split is produced by the real knife
 * gesture through ClipView's mouse handlers.
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <memory>
#include <vector>

#include <QtTest>

#include <QDebug>
#include <QApplication>
#include <QDialog>
#include <QMouseEvent>
#include <QTimer>

#include "lmmsconfig.h"

#include "AudioDummy.h"
#include "AudioEngine.h"
#include "ConfigManager.h"
#include "Engine.h"
#include "GuiApplication.h"
#include "MainWindow.h"
#include "Sample.h"
#include "SampleBuffer.h"
#include "SampleClip.h"
#include "SampleClipView.h"
#include "SamplePlayHandle.h"
#include "SampleStretch.h"
#include "SampleTrack.h"
#include "Song.h"
#include "SongEditor.h"
#include "TrackContainerView.h"
#include "TrackView.h"

using namespace lmms;
using namespace lmms::gui;

namespace {

// 96 px per bar with the default 192 ticks-per-bar gives 2 px per tick, so a
// 4-second span lands on a whole pixel and the drag targets are exact.
constexpr int PixelsPerBar = 96;
constexpr double SourceRate = 44100.0;
constexpr double SectionSeconds = 4.0;
constexpr double OriginalSeconds = SectionSeconds * 2.0;

auto engineRate() -> int
{
	return Engine::audioEngine()->outputSampleRate();
}

auto ticksForSeconds(double seconds) -> TimePos
{
	const double frames = seconds * engineRate();
	return TimePos(static_cast<int>(std::lround(frames / Engine::framesPerTick())));
}

auto secondsForTicks(TimePos ticks) -> double
{
	return double(ticks) * Engine::framesPerTick() / engineRate();
}

auto pixelsForTicks(TimePos ticks) -> int
{
	return static_cast<int>(std::lround(double(ticks) * PixelsPerBar / TimePos::ticksPerBar()));
}

/// 8 s at 44.1 kHz.  Left channel: 440 Hz for the first 4 s, 880 Hz for the
/// second 4 s.  Right channel: 880 Hz throughout, so a clip that plays the
/// *whole* original sample is distinguishable from one that plays only the
/// first half even if only the right channel were measured.
auto makeTwoSectionBuffer() -> std::shared_ptr<const SampleBuffer>
{
	const auto size = static_cast<size_t>(OriginalSeconds * SourceRate);
	std::vector<SampleFrame> data;
	data.reserve(size);
	for (size_t frame = 0; frame < size; ++frame)
	{
		const double t = double(frame) / SourceRate;
		const bool secondSection = t >= SectionSeconds;
		const double leftFrequency = secondSection ? 880.0 : 440.0;
		data.emplace_back(
			sample_t(0.8f * std::sin(2.0 * M_PI * leftFrequency * t)),
			sample_t(0.8f * std::sin(2.0 * M_PI * 880.0 * t)));
	}
	return std::make_shared<const SampleBuffer>(std::move(data), int(SourceRate));
}

/// Count positive-going zero crossings, which is exact for these pure sines
/// (a handful of cycles per period at most, never aliased).
auto countZeroCrossings(const std::vector<SampleFrame>& data, int channel) -> int
{
	int crossings = 0;
	double previous = 0.0;
	bool first = true;
	for (const auto& frame : data)
	{
		const double value = channel == 0 ? frame.left() : frame.right();
		if (!first && previous < 0.0 && value >= 0.0) { ++crossings; }
		previous = value;
		first = false;
	}
	return crossings;
}

struct SectionFacts
{
	double frequency = 0.0;
	int crossings = 0;
	/// Crossings contributed by the first quarter of the render: a render that
	/// contains the whole original sample starts low and ends high, a render of
	/// the retained first half stays low, a render of the retained second half
	/// stays high.
	double firstQuarterFrequency = 0.0;
	double lastQuarterFrequency = 0.0;
};

auto analyseSections(const std::vector<SampleFrame>& data, int channel) -> SectionFacts
{
	SectionFacts facts;
	if (data.size() < 4) { return facts; }
	const double seconds = double(data.size()) / engineRate();
	facts.crossings = countZeroCrossings(data, channel);
	facts.frequency = double(facts.crossings) / seconds;

	const auto quarter = data.size() / 4;
	const std::vector<SampleFrame> head(data.begin(), data.begin() + long(quarter));
	const std::vector<SampleFrame> tail(data.end() - long(quarter), data.end());
	facts.firstQuarterFrequency
		= double(countZeroCrossings(head, channel)) / (double(quarter) / engineRate());
	facts.lastQuarterFrequency
		= double(countZeroCrossings(tail, channel)) / (double(quarter) / engineRate());
	return facts;
}

void waitForStretched()
{
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
}

/// Render exactly what the sample track would hand the audio engine, using the
/// same code path: SampleClip::computePlaybackPlan() -> SamplePlayHandle::play().
auto renderClip(SampleClip* clip) -> std::vector<SampleFrame>
{
	const auto plan = clip->computePlaybackPlan(
		clip->outputFramesFor(clip->startPosition() + clip->startTimeOffset()));
	SamplePlayHandle handle(clip, plan);

	const auto fpp = Engine::audioEngine()->framesPerPeriod();
	std::vector<SampleFrame> out;
	std::vector<SampleFrame> buf(fpp);
	int guardPeriods = 20000;
	while (!handle.isFinished() && guardPeriods-- > 0)
	{
		std::fill(buf.begin(), buf.end(), SampleFrame(0.0f, 0.0f));
		handle.play(buf.data());
		out.insert(out.end(), buf.begin(), buf.end());
	}
	out.resize(std::min(out.size(), size_t(std::max(0, int(handle.totalFrames())))));
	return out;
}

} // namespace

class SampleClipSplitStretchTest : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void cleanupTestCase();
	void init();
	void cleanup();

	void splitProducesTwoClipsWithExpectedGeometry();
	void splitAssignsRetainedSourceRangeToEachHalf();
	void stretchingLeftHalfKeepsFirstSection();
	void stretchingRightHalfKeepsSecondSection();
	void shorteningLeftHalfKeepsFirstSection();
	void freshUnsplitClipStillStretchesWholeSample();

private:
	void createClipWithView();
	void destroyClipWithView();
	void splitAtTick(TimePos tickWithinClip);
	void sendMouse(QEvent::Type type, Qt::MouseButton button, Qt::MouseButtons buttons,
		Qt::KeyboardModifiers mods, QWidget* target, const QPoint& at);
	void dragRightEdgeTo(SampleClipView* view, TimePos targetLength);
	void report(const char* stage, SampleClip* clip);

	SampleTrack* m_track = nullptr;
	SampleClip* m_clip = nullptr;
	SampleClipView* m_view = nullptr;
	TrackView* m_trackView = nullptr;
};

void SampleClipSplitStretchTest::initTestCase()
{
	const QString actual = QGuiApplication::platformName();
	if (actual != "xcb" && actual != "wayland")
	{
		const QString why = QStringLiteral(
			"This test drives ClipView's real mouse handlers through a visible "
			"track view, which needs a windowing system. Run it under a display "
			"server (DISPLAY set); offscreen cannot expose the main window here. "
			"(platform=%1)").arg(actual);
		qInfo().noquote() << why;
		QSKIP(why.toUtf8().constData());
	}

	ConfigManager::inst()->setValue("app", "configured", "1");
	ConfigManager::inst()->setValue("audioengine", "audiodev", AudioDummy::name());

	QTimer guard;
	guard.setInterval(50);
	QObject::connect(&guard, &QTimer::timeout, []() {
		for (QWidget* widget : QApplication::topLevelWidgets())
		{
			if (auto* dialog = qobject_cast<QDialog*>(widget))
			{
				if (dialog->isModal() && dialog->isVisible()) { dialog->reject(); }
			}
		}
	});
	guard.start();
	new GuiApplication();
	guard.stop();

	getGUI()->mainWindow()->show();
	QVERIFY(QTest::qWaitForWindowExposed(getGUI()->mainWindow()));
}

void SampleClipSplitStretchTest::cleanupTestCase()
{
	SampleStretchManager::instance().waitUntilIdle();
}

void SampleClipSplitStretchTest::init()
{
	createClipWithView();
}

void SampleClipSplitStretchTest::cleanup()
{
	destroyClipWithView();
}

void SampleClipSplitStretchTest::createClipWithView()
{
	auto* editor = getGUI()->songEditor()->m_editor;
	editor->setPixelsPerBar(PixelsPerBar);

	m_track = new SampleTrack(Engine::getSong());
	m_clip = new SampleClip(m_track);
	m_clip->setSampleBuffer(makeTwoSectionBuffer());
	m_clip->movePosition(0);
	m_clip->setPitchMode(SampleClip::PitchMode::Stretch);

	TrackView* found = nullptr;
	for (int i = 0; i < 200 && found == nullptr; ++i)
	{
		QCoreApplication::processEvents();
		for (TrackView* tv : editor->trackViews())
		{
			if (tv != nullptr && tv->model() == m_track) { found = tv; break; }
		}
		if (found == nullptr) { QTest::qWait(25); }
	}
	QVERIFY2(found != nullptr, "no TrackView appeared for the sample track");
	m_trackView = found;

	m_view = new SampleClipView(m_clip, m_trackView);
	m_view->show();
	QTest::qWait(50);
	QCoreApplication::processEvents();

	QVERIFY2(m_view->width() > 0, "clip view was not laid out");
	QVERIFY2(m_clip->pitchMode() == SampleClip::PitchMode::Stretch, "clip did not enter Stretch mode");
	const int expectedWidth = pixelsForTicks(m_clip->length());
	QVERIFY2(std::abs(m_view->width() - expectedWidth) <= 2,
		qPrintable(QStringLiteral("clip view width %1, expected %2")
					   .arg(m_view->width()).arg(expectedWidth)));
}

void SampleClipSplitStretchTest::destroyClipWithView()
{
	SampleStretchManager::instance().waitUntilIdle();
	if (m_trackView != nullptr)
	{
		getGUI()->songEditor()->m_editor->deleteTrackView(m_trackView);
	}
	m_trackView = nullptr;
	m_view = nullptr;
	m_clip = nullptr;
	m_track = nullptr;
	QCoreApplication::processEvents();
}

void SampleClipSplitStretchTest::sendMouse(QEvent::Type type, Qt::MouseButton button,
	Qt::MouseButtons buttons, Qt::KeyboardModifiers mods, QWidget* target, const QPoint& at)
{
	QMouseEvent event(type, at, target->mapToGlobal(at), button, buttons, mods);
	QApplication::sendEvent(target, &event);
	QCoreApplication::processEvents();
}

/// Knife-mode split at an exact tick offset inside the clip. Alt is held so the
/// release path uses the unquantized position, which keeps the split point
/// deterministic instead of snapping to the current snap size.
void SampleClipSplitStretchTest::splitAtTick(TimePos tickWithinClip)
{
	auto* editor = getGUI()->songEditor()->m_editor;
	editor->setEditModeKnife();
	QCoreApplication::processEvents();
	QVERIFY2(static_cast<TrackContainerView*>(editor)->knifeMode(),
		"song editor did not enter knife mode");

	const int x = pixelsForTicks(tickWithinClip);
	const QPoint at(x, m_view->height() / 2);
	QVERIFY2(x > 16 && x < m_view->width() - 16,
		qPrintable(QStringLiteral("split x=%1 is inside a resize grip").arg(x)));

	sendMouse(QEvent::MouseButtonPress, Qt::LeftButton, Qt::LeftButton,
		Qt::AltModifier, m_view, at);
	sendMouse(QEvent::MouseMove, Qt::NoButton, Qt::LeftButton, Qt::AltModifier, m_view, at);
	sendMouse(QEvent::MouseButtonRelease, Qt::LeftButton, Qt::NoButton,
		Qt::AltModifier, m_view, at);

	editor->setEditModeDraw();
	QCoreApplication::processEvents();
	QTest::qWait(50);
	QCoreApplication::processEvents();
}

void SampleClipSplitStretchTest::dragRightEdgeTo(SampleClipView* view, TimePos targetLength)
{
	const QPoint press(view->width() - 1, view->height() / 2);
	const QPoint release(pixelsForTicks(targetLength), view->height() / 2);
	sendMouse(QEvent::MouseButtonPress, Qt::LeftButton, Qt::LeftButton,
		Qt::AltModifier, view, press);
	sendMouse(QEvent::MouseMove, Qt::NoButton, Qt::LeftButton, Qt::AltModifier, view, release);
	sendMouse(QEvent::MouseMove, Qt::NoButton, Qt::LeftButton, Qt::AltModifier, view, release);
	sendMouse(QEvent::MouseButtonRelease, Qt::LeftButton, Qt::NoButton,
		Qt::NoModifier, view, release);
}

void SampleClipSplitStretchTest::report(const char* stage, SampleClip* clip)
{
	const auto buffer = clip->sample().buffer();
	const int size = buffer ? int(buffer->size()) : 0;
	const int rate = clip->sample().sampleRate();
	Q_UNUSED(rate)
	qInfo().noquote()
		<< QStringLiteral("[%1] clip@%2 len=%3 (%4 s) offset=%5 | source frames [%6 .. %7] of %8"
						  " => range %9 s | ratio %10 | stretched buffer %11")
			   .arg(QString::fromLatin1(stage))
			   .arg(static_cast<int>(clip->startPosition()))
			   .arg(static_cast<int>(clip->length()))
			   .arg(secondsForTicks(clip->length()), 0, 'f', 3)
			   .arg(static_cast<int>(clip->startTimeOffset()))
			   .arg(clip->sourceStartFrame())
			   .arg(clip->sourceEndFrame())
			   .arg(size)
			   .arg(clip->sourceRangeTicks() * Engine::framesPerTick() / engineRate(), 0, 'f', 3)
			   .arg(clip->stretchRatio(), 0, 'f', 4)
			   .arg(QString::fromLatin1(clip->hasStretchedSample() ? "yes" : "no"));
}

// ---------------------------------------------------------------------------
// 1. The split itself.
// ---------------------------------------------------------------------------
void SampleClipSplitStretchTest::splitProducesTwoClipsWithExpectedGeometry()
{
	splitAtTick(ticksForSeconds(SectionSeconds));

	QVERIFY2(m_track != nullptr, "track vanished");
	if (m_track->numOfClips() != 2)
	{
		QFAIL(qPrintable(QStringLiteral("splitting produced %1 clips, expected 2")
							 .arg(m_track->numOfClips())));
	}

	auto* left = dynamic_cast<SampleClip*>(m_track->getClip(0));
	auto* right = dynamic_cast<SampleClip*>(m_track->getClip(1));
	QVERIFY(left != nullptr);
	QVERIFY(right != nullptr);

	const TimePos fourSeconds = ticksForSeconds(SectionSeconds);
	QVERIFY2(static_cast<int>(left->startPosition()) == 0,
		qPrintable(QStringLiteral("left half starts at %1, expected 0")
				   .arg(static_cast<int>(left->startPosition()))));
	QVERIFY2(static_cast<int>(left->length()) == static_cast<int>(fourSeconds),
		qPrintable(QStringLiteral("left half length %1, expected %2")
				   .arg(static_cast<int>(left->length())).arg(int(fourSeconds))));
	QVERIFY2(static_cast<int>(right->startPosition()) == static_cast<int>(fourSeconds),
		qPrintable(QStringLiteral("right half starts at %1, expected %2")
				   .arg(static_cast<int>(right->startPosition())).arg(int(fourSeconds))));
	QVERIFY2(static_cast<int>(right->length()) == static_cast<int>(fourSeconds),
		qPrintable(QStringLiteral("right half length %1, expected %2")
				   .arg(static_cast<int>(right->length())).arg(int(fourSeconds))));
}

// ---------------------------------------------------------------------------
// 2. THE DEFECT: what source range does the split hand to each half?
// ---------------------------------------------------------------------------
void SampleClipSplitStretchTest::splitAssignsRetainedSourceRangeToEachHalf()
{
	splitAtTick(ticksForSeconds(SectionSeconds));

	if (m_track->numOfClips() != 2)
	{
		QFAIL(qPrintable(QStringLiteral("splitting produced %1 clips, expected 2")
							 .arg(m_track->numOfClips())));
	}
	auto* left = dynamic_cast<SampleClip*>(m_track->getClip(0));
	auto* right = dynamic_cast<SampleClip*>(m_track->getClip(1));
	QVERIFY(left != nullptr);
	QVERIFY(right != nullptr);

	report("after split: LEFT ", left);
	report("after split: RIGHT", right);

	const int bufferSize = int(left->sample().buffer()->size());
	const int half = bufferSize / 2;

	// The left half retained the first section, so its source window must stop
	// halfway through the buffer.
	QVERIFY2(left->sourceStartFrame() == 0,
		qPrintable(QStringLiteral("left half sourceStartFrame() is %1, expected 0")
					   .arg(left->sourceStartFrame())));
	QVERIFY2(left->sourceEndFrame() > 0 && std::abs(left->sourceEndFrame() - half) <= 2,
		qPrintable(QStringLiteral(
					   "left half sourceEndFrame() is %1, expected ~%2 (the retained"
					   " first section); %1 means it still claims the WHOLE sample"
					   " of %3 frames")
					   .arg(left->sourceEndFrame()).arg(half).arg(bufferSize)));

	// The right half retained the second section. Its retained range may be
	// expressed either as an explicit source start frame or as a negative
	// start-time offset that materialiseAudibleRange() folds into the source
	// start when a stretch is computed; either way the EFFECTIVE retained
	// window must be the second half. Check the effective window, which is
	// the public, semantics-preserving way to read what the clip will
	// actually play.
	const auto effectiveStart = right->sourceFrameAtOutputFrame(
		right->outputFramesFor(right->startPosition()));
	const auto effectiveEnd = right->sourceFrameAtOutputFrame(
		right->outputFramesFor(right->endPosition()));
	QVERIFY2(std::abs(effectiveStart - half) <= 2,
		qPrintable(QStringLiteral(
					   "right half effective source start is %1, expected ~%2 (the retained"
					   " second section)").arg(effectiveStart).arg(half)));
	QVERIFY2(std::abs(effectiveEnd - bufferSize) <= 2,
		qPrintable(QStringLiteral("right half effective source end is %1, expected ~%2")
					   .arg(effectiveEnd).arg(bufferSize)));
}

// ---------------------------------------------------------------------------
// 3. Stretching the LEFT half must play only the first section (440 Hz left).
// ---------------------------------------------------------------------------
void SampleClipSplitStretchTest::stretchingLeftHalfKeepsFirstSection()
{
	splitAtTick(ticksForSeconds(SectionSeconds));
	if (m_track->numOfClips() != 2)
	{
		QFAIL(qPrintable(QStringLiteral("splitting produced %1 clips, expected 2")
							 .arg(m_track->numOfClips())));
	}
	auto* left = dynamic_cast<SampleClip*>(m_track->getClip(0));
	QVERIFY(left != nullptr);
	report("LEFT before stretch", left);

	dragRightEdgeTo(m_view, ticksForSeconds(8.0));
	waitForStretched();
	report("LEFT after stretch ", left);

	QVERIFY2(left->pitchMode() == SampleClip::PitchMode::Stretch, "left half left Stretch mode");
	QVERIFY2(std::abs(left->length() - ticksForSeconds(8.0)) <= ticksForSeconds(0.05),
		qPrintable(QStringLiteral("left half length is %1 ticks, expected %2")
					   .arg(left->length()).arg(ticksForSeconds(8.0))));

	const auto rendered = renderClip(left);
	const double seconds = double(rendered.size()) / engineRate();
	qInfo().noquote() << QStringLiteral("LEFT rendered %1 s").arg(seconds, 0, 'f', 3);
	QVERIFY2(std::abs(seconds - 8.0) < 0.15,
		qPrintable(QStringLiteral("left half rendered %1 s, expected ~8 s").arg(seconds)));

	const SectionFacts facts = analyseSections(rendered, 0);
	qInfo().noquote() << QStringLiteral(
		"LEFT left-channel pitch: overall %1 Hz, first quarter %2 Hz, last quarter %3 Hz")
		.arg(facts.frequency, 0, 'f', 1)
		.arg(facts.firstQuarterFrequency, 0, 'f', 1)
		.arg(facts.lastQuarterFrequency, 0, 'f', 1);

	// Only the retained first section may play, at an unchanged pitch.
	QVERIFY2(std::abs(facts.frequency - 440.0) < 25.0,
		qPrintable(QStringLiteral(
					   "stretching the cut left half plays %1 Hz, expected ~440 Hz:"
					   " the discarded second section (880 Hz) leaked into the clip")
					   .arg(facts.frequency, 0, 'f', 1)));
	QVERIFY2(std::abs(facts.lastQuarterFrequency - 440.0) < 25.0,
		qPrintable(QStringLiteral(
					   "the tail of the stretched left half plays %1 Hz, expected ~440 Hz:"
					   " the whole original sample is being squeezed into the clip")
					   .arg(facts.lastQuarterFrequency, 0, 'f', 1)));
}

// ---------------------------------------------------------------------------
// 4. Stretching the RIGHT half must play only the second section (880 Hz left).
// ---------------------------------------------------------------------------
void SampleClipSplitStretchTest::stretchingRightHalfKeepsSecondSection()
{
	splitAtTick(ticksForSeconds(SectionSeconds));
	if (m_track->numOfClips() != 2)
	{
		QFAIL(qPrintable(QStringLiteral("splitting produced %1 clips, expected 2")
							 .arg(m_track->numOfClips())));
	}
	auto* right = dynamic_cast<SampleClip*>(m_track->getClip(1));
	QVERIFY(right != nullptr);

	// The right half's view is created by TrackView::createClipView() through a
	// queued signal, so wait for it rather than constructing one ourselves.
	SampleClipView* rightView = nullptr;
	for (int i = 0; i < 200 && rightView == nullptr; ++i)
	{
		QCoreApplication::processEvents();
		for (SampleClipView* v : m_trackView->findChildren<SampleClipView*>())
		{
			if (v != nullptr && v->getClip() == right) { rightView = v; break; }
		}
		if (rightView == nullptr) { QTest::qWait(25); }
	}
	QVERIFY2(rightView != nullptr, "no clip view appeared for the right half");
	QVERIFY2(rightView->width() > 0, "right half clip view was not laid out");

	report("RIGHT before stretch", right);

	dragRightEdgeTo(rightView, ticksForSeconds(8.0));
	waitForStretched();
	report("RIGHT after stretch", right);

	QVERIFY2(right->pitchMode() == SampleClip::PitchMode::Stretch, "right half left Stretch mode");
	QVERIFY2(std::abs(right->length() - ticksForSeconds(8.0)) <= ticksForSeconds(0.05),
		qPrintable(QStringLiteral("right half length is %1 ticks, expected %2")
					   .arg(right->length()).arg(ticksForSeconds(8.0))));

	const auto rendered = renderClip(right);
	const double seconds = double(rendered.size()) / engineRate();
	qInfo().noquote() << QStringLiteral("RIGHT rendered %1 s").arg(seconds, 0, 'f', 3);
	QVERIFY2(std::abs(seconds - 8.0) < 0.15,
		qPrintable(QStringLiteral("right half rendered %1 s, expected ~8 s").arg(seconds)));

	const SectionFacts facts = analyseSections(rendered, 0);
	qInfo().noquote() << QStringLiteral(
		"RIGHT left-channel pitch: overall %1 Hz, first quarter %2 Hz, last quarter %3 Hz")
		.arg(facts.frequency, 0, 'f', 1)
		.arg(facts.firstQuarterFrequency, 0, 'f', 1)
		.arg(facts.lastQuarterFrequency, 0, 'f', 1);

	QVERIFY2(std::abs(facts.frequency - 880.0) < 40.0,
		qPrintable(QStringLiteral(
					   "stretching the cut right half plays %1 Hz, expected ~880 Hz:"
					   " the discarded first section (440 Hz) leaked into the clip")
					   .arg(facts.frequency, 0, 'f', 1)));
	QVERIFY2(std::abs(facts.firstQuarterFrequency - 880.0) < 40.0,
		qPrintable(QStringLiteral(
					   "the head of the stretched right half plays %1 Hz, expected ~880 Hz:"
					   " the whole original sample is being squeezed into the clip")
					   .arg(facts.firstQuarterFrequency, 0, 'f', 1)));
}

// ---------------------------------------------------------------------------
// 5. Stretching a cut clip *shorter* must also stay inside the retained
// section. A right-edge drag on a sample clip always goes through
// SampleClip::stretchToLength(), so this is the same operation with a ratio
// below 1 rather than a trim.
// ---------------------------------------------------------------------------
void SampleClipSplitStretchTest::shorteningLeftHalfKeepsFirstSection()
{
	splitAtTick(ticksForSeconds(SectionSeconds));
	if (m_track->numOfClips() != 2)
	{
		QFAIL(qPrintable(QStringLiteral("splitting produced %1 clips, expected 2")
							 .arg(m_track->numOfClips())));
	}
	auto* left = dynamic_cast<SampleClip*>(m_track->getClip(0));
	QVERIFY(left != nullptr);
	report("LEFT before shorten", left);

	dragRightEdgeTo(m_view, ticksForSeconds(2.0));
	waitForStretched();
	report("LEFT after shorten ", left);

	QVERIFY2(std::abs(left->length() - ticksForSeconds(2.0)) <= ticksForSeconds(0.05),
		qPrintable(QStringLiteral("left half length is %1 ticks, expected %2")
					   .arg(left->length()).arg(ticksForSeconds(2.0))));

	const auto rendered = renderClip(left);
	const double seconds = double(rendered.size()) / engineRate();
	qInfo().noquote() << QStringLiteral("LEFT rendered %1 s").arg(seconds, 0, 'f', 3);
	QVERIFY2(std::abs(seconds - 2.0) < 0.1,
		qPrintable(QStringLiteral("left half rendered %1 s, expected ~2 s").arg(seconds)));

	const SectionFacts facts = analyseSections(rendered, 0);
	qInfo().noquote() << QStringLiteral(
		"LEFT left-channel pitch: overall %1 Hz, first quarter %2 Hz, last quarter %3 Hz")
		.arg(facts.frequency, 0, 'f', 1)
		.arg(facts.firstQuarterFrequency, 0, 'f', 1)
		.arg(facts.lastQuarterFrequency, 0, 'f', 1);

	QVERIFY2(std::abs(facts.frequency - 440.0) < 25.0,
		qPrintable(QStringLiteral(
					   "shortening the cut left half plays %1 Hz, expected ~440 Hz:"
					   " the discarded second section (880 Hz) leaked into the clip")
					   .arg(facts.frequency, 0, 'f', 1)));
}

// ---------------------------------------------------------------------------
// 6. Guard: the fix must not disturb stretching a fresh, unsplit clip.
// ---------------------------------------------------------------------------
void SampleClipSplitStretchTest::freshUnsplitClipStillStretchesWholeSample()
{
	dragRightEdgeTo(m_view, ticksForSeconds(16.0));
	waitForStretched();
	report("FRESH after stretch", m_clip);

	QVERIFY2(m_clip->pitchMode() == SampleClip::PitchMode::Stretch, "fresh clip left Stretch mode");
	QVERIFY2(std::abs(m_clip->stretchRatio() - 2.0) < 0.05,
		qPrintable(QStringLiteral("fresh clip stretch ratio is %1, expected ~2")
					   .arg(m_clip->stretchRatio(), 0, 'f', 4)));
	QVERIFY2(m_clip->hasStretchedSample(), "fresh clip produced no stretched buffer");

	const auto rendered = renderClip(m_clip);
	const double seconds = double(rendered.size()) / engineRate();
	QVERIFY2(std::abs(seconds - 16.0) < 0.2,
		qPrintable(QStringLiteral("fresh clip rendered %1 s, expected ~16 s").arg(seconds)));

	const SectionFacts facts = analyseSections(rendered, 0);
	// Whole original sample: first half 440 Hz, second half 880 Hz.
	QVERIFY2(std::abs(facts.firstQuarterFrequency - 440.0) < 25.0,
		qPrintable(QStringLiteral("fresh clip head plays %1 Hz, expected ~440 Hz")
					   .arg(facts.firstQuarterFrequency, 0, 'f', 1)));
	QVERIFY2(std::abs(facts.lastQuarterFrequency - 880.0) < 40.0,
		qPrintable(QStringLiteral("fresh clip tail plays %1 Hz, expected ~880 Hz")
					   .arg(facts.lastQuarterFrequency, 0, 'f', 1)));
}

int main(int argc, char** argv)
{
	if (qEnvironmentVariableIsEmpty("DISPLAY") && qEnvironmentVariableIsEmpty("WAYLAND_DISPLAY"))
	{
		qputenv("QT_QPA_PLATFORM", "offscreen");
	}
	QApplication app(argc, argv);
	SampleClipSplitStretchTest test;
	return QTest::qExec(&test, argc, argv);
}

#include "SampleClipSplitStretchTest.moc"
