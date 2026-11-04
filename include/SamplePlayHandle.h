
/*
 * SamplePlayHandle.h - play-handle for playing a sample
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

#ifndef LMMS_SAMPLE_PLAY_HANDLE_H
#define LMMS_SAMPLE_PLAY_HANDLE_H

#include <memory>

#include "SampleClip.h"

#include "Sample.h"
#include "PlayHandle.h"

namespace lmms
{


class PatternTrack;
class SampleClip;
class Track;


class LMMS_EXPORT SamplePlayHandle : public PlayHandle
{
public:
	SamplePlayHandle(Sample* sample, bool ownAudioBusHandle = true);
	SamplePlayHandle( const QString& sampleFile );

	/**
	 * @brief Play a sample clip according to a pre-computed playback plan.
	 *
	 * The plan comes from @c SampleClip::computePlaybackPlan, which SampleTrack
	 * resolves from the timeline position playback started at. This handle
	 * therefore never derives a position, a length or a rate on its own: it
	 * plays exactly the buffer, frame range, rate and duration it was handed, so
	 * a fresh start at a timeline position produces the same audio as
	 * uninterrupted playback reaching that position.
	 */
	SamplePlayHandle( SampleClip* clip, const SampleClip::PlaybackPlan& plan );
	~SamplePlayHandle() override;

	// The clip this handle plays, if any. Used to read the live stretch ratio
	// and pitch mode so the handle can adapt to clip length changes on the fly.
	auto clip() const -> SampleClip* { return m_clip; }

	inline bool affinityMatters() const override
	{
		return true;
	}


	void play( SampleFrame* buffer ) override;
	bool isFinished() const override;

	bool isFromTrack( const Track * _track ) const override;

	f_cnt_t totalFrames() const;
	inline f_cnt_t framesDone() const
	{
		return( m_frame );
	}
	void setDoneMayReturnTrue( bool _enable )
	{
		m_doneMayReturnTrue = _enable;
	}

	void setPatternTrack(PatternTrack* pt)
	{
		m_patternTrack = pt;
	}

private:
	Sample::PlaybackState m_state;
	f_cnt_t m_frame = 0;
	Sample* m_sample = nullptr;
	SampleClip* m_clip = nullptr;
	// The buffer this handle actually reads: a private copy of either the clip's
	// stretched sample (Stretch mode) or the clip's original sample, with the
	// plan's frame range applied. Owning it keeps the buffer alive for the whole
	// life of the handle, lets the real-time play() callback run without touching
	// the clip or taking a lock, and keeps this handle's frame positions private
	// so two handles -- or two clips sharing one source file -- can never
	// disturb each other's playback position.
	std::shared_ptr<Sample> m_source;
	// Playback ratio applied on top of the sample-rate conversion; 1.0 when
	// playing a pre-stretched buffer or when no clip is attached.
	double m_playbackRatio = 1.0;
	// Total engine frames this handle renders, taken from the plan so
	// isFinished() stays consistent with play() even if the clip is resized
	// mid-playback (the next clip trigger creates a new handle with a new plan).
	f_cnt_t m_totalFrames = 0;
	Track* m_track = nullptr;
	PatternTrack* m_patternTrack = nullptr;
	bool m_doneMayReturnTrue = true;
	bool m_ownAudioBusHandle = false;
} ;


} // namespace lmms

#endif // LMMS_SAMPLE_PLAY_HANDLE_H
