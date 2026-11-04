/*
 * SampleClipContextMenuTest.cpp - end-to-end regression test for the exact
 * control reported as broken:
 *
 *   right-click a sample clip -> "Pitch mode" -> "Stretch"
 *
 * Unlike every other test in this suite, nothing here calls
 * SampleClip::setPitchMode() directly, and nothing here builds a menu by hand.
 * The test delivers a real QContextMenuEvent to a real SampleClipView, so
 * ClipView::contextMenuEvent() runs and QMenu::exec() pops up the menu the user
 * would see; the test then finds the "Stretch" QAction inside that live popup
 * and triggers it -- the same object a mouse click activates. The resize is
 * produced by sending real mouse events to the real clip widget, so
 * ClipView::mousePressEvent/mouseMoveEvent run exactly as they do under the
 * GUI. Playback then goes through the same computePlaybackPlan() ->
 * SamplePlayHandle::play() path the audio engine consumes. If selecting
 * "Stretch" from that menu ever stops affecting what you hear, this test fails
 * at the link responsible.
 *
 * The contract under test, stated in seconds because the test converts
 * seconds <-> ticks through Engine::framesPerTick() and therefore holds at any
 * project tempo:
 *   8 s @ 440 Hz stretched to 16 s:
 *       Resample -> 16 s @ 220 Hz   (pitch follows speed)
 *       Stretch  -> 16 s @ 440 Hz   (pitch preserved)
 *   8 s @ 440 Hz stretched to  4 s:
 *       Resample ->  4 s @ 880 Hz
 *       Stretch  ->  4 s @ 440 Hz
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
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#include <algorithm>
#include <cmath>
#include <functional>
#include <memory>
#include <vector>

#include <QtTest>

#include <QApplication>
#include <QContextMenuEvent>
#include <QDialog>
#include <QMenu>
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

namespace
{

//! Horizontal zoom used by every case. Combined with the default 192
//! ticks/bar this gives exactly half a pixel per tick, so `pixelsForTicks`
//! round-trips without any rounding loss and the drag lands where the test
//! intends. It says nothing about tempo: seconds are converted to ticks with
//! `Engine::framesPerTick()`, which reads the project tempo as configured.
constexpr int PixelsPerBar = 96;

sample_rate_t engineRate() { return Engine::audioEngine()->outputSampleRate(); }

//! @brief Timeline ticks spanning @a seconds at the project tempo.
TimePos ticksForSeconds(double seconds)
{
	return TimePos(static_cast<int>(std::lround(
		seconds * Engine::audioEngine()->outputSampleRate() / Engine::framesPerTick())));
}

//! @brief Pixels spanning @a ticks at the zoom the tests install.
int pixelsForTicks(TimePos ticks)
{
	return static_cast<int>(std::lround(
		double(ticks) * PixelsPerBar / TimePos::ticksPerBar()));
}

//! @brief An 8-second stereo buffer: left = 440 Hz, right = 880 Hz.
std::shared_ptr<const SampleBuffer> makeSineBuffer(size_t frames, int rate)
{
	std::vector<SampleFrame> data;
	data.reserve(frames);
	for (size_t i = 0; i < frames; ++i)
	{
		const auto t = static_cast<double>(i) / rate;
		data.emplace_back(
			static_cast<sample_t>(std::sin(2.0 * M_PI * 440.0 * t)),
			static_cast<sample_t>(std::sin(2.0 * M_PI * 880.0 * t)));
	}
	return std::make_shared<const SampleBuffer>(std::move(data), rate);
}

/**
 * @brief Zero-crossing frequency of one channel over a run of frames.
 *
 * Good enough to tell 220/440/880 Hz apart, which is the whole question here.
 */
