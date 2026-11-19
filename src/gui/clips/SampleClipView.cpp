/*
 * SampleClipView.cpp
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
 
#include "SampleClipView.h"

#include <QApplication>
#include <QMenu>
#include <QPainter>

#include "lmmsconfig.h"

#include "AudioEngine.h"
#include "FileDialog.h"
#include "GuiApplication.h"
#include "AutomationEditor.h"
#include "embed.h"
#include "FontHelper.h"
#include "PathUtil.h"
#include "SampleClip.h"
#include "SampleThumbnail.h"
#include "StretchDebug.h"
#include "Song.h"
#include "SongEditor.h"
#include "StringPairDrag.h"
#include "TrackContainerView.h"
#include "TrackView.h"

namespace lmms::gui
{


SampleClipView::SampleClipView( SampleClip * _clip, TrackView * _tv ) :
	ClipView( _clip, _tv ),
	m_clip( _clip ),
	m_paintPixmap(),
	m_paintPixmapXPosition(0)
{
	// update UI and tooltip
	updateSample();

	// track future changes of SampleClip
	connect(m_clip, SIGNAL(sampleChanged()), this, SLOT(updateSample()));

	connect(m_clip, SIGNAL(wasReversed()), this, SLOT(update()));

	// The waveform geometry depends on the toolbar's Stretch edit mode, which
	// is pure view state: toggling it changes no model, so no model signal
	// would ever reach this view. Listen for the edit-mode change directly.
	// The handler is the ONLY code the toolbar toggle may run, and it never
	// re-derives the waveform from the clip's live state on an ON -> OFF
	// transition -- it freezes what is on screen (see onEditModeChanged).
	if (auto* songEditor = getGUI() ? getGUI()->songEditor() : nullptr)
	{
		connect(songEditor->m_editor, &SongEditor::editModeChanged,
			this, &SampleClipView::onEditModeChanged);
	}

	setStyle( QApplication::style() );
}

SampleClipView::~SampleClipView() = default;

void SampleClipView::updateSample()
{
	update();

	// Detect a sample buffer replacement: the frozen mapping may point at a
	// Sample that is no longer the clip's current one. When the clip's own
	// source sample is replaced the old Sample object is destroyed and the
	// raw pointer dangles; a frozen stretched buffer is kept alive by
	// m_displayMappingOwner and is unaffected. A mapping that has neither an
	// owner nor a match against the current sample is stale and must be
	// invalidated before anything else reads it.
	const auto& currentSample = m_clip->m_sample;
	const auto currentSize = currentSample.sampleSize();
	const auto bufferReplaced = m_displayMapping.valid
		&& m_displayMapping.buffer != nullptr
		&& m_displayMapping.buffer != &currentSample
		&& !m_displayMappingOwner;
	if (bufferReplaced)
	{
		StretchDebug::instance().logSampleLifecycle(
			makeClipId(m_clip), "buffer replaced", currentSize, false,
			"frozen mapping pointed at a previous sample; invalidating");
		m_displayMapping = DisplayMapping{};
		m_displayMappingOwner.reset();
	}
	else if (currentSize > 0 && m_displayMapping.valid)
	{
		StretchDebug::instance().logSampleLifecycle(
			makeClipId(m_clip), "sampleChanged", currentSize, true,
			"frozen mapping still valid");
	}

	// The thumbnail caches peaks taken from one particular buffer, so it has
	// to be rebuilt from exactly the buffer that `paintEvent` is about to
	// draw -- the frozen buffer when the toolbar is OFF, the stretched buffer
	// when the waveform is shown stretched, the original otherwise. Sharing
	// `waveformBuffer()` keeps the two in step.
	m_sampleThumbnail = SampleThumbnail{*waveformBuffer()};

	// Keep the display mapping in step with legitimate edits only:
	// - Toolbar ON: an explicit stretch commit (or any edit that changed the
	//   clip's audible content) re-derives the spans-clip mapping, so the
	//   next ON -> OFF freeze captures the freshly stretched waveform.
	// - Toolbar OFF: only source-space edits (trims) may move the drawn
	//   source window, and only at the frozen natural scale. The buffer and
	//   the width in ticks are preserved; nothing is re-derived from the
	//   clip's length or pitch mode.
	// A toolbar toggle never reaches this path: onEditModeChanged handles it
	// and deliberately does not call updateSample on ON -> OFF.
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;
	const auto toolbarStretch = tcv && tcv->stretchMode();
	if (toolbarStretch || !m_displayMapping.valid)
	{
		captureDisplayMapping();
	}
	else if (m_displayMapping.buffer == &m_clip->m_sample)
	{
		// Only source-space edits of the clip's own sample may move the
		// frozen source window. Edits of a frozen stretched buffer's clip
		// (e.g. a toolbar-off trim after a stretch) must leave the frozen
		// mapping completely untouched.
		refreshSourceSpaceMapping();
	}
	else if (m_displayMapping.valid && m_displayMapping.buffer)
	{
		// Observational instrumentation: a toolbar-OFF sampleChanged arrived
		// for a frozen stretched buffer's clip. Record the untouched frozen
		// mapping (with its pixels-per-source-frame ratio) so the log can
		// prove the drawing did not move.
		const auto size = static_cast<double>(m_displayMapping.buffer->sampleSize());
		const auto frames = (m_displayMapping.sampleEnd - m_displayMapping.sampleStart) * size;
		StretchDebug::instance().logTrimFromStartView(makeClipId(m_clip),
			"toolbar-off edit of frozen stretched buffer (mapping untouched)",
			reinterpret_cast<uintptr_t>(m_displayMapping.buffer),
			static_cast<int>(size), m_displayMapping.sampleStart,
			m_displayMapping.sampleEnd, m_displayMapping.widthInTicks,
			m_displayMapping.xInTicks, frames > 0.0 ? m_displayMapping.widthInTicks / frames : 0.0);
	}

	// set tooltip to filename so that user can see what sample this
	// sample-clip contains
	setToolTip(
		!m_clip->m_sample.sampleFile().isEmpty()
			? PathUtil::toAbsolute(m_clip->m_sample.sampleFile())
			: tr("Double-click to open sample")
	);
}


const Sample* SampleClipView::waveformBuffer() const
{
	// With the toolbar OFF and a frozen mapping, the waveform is drawn from
	// exactly the buffer it was drawn from when the mapping was captured.
	// The clip's pitch mode and the existence of a stretched buffer are
	// deliberately NOT consulted here: neither may change what is displayed
	// merely because it changed (STRETCH_CALL_PATH_AUDIT.md, flaw 3). A
	// previously generated stretched buffer may remain available for
	// playback, but its existence must not force the waveform to change.
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;
	const auto toolbarStretch = tcv && tcv->stretchMode();
	if (!toolbarStretch && m_displayMapping.valid)
	{
		return m_displayMapping.buffer;
	}

	// Toolbar ON (or the mapping is not captured yet): the spans-clip display
	// follows the buffer the clip actually plays -- the stretched buffer once
	// an explicitly requested stretch has landed, otherwise the source. This
	// branch is unreachable while the toolbar is OFF with a frozen mapping,
	// so pitch mode alone can never select the stretched buffer for display.
	if (m_clip->pitchMode() == SampleClip::PitchMode::Stretch)
	{
		if (const auto stretched = m_clip->stretchedSample())
		{
			return stretched.get();
		}
	}
	return &m_clip->m_sample;
}


SampleClipView::WaveformPlan SampleClipView::waveformGeometry(const SampleClip& clip,
	const Sample& buffer, double pxPerTick, bool stretchMode, double xOffset)
{
	WaveformPlan plan;
	plan.buffer = &buffer;

	const double size = buffer.sampleSize();
	if (size <= 0.0)
	{
		return plan;
	}

	// Width of the *whole* source in pixels at the source's natural speed.
	// Every pixel of that width is worth the same amount of source audio no
	// matter how long the clip is, which is what "the waveform keeps its
	// natural scale" means.
	const double naturalWidth = static_cast<double>(clip.sampleLength()) * pxPerTick;

	// Where source frame 0 sits: upstream draws the sample offset by the
	// clip's start-time offset, so a positive offset (leading silence) shifts
	// the waveform right and a left trim shifts it left.
	const double frameZeroX = static_cast<double>(clip.startTimeOffset()) * pxPerTick - xOffset;

	// The stretchMode parameter comes from waveformPlan() and reflects ONLY
	// the toolbar Stretch state. It must not be overridden by the clip's
	// pitch mode or stretch ratio. Audio processing and waveform rendering
	// are independent: the toolbar controls the drawing geometry, the pitch
	// mode controls the audio processing.
	const auto spansClip = stretchMode;

	if (!spansClip)
	{
		// Source-space drawing: the buffer being played is the original source,
		// drawn at its natural scale, so resizing the clip -- longer *or* shorter
		// -- can never change how many pixels one cycle of the waveform occupies.
		// Only the retained source range is drawn, so a trim visibly removes audio
		// instead of compressing it.
		// The clip's length is deliberately not consulted: deriving the drawn
		// range from it is what made a shortened clip draw a fraction of the
		// source across the full natural width, i.e. a waveform that visibly
		// slowed down as the clip was dragged shorter.
		const double first = std::clamp(static_cast<double>(clip.sourceStartFrame()), 0.0, size);
		const double last = std::clamp(static_cast<double>(clip.sourceEndFrame()), first, size);
		const double range = last - first;
		if (range <= 0.0)
		{
			plan.width = 0;
			return plan;
		}

		// The visible waveform is clipped at the clip's left edge, not pinned
		// to source frame 0. A left trim discards the beginning of the audio;
		// the retained portion must appear starting at the clip's left edge
		// with the same horizontal scale and phase, not shifted rightward
		// into the clip. The width tracks the retained range at the natural
		// scale, so the drawing never stretches or compresses.
		plan.sampleStart = static_cast<float>(first / size);
		plan.sampleEnd = static_cast<float>(last / size);
		plan.width = static_cast<float>(naturalWidth * (range / size));
		plan.x = static_cast<float>(frameZeroX);
		return plan;
	}

	// Toolbar on: every pixel of the clip is audible output, so the buffer
	// being played is drawn from edge to edge of the clip.
	plan.x = static_cast<float>(-xOffset);
	plan.width = static_cast<float>(static_cast<double>(clip.length()) * pxPerTick);

	// Whether the pitch-preserving buffer has landed yet or not, the clip's own
	// mapping reports the source range that is audible inside this clip, which
	// is exactly what the listener hears from left edge to right edge.
	const auto mapping = clip.waveformMapping(buffer);
	plan.sampleStart = mapping.sampleStart;
	plan.sampleEnd = mapping.sampleEnd;

	return plan;
}


SampleClipView::WaveformPlan SampleClipView::waveformPlan()
{
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;
	const auto toolbarStretch = tcv && tcv->stretchMode();

	// Toolbar OFF with a frozen mapping: draw exactly the frozen mapping,
	// rescaled only for zoom and scroll. The clip's live length, pitch
	// mode, stretch ratio and stretched buffer are deliberately not
	// consulted -- resizing the clip changes its boundary, never the
	// waveform's existing audio-to-display mapping.
	if (!toolbarStretch && m_displayMapping.valid) { return frozenPlan(); }

	return derivePlan();
}



SampleClipView::WaveformPlan SampleClipView::frozenPlan()
{
	WaveformPlan plan;
	const float ppb = fixedClips()
		? (parentWidget()->width() - 2 * BORDER_WIDTH) / (float) m_clip->length().getBar()
		: pixelsPerBar();
	const float nom = Engine::getSong()->getTimeSigModel().getNumerator();
	const float den = Engine::getSong()->getTimeSigModel().getDenominator();
	const float ticksPerBar = DefaultTicksPerBar * nom / den;

	plan.buffer = m_displayMapping.buffer;
	plan.sampleStart = m_displayMapping.sampleStart;
	plan.sampleEnd = m_displayMapping.sampleEnd;
	// The mapping is stored in ticks; waveformGeometry works in pixels per
	// tick, so rescale with ppb / ticksPerBar -- the same conversion
	// derivePlan() feeds waveformGeometry(). Zoom changes ppb and nothing
	// else; the mapping itself is never recomputed here.
	const float pxPerTick = ppb / ticksPerBar;
	plan.width = static_cast<float>(m_displayMapping.widthInTicks * pxPerTick);
	plan.x = static_cast<float>(m_displayMapping.xInTicks * pxPerTick - m_paintPixmapXPosition);
	return plan;
}



SampleClipView::WaveformPlan SampleClipView::derivePlan()
{
	const auto& original = m_clip->m_sample;
	if (original.sampleSize() <= 0)
	{
		WaveformPlan plan;
		plan.buffer = waveformBuffer();
		return plan;
	}

	const float ppb = fixedClips()
		? (parentWidget()->width() - 2 * BORDER_WIDTH) / (float) m_clip->length().getBar()
		: pixelsPerBar();
	const float nom = Engine::getSong()->getTimeSigModel().getNumerator();
	const float den = Engine::getSong()->getTimeSigModel().getDenominator();
	const float ticksPerBar = DefaultTicksPerBar * nom / den;

	// Waveform rendering obeys the toolbar Stretch state ONLY.
	// The toolbar Stretch button controls whether the waveform is drawn
	// stretched across the clip (ON) or at natural source scale (OFF).
	// Audio processing (pitch mode Stretch/Resample) is independent and
	// must not affect the waveform geometry.
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;
	const auto toolbarStretch = tcv && tcv->stretchMode();
	const auto pitchModeIsStretch = m_clip->pitchMode() == SampleClip::PitchMode::Stretch;
	const auto hasStretchedBuffer = pitchModeIsStretch && m_clip->stretchedSample() != nullptr;
	const auto pitchModeIsResample = m_clip->pitchMode() == SampleClip::PitchMode::Resample;
	const auto clipIsStretched = m_clip->isStretched();

	// Display state: waveform spans clip ONLY when toolbar Stretch is ON
	const auto spansClip = toolbarStretch;

	// Enhanced diagnostic logging with all three states
	StretchDebug::instance().logWaveformPlan(
		makeClipId(m_clip),
		static_cast<bool>(toolbarStretch),
		static_cast<bool>(pitchModeIsStretch),
		static_cast<bool>(hasStretchedBuffer),
		static_cast<bool>(pitchModeIsResample),
		static_cast<bool>(clipIsStretched),
		static_cast<bool>(spansClip),
		m_clip->stretchRatio());

	return waveformGeometry(*m_clip, *waveformBuffer(), ppb / ticksPerBar,
		spansClip, m_paintPixmapXPosition);
}



void SampleClipView::onEditModeChanged()
{
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;
	const auto toolbarStretch = tcv && tcv->stretchMode();

	if (toolbarStretch)
	{
		// OFF -> ON: the toolbar promises that resizing now stretches the
		// waveform, so the frozen mapping is discarded and the waveform is
		// recomputed to span the clip. This is the only toolbar transition
		// that re-derives the mapping.
		m_displayMapping = DisplayMapping{};
		m_displayMappingOwner.reset();
		updateSample();
		return;
	}

	// ON -> OFF: the mode has already changed, so derivePlan() would now
	// produce the source-space mapping. Freeze the mapping that was on
	// screen immediately before the toggle instead: capture it from the
	// pre-toggle state (as if the toolbar were still ON), byte-for-byte.
	// No re-derivation from the clip's live state, no audio processing,
	// no reset to the pre-stretch source. The waveform must remain
	// exactly as it was immediately before the toggle.
	//
	// updateSample() is called after the mapping is frozen so the cached
	// thumbnail is rebuilt from the frozen buffer. Without this the
	// thumbnail keeps showing the pre-toggle buffer and the drawn
	// waveform disagrees with the painted one -- the clip body renders
	// the stretched audio while the waveform inside it shows the
	// original, which is the regression the user reported.
	captureDisplayMapping(true);
	updateSample();

	// Observational instrumentation: record the frozen mapping the toggle
	// captured (with its pixels-per-source-frame ratio) so the log can prove
	// the ON -> OFF transition preserved the drawing byte-for-byte.
	if (m_displayMapping.valid && m_displayMapping.buffer)
	{
		const auto size = static_cast<double>(m_displayMapping.buffer->sampleSize());
		const auto frames = (m_displayMapping.sampleEnd - m_displayMapping.sampleStart) * size;
		StretchDebug::instance().logTrimFromStartView(makeClipId(m_clip),
			"toolbar toggled OFF, mapping frozen",
			reinterpret_cast<uintptr_t>(m_displayMapping.buffer),
			static_cast<int>(size), m_displayMapping.sampleStart,
			m_displayMapping.sampleEnd, m_displayMapping.widthInTicks,
			m_displayMapping.xInTicks, frames > 0.0 ? m_displayMapping.widthInTicks / frames : 0.0);
	}
}



void SampleClipView::captureDisplayMapping(bool preToggleStretch)
{
	// Capture the mapping that is on screen right now. Width and x are
	// stored in timeline ticks so that zooming (which legitimately changes
	// pixel geometry) rescales the frozen drawing proportionally without
	// re-deriving anything from the clip's live model state.
	//
	// preToggleStretch: the ON -> OFF toolbar transition calls this AFTER
	// the mode has already changed, so derivePlan() would produce the
	// source-space mapping. Passing true captures the spans-clip mapping
	// from the pre-toggle state instead -- exactly what was on screen
	// immediately before the toggle.
	WaveformPlan current;
	if (preToggleStretch)
	{
		const float ppb = fixedClips()
			? (parentWidget()->width() - 2 * BORDER_WIDTH) / (float) m_clip->length().getBar()
			: pixelsPerBar();
		const float nom = Engine::getSong()->getTimeSigModel().getNumerator();
		const float den = Engine::getSong()->getTimeSigModel().getDenominator();
		const float ticksPerBar = DefaultTicksPerBar * nom / den;
		const double pxPerTick = ppb / ticksPerBar;

		const auto stretched = m_clip->stretchedSample();
		const Sample& drawn = stretched ? *stretched : m_clip->m_sample;
		current.buffer = &drawn;
		// Toolbar-on geometry (see waveformGeometry's spansClip branch): the
		// buffer is drawn from edge to edge of the clip.
		current.x = static_cast<float>(-m_paintPixmapXPosition);
		current.width = static_cast<float>(static_cast<double>(m_clip->length()) * pxPerTick);
		const auto mapping = m_clip->waveformMapping(drawn);
		current.sampleStart = mapping.sampleStart;
		current.sampleEnd = mapping.sampleEnd;
	}
	else
	{
		current = derivePlan();
	}

	const float ppb = fixedClips()
		? (parentWidget()->width() - 2 * BORDER_WIDTH) / (float) m_clip->length().getBar()
		: pixelsPerBar();
	const float nom = Engine::getSong()->getTimeSigModel().getNumerator();
	const float den = Engine::getSong()->getTimeSigModel().getDenominator();
	const float ticksPerBar = DefaultTicksPerBar * nom / den;
	const double pxPerTick = ppb / ticksPerBar;

	m_displayMapping.buffer = current.buffer;
	m_displayMapping.sampleStart = current.sampleStart;
	m_displayMapping.sampleEnd = current.sampleEnd;
	m_displayMapping.widthInTicks = pxPerTick > 0.0 ? current.width / pxPerTick : 0.0;
	m_displayMapping.xInTicks = pxPerTick > 0.0 ? (current.x + m_paintPixmapXPosition) / pxPerTick : 0.0;

	// A mapping is only valid when its source buffer actually holds audio.
	// Capturing while the sample is still being loaded (or has been replaced
	// by an empty one) would freeze an empty waveform permanently: the next
	// paint would draw nothing, and no subsequent edit would ever re-capture
	// because the mapping would already be "valid". Leave it invalid instead;
	// the next sampleChanged re-enters updateSample and captures from the
	// buffer that is now ready.
	const auto capturedSize = current.buffer ? current.buffer->sampleSize() : 0;
	m_displayMapping.valid = (capturedSize > 0);
	StretchDebug::instance().logMappingCapture(
		makeClipId(m_clip),
		reinterpret_cast<uintptr_t>(current.buffer),
		static_cast<int>(capturedSize),
		m_displayMapping.valid,
		preToggleStretch ? "pre-toggle freeze" : "updateSample capture");

	// Keep a mapped stretched buffer alive so the raw pointer can never
	// dangle even if the clip later replaces its stretched buffer. The
	// clip's own m_sample needs no owner: the view reaches it through
	// m_clip, which outlives the mapping. derivePlan() above resolved the
	// buffer through the very same stretchedSample() call, so when the drawn
	// buffer is not the clip's own sample this returns the same object.
	m_displayMappingOwner = current.buffer != &m_clip->m_sample
		? m_clip->stretchedSample()
		: nullptr;
	if (current.buffer != &m_clip->m_sample && !m_displayMappingOwner)
	{
		// Defensive: the drawn buffer came from somewhere else and we could
		// not take ownership of it. Invalidate rather than risk a dangling
		// pointer; the next paint re-derives the mapping.
		m_displayMapping = DisplayMapping{};
	}
}



void SampleClipView::refreshSourceSpaceMapping()
{
	// Toolbar OFF: a source-space edit (a trim or an extension) moved the
	// clip's boundary. The frozen mapping must follow the edit while keeping
	// the exact same audio-to-screen transformation: the same buffer, the
	// same pixels-per-source-frame, and the same audio at the same song-time
	// coordinates. Only the visible clipping interval may change.
	//
	// SampleThumbnail::visualize() maps the drawn source window linearly onto
	// the drawing rectangle, so the pixels-per-source-frame ratio is
	// width / (window size in frames). Keeping the old width while shrinking
	// the window would therefore RESCALE the drawing -- the bug this function
	// used to have. Instead the whole mapping is re-derived from the clip's
	// live source-space geometry (waveformGeometry's source-space branch),
	// which is exactly the transformation the toolbar-OFF drawing would use
	// without a frozen mapping: width = retained range at the natural scale,
	// x = the start-time offset's position of source frame 0. A right trim
	// changes only the drawn range (the drawing's right edge moves in); a
	// left trim changes only the offset (the drawing slides left with the
	// clip's edge); both keep the ratio constant.
	if (!m_displayMapping.valid || !m_displayMapping.buffer) { return; }
	const auto& buffer = *m_displayMapping.buffer;
	if (buffer.sampleSize() <= 0) { return; }

	const auto before = m_displayMapping;
	const auto beforeSize = static_cast<double>(buffer.sampleSize());
	const auto beforeFrames = (before.sampleEnd - before.sampleStart) * beforeSize;
	const auto beforeRatio = beforeFrames > 0.0 ? before.widthInTicks / beforeFrames : 0.0;

	const float ppb = fixedClips()
		? (parentWidget()->width() - 2 * BORDER_WIDTH) / (float) m_clip->length().getBar()
		: pixelsPerBar();
	const float nom = Engine::getSong()->getTimeSigModel().getNumerator();
	const float den = Engine::getSong()->getTimeSigModel().getDenominator();
	const float ticksPerBar = DefaultTicksPerBar * nom / den;
	const double pxPerTick = ppb / ticksPerBar;
	if (pxPerTick <= 0.0) { return; }

	// Re-derive the source-space drawing from the clip's live state, at the
	// frozen buffer and the current zoom. The buffer is passed explicitly so
	// the mapping can never silently switch buffers.
	const auto plan = waveformGeometry(*m_clip, buffer, pxPerTick,
		/*stretchMode=*/false, m_paintPixmapXPosition);

	m_displayMapping.sampleStart = plan.sampleStart;
	m_displayMapping.sampleEnd = plan.sampleEnd;
	m_displayMapping.widthInTicks = plan.width / pxPerTick;
	m_displayMapping.xInTicks = (plan.x + m_paintPixmapXPosition) / pxPerTick;

	const auto afterSize = static_cast<double>(buffer.sampleSize());
	const auto afterFrames = (m_displayMapping.sampleEnd - m_displayMapping.sampleStart) * afterSize;
	const auto afterRatio = afterFrames > 0.0 ? m_displayMapping.widthInTicks / afterFrames : 0.0;
	StretchDebug::instance().logTrimFromStartView(makeClipId(m_clip),
		"source-space edit applied", reinterpret_cast<uintptr_t>(&buffer),
		static_cast<int>(afterSize), m_displayMapping.sampleStart,
		m_displayMapping.sampleEnd, m_displayMapping.widthInTicks,
		m_displayMapping.xInTicks, afterRatio);
	StretchDebug::instance().logTrimFromStartView(makeClipId(m_clip),
		"previous frozen mapping", reinterpret_cast<uintptr_t>(&buffer),
		static_cast<int>(beforeSize), before.sampleStart, before.sampleEnd,
		before.widthInTicks, before.xInTicks, beforeRatio);
}



