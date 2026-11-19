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
	// Defined out of line: m_displayMappingOwner holds a shared_ptr to an
	// incomplete type here, and destroying it requires the complete type.
	~SampleClipView() override;

public slots:
	void updateSample();
	void reverseSample();
	void setAutomationGhost();

	//! @brief React to the toolbar's Stretch edit-mode toggle.
	//!
	//! This is the ONLY place the toolbar toggle is allowed to influence the
	//! waveform, and all it does is switch the view between two display
	//! mappings without ever re-deriving either of them:
	//!
	//! - ON -> OFF: the mapping that is on screen right now is frozen
	//!   byte-for-byte (same buffer, same source window, same width in
	//!   timeline ticks). No thumbnail rebuild, no re-derivation from the
	//!   clip's live state, no audio processing.
	//! - OFF -> ON: the frozen mapping is discarded and the waveform is
	//!   recomputed to span the clip, which is what the toolbar promises.
	void onEditModeChanged();

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

	//! @brief The display mapping the waveform is currently drawn with.
	//!
	//! This is the state that makes "toolbar OFF freezes the waveform" true:
	//! it records which buffer is drawn, which fraction of it is drawn, and
	//! how wide the drawing is *in timeline ticks* (so zooming rescales it
	//! proportionally without re-deriving anything from the clip's live
	//! model state).
	//!
	//! Ownership rules (see STRETCH_CALL_PATH_AUDIT.md):
	//! - Written only by an explicit stretch commit (sampleChanged while the
	//!   toolbar is ON), by source-space edits while the toolbar is OFF, and
	//!   by the OFF -> ON toolbar transition.
	//! - The ON -> OFF toolbar transition freezes it byte-for-byte.
	//! - Rendering only reads it.
	struct DisplayMapping
	{
		//! Buffer the waveform is drawn from. The view keeps the underlying
		//! SampleBuffer alive via m_displayMappingOwner while this is set.
		const Sample* buffer = nullptr;
		//! Drawn source window as fractions of that buffer.
		float sampleStart = 0.0f;
		float sampleEnd = 1.0f;
		//! Drawn width in timeline ticks (pixels / pxPerTick at capture time).
		double widthInTicks = 0.0;
		//! Drawn left edge in timeline ticks relative to the clip's left edge
		//! (pixels / pxPerTick at capture time, scroll offset removed).
		double xInTicks = 0.0;
		//! The clip's start-time offset at capture time. A toolbar-off left
		//! trim keeps the audio's absolute timeline anchor (startPosition +
		//! startTimeOffset) fixed by changing the offset; frozenPlan()
		//! applies the offset change since capture to the drawn left edge so
		//! the waveform stays at its absolute timeline position instead of
		//! sliding with the clip's edge.
		double startTimeOffsetAtCapture = 0.0;
		//! True when this mapping was captured from the pre-toggle spans-clip
		//! state (the ON -> OFF toolbar freeze). Such a mapping must never be
		//! re-derived from the clip's source-space geometry, even when its
		//! buffer pointer compares equal to the clip's own sample (a
		//! non-Stretch pitch mode never builds a stretched buffer, so the
		//! spans-clip capture draws the source at the stretched scale).
		bool spansClipCapture = false;
		//! True once a mapping has been captured; false means "no frozen
		//! mapping, derive the waveform from the clip's live state".
		bool valid = false;
	};



protected:
	void constructContextMenu(QMenu* cm) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;
	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;
	void mouseDoubleClickEvent( QMouseEvent * ) override;
	void paintEvent( QPaintEvent * ) override;

	bool recordingCapabilitiesAvailable() const;

public:
	//! @brief The buffer whose samples the waveform should be drawn from.
	//!
	//! Deliberately independent of widget geometry so it can be consulted
	//! while the view is still being constructed. Public for unit-test access.
	const Sample* waveformBuffer() const;

	WaveformPlan waveformPlan();

	SampleClip * m_clip;
	SampleThumbnail m_sampleThumbnail;
	QPixmap m_paintPixmap;
	long m_paintPixmapXPosition;

private:
	//! Capture the mapping that is on screen right now into m_displayMapping.
	//! Used by the ON -> OFF toolbar transition (freeze) and by updateSample
	//! (keep the frozen mapping in step with legitimate edits). With
	//! @a preToggleStretch the spans-clip mapping is captured from the
	//! pre-toggle state, as if the toolbar were still ON.
	void captureDisplayMapping(bool preToggleStretch = false);

	//! The frozen-mapping plan: the captured mapping rescaled for the
	//! current zoom and scroll, plus the clip's start-time offset change
	//! since capture (so a toolbar-off left trim keeps the waveform at its
	//! absolute timeline position). Nothing else is consulted from the
	//! clip's live model state.
	WaveformPlan frozenPlan();

	//! The derived plan: re-derives the waveform from the clip's live state
	//! (spans-clip when the toolbar is ON, source space otherwise). This is
	//! the pre-existing waveformGeometry path.
	WaveformPlan derivePlan();

	//! Toolbar OFF only: move the frozen source window to the clip's current
	//! retained source range, at the frozen natural scale. Called for
	//! source-space edits (trims) of the clip's own sample. Never rescales
	//! the drawing and never touches a frozen stretched buffer's mapping.
	void refreshSourceSpaceMapping();

	//! Log the geometry paintEvent is actually drawing (buffer identity,
	//! sample count, drawn rectangle, source window and the reason the
	//! mapping is what it is).
	void logRenderedWaveform(const WaveformPlan& plan, const char* reason);

	//! The frozen display mapping. See the DisplayMapping docs for who may
	//! write it. m_displayMappingOwner keeps a mapped stretched Sample alive
	//! so the raw pointer can never dangle even if the clip later replaces
	//! its stretched buffer. The clip's own m_sample needs no owner: the view
	//! references it through m_clip, which outlives the mapping.
	DisplayMapping m_displayMapping;
	std::shared_ptr<const Sample> m_displayMappingOwner;
} ;


} // namespace gui

} // namespace lmms

#endif // LMMS_GUI_SAMPLE_CLIP_VIEW_H