double dominantFrequency(const std::vector<SampleFrame>& data, int rate, int channel)
{
	if (data.size() < 2) { return 0.0; }
	int crossings = 0;
	sample_t prev = channel == 0 ? data[0].left() : data[0].right();
	for (size_t i = 1; i < data.size(); ++i)
	{
		const auto cur = channel == 0 ? data[i].left() : data[i].right();
		if (prev < 0.0f && cur >= 0.0f) { ++crossings; }
		prev = cur;
	}
	return crossings / static_cast<double>(data.size()) * rate;
}

/**
 * @brief Block until every stretch job has been computed and delivered.
 *
 * waitUntilIdle() only guarantees the worker finished; delivery is a queued
 * invocation on the GUI thread, so the event loop has to run for the clip's
 * slot to commit the buffer.
 */
void waitForStretched()
{
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
}

/**
 * @brief Render a clip through the real SamplePlayHandle exactly as the audio
 * engine consumes it: plan -> handle -> play() per period.
 */
std::vector<SampleFrame> renderClip(SampleClip* clip)
{
	const auto plan = clip->computePlaybackPlan(
		clip->outputFramesFor(clip->startPosition() + clip->startTimeOffset()));
	SamplePlayHandle handle(clip, plan);

	const auto fpp = Engine::audioEngine()->framesPerPeriod();
	std::vector<SampleFrame> out;
	out.reserve(static_cast<size_t>(handle.totalFrames()) + fpp);
	std::vector<SampleFrame> buf(fpp);
	auto guardPeriods = 100000;
	while (!handle.isFinished() && guardPeriods-- > 0)
	{
		std::fill(buf.begin(), buf.end(), SampleFrame{});
		handle.play(buf.data());
		out.insert(out.end(), buf.begin(), buf.end());
	}
	if (static_cast<size_t>(handle.totalFrames()) < out.size())
	{
		out.resize(static_cast<size_t>(handle.totalFrames()));
	}
	return out;
}

/**
 * @brief Find an action by text in a menu, searching submenus recursively.
 */
QAction* findAction(QMenu* menu, const QString& text)
{
	for (auto* action : menu->actions())
	{
		if (action->text() == text) { return action; }
		if (auto* sub = action->menu())
		{
			if (auto* found = findAction(sub, text)) { return found; }
		}
	}
	return nullptr;
}

/**
 * @brief What the menu on screen says about one item.
 *
 * The menu `ClipView::contextMenuEvent()` shows is a stack object that dies
 * when `exec()` returns, so anything the test wants to know about it has to be
 * read while it is up and copied out.
 */
struct MenuItemFacts
{
	bool found = false;
	bool enabled = false;
	bool checkable = false;
	bool checked = false;
};

} // namespace


class SampleClipContextMenuTest : public QObject
{
	Q_OBJECT

private:
	SampleTrack* m_track = nullptr;
	SampleClip* m_clip = nullptr;
	SampleClipView* m_view = nullptr;
	TrackView* m_trackView = nullptr;
	QString m_pickedFromMenu;
	bool m_menuHandled = false;
	int m_menuTicks = 0;

	/**
	 * @brief Build a fresh 8 s clip with a real widget on a real track row.
	 *
	 * The track view is created by the song editor's queued
	 * `trackAdded -> createTrackView` connection, so this waits for it --
	 * the same way the real GUI creates rows.
	 */
	void createClipWithView()
	{
		auto* editor = getGUI()->songEditor()->m_editor;
		QVERIFY(editor != nullptr);
		editor->setPixelsPerBar(PixelsPerBar);

		m_track = new SampleTrack(Engine::getSong());
		m_clip = new SampleClip(m_track);
		m_clip->setSampleBuffer(makeSineBuffer(static_cast<size_t>(8 * 44100), 44100));
		m_clip->movePosition(0);

		for (auto i = 0; i < 200 && m_trackView == nullptr; ++i)
		{
			QTest::qWait(25);
			for (auto* tv : editor->trackViews())
			{
				if (tv->getTrack() == m_track) { m_trackView = tv; }
			}
		}
		QVERIFY(m_trackView != nullptr);

		m_view = new SampleClipView(m_clip, m_trackView);
		QVERIFY(m_view != nullptr);
		m_view->show();
		QTest::qWait(50);

		// The widget sizes itself from the model; make sure it agrees with
		// the 8 s clip before any drag is measured against it.
		QVERIFY2(std::abs(m_view->width() - pixelsForTicks(m_clip->length())) <= 2,
			qPrintable(QStringLiteral("view width %1, expected ~%2 for a %3-tick clip")
				.arg(m_view->width()).arg(pixelsForTicks(m_clip->length())).arg(int(m_clip->length()))));
	}