void SampleClipView::logRenderedWaveform(const WaveformPlan& plan, const char* reason)
{
	const float ppb = fixedClips()
		? (parentWidget()->width() - 2 * BORDER_WIDTH) / (float) m_clip->length().getBar()
		: pixelsPerBar();
	StretchDebug::instance().logWaveformRendered(
		makeClipId(m_clip),
		reinterpret_cast<uintptr_t>(plan.buffer),
		plan.buffer ? static_cast<int>(plan.buffer->sampleSize()) : 0,
		plan.x, plan.width, plan.sampleStart, plan.sampleEnd,
		std::string(reason) + " ppb=" + std::to_string(ppb));
}


void SampleClipView::constructContextMenu(QMenu* cm)
{
	cm->addSeparator();


	QAction* recordToggleAction = cm->addAction(embed::getIconPixmap("record"),
                          tr("Set/clear record"),
                          m_clip, &SampleClip::toggleRecord);
	
	recordToggleAction->setEnabled(recordingCapabilitiesAvailable());

	cm->addAction(
		embed::getIconPixmap("flip_x"),
		tr("Reverse sample"),
		this,
		SLOT(reverseSample())
	);

	cm->addAction(
		embed::getIconPixmap("automation_ghost_note"),
		tr("Set as ghost in automation editor"),
		this,
		SLOT(setAutomationGhost())
	);

	// Pitch mode: Resample (traditional speed+pitch change) vs Stretch
	// (real time-stretch preserving pitch). Mutually exclusive; selecting
	// the already-active mode is a no-op. The mode switch never changes
	// the clip's length. Stretch is always offered when the build has a
	// pitch-preserving algorithm.
	//
	// Selecting Stretch here also arms the toolbar's Stretch edit mode:
	// edge drags only stretch when that mode is active (ClipView classifies
	// the drag as a stretch solely from the toolbar state), so without this
	// the menu selection alone would leave the user trimming on the next
	// drag. Selecting Resample leaves the toolbar as it is -- stretching
	// the clip's length while rendering resampled audio is a valid
	// combination.
	const auto pitchMenu = cm->addMenu(tr("Pitch mode"));
	const auto resampleAction = pitchMenu->addAction(tr("Resample"));
	resampleAction->setCheckable(true);
	resampleAction->setChecked(m_clip->pitchMode() == SampleClip::PitchMode::Resample);
	const auto stretchAction = pitchMenu->addAction(tr("Stretch"));
	stretchAction->setCheckable(true);
	stretchAction->setChecked(m_clip->pitchMode() == SampleClip::PitchMode::Stretch);
	const auto setMode = [this](SampleClip::PitchMode mode)
	{
		if (m_clip->pitchMode() == mode) { return; }
		m_clip->getTrack()->addJournalCheckPoint();
		m_clip->setJournalling(false);
		m_clip->setPitchMode(mode);
		m_clip->setJournalling(true);
		Engine::getSong()->setModified();
		if (mode == SampleClip::PitchMode::Stretch)
		{
			if (auto* songEditor = getGUI() ? getGUI()->songEditor() : nullptr)
			{
				songEditor->m_editor->setEditMode(SongEditor::EditMode::Stretch);
				songEditor->syncEditMode();
			}
		}
	};

	connect(resampleAction, &QAction::triggered, this, [this, setMode] { setMode(SampleClip::PitchMode::Resample); });
	connect(stretchAction, &QAction::triggered, this, [this, setMode] { setMode(SampleClip::PitchMode::Stretch); });

#ifdef LMMS_HAVE_SOUNDTOUCH
	stretchAction->setEnabled(true);
	stretchAction->setToolTip(tr("Real time-stretch preserving pitch"));
#else
	// Built without SoundTouch, so there is no pitch-preserving algorithm to
	// offer; a clip saved in Stretch mode still plays, just resampled.
	stretchAction->setEnabled(false);
	stretchAction->setToolTip(tr("Stretch requires LMMS to be built with SoundTouch"));
#endif

}




