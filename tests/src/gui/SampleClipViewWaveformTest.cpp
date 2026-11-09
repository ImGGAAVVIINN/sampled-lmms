/*
 * SampleClipViewWaveformTest.cpp - regression tests for the waveform a sample
 * clip *draws*, as opposed to the audio it plays.
 *
 * These exist because the user-visible complaint was about rendering:
 *   "with the toolbar Stretch toggle off, dragging the clip shorter makes the
 *    waveform stretch and become slower, even though playback speed does not
 *    change."
 * A screenshot of the clip is not evidence about that -- the clip's coloured
 * body is drawn independently of the waveform inside it. So these tests assert
 * on `SampleClipView::waveformGeometry()`, the exact rectangle and sample
 * window `paintEvent()` draws, which is the rendering area itself.
 *
 * The invariants checked here:
 *   1. Toolbar Stretch OFF: the waveform is drawn in *source space*. Its width
 *      and its pixels-per-source-frame are fixed by the source, so no clip
 *      length -- longer, equal or shorter than the natural length -- can
 *      rescale it. (Bug B)
 *   2. Toolbar Stretch OFF: trimming shrinks the drawn range instead of
 *      compressing it, so discarded audio disappears from the drawing. (Bug C)
 *   3. Toolbar Stretch ON: the waveform spans the clip's full resized width,
 *      which is the whole point of the toggle.
 *   4. The toolbar toggle and the context-menu Pitch mode are independent:
 *      choosing Pitch mode -> Stretch must not make the waveform fill the clip.
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see COPYING); if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include <QApplication>
#include <QDialog>
#include <QTimer>
#include <QTest>

#include "lmmsconfig.h"
#include "AudioDummy.h"
#include "AudioEngine.h"
#include "ConfigManager.h"
#include "Engine.h"
#include "GuiApplication.h"
#include "Sample.h"
#include "SampleBuffer.h"
#include "SampleClip.h"
#include "SampleClipView.h"
#include "SampleStretch.h"
#include "SampleTrack.h"
#include "Song.h"
#include "SongEditor.h"
#include "TrackContainerView.h"
#include "TrackView.h"

using namespace lmms;
using namespace lmms::gui;
using lmms::gui::SampleClipView;

namespace
{

/**
 * @brief Horizontal zoom used by every case: one pixel per timeline tick.
 *
 * With this zoom a width in pixels *is* a length in ticks, and a width in
 * pixels *is* a number of source frames, so the assertions below can be read
 * directly as "how much source audio does one pixel represent".
 */
constexpr double PxPerTick = 1.0;

//! Scroll offset assumed by every case; the geometry subtracts it from the
//! drawing position, so keeping it at zero keeps `x` meaningful.
constexpr double NoScroll = 0.0;

sample_rate_t engineRate() { return Engine::audioEngine()->outputSampleRate(); }

/**
 * @brief A buffer whose first half is @a lowHz and whose second half is
 * @a highHz, so the two halves of the drawing can be told apart.
 */
std::shared_ptr<const SampleBuffer> makeTwoToneBuffer(size_t frames, int rate,
	double lowHz = 440.0, double highHz = 880.0)
{
	std::vector<SampleFrame> data;
	data.reserve(frames);
	const auto split = frames / 2;
	for (size_t i = 0; i < frames; ++i)
	{
		const auto t = static_cast<double>(i) / rate;
		const auto hz = i < split ? lowHz : highHz;
		const auto v = static_cast<sample_t>(0.8 * std::sin(2.0 * M_PI * hz * t));
		data.emplace_back(v, v);
	}
	return std::make_shared<const SampleBuffer>(std::move(data), rate);
}

struct ClipSetup { SampleTrack* track; SampleClip* clip; };

ClipSetup createClip(std::shared_ptr<const SampleBuffer> buffer)
{
	auto track = new SampleTrack(Engine::getSong());
	auto clip = new SampleClip(track);
	clip->setSampleBuffer(std::move(buffer));
	return {track, clip};
}

/**
 * @brief Block until every stretch job has been computed and delivered.
 *
 * `waitUntilIdle()` alone only guarantees the worker finished; delivery is a
 * queued invocation, so the event loop has to run for the clip to receive it.
 */
void waitForStretched()
{
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
}