	/**
	 * @brief Tear the clip, its widget and its row down again.
	 *
	 * `deleteTrackView` is the GUI's own "delete this track" path: it drops
	 * the row from the editor, destroys it -- which destroys the clip views
	 * parented inside it -- and then destroys the model, whose destructor
	 * destroys the clips. Doing it by hand instead (closing the view, then
	 * deleting the track) leaves the row queued for deletion while its model
	 * is already gone, which crashes in the next event loop.
	 */
	void destroyClipWithView()
	{
		SampleStretchManager::instance().waitUntilIdle();
		auto* editor = getGUI()->songEditor()->m_editor;
		if (m_trackView != nullptr && editor != nullptr)
		{
			editor->deleteTrackView(m_trackView);
		}
		m_view = nullptr;
		m_trackView = nullptr;
		m_clip = nullptr;
		m_track = nullptr;
		QCoreApplication::processEvents();
	}

	/**
	 * @brief Right-click the clip and hand the menu it pops up to @a visit.
	 *
	 * A real QContextMenuEvent is delivered to the real widget, so
	 * ClipView::contextMenuEvent() runs end to end: it gathers the clicked
	 * clips, builds the QMenu -- which calls the shipped
	 * SampleClipView::constructContextMenu() that installs the "Pitch mode"
	 * submenu -- and hands it to QMenu::exec(). Nothing here constructs a menu
	 * itself; the QMenu the callback receives is the one on screen.
	 *
	 * exec() blocks in a nested event loop, so the callback runs from a timer
	 * that keeps firing inside that loop. Returning true from @a visit counts as
	 * handled and stops the timer; a callback that triggers an item dismisses
	 * the menu as a side effect, which is what lets exec() return. The timer is
	 * armed before the event is sent, because control does not return to the
	 * caller until the menu is gone.
	 *
	 * The popup is looked up among the clip view's own children rather than
	 * among the process's top-level widgets, because `contextMenuEvent` builds
	 * it as `QMenu contextMenu(this)` -- parented to the view -- and depending
	 * on the window manager's focus state `activePopupWidget()` is not
	 * guaranteed to report it. The attempt count is bounded, so a regression
	 * that removes the menu, or the item, fails the test instead of hanging it.
	 *
	 * @return true if @a visit handled an item off the menu that was shown.
	 */
	bool visitContextMenu(const std::function<bool(QMenu*)>& visit)
	{
		m_menuTicks = 0;
		m_menuHandled = false;
		auto* picker = new QTimer(this);
		picker->setInterval(50);
		QObject::connect(picker, &QTimer::timeout, this, [this, picker, visit]() {
			QMenu* popup = nullptr;
			for (auto* menu : m_view->findChildren<QMenu*>())
			{
				if (menu->isVisible()) { popup = menu; break; }
			}
			if (popup == nullptr)
			{
				// Nothing is on screen: either exec() has not opened it yet,
				// or it has already returned and the loop is the test's own.
				if (++m_menuTicks >= 40) { picker->stop(); }
				return;
			}
			if (visit(popup))
			{
				m_menuHandled = true;
				picker->stop();
				// Best effort: if the callback read the menu without triggering
				// anything, this is what gets the modal loop out of the way.
				if (popup->isVisible()) { popup->close(); }
				return;
			}
			if (++m_menuTicks >= 40) { popup->close(); }
		});
		picker->start();

		const QPoint at(m_view->width() / 2, m_view->height() / 2);
		QContextMenuEvent event(QContextMenuEvent::Mouse, at, m_view->mapToGlobal(at));
		QApplication::sendEvent(m_view, &event);

		picker->stop();
		picker->deleteLater();
		QCoreApplication::processEvents();
		return m_menuHandled;
	}

