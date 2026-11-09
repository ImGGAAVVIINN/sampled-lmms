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
#include "StretchDebug.h"

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
	// Before anything that could request stretch work: setSampleFile() below
	// already refreshes the stretch buffer.
	setupStretchDelivery();

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

	setupStretchDelivery();
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
	m_startFrameOffset(orig.m_startFrameOffset),
	m_pitchMode(orig.m_pitchMode),
	m_sourceStartFrame(orig.m_sourceStartFrame),
	m_sourceEndFrame(orig.m_sourceEndFrame),
	m_stretchRatio(orig.m_stretchRatio)
{
	// The stretched buffer itself is deliberately not copied: it belongs to the
	// original clip's request. The clone asks for its own (setSampleFile below
	// refreshes it); until that arrives the clone plays the degraded-but
	// pitch-correct source path.
	setupStretchDelivery();
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
	// A bare length change never changes the playback speed: the ratio is
	// explicit stored state, not derived from the length. The playback plan
	// clamps source consumption at the clip's right edge, so this behaves as
	// an ordinary speed-preserving trim/extend. Editing operations that *do*
	// restretch go through stretchToLength / stretchFromStart instead.
	Clip::changeLength(std::max(static_cast<int>(_length), 1));
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
	// A brand-new source: everything of it is playable and nothing of it is
	// stretched yet. Any previous trim or stretch referred to the old buffer.
	m_sourceStartFrame = 0;
	m_sourceEndFrame = 0;
	m_stretchRatio = 1.0;
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
		// Brand-new source: reset the explicit editing state (see above).
		m_sourceStartFrame = 0;
		m_sourceEndFrame = 0;
		m_stretchRatio = 1.0;
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
		sourceStartFrame(),
		sourceEndFrame(),
		buffer->sampleRate(),
		Engine::audioEngine()->outputSampleRate(),
		m_stretchRatio);
}
auto SampleClip::waveformMapping(const Sample& sampleToDraw) const -> WaveformMapping
{
	const auto size = static_cast<double>(sampleToDraw.sampleSize());
	if (size <= 0.0) { return {}; }

	// Output-frame coordinates of the audible range, measured from the clip's
	// audible start. This is the same coordinate system playback uses, so the
	// range the waveform draws is the range the audio thread reads.
	const auto oft = outputFramesPerTick();
	const auto leading = std::max(0, -static_cast<int>(startTimeOffset()));
	const auto startOutput = static_cast<double>(leading) * oft;
	const auto endOutput = std::max(startOutput,
		(static_cast<double>(length()) - static_cast<double>(startTimeOffset())) * oft);

	// When drawing the stretched buffer itself, its frame index *is* the
	// output-frame coordinate by construction, so the mapping is a plain
	// fraction of its size. When drawing the original source, convert output
	// frames to source frames using the same mapping playback uses -- which
	// applies the ratio in Resample mode (the source is consumed at ratio
	// speed) and in Stretch mode without a buffer yet (the temporary resample
	// fallback fills the clip's duration).
	const auto isStretchedBuffer = (m_pitchMode == PitchMode::Stretch
		&& hasStretchedSample()
		&& &sampleToDraw == stretchedSample().get());

	const auto toSourceFrame = [this, isStretchedBuffer](double outputFrame)
	{
		if (isStretchedBuffer)
		{
			return outputFrame; // stretched buffer frame index = output frame
		}
		return sourceFrameAtOutputFrame(outputFrame);
	};

	const auto sampleStart = static_cast<float>(std::clamp(toSourceFrame(startOutput) / size, 0.0, 1.0));
	const auto sampleEnd = static_cast<float>(std::clamp(toSourceFrame(endOutput) / size,
		static_cast<double>(sampleStart), 1.0));
	return {sampleStart, sampleEnd};
}

auto SampleClip::sourceEndFrame() const -> int
{
	const auto size = static_cast<int>(m_sample.sampleSize());
	if (m_sourceEndFrame <= 0 || m_sourceEndFrame > size) { return size; } // 0 == whole buffer
	return std::max(m_sourceStartFrame, m_sourceEndFrame);
}

