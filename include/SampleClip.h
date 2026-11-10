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

#include <cmath>
#include <cstdint>
#include <memory>

#include <QMutex>

#include "Clip.h"
#include "Sample.h"
#include "SampleStretch.h"

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

	/**
	 * @brief The clip's explicit stretch ratio.
	 *
	 * `ratio = audible clip duration / natural duration of the selected source
	 * range`. The ratio is *stored state*, never derived from the clip length:
	 * ordinary trimming changes the clip length and the source range but leaves
	 * the ratio (and therefore the playback speed and pitch) untouched, while
	 * stretching changes the ratio. A ratio of 2.0 means the selected audio is
	 * made to last twice as long; 0.5 means half as long.
	 */
	auto stretchRatio() const -> double { return m_stretchRatio; }
	auto isStretched() const -> bool
	{
		return std::abs(m_stretchRatio - 1.0) > 0.0001;
	}

	//! @brief First source frame the clip plays (inclusive).
	auto sourceStartFrame() const -> int { return m_sourceStartFrame; }
	//! @brief One past the last source frame the clip plays. Clamped to the
	//! buffer so callers never have to care whether the buffer shrank.
	auto sourceEndFrame() const -> int;
	//! @brief The whole playable source range, in timeline ticks at ratio 1.
	auto sourceRangeTicks() const -> double;


	/**
	 * @brief Ordinary right-edge trim: keep the playback speed (ratio) and the
	 * source start untouched, move the clip's right edge to @a newLength and
	 * shorten the playable source range so the retained audio keeps playing at
	 * its original speed. Audio past the new end is cut, never compressed.
	 */
	void trimToLength(const TimePos& newLength);

	/**
	 * @brief Ordinary left-edge trim/extend: the clip's right edge stays put.
	 *
	 * Trimming (moving the left edge right) discards the skipped audio -- the
	 * source start advances and the remaining audio keeps its original speed.
	 * Extending (moving the left edge left) first restores previously trimmed
	 * audio, then prepends silence. The playback speed never changes.
	 */
	void trimFromStart(const TimePos& newPos);

	/**
	 * @brief Pitch-preserving right-edge stretch: the whole selected source
	 * range is time-stretched to fill the clip's new length. The source range
	 * is untouched; only the ratio changes.
	 */
	void stretchToLength(const TimePos& newLength);

	/**
	 * @brief Pitch-preserving left-edge stretch: the clip's right edge stays
	 * put, the whole selected source range is re-stretched to fill the new
	 * length. No audio is discarded -- the source range is untouched.
	 */
	void stretchFromStart(const TimePos& newPos);

	//! @brief True when the clip is in Stretch mode but the build lacks a
	//! pitch-preserving algorithm (no SoundTouch), so stretching is degraded.
	auto stretchUnavailable() const -> bool;

	/**
	 * @brief Number of source frames per timeline tick for this clip's sample.
	 *
	 * Sample lengths are stored in the sample's own frames, so converting
	 * between timeline ticks and source frames must use the sample rate, not
	 * the engine's output rate. Every timeline<->source conversion in the
	 * stretch feature goes through this and @c sourceFramesFor /
	 * @c timelineTicksFor.
	 */
	auto sourceFramesPerTick() const -> double;

	/**
	 * @brief Convert a timeline offset to a position in the clip's *output*
	 * (stretched) frame coordinates.
	 *
	 * Output coordinates are frames at the engine's output sample rate, so this
	 * is the coordinate system both playback and the waveform share.
	 */
	auto outputFramesFor(TimePos timelinePos) const -> double;

	/**
	 * @brief Convert a position in the clip's output frame coordinates back to
	 * the corresponding position in the *original source* frame coordinates.
	 *
	 * This is the one and only timeline-to-source mapping used by playback,
	 * seeking and rendering, so uninterrupted playback and a fresh start at the
	 * same timeline position always land on the same source frame:
	 *
	 *     sourceFrame = sourceStartFrame + outputOffset / outputFramesPerSourceFrame
	 *
	 * It is valid for both pitch modes because in Stretch mode the
	 * pre-computed buffer is built from the same source range at the same
	 * ratio, so its frame index corresponds to the same source position.
	 */
	auto sourceFrameAtOutputFrame(double outputFrame) const -> double;

	/**
	 * @brief Number of output (engine-rate) frames per timeline tick.
	 *
	 * @c sourceFramesPerTick uses the sample's own rate; this uses the engine's
	 * output rate. They differ whenever the two rates differ, which is exactly
	 * why every conversion has to say which of the two it means.
	 */
	auto outputFramesPerTick() const -> double;

	/**
	 * @brief Output frames consumed per source frame, i.e. how much of the
	 * clip's output timeline one frame of the original sample is worth.
	 *
	 * `outputFramesPerTick() / sourceFramesPerTick() * stretchRatio()`. At
	 * ratio 1.0 with equal sample and engine rates this is 1.0, meaning the
	 * clip maps 1:1 onto its source exactly as it did before stretching.
	 */
	auto outputFramesPerSourceFrame() const -> double;

	/**
	 * @brief Everything a @c SamplePlayHandle needs in order to play this clip
	 * from one given position.
	 *
	 * Produced only by @c computePlaybackPlan so that the buffer to read, the
	 * frame range within it, the resample ratio and the total length can never
	 * disagree with each other -- they are all derived from the same mapping in
	 * one place.
	 *
	 * In Stretch mode the plan reads the stretched buffer at ratio 1.0 whenever
	 * one is ready for the clip's current parameters; there is deliberately no
	 * fallback to resampling, so a clip in Stretch mode can never silently play
	 * with a changed pitch. While a result is still being computed -- or when
	 * the build has no SoundTouch at all -- the plan plays the original source
	 * at ratio 1.0, which is pitch-correct and merely shorter or longer than
	 * requested until the real result arrives.
	 */
	struct PlaybackPlan
	{
		//! Buffer to read from: the stretched sample in Stretch mode, or
		//! null meaning "use the clip's own sample".
		std::shared_ptr<Sample> stretchedSource;
		//! First frame to read from that buffer.
		int startFrame = 0;
		//! One past the last frame to read.
		int endFrame = 0;
		//! Rate to feed @c Sample::play with; 1.0 when the buffer is already
		//! stretched and is consumed one output frame per output frame.
		double resampleRatio = 1.0;
		//! How many output frames the handle must produce from this plan.
		double totalOutputFrames = 0.0;
	};

	/**
	 * @brief Map the clip's audible output range onto a fraction of a sample.
	 *
	 * The waveform and playback must describe the same operation, so this is the
	 * single place that turns "what is audible between the clip's left and right
	 * edges" into a [start, end) fraction of a sample. The caller passes the
	 * sample to draw -- the stretched buffer in Stretch mode, or the original
	 * source otherwise -- and gets back how much of it to draw, clamped to the
	 * clip's audible range.
	 *
	 * In Resample mode (or any mode that plays the original source) the mapping
	 * goes through @c sourceFrameAtOutputFrame, which is the same mapping
	 * playback uses, so the drawn range is exactly the range the audio thread
	 * reads. In Stretch mode the stretched buffer's frame index *is* the
	 * output-frame coordinate, so the mapping is a plain fraction of its size.
	 *
	 * A left trim (negative start-time offset) is folded in: output frames
	 * before the clip's audible start are skipped, and the returned range never
	 * starts before the source's first playable frame.
	 */
	struct WaveformMapping
	{
		//! Fraction of the sample to start drawing at, clamped to [0, 1].
		float sampleStart = 0.0f;
		//! Fraction of the sample to stop drawing at, clamped to [sampleStart, 1].
		float sampleEnd = 1.0f;
	};

	auto waveformMapping(const Sample& sampleToDraw) const -> WaveformMapping;

	/**
	 * @brief Build the playback plan for this clip starting at
	 * @a startOutputFrame, an offset in output frames from the clip's audible
	 * start (see @c outputFramesFor).
	 *
	 * In Stretch mode the plan reads the stretched buffer, whose frame index is
	 * already the output-frame coordinate, and resamples nothing. In Resample
	 * mode the plan reads the original sample with @c resampleRatio set to the
	 * stretch ratio. Both cases use the same timeline-to-source mapping, so
	 * switching mode does not jump the audio.
	 */
	auto computePlaybackPlan(double startOutputFrame) const -> PlaybackPlan;

	/**
	 * @brief (Re)compute the time-stretched sample the clip's parameters call for.
	 *
	 * Never computes anything itself: the work is handed to
	 * @c SampleStretchManager, whose worker thread does it away from both the
	 * GUI and the real-time audio thread, and the result is committed by
	 * @c applyStretchResult when it comes back. That keeps dragging a clip edge
	 * cheap no matter how long one stretch takes -- the alternative, computing
	 * here, blocked the GUI thread for over a hundred milliseconds per mouse
	 * move and starved playback of new play handles for the duration.
	 *
	 * Requests are coalesced per clip, so a drag that produces one request per
	 * mouse-move ends up computing only the newest parameters. Until that
	 * result lands, playback and the waveform use the degraded path described on
	 * @c computePlaybackPlan; the final representation is the real stretched
	 * buffer either way, so responsiveness is not bought with correctness.
	 *
	 * When the cached result still matches the current parameters nothing is
	 * requested at all, and when the clip's parameters call for no stretching
	 * (Resample mode, ratio 1.0, reversed or missing sample) the cached buffer
	 * is dropped synchronously.
	 */
	void refreshStretchBuffer();

	/**
	 * @brief Hold off on asking the manager for stretched buffers.
	 *
	 * Dragging a clip edge changes everything a stretched buffer depends on --
	 * the source range and the ratio -- on every single mouse-move. Left to
	 * itself each of those changes would hand the worker thread a new job, so
	 * the audio would start being processed, and the progress dialog would
	 * appear, while the mouse button is still held down.
	 *
	 * A drag therefore calls @ref beginStretchRequestBatch on press and
	 * @ref endStretchRequestBatch on release. The model edits still happen live
	 * -- the clip resizes and its length label follows the pointer -- but the
	 * expensive processing, and the popup that reports it, happens exactly once,
	 * for the parameters the drag ended on. That makes the mouse release the
	 * commit point for audio processing, which is also what makes the *final*
	 * dragged length the processing target instead of some intermediate one.
	 *
	 * A press without a drag never reaches the move handler, so nothing is owed
	 * and releasing asks for no work at all.
	 */
	void beginStretchRequestBatch();

	/// @brief Leave batch mode, issuing the one request the batch left owed.
	/// If the parameters ended up back on a stretched buffer that is already
	/// cached, `refreshStretchBuffer` re-checks the cache and nothing is asked
	/// for at all.
	void endStretchRequestBatch();

	/// @brief True between @ref beginStretchRequestBatch and
	/// @ref endStretchRequestBatch. Lets a caller make sure a batch is never
	/// left open.
	auto isBatchingStretchRequests() const -> bool { return m_batchStretchRequests; }

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

