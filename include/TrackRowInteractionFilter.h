/*
 * TrackRowInteractionFilter.h
 *
 * Copyright (c) 2024 LMMS contributors
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

#ifndef LMMS_GUI_TRACK_ROW_INTERACTION_FILTER_H
#define LMMS_GUI_TRACK_ROW_INTERACTION_FILTER_H

#include <QObject>
#include <QChildEvent>
#include <QEvent>

#include <functional>
#include <utility>

namespace lmms::gui
{

//! @brief Reports every mouse press inside a widget subtree as one interaction.
//!
//! The widgets in a track's row -- its clips, mute/solo buttons, knobs and
//! operations menu -- never propagate their mouse events up to the row, so each
//! one has to be watched directly.  `cover()` installs the filter on a whole
//! subtree, and widgets built after that are picked up through `ChildAdded`,
//! which keeps newly created children and their own subtrees covered too.
//!
//! Presses are never consumed, so the watched widgets behave exactly as they did
//! before.  The filter lives outside `TrackView` rather than being an override of
//! `QWidget::eventFilter` so that this behaviour can be tested on its own.
//!
//! @note Only objects that are *children* of a covered object are watched.  A
//! widget shown in a window of its own -- a detached menu or a floating effect
//! window -- is outside the subtree and its presses are therefore not reported.
//!
//! Every member is defined inline, so the class needs no DLL export annotation.
class TrackRowInteractionFilter final : public QObject
{
public:
	//! @param onInteraction Called for every press on a watched object.
	explicit TrackRowInteractionFilter(std::function<void()> onInteraction)
		: m_onInteraction(std::move(onInteraction))
	{
	}

	//! @brief Watch `object` and everything already parented to it.
	void cover(QObject * object)
	{
		object->installEventFilter(this);
		for (auto * child : object->findChildren<QObject *>())
		{
			child->installEventFilter(this);
		}
	}

	//! @brief Stop watching `object` and its subtree.
	//!
	//! Qt leaves an installed filter in place when an object is reparented, so
	//! without this a widget moved to another track's row would keep reporting
	//! its presses to the row it came from.
	void uncover(QObject * object)
	{
		object->removeEventFilter(this);
		for (auto * child : object->findChildren<QObject *>())
		{
			child->removeEventFilter(this);
		}
	}

	bool eventFilter(QObject * watched, QEvent * e) override
	{
		switch (e->type())
		{
			case QEvent::MouseButtonPress:
				m_onInteraction();
				break;
			case QEvent::ChildAdded:
				// Lazily built UI -- a Sample Track's label button and volume knob,
				// for instance -- is added after construction and counts too.
				if (auto * child = static_cast<QChildEvent *>(e)->child())
				{
					cover(child);
				}
				break;
			case QEvent::ChildRemoved:
				// The subtree is still intact here, so it can be unwrapped in full.
				if (auto * child = static_cast<QChildEvent *>(e)->child())
				{
					uncover(child);
				}
				break;
			default:
				break;
		}
		// Never consume the event; the watched widgets still behave exactly as before.
		return QObject::eventFilter(watched, e);
	}

private:
	std::function<void()> m_onInteraction;
};

} // namespace lmms::gui

#endif // LMMS_GUI_TRACK_ROW_INTERACTION_FILTER_H