auto SampleClip::sourceRangeTicks() const -> double
{
	const auto spt = sourceFramesPerTick();
	if (spt <= 0.0) { return 0.0; }
	return static_cast<double>(sourceEndFrame() - sourceStartFrame()) / spt;
}

auto SampleClip::stretchUnavailable() const -> bool
{
	// Stretch mode with a real stretch to perform, but no pitch-preserving
	// result available *yet*: the result is still being computed off-thread,
	// this build lacks SoundTouch entirely, or the processor failed on these
	// inputs. Playback then plays the source at its original speed (pitch
	// preserved, duration not filled) rather than silently resampling -- see
	// computePlaybackPlan. Once the result lands this returns false again.
	return m_pitchMode == PitchMode::Stretch && isStretched()
		&& !m_sample.reversed() && stretchedSample() == nullptr;
}

void SampleClip::setupStretchDelivery()
{
	// The receiver is a child of the clip, so it dies with the clip and the
	// manager cancels anything still outstanding for it at that point.
	m_stretchResult = new SampleStretchResult(this);
	connect(m_stretchResult, &SampleStretchResult::ready,
		this, &SampleClip::applyStretchResult);
}
void SampleClip::refreshStretchBuffer()
{
	const auto clipId = makeClipId(this);
	const auto buffer = m_sample.buffer();

	StretchDebug::instance().logRefreshStretchBuffer(
		clipId,
		static_cast<int>(m_pitchMode),
		m_stretchRatio,
		sourceStartFrame(),
		sourceEndFrame(),
		buffer && !buffer->empty());

	// Never compute here: see the header. This decides *what* the current
	// parameters call for, then either drops a stale cached buffer
	// synchronously or hands the work to the manager's worker thread.
	const auto clearStretched = [this, clipId]()
	{
		const auto guard = Engine::audioEngine()->requestChangesGuard();
		const auto locker = QMutexLocker{&m_stretchMutex};
		m_stretchedSample.reset();
		m_stretchCacheKey = 0;
		StretchDebug::instance().logBufferStateChange(clipId, "cleared stretched buffer");
	};

	if (m_pitchMode != PitchMode::Stretch || !isStretched() || m_sample.reversed())
	{
		// Resample mode, ratio == 1.0, or a reversed sample: no stretched
		// buffer applies; the original playback path is used unchanged.
		// Invalidate any in-flight request too, so a result that is already
		// being computed cannot land after this point and be committed.
		++m_stretchGeneration;
		StretchDebug::instance().logEarlyReturn(clipId, "refreshStretchBuffer",
			"pitchMode != Stretch || !isStretched() || reversed");
		clearStretched();
		return;
	}

	if (!buffer || buffer->empty())
	{
		++m_stretchGeneration;
		StretchDebug::instance().logEarlyReturn(clipId, "refreshStretchBuffer",
			"no buffer or empty buffer");
		clearStretched();
		return;
	}

	const auto engineRate = Engine::audioEngine()->outputSampleRate();
	const auto key = currentStretchKey();

	{
		const auto locker = QMutexLocker{&m_stretchMutex};
		if (key == m_stretchCacheKey && m_stretchedSample)
		{
			StretchDebug::instance().logEarlyReturn(clipId, "refreshStretchBuffer",
				"cache hit - key matches and stretched sample exists");
			return; // cached result still matches the current parameters
		}
	}

	// Always stretch exactly the *selected source range* of the *original*
	// buffer. Repeated stretching therefore always derives from the original
	// source, never from an already transformed result. The generation makes
	// this request the only one that may still be committed: results of any
	// earlier request are stale by the time they arrive, or already superseded
	// in the manager's queue.
	++m_stretchGeneration;
	StretchDebug::instance().logStretchRequestQueued(
		clipId,
		m_stretchGeneration,
		key,
		sourceStartFrame(),
		sourceEndFrame(),
		buffer->sampleRate(),
		engineRate,
		m_stretchRatio);
	SampleStretchManager::instance().request(
		m_stretchResult,
		m_stretchGeneration,
		key,
		buffer,
		sourceStartFrame(),
		sourceEndFrame(),
		buffer->sampleRate(),
		engineRate,
		m_stretchRatio);
}