	/**
	 * @brief The user's gesture part 1: right-click the clip and pick
	 * "Pitch mode" -> @a modeText out of the menu that pops up.
	 */
	void triggerPitchModeAction(const QString& modeText)
	{
		m_pickedFromMenu.clear();
		const auto sawMenu = visitContextMenu([this, modeText](QMenu* popup) {
			auto* action = findAction(popup, modeText);
			if (action == nullptr) { return false; }
			m_pickedFromMenu = QStringLiteral("%1|%2|%3").arg(action->text())
				.arg(action->isEnabled() ? "enabled" : "disabled")
				.arg(action->isCheckable() ? "checkable" : "not checkable");
			action->trigger();
			return true;
		});

		QVERIFY2(sawMenu,
			qPrintable(QStringLiteral("right-clicking the clip never produced a menu "
				"with a \"%1\" item").arg(modeText)));
		// The user must be able to select it at all, and it must present as a
		// mode (a checkable item), which is what makes "toggle between Resample
		// and Stretch" the description of this control.
		QVERIFY2(m_pickedFromMenu.contains("|enabled|"),
			qPrintable(QStringLiteral("\"%1\" was greyed out in the menu the user "
				"was shown: %2").arg(modeText, m_pickedFromMenu)));
		QVERIFY2(m_pickedFromMenu.contains("checkable"),
			qPrintable(QStringLiteral("\"%1\" is not a checkable mode item: %2")
				.arg(modeText, m_pickedFromMenu)));
	}

