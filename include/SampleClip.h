/*
 * SampleClip.h
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

#ifndef LMMS_SAMPLE_CLIP_H
#define LMMS_SAMPLE_CLIP_H

#include <cstdint>
#include <memory>

#include <QMutex>

#include "Clip.h"
#include "Sample.h"

namespace lmms
{

class SampleBuffer;

namespace gui
{

class SampleClipView;

} // namespace gui


class SampleClip : public Clip
{
	Q_OBJECT
	mapPropertyFromModel(bool,isRecord,setRecord,m_recordModel);
public:
	enum class PitchMode
	{
		Resample,
		Stretch
	};
	SampleClip(Track* track, Sample sample, bool isPlaying);
	SampleClip(Track* track);
	~SampleClip() override;

	SampleClip& operator=( const SampleClip& that ) = delete;

	void changeLength( const TimePos & _length ) override;
	void updateLength() override;

	const QString& sampleFile() const;
	bool hasSampleFileLoaded(const QString & filename) const;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "sampleclip";
	}

	Sample& sample()
	{
		return m_sample;
	}

	TimePos sampleLength() const;
	void setSampleStartFrame( f_cnt_t startFrame );
	void setSamplePlayLength( f_cnt_t length );
	void setStartTimeOffset(const TimePos& startTimeOffset) override;
	gui::ClipView * createView( gui::TrackView * _tv ) override;


	bool isPlaying() const;
	void setIsPlaying(bool isPlaying);
	void setSampleBuffer(std::shared_ptr<const SampleBuffer> sb);

	auto pitchMode() const -> PitchMode { return m_pitchMode; }
	void setPitchMode(PitchMode mode);

	auto stretchRatio() const -> double;
	auto isStretched() const -> bool;

	/**
	 * @brief Recompute (asynchronously) the time-stretched sample used by
	 * Stretch pitch mode.
	 *
	 * Does nothing unless the clip is in Stretch mode and actually stretched
	 * (ratio != 1.0). At ratio 1.0 -- and whenever the cached result still
	 * matches the current parameters -- no processing happens at all, so the
	 * original playback path is used unchanged.
	 */
	void refreshStretchBuffer();

	auto stretchedSample() const -> std::shared_ptr<Sample>;
	auto hasStretchedSample() const -> bool;

	SampleClip* clone() override
	{
		return new SampleClip(*this);
	}

public slots:
	void setSampleFile(const QString& sf);
	void toggleRecord();
	void playbackPositionChanged();
	void updateTrackClips();
	void tempoChanged();

private slots:
	/// Commit an asynchronously computed stretch result (GUI thread). Results
	/// whose generation no longer matches are discarded, so stale results from
	/// superseded requests -- and results that belong to a *different* clip,
	/// to which the manager also broadcasts the result -- are never applied.
	void commitStretchedSample(uint64_t generation, uint64_t key, std::shared_ptr<Sample> stretched);

protected:
	SampleClip( const SampleClip& orig );

private:
	/// Cache key of the stretched buffer the clip's *current* parameters call
	/// for, or 0 when no stretching applies (Resample mode, ratio 1.0, reversed
	/// sample, or no sample at all).
	uint64_t currentStretchKey() const;

	/// Mint the next stretch generation id. The manager broadcasts every
	/// result to every clip, so ids must be unique across clips: the high
	/// half identifies this clip, the low half counts its requests.
	uint64_t bumpStretchGeneration();

	Sample m_sample;
	BoolModel m_recordModel;
	bool m_isPlaying;
	int m_startFrameOffset;
	PitchMode m_pitchMode = PitchMode::Resample;
	// The stretched sample is computed off-thread and swapped in under
	// m_stretchMutex. The real-time thread only ever takes this mutex for the
	// duration of a shared_ptr copy, and commits from the GUI thread are
	// serialised against audio rendering via the audio engine's change lock.
	mutable QMutex m_stretchMutex;
	std::shared_ptr<Sample> m_stretchedSample;
	uint64_t m_stretchCacheKey = 0;
	uint64_t m_stretchPendingKey = 0;
	uint64_t m_stretchId = 0;
	uint64_t m_stretchSequence = 0;
	uint64_t m_stretchGeneration = 0;

	friend class gui::SampleClipView;


signals:
	void sampleChanged();
	void wasReversed();
} ;


} // namespace lmms

#endif // LMMS_SAMPLE_CLIP_H