void SampleClip::applyStretchResult(uint64_t generation, uint64_t key,
	std::shared_ptr<Sample> stretched)
{
	const auto clipId = makeClipId(this);

	// Runs on the GUI thread via the receiver. A result from any but the
	// newest request is stale -- typically an earlier position of a drag whose
	// computation happened to finish later -- and must never replace what the
	// clip is waiting for.
	if (generation != m_stretchGeneration)
	{
		StretchDebug::instance().logStretchJobDiscarded(clipId, generation, key,
			"generation mismatch (expected " + std::to_string(m_stretchGeneration) + ")");
		return;
	}
	// The clip's parameters may also have moved on in ways the generation
	// counter alone does not cover (a trim during the computation changes the
	// key without a new request having been made yet).
	if (key != currentStretchKey())
	{
		StretchDebug::instance().logStretchJobDiscarded(clipId, generation, key,
			"key mismatch (current key: " + std::to_string(currentStretchKey()) + ")");
		return;
	}
	if (!stretched)
	{
		// The processor could not stretch these inputs (no SoundTouch, or a
		// degenerate range). Stay on the degraded source path; stretch mode
		// never silently resamples.
		StretchDebug::instance().logApplyStretchResult(clipId, generation, key, 0, false);
		const auto guard = Engine::audioEngine()->requestChangesGuard();
		const auto locker = QMutexLocker{&m_stretchMutex};
		m_stretchedSample.reset();
		m_stretchCacheKey = 0;
		emit sampleChanged();
		return;
	}

	// Serialise against audio rendering so the real-time thread never observes
	// a half-swapped buffer.
	{
		const auto guard = Engine::audioEngine()->requestChangesGuard();
		const auto locker = QMutexLocker{&m_stretchMutex};
		m_stretchedSample = std::move(stretched);
		m_stretchCacheKey = key;
	}
	StretchDebug::instance().logApplyStretchResult(clipId, generation, key,
		static_cast<int>(m_stretchedSample->sampleSize()), true);
	emit sampleChanged();
}

std::shared_ptr<Sample> SampleClip::stretchedSample() const
{
	// Only hand out the stretched buffer while it still matches the clip's
	// current parameters (source range, ratio, buffer identity).
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
	const auto clipId = makeClipId(this);
	StretchDebug::instance().logPitchModeChanged(clipId, static_cast<int>(m_pitchMode), static_cast<int>(mode));
	m_pitchMode = mode;
	// The mode switch never changes the clip's length or the source range; it
	// only changes how the selected audio is rendered for the current ratio.
	refreshStretchBuffer();
	emit sampleChanged();
	Engine::getSong()->setModified();
}

double SampleClip::sourceFramesPerTick() const
{
	return Engine::framesPerTick(m_sample.sampleRate());
}

double SampleClip::outputFramesPerTick() const
{
	return Engine::framesPerTick(Engine::audioEngine()->outputSampleRate());
}

double SampleClip::outputFramesPerSourceFrame() const
{
	const auto ratio = m_stretchRatio;
	if (ratio <= 0.0) { return 1.0; }
	return outputFramesPerTick() / sourceFramesPerTick() * ratio;
}

double SampleClip::outputFramesFor(TimePos timelinePos) const
{
	// The clip's audible playback starts at startPosition() + startTimeOffset();
	// before that the clip plays silence. A negative start-time offset (left
	// trim) makes this positive at the clip's left edge: playback there skips
	// straight to the trimmed-in position.
	const auto ticks = static_cast<double>(timelinePos)
		- static_cast<double>(startPosition() + startTimeOffset());
	return ticks * outputFramesPerTick();
}