	/**
	 * @brief The user's gesture part 2: drag the clip's right edge to
	 * @a targetLength.
	 *
	 * Real QMouseEvents go to the real widget, so ClipView::mousePressEvent
	 * classifies the press from the grip geometry and mouseMoveEvent converts
	 * pixels to ticks and applies the edit -- the whole resize handler runs.
	 *
	 * Alt is held so the length is unquantized and lands exactly on the target
	 * (Ctrl would start a copy-drag instead). The press happens on the last
	 * pixel of the widget, which is inside the resize grip at any zoom, and the
	 * release x *is* the new length: mouseMoveEvent computes it as
	 * `pos.x() * ticksPerBar / pixelsPerBar`, i.e. in absolute widget
	 * coordinates rather than as a delta from the press point.
	 */
	void dragRightEdgeTo(TimePos targetLength)
	{
		const QPoint press(m_view->width() - 1, m_view->height() / 2);
		const QPoint release(pixelsForTicks(targetLength), m_view->height() / 2);

		// The gesture is dispatched as real QMouseEvents straight to the clip
		// view, which is what a drag on screen delivers. QTest's own helpers
		// were tried first and are unusable here: `mouseMove` has no modifier
		// parameter at all (its third argument is `int delay`, so
		// `mouseMove(w, pos, Qt::AltModifier)` compiles and sleeps for
		// 0x08000000 ms instead of dragging), and its `mouseEvent` variant
		// silently drops the move.
		auto send = [this](QEvent::Type type, Qt::MouseButton button,
				Qt::MouseButtons buttons, Qt::KeyboardModifiers mods, const QPoint& at) {
			QMouseEvent event(type, at, m_view->mapToGlobal(at), button, buttons, mods);
			QApplication::sendEvent(m_view, &event);
			QCoreApplication::processEvents();
		};

		send(QEvent::MouseButtonPress, Qt::LeftButton, Qt::LeftButton, Qt::AltModifier, press);
		send(QEvent::MouseMove, Qt::NoButton, Qt::LeftButton, Qt::AltModifier, release);
		send(QEvent::MouseMove, Qt::NoButton, Qt::LeftButton, Qt::AltModifier, release);
		send(QEvent::MouseButtonRelease, Qt::LeftButton, Qt::NoButton, Qt::NoModifier, release);
		QCoreApplication::processEvents();
	}

private slots:
	void initTestCase()
	{
		// This test is only meaningful on a platform that maps windows: the
		// right-click has to produce a popup that is really on screen, and a
		// drag has to be delivered to a mapped widget. The offscreen plugin
		// neither maps windows nor survives this widget set, so the test
		// reports itself skipped rather than passing for the wrong reason or
		// hanging. `main()` falls back to offscreen when there is no display at
		// all, which is what makes this guard the single place the decision is
		// made.
		const auto platform = QGuiApplication::platformName();
		if (platform != QLatin1String("xcb") && platform != QLatin1String("wayland"))
		{
			const auto why = QStringLiteral("needs a real display (xcb or wayland); this "
				"run is on \"%1\" because no DISPLAY/WAYLAND_DISPLAY is set").arg(platform);
			QSKIP(why.toUtf8().constData());
		}

		// `main.cpp` calls `loadConfigFile()`; a test binary does not, so the
		// in-memory config starts empty. `MainWindow`'s constructor reads two
		// keys out of it and opens a *modal* dialog on each -- the first-run
		// `SetupDialog` when `app/configured` is unset, and an audio-failure
		// box when `audioengine/audiodev` names no usable device. A nested
		// modal loop would block the test forever, so both are settled here.
		// Nothing else in the config affects the path under test.
		ConfigManager::inst()->setValue("app", "configured", "1");
		ConfigManager::inst()->setValue("audioengine", "audiodev", AudioDummy::name());

		// Belt and braces: a modal dialog runs a nested event loop, so this
		// timer keeps firing while one is up. If a future change introduces a
		// new startup prompt the test reports and dismisses it instead of
		// hanging.
		QTimer guard;
		QObject::connect(&guard, &QTimer::timeout, [&guard]() {
			for (auto* widget : QApplication::topLevelWidgets())
			{
				auto* dialog = qobject_cast<QDialog*>(widget);
				if (dialog != nullptr && dialog->isModal() && dialog->isVisible())
				{
					qInfo() << "dismissing unexpected modal dialog:" << dialog->windowTitle();
					dialog->reject();
				}
			}
		});
		guard.start(50);

		// The real GUI stack: MainWindow, SongEditor, everything ClipView and
		// SampleClipView touch during a real right-click and a real drag.
		new GuiApplication();

		guard.stop();

		QVERIFY(getGUI() != nullptr);
		QVERIFY(getGUI()->mainWindow() != nullptr);
		QVERIFY(getGUI()->songEditor() != nullptr);
		QVERIFY(getGUI()->songEditor()->m_editor != nullptr);

		// A user drags a clip they can see. Qt does not deliver mouse events
		// to a widget whose window has never been mapped, so the editor has to
		// be on screen before any gesture is synthesised.
		getGUI()->mainWindow()->show();
		QVERIFY2(QTest::qWaitForWindowExposed(getGUI()->mainWindow()),
			"the song editor window never became visible");
	}

	void cleanupTestCase()
	{
		SampleStretchManager::instance().waitUntilIdle();
	}

	void init() { createClipWithView(); }
	void cleanup() { destroyClipWithView(); }

	/**
	 * @brief Sanity: a fresh clip is 8 s of 440 Hz (left channel), in Resample
	 * mode, and its widget is on screen at the right width.
	 */
	void freshClipIsEightSecondsAt440()
	{
		QCOMPARE(m_clip->pitchMode(), SampleClip::PitchMode::Resample);
		QVERIFY(std::abs(m_clip->length() - ticksForSeconds(8.0)) <= 1);

		const auto rendered = renderClip(m_clip);
		const auto seconds = double(rendered.size()) / engineRate();
		const auto hz = dominantFrequency(rendered, engineRate(), 0);
		qInfo() << "  fresh clip:" << seconds << "s @" << hz << "Hz";
		QVERIFY2(std::abs(seconds - 8.0) < 0.2,
			qPrintable(QStringLiteral("expected ~8 s, got %1").arg(seconds)));
		QVERIFY2(std::abs(hz - 440.0) < 20.0,
			qPrintable(QStringLiteral("expected ~440 Hz, got %1").arg(hz)));
	}

