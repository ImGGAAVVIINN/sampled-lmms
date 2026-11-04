/*
 * SampleClipView.h
 *
 * Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
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

#ifndef LMMS_GUI_SAMPLE_CLIP_VIEW_H
#define LMMS_GUI_SAMPLE_CLIP_VIEW_H

#include "ClipView.h"

#include "SampleThumbnail.h"

namespace lmms
{

class Sample;
class SampleClip;

namespace gui
{


class SampleClipView : public ClipView
{
	Q_OBJECT

public:
	SampleClipView( SampleClip * _clip, TrackView * _tv );
	~SampleClipView() override = default;

public slots:
	void updateSample();
	void reverseSample();
	void setAutomationGhost();

public:
	//! @brief Which sample data to draw and where to draw it.
	//!
	//! Two independent controls feed into this:
	//!   * the toolbar's Stretch edit-mode toggle decides the *geometry* --
	//!     with it off the waveform keeps its natural (un-stretched) width,
	//!     with it on the waveform spans the clip's full resized width;
	//!   * the clip's pitch mode decides *which buffer* is played, and
	//!     therefore which buffer is honest to display when the waveform is
	//!     shown stretched.
	//! `paintEvent` and `updateSample` both go through here so the cached
	//! thumbnail and the drawn geometry can never disagree.
	struct WaveformPlan
	{
		const Sample* buffer = nullptr;
		float sampleStart = 0.0f;
		float sampleEnd = 1.0f;
		float x = 0.0f;
		float width = 0.0f;
	};

	/**
	 * @brief The waveform geometry @a paintEvent is about to draw, as a pure
	 * function of the clip, the buffer being drawn, the zoom and the toolbar's
	 * Stretch edit mode.
	 *
	 * Exposed (rather than inlined into `waveformPlan`) so the invariant the
	 * user can actually see -- "with the toolbar toggle off, resizing the clip
	 * must never rescale the waveform" -- can be checked against the real
	 * drawing geometry instead of against a screenshot proxy.
	 *
	 * @param pxPerTick horizontal zoom, pixels per timeline tick.
	 * @param stretchMode the toolbar's Stretch edit-mode toggle.
	 * @param xOffset horizontal scroll offset subtracted from the drawing position.
	 */
	static WaveformPlan waveformGeometry(const SampleClip& clip, const Sample& buffer,
		double pxPerTick, bool stretchMode, double xOffset);



protected:
	void constructContextMenu(QMenu* cm) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;
	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;
	void mouseDoubleClickEvent( QMouseEvent * ) override;
	void paintEvent( QPaintEvent * ) override;

	bool recordingCapabilitiesAvailable() const;

private:
	//! @brief The buffer whose samples the waveform should be drawn from.
	//!
	//! Deliberately independent of widget geometry so it can be consulted
	//! while the view is still being constructed.
	const Sample* waveformBuffer() const;

	WaveformPlan waveformPlan();

	SampleClip * m_clip;
	SampleThumbnail m_sampleThumbnail;
	QPixmap m_paintPixmap;
	long m_paintPixmapXPosition;
} ;


} // namespace gui

} // namespace lmms

#endif // LMMS_GUI_SAMPLE_CLIP_VIEW_H