double SampleClip::sourceFrameAtOutputFrame(double outputFrame) const
{
	const auto scale = outputFramesPerSourceFrame();
	if (scale <= 0.0) { return static_cast<double>(sourceStartFrame()); }
	return static_cast<double>(sourceStartFrame()) + outputFrame / scale;
}

SampleClip::PlaybackPlan SampleClip::computePlaybackPlan(double startOutputFrame) const
{
	// Everything about *how* this clip is played is decided here, from the
	// explicit source range [sourceStartFrame(), sourceEndFrame()) and the
	// explicit stretch ratio. Callers pass a timeline position converted to
	// output frames with outputFramesFor(); the returned frame range, buffer and
	// resample ratio are consistent with it, so playing to a position and
	// starting at it are the same thing.
	PlaybackPlan plan;

	const auto clipId = makeClipId(this);
	const auto ratio = m_stretchRatio > 0.0 ? m_stretchRatio : 1.0;
	const auto oft = outputFramesPerTick();
	// The clip's right edge, in output frames measured from the audible start.
	const auto clipEndOutput = std::max(0.0,
		(static_cast<double>(length()) - static_cast<double>(startTimeOffset())) * oft);
	const auto start = std::max(0.0, startOutputFrame);
	const auto srcStart = static_cast<double>(sourceStartFrame());
	const auto srcEnd = static_cast<double>(std::max(sourceStartFrame(), sourceEndFrame()));

	if (start >= clipEndOutput)
	{
		StretchDebug::instance().logEarlyReturn(clipId, "computePlaybackPlan",
			"start >= clipEndOutput (nothing to play)");
		return plan; // nothing left to play
	}

	if (pitchMode() == PitchMode::Stretch)
	{
		if (const auto stretched = stretchedSample(); stretched != nullptr)
		{
			// The stretched buffer was produced from exactly the selected source
			// range at the engine rate, so its frame index *is* the output-frame
			// coordinate: stretched frame f corresponds to source frame
			// sourceFrameAtOutputFrame(f) by construction. Index it directly and
			// resample nothing -- pitch is preserved.
			const auto stretchedSize = static_cast<double>(stretched->sampleSize());
			const auto first = std::clamp(start, 0.0, stretchedSize);
			const auto last = std::clamp(std::min(clipEndOutput, stretchedSize), first, stretchedSize);
			plan.stretchedSource = stretched;
			plan.startFrame = static_cast<int>(std::lround(first));
			plan.endFrame = static_cast<int>(std::lround(last));
			plan.resampleRatio = 1.0;
			plan.totalOutputFrames = std::max(0.0, static_cast<double>(plan.endFrame - plan.startFrame));

			StretchDebug::Event logEvent;
			logEvent.sampleRate = Engine::audioEngine()->outputSampleRate();
			logEvent.originalFrames = static_cast<int>(stretchedSize);
			logEvent.clipLength = length();
			logEvent.sourceStartFrame = sourceStartFrame();
			logEvent.sourceEndFrame = sourceEndFrame();
			logEvent.stretchRatio = m_stretchRatio;
			logEvent.pitchMode = static_cast<int>(m_pitchMode);
			logEvent.planStartFrame = plan.startFrame;
			logEvent.planEndFrame = plan.endFrame;
			logEvent.planResampleRatio = plan.resampleRatio;
			logEvent.planTotalOutputFrames = plan.totalOutputFrames;
			logEvent.planHasStretchedSource = true;
			StretchDebug::instance().logComputePlaybackPlan(clipId, logEvent);

			return plan;
		}

		// No stretched buffer yet: the async stretch is still being computed
		// off-thread. Playing the source at the shifted ratio would change the
		// pitch, which is the opposite of what Stretch mode is for, so instead
		// play the source at its natural speed (ratio 1.0) -- pitch is
		// preserved, and the audio runs for its natural duration rather than
		// filling the whole clip. When the async buffer lands the branch above
		// switches to the pitch-preserving buffer at the full stretched
		// duration. This is the degraded-but-correct transition state.
		const auto naturalScale = outputFramesPerSourceFrame() / ratio; // ratio == 1
		const auto toSrc = [this, naturalScale](double outputFrame) {
			return naturalScale > 0.0
				? static_cast<double>(sourceStartFrame()) + outputFrame / naturalScale
				: static_cast<double>(sourceStartFrame());
		};
		const auto first = std::clamp(toSrc(start), srcStart, srcEnd);
		const auto last = std::clamp(toSrc(clipEndOutput), first, srcEnd);
		plan.stretchedSource = nullptr;
		plan.startFrame = static_cast<int>(std::lround(first));
		plan.endFrame = static_cast<int>(std::lround(last));
		plan.resampleRatio = 1.0;
		plan.totalOutputFrames = std::max(0.0,
			static_cast<double>(plan.endFrame - plan.startFrame) * naturalScale);

		StretchDebug::Event logEvent;
		logEvent.sampleRate = Engine::audioEngine()->outputSampleRate();
		logEvent.originalFrames = m_sample.sampleSize();
		logEvent.clipLength = length();
		logEvent.sourceStartFrame = sourceStartFrame();
		logEvent.sourceEndFrame = sourceEndFrame();
		logEvent.stretchRatio = m_stretchRatio;
		logEvent.pitchMode = static_cast<int>(m_pitchMode);
		logEvent.planStartFrame = plan.startFrame;
		logEvent.planEndFrame = plan.endFrame;
		logEvent.planResampleRatio = plan.resampleRatio;
		logEvent.planTotalOutputFrames = plan.totalOutputFrames;
		logEvent.planHasStretchedSource = false;
		StretchDebug::instance().logComputePlaybackPlan(clipId, logEvent);

		return plan;
	}

	// Resample path: the original sample is consumed at `ratio` times its
	// natural speed, which changes the pitch -- that is Resample mode's job.
	// The clip's right edge clamps how much of the source is consumed, so an
	// ordinary trim shortens the audio without touching the ratio.
	const auto first = std::clamp(sourceFrameAtOutputFrame(start), srcStart, srcEnd);
	const auto last = std::clamp(sourceFrameAtOutputFrame(clipEndOutput), first, srcEnd);
	plan.stretchedSource = nullptr;
	plan.startFrame = static_cast<int>(std::lround(first));
	plan.endFrame = static_cast<int>(std::lround(last));
	plan.resampleRatio = ratio;
	plan.totalOutputFrames = std::max(0.0, static_cast<double>(plan.endFrame - plan.startFrame) * outputFramesPerSourceFrame());

	StretchDebug::Event logEvent;
	logEvent.sampleRate = Engine::audioEngine()->outputSampleRate();
	logEvent.originalFrames = m_sample.sampleSize();
	logEvent.clipLength = length();
	logEvent.sourceStartFrame = sourceStartFrame();
	logEvent.sourceEndFrame = sourceEndFrame();
	logEvent.stretchRatio = m_stretchRatio;
	logEvent.pitchMode = static_cast<int>(m_pitchMode);
	logEvent.planStartFrame = plan.startFrame;
	logEvent.planEndFrame = plan.endFrame;
	logEvent.planResampleRatio = plan.resampleRatio;
	logEvent.planTotalOutputFrames = plan.totalOutputFrames;
	logEvent.planHasStretchedSource = false;
	StretchDebug::instance().logComputePlaybackPlan(clipId, logEvent);

	return plan;
}