	/**
	 * @brief The menu itself: right-clicking a fresh clip shows a "Pitch mode"
	 * submenu offering checkable Resample/Stretch, with Stretch enabled in this
	 * build and the checks showing Resample as the current mode.
	 *
	 * The facts are read off the QMenu that is actually on screen, from inside
	 * `QMenu::exec()`, rather than off a menu the test assembled itself.
	 */
	void contextMenuOffersPitchModes()
	{
		struct Observed
		{
			bool submenu = false;
			MenuItemFacts resample;
			MenuItemFacts stretch;
		} seen;

		const auto sawMenu = visitContextMenu([this, &seen](QMenu* popup) {
			auto* pitchMode = findAction(popup, tr("Pitch mode"));
			if (pitchMode == nullptr || pitchMode->menu() == nullptr) { return false; }
			seen.submenu = true;
			auto fill = [pitchMode](const QString& text, MenuItemFacts& out) {
				auto* action = findAction(pitchMode->menu(), text);
				if (action == nullptr) { return; }
				out.found = true;
				out.enabled = action->isEnabled();
				out.checkable = action->isCheckable();
				out.checked = action->isChecked();
			};
			fill(tr("Resample"), seen.resample);
			fill(tr("Stretch"), seen.stretch);
			return true;
		});

		QVERIFY2(sawMenu, "right-clicking the clip never showed a menu with a "
			"\"Pitch mode\" submenu");
		QVERIFY2(seen.submenu, "the clip menu has no \"Pitch mode\" submenu");
		QVERIFY2(seen.resample.found, "\"Pitch mode\" has no \"Resample\" item");
		QVERIFY2(seen.stretch.found, "\"Pitch mode\" has no \"Stretch\" item");
		QVERIFY2(seen.resample.enabled, "\"Resample\" is greyed out");
		QVERIFY2(seen.stretch.enabled,
			"Stretch must be selectable -- this build has SoundTouch");
		QVERIFY2(seen.resample.checkable, "\"Resample\" is not checkable");
		QVERIFY2(seen.stretch.checkable, "\"Stretch\" is not checkable");
		QCOMPARE(seen.resample.checked, true);
		QCOMPARE(seen.stretch.checked, false);
	}

	/**
	 * @brief Selecting the menu item changes the clip's pitch mode -- the first
	 * half of the complaint ("selecting Stretch does nothing").
	 */
	void menuActionSetsPitchMode()
	{
		triggerPitchModeAction(tr("Stretch"));
		QCOMPARE(m_clip->pitchMode(), SampleClip::PitchMode::Stretch);

		triggerPitchModeAction(tr("Resample"));
		QCOMPARE(m_clip->pitchMode(), SampleClip::PitchMode::Resample);
	}

