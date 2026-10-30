/*
 * SamplePlayHandle.cpp - implementation of class SamplePlayHandle
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

#include "SamplePlayHandle.h"

#include <algorithm>
#include <cmath>

#include "AudioEngine.h"
#include "AudioBusHandle.h"
#include "Engine.h"
#include "PatternTrack.h"
#include "SampleClip.h"
#include "SampleTrack.h"

namespace lmms
{

SamplePlayHandle::SamplePlayHandle(Sample* sample, bool ownAudioBusHandle)
	: PlayHandle(Type::SamplePlayHandle)
	, m_sample(sample)
	, m_ownAudioBusHandle(ownAudioBusHandle)
{
	if (ownAudioBusHandle)
	{
		setAudioBusHandle(new AudioBusHandle("SamplePlayHandle", false));
	}
}




SamplePlayHandle::SamplePlayHandle( const QString& sampleFile ) :
	SamplePlayHandle(new Sample(SampleBuffer::fromFile(sampleFile)), true)
{
}




SamplePlayHandle::SamplePlayHandle( SampleClip* clip ) :
	SamplePlayHandle(&clip->sample(), false)
{
	m_clip = clip;
	m_track = clip->getTrack();
	setAudioBusHandle(((SampleTrack *)clip->getTrack())->audioBusHandle());

	// Decide the playback strategy once, when this handle is created (GUI /
	// rendering thread), so the real-time play() callback below never has to
	// query the clip, take a lock, or allocate.
	//
	// - Stretch mode with a ready stretched buffer: play the pre-stretched
	// buffer at ratio 1.0 (pitch preserved, duration follows the clip).
	// - Otherwise (Resample mode, or Stretch mode while the stretched buffer
	// is still being computed or unavailable): play the original sample with
	// a playback ratio so its duration matches the clip's duration. This is
	// the traditional resampling behaviour where speed and pitch change
	// together.
	if (clip->pitchMode() == SampleClip::PitchMode::Stretch)
	{
		if (const auto stretched = clip->stretchedSample(); stretched != nullptr)
		{
			// Take our own copy of the (cheap, buffer-sharing) Sample wrapper
			// so the frame positions below are private to this handle and can
			// never interfere with another handle playing the same clip.
			m_stretchedSample = std::make_shared<Sample>(*stretched);

			// SampleTrack::play() positioned the original sample within its
			// buffer before creating this handle (this maps a mid-clip seek or
			// a left-edge trim to a source offset). The stretched buffer holds
			// the same source subrange stretched by the ratio, so map the
			// source offset into stretched-buffer coordinates.
			const auto ratio = clip->stretchRatio();
			const auto stretchedStart = static_cast<int>(
				std::lround(m_sample->startFrame() * ratio));
			const auto stretchedSize = static_cast<int>(m_stretchedSample->sampleSize());
			m_stretchedSample->setStartFrame(std::clamp(stretchedStart, 0, std::max(stretchedSize - 1, 0)));
			m_stretchedSample->setEndFrame(stretchedSize);
		}
	}

	if (!m_stretchedSample)
	{
		const auto ratio = clip->stretchRatio();
		// A clip longer than the sample plays it back slower (ratio < 1);
		// a shorter clip plays it back faster (ratio > 1).
		m_playbackRatio = ratio > 0.0 ? 1.0 / ratio : 1.0;
	}

	const auto* source = m_stretchedSample ? m_stretchedSample.get() : m_sample;
	const auto frames = (source->endFrame() - source->startFrame())
		* (static_cast<double>(Engine::audioEngine()->outputSampleRate()) / source->sampleRate());
	m_totalFrames = static_cast<f_cnt_t>(frames / m_playbackRatio);
}




SamplePlayHandle::~SamplePlayHandle()
{
	if(m_ownAudioBusHandle)
	{
		delete audioBusHandle();
		delete m_sample;
	}
}




void SamplePlayHandle::play( SampleFrame* buffer )
{
	const f_cnt_t fpp = Engine::audioEngine()->framesPerPeriod();
	//play( 0, _try_parallelizing );
	if( framesDone() >= totalFrames() )
	{
		zeroSampleFrames(buffer, fpp);
		return;
	}

	SampleFrame* workingBuffer = buffer;
	f_cnt_t frames = fpp;

	// apply offset for the first period
	if( framesDone() == 0 )
	{
		zeroSampleFrames(buffer, offset());
		workingBuffer += offset();
		frames -= offset();
	}

	if( !( m_track && m_track->isMuted() )
				&& !(m_patternTrack && m_patternTrack->isMuted()))
	{
		// In Stretch mode we play the pre-computed stretched buffer at its
		// original rate (pitch preserved); otherwise we play the original
		// sample with the clip's playback ratio (Resample mode), which is
		// 1.0 for previews, SampleTracks previews and the metronome.
		const auto* source = m_stretchedSample ? m_stretchedSample.get() : m_sample;
		if (!source->play(workingBuffer, &m_state, frames, Sample::Loop::Off, m_playbackRatio))
		{
			zeroSampleFrames(workingBuffer, frames);
		}
	}

	m_frame += frames;
}




bool SamplePlayHandle::isFinished() const
{
	return framesDone() >= totalFrames() && m_doneMayReturnTrue == true;
}




bool SamplePlayHandle::isFromTrack( const Track * _track ) const
{
	return m_track == _track || m_patternTrack == _track;
}




f_cnt_t SamplePlayHandle::totalFrames() const
{
	// For clip-backed handles this is computed once at construction so that it
	// stays consistent with the ratio used by play() even if the clip is
	// resized mid-playback (the next clip trigger creates a new handle).
	// For preview/metronome handles m_totalFrames is computed lazily here.
	if (m_clip) { return m_totalFrames; }
	return (m_sample->endFrame() - m_sample->startFrame()) *
			(static_cast<float>(Engine::audioEngine()->outputSampleRate()) / m_sample->sampleRate());
}


} // namespace lmms