// ---------------------------------------------------------------------------
// Editing operations: trim (speed-preserving) vs stretch (ratio-changing)
// ---------------------------------------------------------------------------
//
// The distinction is absolute:
//   * Trimming changes the clip length and/or the start-time offset. It never
//     touches the ratio, so the retained audio always keeps playing at the
//     speed it had before the drag.
//   * Stretching changes the ratio so that the whole playable source range
//     fills the clip's new length. It derives the ratio from the *original*
//     source range, never from a previously stretched result, so repeated
//     stretching cannot accumulate degradation.

void SampleClip::trimToLength(const TimePos& newLength)
{
	const auto clipId = makeClipId(this);
	const auto clamped = std::max(static_cast<int>(newLength), 1);

	StretchDebug::instance().logTrimToLength(clipId, clamped, sourceStartFrame(), sourceEndFrame());

	// Ordinary right-edge trim/extend at the current speed. The clip's right
	// edge marks where the retained audio ends, so the *playable source range*
	// has to shrink (or grow) by the same amount of audio: what falls off the
	// right is cut, and extending reveals more of the source again -- always at
	// the original speed. The ratio -- and therefore the playback speed and
	// pitch -- is untouched.
	//
	// Narrowing the range here is also what makes a later stretch correct: the
	// ratio a stretch computes is derived from sourceRangeTicks(), so without
	// this the stretch would fit the *original* full source into the clip and
	// resurrect audio the user had trimmed away.
	Clip::changeLength(clamped);

	// The frame the clip's new right edge lands on, using the very same
	// timeline-to-source mapping playback uses -- so this stays correct for a
	// leading start-time offset (positive or negative) and for any ratio.
	const auto retained = sourceFrameAtOutputFrame(outputFramesFor(endPosition()));
	const auto bufferSize = static_cast<int>(m_sample.sampleSize());
	m_sourceEndFrame = std::clamp(static_cast<int>(std::lround(retained)),
		sourceStartFrame(), bufferSize);

	setAutoResize(false);
	// In Stretch mode the cached buffer was computed from the range that just
	// changed, so it no longer matches; ask for the one the narrowed range
	// calls for. A cheap no-op in every other case.
	refreshStretchBuffer();
	// The retained source range is part of what the waveform draws, so the view
	// has to redraw even in Resample mode, where nothing else changed.
	emit sampleChanged();
	Engine::getSong()->setModified();
}