	/**
	 * @brief CONTRACT: menu -> Stretch, then drag the right edge to 16 s:
	 * the clip plays 16 s at 440 Hz.
	 */
	void stretchTo16sKeepsPitch()
	{
		triggerPitchModeAction(tr("Stretch"));
		dragRightEdgeTo(ticksForSeconds(16.0));

		QVERIFY2(std::abs(m_clip->length() - ticksForSeconds(16.0)) <= ticksForSeconds(0.1),
			qPrintable(QStringLiteral("clip length %1 ticks, expected ~%2")
				.arg(int(m_clip->length())).arg(int(ticksForSeconds(16.0)))));
		QVERIFY2(std::abs(m_clip->stretchRatio() - 2.0) < 0.05,
			qPrintable(QStringLiteral("stretch ratio %1, expected ~2")
				.arg(m_clip->stretchRatio())));

		waitForStretched();
		QVERIFY2(m_clip->hasStretchedSample(),
			"the pitch-preserving buffer never arrived for the menu-selected "
			"Stretch mode, so playback stays on the resample fallback");

		const auto rendered = renderClip(m_clip);
		const auto seconds = double(rendered.size()) / engineRate();
		const auto hz = dominantFrequency(rendered, engineRate(), 0);
		qInfo() << "  menu Stretch -> 16 s:" << seconds << "s @" << hz << "Hz";
		QVERIFY2(std::abs(seconds - 16.0) < 0.4,
			qPrintable(QStringLiteral("expected ~16 s, got %1").arg(seconds)));
		QVERIFY2(std::abs(hz - 440.0) < 30.0,
			qPrintable(QStringLiteral("Stretch must preserve pitch: expected "
				"~440 Hz, got %1").arg(hz)));
	}

	/**
	 * @brief CONTRACT: leave the mode at Resample, drag to 16 s: 16 s at 220 Hz.
	 * Proves the drag alone changes duration and that the menu mode is what
	 * decides pitch.
	 */
	void resampleTo16sShiftsPitch()
	{
		dragRightEdgeTo(ticksForSeconds(16.0));

		QVERIFY2(std::abs(m_clip->length() - ticksForSeconds(16.0)) <= ticksForSeconds(0.1),
			qPrintable(QStringLiteral("clip length %1 ticks, expected ~%2")
				.arg(int(m_clip->length())).arg(int(ticksForSeconds(16.0)))));

		const auto rendered = renderClip(m_clip);
		const auto seconds = double(rendered.size()) / engineRate();
		const auto hz = dominantFrequency(rendered, engineRate(), 0);
		qInfo() << "  Resample -> 16 s:" << seconds << "s @" << hz << "Hz";
		QVERIFY2(std::abs(seconds - 16.0) < 0.4,
			qPrintable(QStringLiteral("expected ~16 s, got %1").arg(seconds)));
		QVERIFY2(std::abs(hz - 220.0) < 20.0,
			qPrintable(QStringLiteral("Resample must shift pitch: expected "
				"~220 Hz, got %1").arg(hz)));
	}

	/**
	 * @brief CONTRACT: menu -> Stretch, drag the edge inward to 4 s:
	 * 4 s at 440 Hz.
	 */
	void stretchTo4sKeepsPitch()
	{
		triggerPitchModeAction(tr("Stretch"));
		dragRightEdgeTo(ticksForSeconds(4.0));

		QVERIFY2(std::abs(m_clip->length() - ticksForSeconds(4.0)) <= ticksForSeconds(0.1),
			qPrintable(QStringLiteral("clip length %1 ticks, expected ~%2")
				.arg(int(m_clip->length())).arg(int(ticksForSeconds(4.0)))));

		waitForStretched();
		QVERIFY(m_clip->hasStretchedSample());

		const auto rendered = renderClip(m_clip);
		const auto seconds = double(rendered.size()) / engineRate();
		const auto hz = dominantFrequency(rendered, engineRate(), 0);
		qInfo() << "  menu Stretch -> 4 s:" << seconds << "s @" << hz << "Hz";
		QVERIFY2(std::abs(seconds - 4.0) < 0.2,
			qPrintable(QStringLiteral("expected ~4 s, got %1").arg(seconds)));
		QVERIFY2(std::abs(hz - 440.0) < 30.0,
			qPrintable(QStringLiteral("Stretch must preserve pitch when "
				"shortening: expected ~440 Hz, got %1").arg(hz)));
	}