void SampleClipView::dragEnterEvent( QDragEnterEvent * _dee )
{
	if( StringPairDrag::processDragEnterEvent( _dee,
					{"samplefile", "sampledata"} ) == false )
	{
		ClipView::dragEnterEvent( _dee );
	}
}






void SampleClipView::dropEvent( QDropEvent * _de )
{
	if( StringPairDrag::decodeKey( _de ) == "samplefile" )
	{
		m_clip->setSampleFile( StringPairDrag::decodeValue( _de ) );
		_de->accept();
	}
	else if( StringPairDrag::decodeKey( _de ) == "sampledata" )
	{
		m_clip->setSampleBuffer(SampleBuffer::fromBase64(StringPairDrag::decodeValue(_de)));
		m_clip->updateLength();
		update();
		_de->accept();
	}
	else
	{
		ClipView::dropEvent( _de );
	}
}




void SampleClipView::mousePressEvent( QMouseEvent * _me )
{
	if( _me->button() == Qt::LeftButton &&
		_me->modifiers() & Qt::ControlModifier &&
		_me->modifiers() & Qt::ShiftModifier )
	{
		m_clip->toggleRecord();
	}
	else
	{
		if( _me->button() == Qt::MiddleButton && _me->modifiers() == Qt::ControlModifier )
		{
			auto sClip = dynamic_cast<SampleClip*>(getClip());
			if( sClip )
			{
				sClip->updateTrackClips();
			}
		}
		ClipView::mousePressEvent( _me );
	}
}