void SampleClip::trimFromStart(const TimePos& newPos)
{
	// Ordinary left-edge trim/extend with the right edge anchored. This is the
	// classic content-pinned-to-the-timeline behaviour: the clip's left edge
	// slides under the audio, discarding whatever it passes. The start-time
	// offset absorbs the edge movement (it may go negative, which the playback
	// plan turns into a skip into the audio), so the retained audio keeps its
	// original speed and the right edge -- and the audio at it -- does not move.
	const auto delta = newPos - startPosition();
	const auto newLength = length() - delta;
	if (newLength < 1) { return; }
	movePosition(newPos);
	Clip::changeLength(newLength);
	setStartTimeOffset(startTimeOffset() - delta);
	setAutoResize(false);
	Engine::getSong()->setModified();
}

void SampleClip::stretchToLength(const TimePos& newLength)
{
	const auto clipId = makeClipId(this);
	const auto clamped = std::max(static_cast<int>(newLength), 1);

	// Materialise the audible range: a left trim (negative start-time offset)
	// skipped part of the source; that audio is inaudible, so the range that
	// the stretch must fit into the clip starts after it.
	materialiseAudibleRange();

	const auto natural = sourceRangeTicks(); // timeline ticks at ratio 1
	const auto leading = std::max(0, static_cast<int>(startTimeOffset()));
	const auto audible = std::max(1.0, static_cast<double>(clamped - leading));
	if (natural > 0.0)
	{
		m_stretchRatio = std::clamp(audible / natural, 0.01, 100.0);
	}

	StretchDebug::instance().logStretchToLength(clipId, clamped, sourceStartFrame(), sourceEndFrame(), m_stretchRatio);

	Clip::changeLength(clamped);
	setAutoResize(false);
	refreshStretchBuffer();
	emit sampleChanged();
	Engine::getSong()->setModified();
}

