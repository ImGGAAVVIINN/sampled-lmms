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
	// would ever reach this view. Listen for the edit-mode change directly so
	// the waveform is rebuilt and repainted the moment the button is toggled.
	if (auto* songEditor = getGUI() ? getGUI()->songEditor() : nullptr)
	{
		connect(songEditor->m_editor, &SongEditor::editModeChanged,
			this, &SampleClipView::updateSample);
	}

	setStyle( QApplication::style() );
}

void SampleClipView::updateSample()
{
	update();

	// The thumbnail caches peaks taken from one particular buffer, so it has
	// to be rebuilt from exactly the buffer that `paintEvent` is about to
	// draw -- the stretched buffer when the waveform is shown stretched, the
	// original otherwise. Sharing `waveformBuffer()` keeps the two in step.
	m_sampleThumbnail = SampleThumbnail{*waveformBuffer()};

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
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;
	if (tcv && tcv->stretchMode())
	{
		// The waveform is being shown stretched, so show the buffer that is
		// actually played. `stretchedSample()` only returns a buffer while it
		// still matches the clip's current parameters.
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

	if (!stretchMode)
	{
		// Toolbar off: pure source-space drawing. The buffer being played is
		// the original source, drawn at its natural scale, so resizing the
		// clip -- longer *or* shorter -- can never change how many pixels one
		// cycle of the waveform occupies. Only the retained source range is
		// drawn, so a trim visibly removes audio instead of compressing it.
		// The clip's length and stretch ratio are deliberately not consulted:
		// deriving the drawn range from them is what made a shortened clip
		// draw a fraction of the source across the full natural width, i.e.
		// a waveform that visibly slowed down as the clip was dragged
		// shorter.
		const double first = std::clamp(static_cast<double>(clip.sourceStartFrame()), 0.0, size);
		const double last = std::clamp(static_cast<double>(clip.sourceEndFrame()), first, size);
		const double range = last - first;
		if (range <= 0.0)
		{
			plan.width = 0;
			return plan;
		}

		plan.sampleStart = static_cast<float>(first / size);
		plan.sampleEnd = static_cast<float>(last / size);
		plan.width = static_cast<float>(naturalWidth * (range / size));
		plan.x = static_cast<float>(frameZeroX + naturalWidth * (first / size));
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

	// Bug B: the toolbar's Stretch edit-mode toggle -- not the context-menu
	// pitch method -- decides whether the waveform is drawn stretched across
	// the clip's full resized width.
	const TrackContainerView* tcv =
		m_trackView ? m_trackView->trackContainerView() : nullptr;

	return waveformGeometry(*m_clip, *waveformBuffer(), ppb / ticksPerBar,
		tcv && tcv->stretchMode(), m_paintPixmapXPosition);
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
	// pitch-preserving algorithm -- the user switches into the mode and
	// then drags an edge to actually stretch.
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