void SampleClipView::mouseReleaseEvent(QMouseEvent *_me)
{
	if( _me->button() == Qt::MiddleButton && !_me->modifiers() )
	{
		auto sClip = dynamic_cast<SampleClip*>(getClip());
		if( sClip )
		{
			sClip->playbackPositionChanged();
		}
	}
	ClipView::mouseReleaseEvent( _me );
}




void SampleClipView::mouseDoubleClickEvent( QMouseEvent * )
{
	if (m_trackView->trackContainerView()->knifeMode()) { return; }

	const QString selectedAudioFile = FileDialog::openAudioFile();

	if (selectedAudioFile.isEmpty()) { return; }
	
	if (!m_clip->hasSampleFileLoaded(selectedAudioFile))
	{
		auto sampleBuffer = SampleBuffer::fromFile(selectedAudioFile);
		if (sampleBuffer != SampleBuffer::emptyBuffer())
		{
			m_clip->setSampleBuffer(sampleBuffer);
		}
	}
	m_clip->updateLength();
}




void SampleClipView::paintEvent( QPaintEvent * pe )
{
	QPainter painter( this );

	if( !needsUpdate() )
	{
		painter.drawPixmap(m_paintPixmapXPosition, 0, m_paintPixmap);
		return;
	}

	setNeedsUpdate( false );

	const auto trackViewWidth = getTrackView()->rect().width();

	// Use the clip's height to avoid artifacts when rendering while something else is overlaying the clip.
	const auto viewPortRect = QRect(0, 0, trackViewWidth * 2, rect().height());

	m_paintPixmapXPosition = std::max(0, pe->rect().x() - trackViewWidth);

	if (m_paintPixmap.isNull() || m_paintPixmap.size() != viewPortRect.size())
	{
		m_paintPixmap = QPixmap(viewPortRect.size());
	}

	QPainter p( &m_paintPixmap );

	bool muted = m_clip->getTrack()->isMuted() || m_clip->isMuted();
	bool selected = isSelected();

	QLinearGradient lingrad(0, 0, 0, height());
	QColor c = painter.background().color();
	if (muted) { c = c.darker(150); }
	if (selected) { c = c.darker(150); }

	lingrad.setColorAt( 1, c.darker( 300 ) );
	lingrad.setColorAt( 0, c );

	// paint a black rectangle under the clip to prevent glitches with transparent backgrounds
	p.fillRect( rect(), QColor( 0, 0, 0 ) );

	if( gradient() )
	{
		p.fillRect( rect(), lingrad );
	}
	else
	{
		p.fillRect( rect(), c );
	}

	auto clipColor = m_clip->color().value_or(m_clip->getTrack()->color().value_or(painter.pen().brush().color()));

	p.setPen(clipColor);

	if (muted)
	{
		QColor penColor = p.pen().brush().color();
		penColor.setHsv(penColor.hsvHue(), penColor.hsvSaturation() / 4, penColor.value());
		p.setPen(penColor.darker(250));
	}
	if (selected)
	{
		p.setPen(p.pen().brush().color().darker(150));
	}

	const float spacing = BORDER_WIDTH + 1;

	const WaveformPlan plan = waveformPlan();

	// Observational instrumentation: record the geometry that is actually
	// being drawn. This call must never mutate the plan or the view state.
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;
	const auto toolbarStretch = tcv && tcv->stretchMode();
	logRenderedWaveform(plan,
		toolbarStretch ? "spans clip (toolbar on)"
		: m_displayMapping.valid ? "frozen (toolbar off)"
		: "source space");

	if (plan.buffer->sampleSize() > 0)
	{
		const auto param = SampleThumbnail::VisualizeParameters{
			.sampleRect = QRect(static_cast<int>(plan.x), spacing, static_cast<int>(plan.width), height() - spacing),
			.viewportRect = viewPortRect,
			.amplification = plan.buffer->amplification(),
			.sampleStart = plan.sampleStart,
			.sampleEnd = plan.sampleEnd,
			.reversed = plan.buffer->reversed()
		};

		m_sampleThumbnail.visualize(param, p);
	}

	QString name = PathUtil::cleanName(m_clip->m_sample.sampleFile());
	paintTextLabel(name, p);

	// disable antialiasing for borders, since its not needed
	p.setRenderHint( QPainter::Antialiasing, false );

	// inner border
	p.setPen( c.lighter( 135 ) );
	p.drawRect(
		-m_paintPixmapXPosition + 1,
		1,
		rect().right() - BORDER_WIDTH,
		rect().bottom() - BORDER_WIDTH );

	// outer border
	p.setPen( c.darker( 200 ) );
	p.drawRect(-m_paintPixmapXPosition, 0, rect().right(), rect().bottom());

	// draw the 'muted' pixmap only if the clip was manually muted
	if( m_clip->isMuted() )
	{
		const int spacing = BORDER_WIDTH;
		const int size = 14;
		p.drawPixmap( spacing, height() - ( size + spacing ),
			embed::getIconPixmap( "muted", size, size ) );
	}

	if ( m_marker )
	{
		p.setPen(markerColor());
		p.drawLine(m_markerPos, rect().bottom(), m_markerPos, rect().top());
	}
	// recording sample tracks is not possible at the moment

	if (m_clip->isRecord())
	{
		p.setFont(adjustedToPixelSize(p.font(), 10));

		const auto fontHeight = p.fontMetrics().height();

		const auto baseLine = height() - 3;

		constexpr int recordSymbolRadius = 3;
		constexpr int recordSymbolCenterX = recordSymbolRadius + 4;
		const int recordSymbolCenterY = baseLine - fontHeight / 2 + 1;

		constexpr int textStartX = recordSymbolCenterX + recordSymbolRadius + 4;

		auto textPos = QPoint(textStartX, baseLine);

		const auto rec = tr("Rec");

		p.setPen(textShadowColor());
		p.drawText(textPos + QPoint(1, 1), rec);

		p.setPen(textColor());
		p.drawText(textPos, rec);

		p.setBrush(QBrush(textColor()));

		p.drawEllipse(QPoint(recordSymbolCenterX, recordSymbolCenterY), recordSymbolRadius, recordSymbolRadius);
	}

	p.end();

	painter.drawPixmap(m_paintPixmapXPosition, 0, m_paintPixmap);
}




void SampleClipView::reverseSample()
{
	m_clip->m_sample.setReversed(!m_clip->m_sample.reversed());
	m_clip->setStartTimeOffset(m_clip->length() - m_clip->startTimeOffset() - m_clip->sampleLength());
	Engine::getSong()->setModified();
	update();
}



void SampleClipView::setAutomationGhost()
{
	auto aEditor = gui::getGUI()->automationEditor();
	aEditor->setGhostSample(m_clip);
	aEditor->parentWidget()->show();
	aEditor->show();
	aEditor->setFocus();
}
bool SampleClipView::recordingCapabilitiesAvailable() const
{
	return Engine::audioEngine()->captureDeviceAvailable();
}

} // namespace lmms::gui
