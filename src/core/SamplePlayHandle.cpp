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




SamplePlayHandle::SamplePlayHandle( SampleClip* clip, const SampleClip::PlaybackPlan& plan ) :
	SamplePlayHandle(&clip->sample(), false)
{
	m_clip = clip;
	m_track = clip->getTrack();
	setAudioBusHandle(((SampleTrack *)clip->getTrack())->audioBusHandle());

	// Everything that decides *what* is played -- which buffer, which frames of
	// it, at which rate and for how long -- was resolved by
	// SampleClip::computePlaybackPlan from the timeline position playback started
	// at. This constructor only applies that decision, so the mapping exists in
	// exactly one place and a fresh start here lands on the same audio that
	// uninterrupted playback would have reached.
	//
	// The buffers are copied into `m_source` (a cheap, buffer-sharing Sample
	// wrapper) so the frame range below belongs to this handle alone: two
	// handles, or two clips sharing one source file, can never move each other's
	// playback position, and the real-time play() callback below reads no clip
	// state and takes no lock.
	const auto* source = plan.stretchedSource ? plan.stretchedSource.get() : &clip->sample();
	m_source = std::make_shared<Sample>(*source);
	m_source->setStartFrame(plan.startFrame);
	m_source->setEndFrame(plan.endFrame);
	// Sample::play() reads its position from the playback state, not from the
	// sample, so the seek has to be seeded there.
	m_state.setFrameIndex(plan.startFrame);
	m_state.setBackwards(false);

	// 1.0 when a pre-stretched buffer is played (it is already at the engine
	// rate and already has the clip's duration); the clip's ratio otherwise,
	// which is what makes the source last exactly as long as the clip does.
	m_playbackRatio = plan.resampleRatio;
	m_totalFrames = static_cast<f_cnt_t>(std::lround(plan.totalOutputFrames));
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
		// Clip-backed handles play `m_source`, the buffer and frame range the
		// playback plan selected: a pre-stretched buffer at its own rate (Stretch
		// mode) or the original sample resampled by the clip's ratio (Resample
		// mode). Preview and metronome handles have no plan and play `m_sample`
		// unmodified.
		const auto* source = m_source ? m_source.get() : m_sample;
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