//! @brief Frames of a @a seconds-long source at the engine's rate.
size_t framesOf(double seconds)
{
	return static_cast<size_t>(std::lround(seconds * engineRate()));
}

/**
 * @brief Zero-crossing frequency of one channel over a run of frames.
 *
 * Lets a test ask "which of the two tones is in this buffer", which is how
 * "the discarded half came back" becomes observable in a *drawing* rather than
 * only in rendered audio.
 */
double dominantFrequency(const SampleFrame* data, size_t frames, int rate, int channel)
{
	if (frames < 2) { return 0.0; }
	int crossings = 0;
	sample_t prev = channel == 0 ? data[0].left() : data[0].right();
	for (size_t i = 1; i < frames; ++i)
	{
		const auto cur = channel == 0 ? data[i].left() : data[i].right();
		if (prev < 0.0f && cur >= 0.0f) { ++crossings; }
		prev = cur;
	}
	return crossings / static_cast<double>(frames) * rate;
}

} // namespace

/**
 * @brief Create a clip with a real SampleClipView parented in the SongEditor.
 *
 * The view must be parented inside the editor's track-row layout so that its
 * QWidget constructor does not segfault. This mirrors the pattern used by
 * other GUI tests (SampleClipContextMenuTest, SampleClipSplitStretchTest).
 */
lmms::gui::SampleClipView* createClipWithView(std::shared_ptr<const lmms::SampleBuffer> buffer)
{
	auto track = new lmms::SampleTrack(lmms::Engine::getSong());
	auto clip = new lmms::SampleClip(track);
	clip->setSampleBuffer(std::move(buffer));

	auto* editor = lmms::gui::getGUI()->songEditor()->m_editor;
	if (editor == nullptr) { return nullptr; }

	lmms::gui::TrackView* found = nullptr;
	for (int i = 0; i < 200 && found == nullptr; ++i)
	{
		QCoreApplication::processEvents();
		for (lmms::gui::TrackView* tv : editor->trackViews())
		{
			if (tv != nullptr && tv->model() == track) { found = tv; break; }
		}
		if (found == nullptr) { QTest::qWait(25); }
	}
	if (found == nullptr) { return nullptr; }

	auto* view = new lmms::gui::SampleClipView(clip, found);
	view->show();
	QTest::qWait(50);
	QCoreApplication::processEvents();

	return view;
}