	/**
	 * @brief CONTRACT: Resample, drag to 4 s: 4 s at 880 Hz.
	 */
	void resampleTo4sShiftsPitch()
	{
		dragRightEdgeTo(ticksForSeconds(4.0));

		const auto rendered = renderClip(m_clip);
		const auto seconds = double(rendered.size()) / engineRate();
		const auto hz = dominantFrequency(rendered, engineRate(), 0);
		qInfo() << "  Resample -> 4 s:" << seconds << "s @" << hz << "Hz";
		QVERIFY2(std::abs(seconds - 4.0) < 0.2,
			qPrintable(QStringLiteral("expected ~4 s, got %1").arg(seconds)));
		QVERIFY2(std::abs(hz - 880.0) < 40.0,
			qPrintable(QStringLiteral("Resample must shift pitch: expected "
				"~880 Hz, got %1").arg(hz)));
	}

	/**
	 * @brief The full user story in one timeline: stretch to 16 s while the
	 * mode is still Resample (220 Hz), then select Stretch from the menu
	 * *without touching the length* -- and the very next playback is 440 Hz.
	 *
	 * This is precisely "selecting Stretch from the right-click menu changes
	 * what I hear", with no other input involved.
	 */
	void selectingStretchFromMenuChangesWhatIsHeard()
	{
		// 1. Drag to 16 s while still in Resample mode.
		dragRightEdgeTo(ticksForSeconds(16.0));
		QCOMPARE(m_clip->pitchMode(), SampleClip::PitchMode::Resample);

		const auto before = renderClip(m_clip);
		const auto hzBefore = dominantFrequency(before, engineRate(), 0);
		qInfo() << "  before the menu choice:" << double(before.size()) / engineRate()
			<< "s @" << hzBefore << "Hz";
		QVERIFY2(std::abs(hzBefore - 220.0) < 20.0,
			qPrintable(QStringLiteral("expected ~220 Hz before selecting "
				"Stretch, got %1").arg(hzBefore)));

		// 2. Right-click -> Pitch mode -> Stretch. Nothing else.
		triggerPitchModeAction(tr("Stretch"));
		QCOMPARE(m_clip->pitchMode(), SampleClip::PitchMode::Stretch);
		QVERIFY2(std::abs(m_clip->length() - ticksForSeconds(16.0)) <= ticksForSeconds(0.1),
			"the menu action must not change the clip's length");

		// 3. The async pitch-preserving buffer arrives.
		waitForStretched();
		QVERIFY2(m_clip->hasStretchedSample(),
			"selecting Stretch from the menu never produced a stretched "
			"buffer -- this is where the GUI path breaks");

		// 4. The next playback is 16 s at 440 Hz.
		const auto after = renderClip(m_clip);
		const auto secondsAfter = double(after.size()) / engineRate();
		const auto hzAfter = dominantFrequency(after, engineRate(), 0);
		qInfo() << "  after the menu choice:" << secondsAfter << "s @" << hzAfter << "Hz";
		QVERIFY2(std::abs(secondsAfter - 16.0) < 0.4,
			qPrintable(QStringLiteral("expected ~16 s, got %1").arg(secondsAfter)));
		QVERIFY2(std::abs(hzAfter - 440.0) < 30.0,
			qPrintable(QStringLiteral("selecting Stretch from the menu must "
				"preserve pitch: expected ~440 Hz, got %1").arg(hzAfter)));
	}
};


//! The full LMMS GUI is instantiated, so a display is required. The offscreen
//! Qt platform is deliberately avoided: it blocks inside the style/polish pass
//! of this widget set, so the xcb platform on the session display is the only
//! faithful (and only working) choice. With no display at all the test falls
//! back to offscreen purely so a QApplication can exist, and `initTestCase`
//! then reports it skipped -- see the guard there.
int main(int argc, char* argv[])
{
	if (qEnvironmentVariableIsEmpty("DISPLAY") && qEnvironmentVariableIsEmpty("WAYLAND_DISPLAY"))
	{
		qputenv("QT_QPA_PLATFORM", "offscreen");
	}

	QApplication app(argc, argv);

	SampleClipContextMenuTest test;
	return QTest::qExec(&test, argc, argv);
}

#include "SampleClipContextMenuTest.moc"