void SampleClip::stretchFromStart(const TimePos& newPos)
{
	// Pitch-preserving left-edge stretch: the right edge stays anchored, the
	// clip's length changes, and the *whole* playable source range is
	// re-stretched to fill the new length. No audio is discarded by the
	// stretch itself -- the source range is only narrowed to what a previous
	// trim already made inaudible. Whether that ratio is rendered with a
	// pitch-preserving buffer or by resampling is decided by the clip's
	// Pitch mode, which this function does not touch -- the toolbar Stretch
	// edit mode and the context-menu Pitch mode are independent controls
	// (see the behaviour matrix in STRETCH_REPAIR_REPORT.md).
	const auto end = endPosition();
	// The timeline has no positions before tick 0 and Clip::movePosition
	// clamps there, so clamp here too -- otherwise the length computed from
	// the unclamped position would disagree with the clamped position and
	// the clip's right edge would move.
	const auto clampedPos = TimePos(std::clamp(static_cast<int>(newPos), 0,
		static_cast<int>(end) - 1));
	const auto newLength = end - clampedPos;

	materialiseAudibleRange();

	const auto natural = sourceRangeTicks();
	const auto leading = std::max(0, static_cast<int>(startTimeOffset()));
	const auto audible = std::max(1.0, static_cast<double>(newLength - leading));
	if (natural > 0.0)
	{
		m_stretchRatio = std::clamp(audible / natural, 0.01, 100.0);
	}
	movePosition(clampedPos);
	Clip::changeLength(newLength);
	setAutoResize(false);
	refreshStretchBuffer();
	emit sampleChanged();
	Engine::getSong()->setModified();
}

void SampleClip::materialiseAudibleRange()
{
	// Fold a left trim (negative start-time offset) into the source range: the
	// skipped audio becomes permanently out of the playable range, the offset
	// returns to >= 0, and the ratio is rescaled so the audible audio keeps
	// playing at exactly the speed it had before. Called before a stretch so
	// the ratio is always derived from the audio the user can actually hear.
	if (startTimeOffset() >= 0) { return; }
	const auto skipped = static_cast<double>(-startTimeOffset()); // ticks before the left edge
	// The skipped audio occupies `skipped` ticks of *output* time; converting
	// to source frames divides by the stretch scale (output frames per source
	// frame), so a stretched clip folds in proportionally fewer source frames.
	const auto scale = outputFramesPerSourceFrame();
	const auto skippedSource = scale > 0.0 ? skipped * outputFramesPerTick() / scale : 0.0;
	m_sourceStartFrame = std::min(
		static_cast<int>(std::lround(sourceStartFrame() + skippedSource)),
		sourceEndFrame());
	setStartTimeOffset(0);
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
	// The explicit editing state: which part of the source is playable and how
	// fast it plays. Both are needed to reproduce the clip's sound exactly
	// after a save/reload cycle.
	_this.setAttribute("srcstart", m_sourceStartFrame);
	_this.setAttribute("srcend", m_sourceEndFrame);
	_this.setAttribute("stretchratio", QString::number(m_stretchRatio, 'g', 17));
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

	// Restore the explicit editing state (which part of the source is playable
	// and at what speed). Loading the sample above reset it to the whole buffer
	// at ratio 1, and projects saved before stretching existed simply have no
	// such attributes, so the defaults reproduce the old behaviour exactly.
	m_sourceStartFrame = std::max(0, _this.attribute("srcstart", "0").toInt());
	m_sourceEndFrame = std::max(0, _this.attribute("srcend", "0").toInt());
	m_stretchRatio = _this.attribute("stretchratio", "1").toDouble();
	if (!(m_stretchRatio > 0.0)) { m_stretchRatio = 1.0; }

	// The clip length was restored above, possibly before the pitch mode was
	// known, so compute the stretched buffer now if the project asked for
	// Stretch mode. No-op for Resample mode and whenever the ratio is 1.0.
	refreshStretchBuffer();
}




gui::ClipView * SampleClip::createView( gui::TrackView * _tv )
{
	return new gui::SampleClipView( this, _tv );
}


} // namespace lmms
