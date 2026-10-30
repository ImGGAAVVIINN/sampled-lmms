/*
 * SampleClip.cpp
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
 
#include "SampleClip.h"

#include <atomic>

#include <QDomElement>
#include <QFileInfo>

#include "PatternStore.h"
#include "PathUtil.h"
#include "SampleClipView.h"
#include "SampleStretch.h"
#include "SampleTrack.h"
#include "Song.h"

namespace lmms
{

SampleClip::SampleClip(Track* _track, Sample sample, bool isPlaying):
	Clip(_track),
	m_sample(std::move(sample)),
	m_isPlaying(false),
	m_startFrameOffset(0)
{
	saveJournallingState( false );
	setSampleFile( "" );
	restoreJournallingState();

	// we need to receive bpm-change-events, because then we have to
	// change length of this Clip
	connect(Engine::getSong(), &Song::tempoChanged, this, &SampleClip::tempoChanged, Qt::DirectConnection);
	connect(Engine::getSong(), &Song::timeSignatureChanged, this, &SampleClip::updateLength);

	//playbutton clicked or space key / on Export Song set isPlaying to false
	connect( Engine::getSong(), SIGNAL(playbackStateChanged()),
			this, SLOT(playbackPositionChanged()), Qt::DirectConnection );
	//care about loops and jumps
	connect(Engine::getSong(), &Song::playbackPositionJumped,
			this, &SampleClip::playbackPositionChanged, Qt::DirectConnection);
	//care about mute Clips
	connect( this, SIGNAL(dataChanged()), this, SLOT(playbackPositionChanged()));
	//care about mute track
	connect( getTrack()->getMutedModel(), SIGNAL(dataChanged()),
			this, SLOT(playbackPositionChanged()), Qt::DirectConnection );
	//care about Clip position
	connect( this, SIGNAL(positionChanged()), this, SLOT(updateTrackClips()));

	connect( &SampleStretchManager::instance(), &SampleStretchManager::resultReady,
		this, &SampleClip::commitStretchedSample );

	updateTrackClips();
}

SampleClip::SampleClip(Track* track)
	: SampleClip(track, Sample(), false)
{
}

SampleClip::SampleClip(const SampleClip& orig) :
	Clip(orig),
	m_sample(std::move(orig.m_sample)),
	m_isPlaying(orig.m_isPlaying),
	m_startFrameOffset(orig.m_startFrameOffset)
{
	saveJournallingState( false );
	setSampleFile( "" );
	restoreJournallingState();

	// we need to receive bpm-change-events, because then we have to
	// change length of this Clip
	connect(Engine::getSong(), &Song::tempoChanged, this, &SampleClip::tempoChanged, Qt::DirectConnection);
	connect( Engine::getSong(), SIGNAL(timeSignatureChanged(int,int)),
					this, SLOT(updateLength()));

	//playbutton clicked or space key / on Export Song set isPlaying to false
	connect( Engine::getSong(), SIGNAL(playbackStateChanged()),
			this, SLOT(playbackPositionChanged()), Qt::DirectConnection );
	//care about loops and jumps
	connect(Engine::getSong(), &Song::playbackPositionJumped,
			this, &SampleClip::playbackPositionChanged, Qt::DirectConnection);
	//care about mute Clips
	connect( this, SIGNAL(dataChanged()), this, SLOT(playbackPositionChanged()));
	//care about mute track
	connect( getTrack()->getMutedModel(), SIGNAL(dataChanged()),
			this, SLOT(playbackPositionChanged()), Qt::DirectConnection );
	//care about Clip position
	connect( this, SIGNAL(positionChanged()), this, SLOT(updateTrackClips()));

	connect( &SampleStretchManager::instance(), &SampleStretchManager::resultReady,
		this, &SampleClip::commitStretchedSample );

	updateTrackClips();
}




SampleClip::~SampleClip()
{
	auto sampletrack = dynamic_cast<SampleTrack*>(getTrack());
	if ( sampletrack )
	{
		sampletrack->updateClips();
	}
}




void SampleClip::changeLength( const TimePos & _length )
{
	Clip::changeLength(std::max(static_cast<int>(_length), 1));
	// The stretch ratio is derived from the clip length, so a length change
	// (drag, auto-resize, tempo change, ...) may require a new stretched
	// buffer. This is a no-op unless the clip is in Stretch mode and stretched.
	refreshStretchBuffer();
}



const QString& SampleClip::sampleFile() const
{
	return m_sample.sampleFile();
}

bool SampleClip::hasSampleFileLoaded(const QString & filename) const
{
	return m_sample.sampleFile() == filename;
}

void SampleClip::setSampleBuffer(std::shared_ptr<const SampleBuffer> sb)
{
	{
		const auto guard = Engine::audioEngine()->requestChangesGuard();
		m_sample = Sample(std::move(sb));
	}
	updateLength();

	emit sampleChanged();

	Engine::getSong()->setModified();
	refreshStretchBuffer();
}

void SampleClip::setSampleFile(const QString& sf)
{
	// Remove any prior offset in the clip
	setStartTimeOffset(0);
	if (!sf.isEmpty())
	{
		m_sample = Sample(SampleBuffer::fromFile(sf));
		updateLength();
	}
	else
	{
		// If there is no sample, make the clip a bar long
		float nom = Engine::getSong()->getTimeSigModel().getNumerator();
		float den = Engine::getSong()->getTimeSigModel().getDenominator();
		changeLength(DefaultTicksPerBar * (nom / den));
	}

	emit sampleChanged();
	emit playbackPositionChanged();
	refreshStretchBuffer();
}




void SampleClip::toggleRecord()
{
	m_recordModel.setValue( !m_recordModel.value() );
	emit dataChanged();
}




void SampleClip::playbackPositionChanged()
{
	Engine::audioEngine()->removePlayHandlesOfTypes( getTrack(), PlayHandle::Type::SamplePlayHandle );
	auto st = dynamic_cast<SampleTrack*>(getTrack());
	st->setPlayingClips( false );
}




void SampleClip::updateTrackClips()
{
	auto sampletrack = dynamic_cast<SampleTrack*>(getTrack());
	if( sampletrack)
	{
		sampletrack->updateClips();
	}
}




bool SampleClip::isPlaying() const
{
	return m_isPlaying;
}




void SampleClip::setIsPlaying(bool isPlaying)
{
	m_isPlaying = isPlaying;
}




void SampleClip::updateLength()
{
	// If the clip has already been manually resized, don't automatically resize it.
	if (getAutoResize())
	{
		if (getTrack()->trackContainer() == Engine::patternStore())
		{
			changeLength(TimePos::ticksPerBar() * Engine::patternStore()->lengthOfPattern(getTrack()->getClipNum(this)));
			return;
		}
		changeLength(sampleLength());
		setStartTimeOffset(0);
	}

	emit sampleChanged();
}


void SampleClip::tempoChanged()
{
	Clip::setStartTimeOffset(std::round(1.0f * m_startFrameOffset / Engine::framesPerTick()));
	updateLength();
	emit sampleChanged();
}

void SampleClip::setStartTimeOffset(const TimePos& startTimeOffset)
{
	m_startFrameOffset = startTimeOffset * Engine::framesPerTick();
	Clip::setStartTimeOffset(startTimeOffset);
}


TimePos SampleClip::sampleLength() const
{
	return static_cast<int>(m_sample.sampleSize() / Engine::framesPerTick(m_sample.sampleRate()));
}




void SampleClip::setSampleStartFrame(f_cnt_t startFrame)
{
	m_sample.setStartFrame(startFrame);
}




void SampleClip::setSamplePlayLength(f_cnt_t length)
{
	m_sample.setEndFrame(length);
}

uint64_t SampleClip::currentStretchKey() const
{
	// Key of the stretched buffer the clip's *current* parameters call for,
	// or 0 when no stretching applies (Resample mode, ratio 1.0, reversed
	// sample, or no sample at all).
	if (m_pitchMode != PitchMode::Stretch || !isStretched() || m_sample.reversed())
	{
		return 0;
	}
	const auto buffer = m_sample.buffer();
	if (!buffer || buffer->empty()) { return 0; }

	return SampleStretch::cacheKey(
		buffer.get(),
		0,
		static_cast<int>(buffer->size()),
		buffer->sampleRate(),
		Engine::audioEngine()->outputSampleRate(),
		stretchRatio());
}

uint64_t SampleClip::bumpStretchGeneration()
{
	// The manager broadcasts every result to every clip, so a plain per-clip
	// counter would let one clip accept another clip's result. Combine a
	// per-clip id (high bits) with a per-request sequence (low bits).
	if (m_stretchId == 0)
	{
		static auto s_nextStretchId = std::atomic<uint64_t>{1};
		m_stretchId = s_nextStretchId.fetch_add(1, std::memory_order_relaxed);
	}
	m_stretchGeneration = (m_stretchId << 32) | (++m_stretchSequence & 0xffffffffu);
	return m_stretchGeneration;
}

void SampleClip::refreshStretchBuffer()
{
	// The heavy time-stretch work must never run on the real-time audio thread,
	// so it is delegated to the stretch worker thread. This function only
	// decides *whether* a new stretched sample is needed and queues the job.
	const auto clearStretched = [this]()
	{
		{
			const auto locker = QMutexLocker{&m_stretchMutex};
			m_stretchedSample.reset();
			m_stretchCacheKey = 0;
			m_stretchPendingKey = 0;
		}
		bumpStretchGeneration(); // invalidate any in-flight result
	};

	if (m_pitchMode != PitchMode::Stretch || !isStretched() || m_sample.reversed())
	{
		// Resample mode, ratio == 1.0, or a reversed sample: bypass stretch
		// processing entirely and use the original playback path.
		clearStretched();
		return;
	}

	const auto buffer = m_sample.buffer();
	if (!buffer || buffer->empty())
	{
		clearStretched();
		return;
	}

	// Always stretch the full source range so that a mid-clip seek or a
	// left-edge trim can be mapped into stretched-buffer coordinates at
	// handle-creation time, no matter which subrange happened to be active
	// when this request was made. The source buffer itself is never modified.
	const auto engineRate = Engine::audioEngine()->outputSampleRate();
	const auto key = currentStretchKey();

	{
		const auto locker = QMutexLocker{&m_stretchMutex};
		if ((key == m_stretchCacheKey && m_stretchedSample) || key == m_stretchPendingKey)
		{
			return; // cached result still valid, or an identical job is in flight
		}
	}

	const auto generation = bumpStretchGeneration();
	{
		const auto locker = QMutexLocker{&m_stretchMutex};
		m_stretchPendingKey = key;
	}
	SampleStretchManager::instance().request(
		this,
		generation,
		key,
		buffer,
		0,
		static_cast<int>(buffer->size()),
		buffer->sampleRate(),
		engineRate,
		stretchRatio());
}

void SampleClip::commitStretchedSample(uint64_t generation, uint64_t key, std::shared_ptr<Sample> stretched)
{
	// Runs on the GUI thread (queued connection). Discard stale results from
	// requests that were superseded while the worker was busy.
	if (generation != m_stretchGeneration) { return; }

	// Serialise against audio rendering so the real-time thread never observes
	// a half-swapped buffer. This blocks until the current period is done.
	const auto guard = Engine::audioEngine()->requestChangesGuard();
	{
		const auto locker = QMutexLocker{&m_stretchMutex};
		m_stretchedSample = std::move(stretched);
		m_stretchCacheKey = m_stretchedSample ? key : 0;
		if (m_stretchPendingKey == key) { m_stretchPendingKey = 0; }
	}

	emit sampleChanged();
}

std::shared_ptr<Sample> SampleClip::stretchedSample() const
{
	// Only hand out the stretched buffer while it still matches the clip's
	// current parameters. As soon as the clip is resized (or the sample is
	// swapped) the cached result is stale, and callers must fall back to the
	// original resampling path so the rendered duration keeps following the
	// clip length instead of the outdated buffer.
	const auto locker = QMutexLocker{&m_stretchMutex};
	if (!m_stretchedSample || m_stretchCacheKey != currentStretchKey())
	{
		return nullptr;
	}
	return m_stretchedSample;
}

bool SampleClip::hasStretchedSample() const
{
	return stretchedSample() != nullptr;
}

void SampleClip::setPitchMode(PitchMode mode)
{
	if (m_pitchMode == mode) { return; } // selecting the active mode does nothing
	m_pitchMode = mode;
	// The mode switch never changes the clip's length; it only changes how the
	// sample is rendered for the current length.
	refreshStretchBuffer();
	emit sampleChanged();
	Engine::getSong()->setModified();
}

double SampleClip::stretchRatio() const
{
	const auto len = length();
	const auto sl = sampleLength();
	if (sl <= 0 || len <= 0) return 1.0;
	return static_cast<double>(len) / static_cast<double>(sl);
}

bool SampleClip::isStretched() const
{
	return std::abs(stretchRatio() - 1.0) > 0.005;
}




void SampleClip::saveSettings( QDomDocument & _doc, QDomElement & _this )
{
	if( _this.parentNode().nodeName() == "clipboard" )
	{
		_this.setAttribute( "pos", -1 );
	}
	else
	{
		_this.setAttribute( "pos", startPosition() );
	}
	_this.setAttribute( "len", length() );
	_this.setAttribute( "muted", isMuted() );
	_this.setAttribute( "src", sampleFile() );
	_this.setAttribute( "off", startTimeOffset() );
	_this.setAttribute("autoresize", QString::number(getAutoResize()));
	if( sampleFile() == "" )
	{
		QString s;
		_this.setAttribute("data", m_sample.toBase64());
	}

	_this.setAttribute( "sample_rate", m_sample.sampleRate());
	if (const auto& c = color())
	{
		_this.setAttribute("color", c->name());
	}
	if (m_sample.reversed())
	{
		_this.setAttribute("reversed", "true");
	}
	_this.setAttribute("stretchmode", static_cast<int>(m_pitchMode));
	// TODO: start- and end-frame
}




void SampleClip::loadSettings( const QDomElement & _this )
{
	if( _this.attribute( "pos" ).toInt() >= 0 )
	{
		movePosition( _this.attribute( "pos" ).toInt() );
	}

	if (const auto srcFile = _this.attribute("src"); !srcFile.isEmpty())
	{
		if (QFileInfo(PathUtil::toAbsolute(srcFile)).exists())
		{
			setSampleFile(srcFile);
		}
		else { Engine::getSong()->collectError(QString("%1: %2").arg(tr("Sample not found"), srcFile)); }
	}

	if( sampleFile().isEmpty() && _this.hasAttribute( "data" ) )
	{
		auto sampleRate = _this.hasAttribute("sample_rate") ? _this.attribute("sample_rate").toInt() :
			Engine::audioEngine()->outputSampleRate();

		auto buffer = SampleBuffer::fromBase64(_this.attribute("data"), sampleRate);
		m_sample = Sample(std::move(buffer));
	}
	changeLength( _this.attribute( "len" ).toInt() );
	setMuted( _this.attribute( "muted" ).toInt() );
	setStartTimeOffset( _this.attribute( "off" ).toInt() );
	setAutoResize(_this.attribute("autoresize", "1").toInt());

	if (_this.hasAttribute("color"))
	{
		setColor(QColor{_this.attribute("color")});
	}

	if(_this.hasAttribute("reversed"))
	{
		m_sample.setReversed(true);
		emit wasReversed(); // tell SampleClipView to update the view
	}
	if (_this.hasAttribute("stretchmode"))
	{
		m_pitchMode = static_cast<PitchMode>(_this.attribute("stretchmode").toInt());
	}
	// missing attribute => old projects keep Resample (existing playback path)

	// The clip length was restored above, possibly before the pitch mode was
	// known, so queue the stretched buffer now if the project asked for Stretch
	// mode. No-op for Resample mode and whenever the ratio is 1.0.
	refreshStretchBuffer();
}




gui::ClipView * SampleClip::createView( gui::TrackView * _tv )
{
	return new gui::SampleClipView( this, _tv );
}


} // namespace lmms
