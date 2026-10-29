/*
 * TrackRowInteractionFilterTest.cpp - tests for the widget layer of the
 * "last-interacted Sample Track" rule: the event filter that turns a mouse
 * press anywhere in a track's row into one notification to the model.
 *
 * The model side of that rule is covered by RecordingWorkflowTest.cpp.  This
 * file covers the half that RecordingWorkflowTest cannot reach, namely whether
 * a press on a widget inside a row is reported at all -- on the row itself, on
 * a widget nested in the row, on a widget created after the row was built, and
 * on a widget that swallows the press instead of propagating it.  Those are the
 * properties the real track row depends on, because its clips, mute/solo
 * buttons, knobs and operations menu never propagate their presses upwards.
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

#include <QtTest>

#include <QApplication>
#include <QEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>

#include "TrackRowInteractionFilter.h"

using namespace lmms::gui;


namespace
{

//! A press delivered the way Qt delivers a real click: through
//! `QApplication::notify()`, which is what runs event filters.  Sending the
//! event to a widget also runs the widget's own `mousePressEvent()`, so this
//! exercises the same path a user click does.
void click(QWidget* widget)
{
	QMouseEvent press(QEvent::MouseButtonPress, QPointF(2, 2), QPointF(2, 2),
		QPointF(2, 2), Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
	QApplication::sendEvent(widget, &press);
}

} // namespace


class TrackRowInteractionFilterTest : public QObject
{
	Q_OBJECT

private:
	//! The row under test, plus a counter standing in for the model.
	QWidget* m_view = nullptr;
	int m_interactions = 0;
	TrackRowInteractionFilter* m_filter = nullptr;

private slots:

	void init()
	{
		m_interactions = 0;
		m_view = new QWidget;
		m_filter = new TrackRowInteractionFilter([this] { ++m_interactions; });
		m_filter->cover(m_view);
	}

	void cleanup()
	{
		// `m_view` is already gone in `destroyingRowIsSafe`, which is the point.
		delete m_view;
		m_view = nullptr;
		delete m_filter;
		m_filter = nullptr;
	}


	// ------------------------------------------------------------------
	// (a) A press on the row itself is reported once.
	// ------------------------------------------------------------------
	void pressOnRowIsReported()
	{
		click(m_view);

		QCOMPARE(m_interactions, 1);
	}


	// ------------------------------------------------------------------
	// (b) A press on a widget nested in the row is reported too.
	//
	// The row's own widgets live inside a settings strip rather than directly
	// in the row, so covering the whole subtree is what makes them count.
	// ------------------------------------------------------------------
	void pressOnNestedWidgetIsReported()
	{
		auto* strip = new QWidget(m_view);
		auto* knob = new QPushButton(strip);

		click(knob);

		QCOMPARE(m_interactions, 1);
	}


	// ------------------------------------------------------------------
	// (c) A widget that consumes the press still counts.
	//
	// A button handles its own press and does not pass it on to the row, which
	// is exactly why the row cannot rely on `mousePressEvent()` alone.
	// ------------------------------------------------------------------
	void pressOnSelfContainedButtonStillCounts()
	{
		auto* button = new QPushButton(m_view);
		QSignalSpy pressedSpy(button, &QPushButton::pressed);

		click(button);

		QCOMPARE(m_interactions, 1);
		// The button still behaves normally: the filter does not eat the press.
		QCOMPARE(pressedSpy.count(), 1);
		QVERIFY(button->isDown());
	}


	// ------------------------------------------------------------------
	// (d) A widget built after the row is covered still counts.
	//
	// A Sample Track's label button, mixer spin box and knobs are created by
	// the subclass constructor, after the base row has installed its filter.
	// ------------------------------------------------------------------
	void widgetCreatedLaterIsReported()
	{
		auto* lateButton = new QPushButton(m_view);

		click(lateButton);

		QCOMPARE(m_interactions, 1);
	}


	// ------------------------------------------------------------------
	// (e) A whole subtree added late is covered, not just its root.
	// ------------------------------------------------------------------
	void subtreeCreatedLaterIsReported()
	{
		auto* strip = new QWidget(m_view);
		auto* deepButton = new QPushButton(strip);

		click(deepButton);

		QCOMPARE(m_interactions, 1);
	}


	// ------------------------------------------------------------------
	// (f) Presses outside the row are not reported.
	//
	// Clicking a different track must retarget, and clicking something that is
	// not a track row at all must leave the target alone.
	// ------------------------------------------------------------------
	void pressElsewhereIsNotReported()
	{
		auto* otherView = new QWidget;
		auto* otherButton = new QPushButton(otherView);

		click(otherButton);

		QCOMPARE(m_interactions, 0);
		delete otherView;
	}


	// ------------------------------------------------------------------
	// (g) Only presses count: hovering, painting and focus changes are not
	// interactions with the track.
	// ------------------------------------------------------------------
	void otherEventsAreNotInteractions()
	{
		auto* button = new QPushButton(m_view);

		QEvent hover(QEvent::HoverEnter);
		QApplication::sendEvent(button, &hover);
		QEvent focusIn(QEvent::FocusIn);
		QApplication::sendEvent(button, &focusIn);
		QEvent showEvent(QEvent::Show);
		QApplication::sendEvent(button, &showEvent);

		QCOMPARE(m_interactions, 0);
	}


	// ------------------------------------------------------------------
	// (h) Releasing a button is not a second interaction.
	//
	// Press-drag-release on a row must retarget once, not three times.
	// ------------------------------------------------------------------
	void releaseIsNotAnInteraction()
	{
		auto* button = new QPushButton(m_view);

		click(button);
		QMouseEvent release(QEvent::MouseButtonRelease, QPointF(2, 2), QPointF(2, 2),
			QPointF(2, 2), Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
		QApplication::sendEvent(button, &release);

		QCOMPARE(m_interactions, 1);
	}


	// ------------------------------------------------------------------
	// (i) The filter never consumes the event, so a press that both the filter
	// and the widget care about is delivered to both.
	// ------------------------------------------------------------------
	void pressStillReachesTheWidget()
	{
		auto* button = new QPushButton(m_view);
		QSignalSpy pressedSpy(button, &QPushButton::pressed);

		click(button);
		click(button);

		QCOMPARE(m_interactions, 2);
		QCOMPARE(pressedSpy.count(), 2);
	}


	// ------------------------------------------------------------------
	// (j) Each row reports only its own presses, so two rows never fight over
	// the target and the last one pressed wins.
	// ------------------------------------------------------------------
	void twoRowsReportIndependently()
	{
		auto* firstView = new QWidget;
		auto* secondView = new QWidget;
		int firstHits = 0;
		int secondHits = 0;
		TrackRowInteractionFilter firstFilter([&] { ++firstHits; });
		TrackRowInteractionFilter secondFilter([&] { ++secondHits; });
		firstFilter.cover(firstView);
		secondFilter.cover(secondView);

		auto* firstButton = new QPushButton(firstView);
		auto* secondButton = new QPushButton(secondView);

		click(firstButton);
		QCOMPARE(firstHits, 1);
		QCOMPARE(secondHits, 0);

		click(secondButton);
		QCOMPARE(firstHits, 1);
		QCOMPARE(secondHits, 1);

		delete firstView;
		delete secondView;
	}


	// ------------------------------------------------------------------
	// (k) A widget reparented out of the row stops reporting to it.
	//
	// Covers the case of a clip view being moved to another track's row: the
	// old row must not keep claiming presses on it.
	// ------------------------------------------------------------------
	void reparentedWidgetStopsReporting()
	{
		auto* strip = new QWidget(m_view);
		auto* button = new QPushButton(strip);

		// Move the button to a widget nobody watches.
		auto* elsewhere = new QWidget;
		button->setParent(elsewhere);

		click(button);

		QCOMPARE(m_interactions, 0);
		delete elsewhere;
	}


	// ------------------------------------------------------------------
	// (l) Destroying the row does not leave the filter watching freed memory.
	//
	// Qt removes an installed filter when the watched object is destroyed, so
	// pressing on an unrelated widget afterwards must be harmless.
	// ------------------------------------------------------------------
	void destroyingRowIsSafe()
	{
		auto* button = new QPushButton(m_view);
		delete m_view;
		m_view = nullptr;

		QWidget unrelated;
		click(&unrelated);

		QCOMPARE(m_interactions, 0);
	}
};


//! The filter watches widgets, so it needs a `QApplication` rather than the
//! guiless one the other tests use.  Under `ctest` there is usually no display,
//! so fall back to Qt's offscreen platform when there is nothing to draw to.
int main(int argc, char* argv[])
{
	if (qEnvironmentVariableIsEmpty("QT_QPA_PLATFORM")
		&& qEnvironmentVariableIsEmpty("DISPLAY")
		&& qEnvironmentVariableIsEmpty("WAYLAND_DISPLAY"))
	{
		qputenv("QT_QPA_PLATFORM", "offscreen");
	}

	QApplication app(argc, argv);
	TrackRowInteractionFilterTest test;
	return QTest::qExec(&test, argc, argv);
}

#include "TrackRowInteractionFilterTest.moc"