protected:
	SampleClip( const SampleClip& orig );

private:
	/// Cache key of the stretched buffer the clip's *current* parameters call
	/// for, or 0 when no stretching applies (Resample mode, ratio 1.0, reversed
	/// sample, or no sample at all).
	uint64_t currentStretchKey() const;

	/// Fold a negative start-time offset (left trim) into the source range so
	/// a following stretch derives its ratio from the audible audio only.
	void materialiseAudibleRange();

	/// Commit a stretched sample computed off-thread, provided it is still the
	/// one the clip's current parameters call for. Results from a superseded
	/// request -- typically an earlier position of an in-progress drag -- are
	/// discarded, so an old, longer computation can never overwrite a newer one.
	void applyStretchResult(uint64_t generation, uint64_t key,
		std::shared_ptr<Sample> stretched);

	/// Create this clip's stretch delivery receiver and hook it up. Called from
	/// every constructor, since a clip can request work at any point.
	void setupStretchDelivery();

	Sample m_sample;
	BoolModel m_recordModel;
	bool m_isPlaying;
	int m_startFrameOffset;
	PitchMode m_pitchMode = PitchMode::Resample;
	// The playable subrange of the original source. Trimming moves these;
	// stretching never does. Repeated stretching always re-derives its result
	// from this *original* range, never from a previously stretched buffer.
	int m_sourceStartFrame = 0;
	int m_sourceEndFrame = 0;
	// Explicit stretch ratio (1.0 = original speed). Stored state, never
	// derived from the clip length, so trimming cannot change the speed.
	double m_stretchRatio = 1.0;
	// Stretched samples are computed on the manager's worker thread and
	// delivered through m_stretchResult, a child of this clip so that results
	// for a clip that is gone are dropped. m_stretchGeneration identifies the
	// newest request: a result carrying any other generation is stale and is
	// ignored, which is what keeps a slow earlier computation from replacing a
	// fast newer one. The real-time thread only ever takes m_stretchMutex for
	// the duration of a shared_ptr copy, and swaps from the GUI thread are
	// serialised against audio rendering via the audio engine's change lock.
	SampleStretchResult* m_stretchResult = nullptr;
	uint64_t m_stretchGeneration = 0;
	// Batch mode entered by a clip-edge drag: refreshStretchBuffer() records
	// that work is owed instead of queueing it, so the drag itself never starts
	// a computation (see beginStretchRequestBatch).
	bool m_batchStretchRequests = false;
	bool m_stretchRequestOwed = false;
	mutable QMutex m_stretchMutex;
	std::shared_ptr<Sample> m_stretchedSample;
	uint64_t m_stretchCacheKey = 0;

	friend class gui::SampleClipView;


signals:
	void sampleChanged();
	void wasReversed();
} ;


} // namespace lmms

#endif // LMMS_SAMPLE_CLIP_H