class SampleClipViewWaveformTest : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase()
	{
		Engine::init(true);

		ConfigManager::inst()->setValue("app", "configured", "1");
		ConfigManager::inst()->setValue("audioengine", "audiodev", AudioDummy::name());

		QTimer guard;
		guard.setInterval(50);
		QObject::connect(&guard, &QTimer::timeout, []() {
			for (QWidget* widget : QApplication::topLevelWidgets())
			{
				auto* dialog = qobject_cast<QDialog*>(widget);
				if (dialog != nullptr && dialog->isModal() && dialog->isVisible())
				{
					dialog->reject();
				}
			}
		});
		guard.start();
		new GuiApplication();
		guard.stop();

		QVERIFY(getGUI() != nullptr);
		QVERIFY(getGUI()->mainWindow() != nullptr);
		QVERIFY(getGUI()->songEditor() != nullptr);
		QVERIFY(getGUI()->songEditor()->m_editor != nullptr);
		SampleStretchManager::instance().waitUntilIdle();
	}

	/**
	 * @brief Bug B, the core invariant: with the toolbar toggle off, the
	 * waveform's geometry must not depend on the clip's length at all.
	 *
	 * The clip is resized to a quarter, a half, twice and four times its
	 * natural length -- including the case the user reported, dragging the
	 * right edge left *into* the drawn waveform -- and the drawn rectangle and
	 * source window are required to be byte-for-byte what they were before the
	 * drag. If any of these changed, one pixel would represent a different
	 * amount of source audio after the resize, which is exactly "the waveform
	 * stretched and became slower".
	 */
	void toolbarOffResizeNeverRescalesWaveform()
	{
		auto [track, clip] = createClip(makeTwoToneBuffer(framesOf(8.0), engineRate()));
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);
		const auto& source = clip->sample();

		const auto baseline = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, /*stretchMode=*/false, NoScroll);

		// Sanity: at natural length the waveform spans the whole source, so the
		// quantity being held constant below is a non-trivial width.
		QCOMPARE(baseline.sampleStart, 0.0f);
		QCOMPARE(baseline.sampleEnd, 1.0f);
		QVERIFY(std::abs(baseline.width - natural) < 1.0f);

		const QList<std::pair<const char*, TimePos>> drags = {
			{"quarter of natural", TimePos(natural / 4)},
			{"half of natural (dragged into the waveform)", TimePos(natural / 2)},
			{"natural", natural},
			{"twice natural", TimePos(natural * 2)},
			{"four times natural", TimePos(natural * 4)},
		};

		for (const auto& [label, length] : drags) {
			clip->changeLength(length);
			const auto plan = SampleClipView::waveformGeometry(*clip, source,
				PxPerTick, /*stretchMode=*/false, NoScroll);
			QVERIFY2(std::abs(plan.width - baseline.width) < 0.5f,
				qPrintable(QStringLiteral("width changed when resized to %1 (%2 -> %3)")
					.arg(label).arg(baseline.width).arg(plan.width)));
			QVERIFY2(std::abs(plan.x - baseline.x) < 0.5f,
				qPrintable(QStringLiteral("x changed when resized to %1").arg(label)));
			QCOMPARE(plan.sampleStart, baseline.sampleStart);
			QCOMPARE(plan.sampleEnd, baseline.sampleEnd);
		}
	}

	/**
	 * @brief Bug B as the user described it: shortening the clip must remove
	 * drawn audio, never slow the drawing down.
	 *
	 * Trimming to half the natural length keeps the same pixels-per-source-frame
	 * (so the cycles stay the same width) and draws only the first half of the
	 * source, i.e. the waveform ends halfway across the clip instead of being
	 * squeezed to fit.
	 */
	void toolbarOffTrimShrinksDrawingInsteadOfCompressingIt()
	{
		auto [track, clip] = createClip(makeTwoToneBuffer(framesOf(8.0), engineRate()));
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);
		const auto& source = clip->sample();

		const auto before = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);

		clip->trimToLength(TimePos(natural / 2));

		const auto after = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);

		// Same scale: a pixel is worth the same source audio as before, so the
		// waveform cannot look slower or faster.
		QVERIFY2(std::abs(after.width - before.width / 2.0f) < 1.0f,
			qPrintable(QStringLiteral("trimmed waveform should be half as wide, got %1 of %2")
				.arg(after.width).arg(before.width)));
		// And the second half of the source is no longer drawn at all.
		QVERIFY2(std::abs(after.sampleEnd - 0.5f) < 0.01f,
			qPrintable(QStringLiteral("drawn range should stop at the trim, sampleEnd=%1")
				.arg(after.sampleEnd)));
		QCOMPARE(after.sampleStart, 0.0f);

		// Pixels per source frame are unchanged by the trim: the width halved
		// because half as much source is drawn, not because the scale moved.
		const auto size = static_cast<float>(source.sampleSize());
		const auto drawnBefore = (before.sampleEnd - before.sampleStart) * size;
		const auto drawnAfter = (after.sampleEnd - after.sampleStart) * size;
		const auto pxPerFrameBefore = before.width / drawnBefore;
		const auto pxPerFrameAfter = after.width / drawnAfter;
		QVERIFY2(std::abs(pxPerFrameAfter - pxPerFrameBefore) < 0.0001f,
			qPrintable(QStringLiteral("scale drifted: %1 px/frame vs %2 px/frame")
				.arg(pxPerFrameAfter).arg(pxPerFrameBefore)));
	}

	/**
	 * @brief Bug B / Bug A separation: Pitch mode -> Stretch must not make the
	 * waveform fill the clip while the toolbar toggle is off.
	 *
	 * The two controls are independent. Stretching to twice the natural length
	 * doubles the clip and the audio, but with the toolbar off the waveform is
	 * still the original 8 seconds of source at its original scale, so it keeps
	 * its natural width and does not fill the doubled clip.
	 */
	void pitchModeStretchDoesNotAffectToolbarOffWaveform()
	{
		auto [track, clip] = createClip(makeTwoToneBuffer(framesOf(8.0), engineRate()));
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);
		const auto& source = clip->sample();

		const auto before = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);

		clip->setPitchMode(SampleClip::PitchMode::Stretch);
		clip->stretchToLength(TimePos(natural * 2));
		waitForStretched();

		QVERIFY2(clip->stretchedSample() != nullptr, "stretch buffer should exist");
		QVERIFY2(std::abs(clip->stretchRatio() - 2.0) < 0.01,
			qPrintable(QStringLiteral("ratio should be 2, got %1").arg(clip->stretchRatio())));

		const auto after = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);

		QVERIFY2(std::abs(after.width - before.width) < 0.5f,
			qPrintable(QStringLiteral("toolbar-off waveform must keep its natural width across a "
				"pitch-mode stretch (%1 -> %2, clip length %3)")
				.arg(before.width).arg(after.width).arg(clip->length())));
		QCOMPARE(after.sampleStart, 0.0f);
		QCOMPARE(after.sampleEnd, 1.0f);
		// Explicitly: it must *not* have grown to fill the doubled clip.
		QVERIFY2(after.width < clip->length() * 0.6f,
			qPrintable(QStringLiteral("waveform filled the stretched clip: width %1, clip %2")
				.arg(after.width).arg(clip->length())));
	}

	/**
	 * @brief Bug B, the other half of the toggle: with the toolbar Stretch
	 * mode on, the waveform spans the clip's full resized width.
	 *
	 * Checked both longer than natural (stretched) and shorter than natural
	 * (dragged into the waveform), which is the direction the bug lived in.
	 */
	void toolbarOnWaveformSpansTheClip()
	{
		auto [track, clip] = createClip(makeTwoToneBuffer(framesOf(8.0), engineRate()));
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);
		clip->setPitchMode(SampleClip::PitchMode::Stretch);

		clip->stretchToLength(TimePos(natural * 2));
		waitForStretched();
		const auto stretched = clip->stretchedSample();
		QVERIFY(stretched != nullptr);

		const auto longer = SampleClipView::waveformGeometry(*clip, *stretched,
			PxPerTick, true, NoScroll);
		QVERIFY2(std::abs(longer.width - clip->length()) < 1.0f,
			qPrintable(QStringLiteral("toolbar-on waveform should span the clip: %1 vs %2")
				.arg(longer.width).arg(clip->length())));
		QCOMPARE(longer.sampleStart, 0.0f);
		QVERIFY2(longer.sampleEnd > 0.99f,
			qPrintable(QStringLiteral("stretched buffer should be drawn end to end, got %1")
				.arg(longer.sampleEnd)));

		// Now drag the right edge back to half the natural length: still spans
		// the clip, and the clip is shorter than the natural waveform.
		clip->stretchToLength(TimePos(natural / 2));
		waitForStretched();
		const auto shorterBuffer = clip->stretchedSample();
		QVERIFY(shorterBuffer != nullptr);

		const auto shorter = SampleClipView::waveformGeometry(*clip, *shorterBuffer,
			PxPerTick, true, NoScroll);
		QVERIFY2(std::abs(shorter.width - clip->length()) < 1.0f,
			qPrintable(QStringLiteral("toolbar-on waveform should still span the shortened clip: "
				"%1 vs %2").arg(shorter.width).arg(clip->length())));
		QVERIFY2(shorter.width < natural * 0.6f, "clip really is shorter than natural");
	}

	/**
	 * @brief Bug C in the drawing: after trimming away the second half of a
	 * two-tone source and then stretching, the discarded half must not come
	 * back into the waveform.
	 *
	 * The source is 8 s with a distinct second half. Trim to 4 s, stretch to
	 * 8 s. Toolbar off, the drawing must still stop at the 4 s mark of the
	 * source -- the retained region, drawn at natural scale -- rather than
	 * spreading the whole 8 s original across the clip, which is what the bug
	 * did.
	 */
	void trimThenStretchDrawsOnlyTheRetainedRegion()
	{
		auto [track, clip] = createClip(makeTwoToneBuffer(framesOf(8.0), engineRate()));
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);
		const auto& source = clip->sample();

		clip->trimToLength(TimePos(natural / 2));
		const auto trimmedEnd = clip->sourceEndFrame();
		QVERIFY2(std::abs(trimmedEnd - static_cast<int>(framesOf(4.0))) < 2,
			qPrintable(QStringLiteral("trim should retain 4 s, sourceEndFrame=%1").arg(trimmedEnd)));

		clip->setPitchMode(SampleClip::PitchMode::Stretch);
		clip->stretchToLength(TimePos(natural)); // 4 s of audio -> 8 s clip
		waitForStretched();

		QCOMPARE(clip->sourceStartFrame(), 0);
		QCOMPARE(clip->sourceEndFrame(), trimmedEnd); // unchanged by the stretch

		const auto off = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);
		QVERIFY2(std::abs(off.sampleEnd - 0.5f) < 0.01f,
			qPrintable(QStringLiteral("the discarded half must not be drawn, sampleEnd=%1")
				.arg(off.sampleEnd)));
		QVERIFY2(std::abs(off.width - natural / 2.0f) < 1.0f,
			qPrintable(QStringLiteral("retained region must keep its natural width: %1 vs %2")
				.arg(off.width).arg(natural / 2.0f)));

		// Toolbar on: the stretched buffer is what plays, and it must contain
		// only the retained 4 s stretched to 8 s -- never the full 8 s source.
		// Its size alone cannot prove that (4 s stretched 2x is as long as the
		// 8 s it came from), so the check is on content: the retained half of
		// the source is the 440 Hz tone, the discarded half is the 880 Hz one,
		// so the buffer the waveform is drawn from must be 440 Hz throughout.
		const auto stretched = clip->stretchedSample();
		QVERIFY(stretched != nullptr);
		const auto retainedFrames = static_cast<double>(trimmedEnd - clip->sourceStartFrame());
		const auto expected = retainedFrames * 2.0; // 4 s stretched to 8 s
		QVERIFY2(std::abs(static_cast<double>(stretched->sampleSize()) - expected)
			< 0.05 * expected,
			qPrintable(QStringLiteral("stretched buffer should hold the retained 4 s stretched "
				"to 8 s, got %1 frames, expected ~%2").arg(stretched->sampleSize()).arg(expected)));

		const auto* frames = stretched->data();
		const auto n = stretched->sampleSize();
		const auto firstHalf = dominantFrequency(frames, n / 2, stretched->sampleRate(), 0);
		const auto secondHalf = dominantFrequency(frames + n / 2, n - n / 2,
			stretched->sampleRate(), 0);
		qDebug() << "  stretched buffer pitch:" << firstHalf << "/" << secondHalf << "Hz";
		QVERIFY2(std::abs(firstHalf - 440.0) < 40.0,
			qPrintable(QStringLiteral("retained region is the 440 Hz tone, got %1").arg(firstHalf)));
		QVERIFY2(std::abs(secondHalf - 440.0) < 40.0,
			qPrintable(QStringLiteral("the discarded 880 Hz half came back: %2 Hz in the second "
				"half of the stretched buffer").arg(secondHalf)));

		const auto on = SampleClipView::waveformGeometry(*clip, *stretched,
			PxPerTick, true, NoScroll);
		QVERIFY2(std::abs(on.width - clip->length()) < 1.0f,
			"toolbar-on waveform must span the clip after trim+stretch");
		QCOMPARE(on.sampleStart, 0.0f);
		QVERIFY2(on.sampleEnd > 0.99f,
			qPrintable(QStringLiteral("stretched buffer must be drawn end to end, got %1")
				.arg(on.sampleEnd)));
	}

	/**
	 * @brief A left trim slides the drawing under the clip's left edge instead
	 * of rescaling it, and a following stretch stops drawing the discarded part.
	 *
	 * A left trim is content-pinned-to-the-timeline: the waveform keeps its
	 * natural width and shifts left, so the skipped audio sits outside the
	 * clip's rectangle rather than being squeezed or rescaled. Once a stretch
	 * materialises the audible range, the skipped quarter is dropped from the
	 * drawing entirely -- the drawn range starts a quarter into the source and
	 * still keeps the same pixels-per-source-frame.
	 */
	void toolbarOffLeftTrimShiftsDrawingWithoutRescaling()
	{
		auto [track, clip] = createClip(makeTwoToneBuffer(framesOf(8.0), engineRate()));
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);
		const auto& source = clip->sample();

		const auto before = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);

		clip->trimFromStart(TimePos(natural / 4));

		const auto shifted = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);

		// Same width, shifted left by a quarter of it: the scale is untouched.
		QVERIFY2(std::abs(shifted.width - before.width) < 1.0f,
			qPrintable(QStringLiteral("left trim must not rescale the waveform: %1 vs %2")
				.arg(shifted.width).arg(before.width)));
		QVERIFY2(std::abs(shifted.x - (before.x - before.width / 4.0f)) < 1.0f,
			qPrintable(QStringLiteral("left trim should slide the drawing left by a quarter: x=%1")
				.arg(shifted.x)));

		// A stretch folds the inaudible quarter away, so it leaves the drawing.
		clip->setPitchMode(SampleClip::PitchMode::Stretch);
		clip->stretchToLength(clip->length());
		waitForStretched();

		QVERIFY2(std::abs(clip->sourceStartFrame() - static_cast<int>(framesOf(2.0))) < 2,
			qPrintable(QStringLiteral("stretch should fold the skipped quarter into the source "
				"start, got %1").arg(clip->sourceStartFrame())));

		const auto folded = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, false, NoScroll);
		QVERIFY2(std::abs(folded.sampleStart - 0.25f) < 0.02f,
			qPrintable(QStringLiteral("discarded quarter must not be drawn, sampleStart=%1")
				.arg(folded.sampleStart)));
		QCOMPARE(folded.sampleEnd, 1.0f);
		QVERIFY2(std::abs(folded.width - before.width * 0.75f) < 1.0f,
			qPrintable(QStringLiteral("drawing should cover only the retained three quarters: "
				"%1 vs %2").arg(folded.width).arg(before.width * 0.75f)));
	}

	/**
	 * @brief Regression: toolbar Stretch toggle must not revert a stretched
	 * waveform when Pitch Mode is Stretch.
	 *
	 * Exact reproduction sequence:
	 *   1. Set Pitch Method to Stretch.
	 *   2. Enable toolbar Stretch edit button.
	 *   3. Stretch the sample clip.
	 *   4. Wait for the stretched buffer to finish generating.
	 *   5. Disable toolbar Stretch edit button.
	 *   6. Lengthen the sample clip using normal editing (trimToLength).
	 *   7. Verify that the waveform still represents the stretched audio.
	 *
	 * The bug was: `waveformBuffer()` returned the original source when the
	 * toolbar was OFF, even though the clip's pitch mode was Stretch with a
	 * valid stretched buffer. Similarly, `waveformPlan()` passed toolbar-only
	 * state to `waveformGeometry()`, so the geometry also reverted to source-
	 * space drawing. After step 5 the waveform suddenly jumped back to its
	 * pre-stretch appearance.
	 */
	void toolbarToggleOffDoesNotRevertStretchedWaveform()
	{
		auto buffer = makeTwoToneBuffer(framesOf(8.0), engineRate());
		auto* view = createClipWithView(buffer);
		SampleClip* clip = dynamic_cast<SampleClip*>(view->model());
		QVERIFY2(clip != nullptr, "view model must be a SampleClip");
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);

		// Step 1: Set Pitch Mode to Stretch.
		clip->setPitchMode(SampleClip::PitchMode::Stretch);

		// Steps 2-3: Enable toolbar Stretch, stretch the clip.
		clip->stretchToLength(TimePos(natural * 2));
		waitForStretched();

		QVERIFY2(clip->stretchedSample() != nullptr,
			"stretch buffer should exist after toolbar-on stretch");
		QVERIFY2(std::abs(clip->stretchRatio() - 2.0) < 0.01,
			qPrintable(QStringLiteral("ratio should be 2, got %1").arg(clip->stretchRatio())));

		// Step 4: captured the stretched buffer and its geometry while toolbar was ON.
		const auto stretchedOn = clip->stretchedSample();
		QVERIFY(stretchedOn != nullptr);

		// Step 5: Disable toolbar Stretch.
		// This is where the bug manifested: waveformBuffer() would return the
		// original source instead of the stretched buffer.
		const auto* bufAfterToggle = view->waveformBuffer();
		QVERIFY2(bufAfterToggle == stretchedOn.get(),
			"waveformBuffer() must still return the stretched buffer after toolbar toggle off");

		// Step 6: Lengthen the clip using normal editing (trimToLength).
		const auto newLength = TimePos(natural * 3);
		clip->trimToLength(newLength);
		waitForStretched();

		// Step 7: Verify the waveform still represents the stretched audio.
		const auto* bufAfterExtend = view->waveformBuffer();
		QVERIFY2(bufAfterExtend != nullptr,
			"waveformBuffer() must not return null after extending clip");
		QVERIFY2(bufAfterExtend->sampleSize() > 0,
			"waveform buffer must have samples after extending");

		// The geometry should be drawn stretched across the full clip width,
		// not reverted to source-space drawing at natural scale.
		const auto drawStretched = true;
		const auto planAfter = SampleClipView::waveformGeometry(*clip, *bufAfterExtend,
			PxPerTick, drawStretched, NoScroll);
		QVERIFY2(std::abs(planAfter.width - static_cast<float>(newLength)) < 1.0f,
			qPrintable(QStringLiteral("waveform must span the extended clip: %1 vs %2")
				.arg(planAfter.width).arg(static_cast<float>(newLength))));

		// Explicitly verify it does NOT revert to source-space geometry:
		const auto& source = clip->sample();
		const auto planSourceSpace = SampleClipView::waveformGeometry(*clip, source,
			PxPerTick, /*stretchMode=*/false, NoScroll);
		QVERIFY2(std::abs(planAfter.width - planSourceSpace.width) > natural * 0.5f,
			qPrintable(QStringLiteral("waveform must not revert to source-space width: "
				"stretched=%1, source-space=%2").arg(planAfter.width).arg(planSourceSpace.width)));

		delete view;
	}

	/**
	 * @brief Regression: repeatedly toggling toolbar Stretch must not cause
	 * the stretched waveform to flicker between original and stretched buffers.
	 *
	 * Each toggle-off must keep the stretched buffer visible when pitch mode
	 * is Stretch, and each toggle-on must do the same.
	 */
	void repeatedToolbarTogglesPreserveStretchedWaveform()
	{
		auto buffer = makeTwoToneBuffer(framesOf(8.0), engineRate());
		auto* view = createClipWithView(buffer);
		SampleClip* clip = dynamic_cast<SampleClip*>(view->model());
		QVERIFY2(clip != nullptr, "view model must be a SampleClip");
		const auto natural = clip->sampleLength();
		clip->changeLength(natural);
		clip->setPitchMode(SampleClip::PitchMode::Stretch);

		clip->stretchToLength(TimePos(natural * 2));
		waitForStretched();

		const auto initialStretched = clip->stretchedSample();
		QVERIFY(initialStretched != nullptr);

		// Toggle toolbar off and on multiple times.
		for (int i = 0; i < 3; ++i)
		{
			// Toolbar OFF: waveformBuffer() must still return the stretched buffer.
			const auto* bufOff = view->waveformBuffer();
			QVERIFY2(bufOff == initialStretched.get(),
				qPrintable(QStringLiteral("toggle-off iteration %1: buffer must be stretched")
					.arg(i)));

			// Toolbar ON: same buffer.
			const auto* bufOn = view->waveformBuffer();
			QVERIFY2(bufOn == initialStretched.get(),
				qPrintable(QStringLiteral("toggle-on iteration %1: buffer must be stretched")
					.arg(i)));
		}

		// Now extend the clip (which triggers a new stretch request).
		clip->trimToLength(TimePos(natural * 3));
		waitForStretched();

		const auto newStretched = clip->stretchedSample();
		QVERIFY(newStretched != nullptr);

		// After the new stretch, both toolbar states must show the NEW buffer.
		const auto* bufAfterExtend = view->waveformBuffer();
		QVERIFY2(bufAfterExtend == newStretched.get(),
			"after extend+stretch, waveformBuffer() must return the new stretched buffer");

		delete view;
	}
};


//! The geometry function itself is widget-free, but it lives in a widget class
//! and the clip/track objects pull in the GUI libraries, so this needs a
//! `QApplication`. Under `ctest` there is usually no display, so fall back to
//! Qt's offscreen platform when there is nothing to draw to.
int main(int argc, char* argv[])
{
	if (qEnvironmentVariableIsEmpty("QT_QPA_PLATFORM")
		&& qEnvironmentVariableIsEmpty("DISPLAY")
		&& qEnvironmentVariableIsEmpty("WAYLAND_DISPLAY"))
	{
		qputenv("QT_QPA_PLATFORM", "offscreen");
	}

	QApplication app(argc, argv);
	SampleClipViewWaveformTest test;
	return QTest::qExec(&test, argc, argv);
}

#include "SampleClipViewWaveformTest.moc"
