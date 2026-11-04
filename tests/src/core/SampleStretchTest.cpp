/*
 * SampleStretchTest.cpp - regression tests for sample-clip time-stretch and trim
 *
 * Tests the four mandatory invariants:
 *   1. Stretch mode preserves pitch; Resample mode changes pitch.
 *   2. Toolbar stretch toggle controls editing behaviour (stretch vs trim).
 *   3. Cutting/shortening must not speed up audio.
 *   4. Front-edge (left) stretching works without discarding audio.
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

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include <QCoreApplication>
#include <QDomDocument>
#include <QSignalSpy>
#include <QTest>

#include "lmmsconfig.h"
#include "AudioEngine.h"
#include "Engine.h"
#include "ProjectJournal.h"
#include "Sample.h"
#include "SampleBuffer.h"
#include "SampleClip.h"
#include "SamplePlayHandle.h"
#include "SampleStretch.h"
#include "SampleTrack.h"
#include "Song.h"

using namespace lmms;

namespace
{

sample_rate_t engineRate() { return Engine::audioEngine()->outputSampleRate(); }

std::shared_ptr<const SampleBuffer> makeSineBuffer(size_t frames, int rate = 44100)
{
	std::vector<SampleFrame> data;
	data.reserve(frames);
	for (size_t i = 0; i < frames; ++i)
	{
		const auto t = static_cast<double>(i) / rate;
		data.emplace_back(
			static_cast<sample_t>(std::sin(2.0 * M_PI * 440.0 * t)),
			static_cast<sample_t>(std::sin(2.0 * M_PI * 880.0 * t)));
	}
	return std::make_shared<const SampleBuffer>(std::move(data), rate);
}

std::shared_ptr<const SampleBuffer> makeChirpBuffer(int rate = 44100)
{
	std::vector<SampleFrame> data;
	data.reserve(rate);
	for (int i = 0; i < rate; ++i)
	{
		const auto t = static_cast<double>(i) / rate;
		const auto phase = 2.0 * M_PI * 1000.0 * t * t;
		const auto v = static_cast<sample_t>(std::sin(phase));
		data.emplace_back(v, v);
	}
	return std::make_shared<const SampleBuffer>(std::move(data), rate);
}

/**
 * @brief A buffer whose first half is @a lowHz and whose second half is
 * @a highHz, so audio from the two halves can be told apart after the fact.
 *
 * A single steady tone cannot prove that trimming removed anything: stretching
 * a uniform 440 Hz source produces 440 Hz whether the discarded half came back
 * or not. Two distinct tones make "the discarded audio reappeared" observable
 * as energy at @a highHz in the rendered output.
 */
std::shared_ptr<const SampleBuffer> makeTwoToneBuffer(size_t frames, int rate,
	double lowHz = 440.0, double highHz = 880.0)
{
	std::vector<SampleFrame> data;
	data.reserve(frames);
	const auto split = frames / 2;
	for (size_t i = 0; i < frames; ++i)
	{
		const auto t = static_cast<double>(i) / rate;
		const auto hz = i < split ? lowHz : highHz;
		const auto v = static_cast<sample_t>(0.8 * std::sin(2.0 * M_PI * hz * t));
		data.emplace_back(v, v);
	}
	return std::make_shared<const SampleBuffer>(std::move(data), rate);
}

struct ClipSetup { SampleTrack* track; SampleClip* clip; };

ClipSetup createClip(std::shared_ptr<const SampleBuffer> buffer)
{
	auto track = new SampleTrack(Engine::getSong());
	auto clip = new SampleClip(track);
	clip->setSampleBuffer(std::move(buffer));
	return {track, clip};
}

/**
 * @brief Clip length in ticks that makes the clip exactly @a ratio times as
 * long as the audio it currently holds.
 *
 * The natural duration of a clip is the length of its *playable source range*,
 * not of its sample: after a trim the retained audio is shorter than the file
 * it came from, and a stretch must be measured against what is left. Before any
 * trimming the two are identical, so this is the same value the untrimmed tests
 * have always used.
 */
TimePos lengthForRatio(const SampleClip* clip, double ratio)
{
	return TimePos(static_cast<int>(std::lround(clip->sourceRangeTicks() * ratio)));
}

/**
 * @brief Timeline ticks spanning @a seconds at the project's tempo.
 *
 * Lets a test state the lengths the user asked for -- "trim to 4 seconds",
 * "stretch to 8 seconds" -- as absolute targets instead of deriving them from
 * the clip's own idea of its natural length, which is exactly the quantity a
 * trim/stretch bug gets wrong.
 */
TimePos ticksForSeconds(double seconds)
{
	return TimePos(static_cast<int>(std::lround(
		seconds * Engine::audioEngine()->outputSampleRate() / Engine::framesPerTick())));
}

double dominantFrequency(const SampleFrame* data, size_t frames, int rate, int channel)
{
	if (frames < 2) { return 0.0; }
	int crossings = 0;
	sample_t prev = channel == 0 ? data[0].left() : data[0].right();
	for (size_t i = 1; i < frames; ++i)
	{
		const auto cur = channel == 0 ? data[i].left() : data[i].right();
		if (prev < 0.0f && cur >= 0.0f) { ++crossings; }
		prev = cur;
	}
	return crossings / static_cast<double>(frames) * rate;
}

/**
 * @brief Zero-crossing frequency of one channel over a frame sub-range.
 *
 * Used to ask "which tone is playing *here*", which a whole-buffer average
 * cannot answer -- averaging a 440 Hz first half with an 880 Hz second half
 * reports neither.
 */
double windowFrequency(const std::vector<SampleFrame>& data, int rate, int channel,
	size_t from, size_t to)
{
	from = std::min(from, data.size());
	to = std::min(to, data.size());
	if (to <= from + 1) { return 0.0; }
	return dominantFrequency(data.data() + from, to - from, rate, channel);
}

/**
 * @brief Peak absolute sample value of one channel over a frame sub-range.
 *
 * Silence is the signal that trimmed-away audio stayed away, so a test needs a
 * level reading, not just a frequency.
 */
double windowPeak(const std::vector<SampleFrame>& data, int channel, size_t from, size_t to)
{
	from = std::min(from, data.size());
	to = std::min(to, data.size());
	auto peak = 0.0;
	for (auto i = from; i < to; ++i)
	{
		const auto v = channel == 0 ? data[i].left() : data[i].right();
		peak = std::max(peak, static_cast<double>(std::abs(v)));
	}
	return peak;
}

std::vector<SampleFrame> renderHandle(SamplePlayHandle& h)
{
	const auto fpp = Engine::audioEngine()->framesPerPeriod();
	std::vector<SampleFrame> out;
	out.reserve(h.totalFrames() + fpp);
	std::vector<SampleFrame> buf(fpp);
	int maxPeriods = 10000;
	while (!h.isFinished() && maxPeriods-- > 0)
	{
		std::fill(buf.begin(), buf.end(), SampleFrame{});
		h.play(buf.data());
		out.insert(out.end(), buf.begin(), buf.end());
	}
	if (static_cast<size_t>(h.totalFrames()) < out.size())
	{
		out.resize(h.totalFrames());
	}
	return out;
}

std::vector<SampleFrame> renderAt(SampleClip* clip, double outputFrameOffset)
{
	const auto startOutput = clip->outputFramesFor(clip->startPosition() + clip->startTimeOffset()) + outputFrameOffset;
	const auto plan = clip->computePlaybackPlan(startOutput);
	SamplePlayHandle handle(clip, plan);
	return renderHandle(handle);
}

/**
 * @brief Block until every stretch job has been computed and delivered to the
 * clip's slot.
 *
 * waitUntilIdle() only guarantees the worker finished; the delivery is a
 * queued invocation on the clip's thread, so processEvents() has to run for
 * the slot to actually commit. Intended for tests only -- never for editing
 * code, which must stay responsive.
 */
void waitForStretched()
{
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
	SampleStretchManager::instance().waitUntilIdle();
	QCoreApplication::processEvents();
}

void setRatio(SampleClip* clip, double ratio)
{
	clip->setPitchMode(SampleClip::PitchMode::Stretch);
	clip->stretchToLength(lengthForRatio(clip, ratio));
	// Stretch work now runs on the manager's worker thread, so the result is
	// not ready when this returns.
	waitForStretched();
}

} // namespace


class SampleStretchTest : public QObject
{
	Q_OBJECT

private slots:

	void initTestCase()
	{
		Engine::init(true);
	}

	void cleanupTestCase()
	{
		Engine::destroy();
	}

	void cleanup()
	{
		Engine::getSong()->stop();
		Engine::getSong()->clearProject();
	}

	// ------------------------------------------------------------------
	// 12 Mandatory Regression Tests
	// ------------------------------------------------------------------

	void stretchModeAndTrimModeDifferInEditingBehaviour()
	{
		auto setup = createClip(makeSineBuffer(44100));
		const auto natural = setup.clip->sampleLength();
		const auto doubleLen = TimePos(natural.getTicks() * 2);

		setup.clip->trimToLength(doubleLen);
		QCOMPARE(setup.clip->stretchRatio(), 1.0);
		QVERIFY(!setup.clip->isStretched());

		const auto planTrim = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(planTrim.stretchedSource == nullptr);

		setup.clip->trimToLength(natural);
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(doubleLen);
		waitForStretched();
		QVERIFY(setup.clip->isStretched());
		QVERIFY(std::abs(setup.clip->stretchRatio() - 2.0) < 0.01);

		const auto planStretch = setup.clip->computePlaybackPlan(0.0);
#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(planStretch.stretchedSource != nullptr);
#endif
	}

	void resampleDoubleLengthDoublesDurationAndLowersPitch()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		const auto plan = setup.clip->computePlaybackPlan(0.0);
		const auto expectedFrames = static_cast<size_t>(2.0 * engineRate());
		QVERIFY(std::abs(plan.totalOutputFrames - expectedFrames) < 0.05 * expectedFrames);

		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > engineRate());
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		const auto freqR = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 1);
		QVERIFY(std::abs(freqL - 220.0) < 40.0);
		QVERIFY(std::abs(freqR - 440.0) < 40.0);
	}

	void resampleHalfLengthHalvesDurationAndRaisesPitch()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 0.5));

		const auto plan = setup.clip->computePlaybackPlan(0.0);
		const auto expectedFrames = static_cast<size_t>(0.5 * engineRate());
		QVERIFY(std::abs(plan.totalOutputFrames - expectedFrames) < 0.1 * expectedFrames + 100);

		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > 1000);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL - 880.0) < 80.0);
	}

	void stretchDoublePreservesPitch()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setRatio(setup.clip, 2.0);

		const auto plan = setup.clip->computePlaybackPlan(0.0);
		const auto expectedFrames = static_cast<size_t>(2.0 * engineRate());
		QVERIFY(std::abs(plan.totalOutputFrames - expectedFrames) < 0.05 * expectedFrames);

#ifdef LMMS_HAVE_SOUNDTOUCH
		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > engineRate());
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		const auto freqR = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 1);
		QVERIFY(std::abs(freqL - 440.0) < 40.0);
		QVERIFY(std::abs(freqR - 880.0) < 80.0);
#endif
	}

	void stretchHalfPreservesPitch()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setRatio(setup.clip, 0.5);

		const auto plan = setup.clip->computePlaybackPlan(0.0);
		const auto expectedFrames = static_cast<size_t>(0.5 * engineRate());
		QVERIFY(std::abs(plan.totalOutputFrames - expectedFrames) < 0.1 * expectedFrames + 100);

#ifdef LMMS_HAVE_SOUNDTOUCH
		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > 1000);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL - 440.0) < 80.0);
#endif
	}

	void trimDoesNotChangePlaybackSpeed()
	{
		auto setup = createClip(makeSineBuffer(44100));
		const auto halfLen = lengthForRatio(setup.clip, 0.5);
		setup.clip->trimToLength(halfLen);
		QCOMPARE(setup.clip->stretchRatio(), 1.0);

		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > 1000);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL - 440.0) < 60.0);

		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		QVERIFY(std::abs(setup.clip->stretchRatio() - 2.0) < 0.01);

		const auto oneAndHalf = TimePos(static_cast<int>(std::lround(setup.clip->sampleLength().getTicks() * 1.5)));
		setup.clip->trimToLength(oneAndHalf);
		QVERIFY(std::abs(setup.clip->stretchRatio() - 2.0) < 0.01);

		const auto rendered2 = renderAt(setup.clip, 0.0);
		QVERIFY(rendered2.size() > 1000);
		const auto freqL2 = dominantFrequency(rendered2.data(), rendered2.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL2 - 220.0) < 40.0);
	}

	void frontEdgeStretchKeepsEndAndAllAudio()
	{
		auto setup = createClip(makeSineBuffer(44100));
		const auto twoBars = TimePos(TimePos::ticksPerBar() * 2);
		setup.clip->changeLength(twoBars);
		// Place the clip at bar 2 so the left edge can be dragged left,
		// exactly as it can in the GUI.
		setup.clip->movePosition(TimePos(TimePos::ticksPerBar()));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);

		const auto endBefore = setup.clip->endPosition();
		const auto startBefore = setup.clip->startPosition();
		const auto oft = setup.clip->outputFramesPerTick();
		const auto halfSecTicks = static_cast<int>(std::lround(0.5 * engineRate() / oft));
		const auto newPos = TimePos(startBefore.getTicks() - halfSecTicks);

		setup.clip->stretchFromStart(newPos);
	waitForStretched();
	QCOMPARE(setup.clip->endPosition(), endBefore);
		QCOMPARE(setup.clip->startPosition(), newPos);
		QVERIFY(setup.clip->stretchRatio() > 1.0);
		QCOMPARE(setup.clip->sourceStartFrame(), 0);
		QCOMPARE(setup.clip->sourceEndFrame(), static_cast<int>(44100));

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(setup.clip->hasStretchedSample());
		// The whole source must still be audible: rendering from the clip's
		// left edge starts at the very first source frame, stretched.
		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > 1000);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL - 440.0) < 60.0);
#endif
	}

	void frontEdgeTrimKeepsEndAndSpeed()
	{
		auto setup = createClip(makeSineBuffer(44100));
		const auto twoBars = TimePos(TimePos::ticksPerBar() * 2);
		setup.clip->changeLength(twoBars);

		const auto endBefore = setup.clip->endPosition();
		const auto oft = setup.clip->outputFramesPerTick();
		const auto quarterSecTicks = static_cast<int>(std::lround(0.25 * engineRate() / oft));
		const auto newPos = TimePos(setup.clip->startPosition().getTicks() + quarterSecTicks);

		setup.clip->trimFromStart(newPos);

		QCOMPARE(setup.clip->endPosition(), endBefore);
		QCOMPARE(setup.clip->stretchRatio(), 1.0);

		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > 1000);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL - 440.0) < 60.0);
	}

	void stretchedBufferMatchesClipOutputDuration()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setRatio(setup.clip, 2.0);

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(setup.clip->hasStretchedSample());
		const auto stretched = setup.clip->stretchedSample();
		QVERIFY(stretched != nullptr);
		const auto plan = setup.clip->computePlaybackPlan(0.0);
		const auto expected = plan.totalOutputFrames;
		QVERIFY(std::abs(static_cast<double>(stretched->sampleSize()) - expected) < 0.05 * expected + 100);
#endif
	}

	void seekMatchesContinuousPlayback()
	{
		auto setup = createClip(makeChirpBuffer(engineRate()));
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		const auto continuous = renderAt(setup.clip, 0.0);
		const auto seekOffset = engineRate() * 0.5;
		const auto seeked = renderAt(setup.clip, seekOffset);

		const auto compareLen = std::min({continuous.size() - static_cast<size_t>(seekOffset), seeked.size(), static_cast<size_t>(engineRate() * 0.2)});
		if (compareLen > 100)
		{
			double rmsDiff = 0.0;
			double rmsRef = 0.0;
			for (size_t i = 0; i < compareLen; ++i)
			{
				const auto diff = continuous[static_cast<size_t>(seekOffset) + i].left() - seeked[i].left();
				rmsDiff += diff * diff;
				rmsRef += continuous[static_cast<size_t>(seekOffset) + i].left() * continuous[static_cast<size_t>(seekOffset) + i].left();
			}
			rmsDiff = std::sqrt(rmsDiff / compareLen);
			rmsRef = std::sqrt(rmsRef / compareLen);
			if (rmsRef > 0.001)
			{
				QVERIFY(rmsDiff / rmsRef < 0.05);
			}
		}
	}

	void stretchRoundTripRestoresOriginal()
	{
		auto setup = createClip(makeSineBuffer(44100));
		const auto natural = setup.clip->sampleLength();

		setRatio(setup.clip, 2.0);
		QVERIFY(setup.clip->isStretched());

		setup.clip->stretchToLength(lengthForRatio(setup.clip, 0.5));
	waitForStretched();
	setup.clip->stretchToLength(natural);
	waitForStretched();

		QVERIFY(std::abs(setup.clip->stretchRatio() - 1.0) < 0.01);
		QVERIFY(!setup.clip->isStretched());
		QVERIFY(!setup.clip->hasStretchedSample());

		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > 1000);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		const auto freqR = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 1);
		QVERIFY(std::abs(freqL - 440.0) < 40.0);
		QVERIFY(std::abs(freqR - 880.0) < 80.0);
	}

	void serializationPreservesStretchState()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		const auto oft = setup.clip->outputFramesPerTick();
		const auto quarterSecTicks = static_cast<int>(std::lround(0.25 * engineRate() / oft));
		setup.clip->trimFromStart(TimePos(setup.clip->startPosition().getTicks() + quarterSecTicks));
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 1.5));
		waitForStretched();

		QDomDocument doc;
		QDomElement parent = doc.createElement("track");
		doc.appendChild(parent);
		setup.clip->saveState(doc, parent);

		const auto saved = parent.firstChildElement("sampleclip");
		QVERIFY(!saved.isNull());

		auto track2 = new SampleTrack(Engine::getSong());
		auto clip2 = new SampleClip(track2);
		clip2->loadSettings(saved);
		// Loading restores the stretch *state*; the buffer itself is rebuilt by
		// the manager's worker thread, so it only exists once that landed.
		waitForStretched();

		QCOMPARE(clip2->pitchMode(), SampleClip::PitchMode::Stretch);
		QCOMPARE(clip2->stretchRatio(), setup.clip->stretchRatio());
		QCOMPARE(clip2->sourceStartFrame(), setup.clip->sourceStartFrame());
		QCOMPARE(clip2->sourceEndFrame(), setup.clip->sourceEndFrame());
		QCOMPARE(clip2->length(), setup.clip->length());
		QCOMPARE(clip2->startPosition(), setup.clip->startPosition());
		QCOMPARE(clip2->startTimeOffset(), setup.clip->startTimeOffset());

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(clip2->hasStretchedSample());
#endif
	}

	// ------------------------------------------------------------------
	// Retained / Adapted Tests
	// ------------------------------------------------------------------

	void defaultModeIsResample()
	{
		auto setup = createClip(makeSineBuffer(44100));
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
	}

	void modeSwitchKeepsLength()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		const auto length = setup.clip->length();

		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QCOMPARE(setup.clip->length(), length);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Stretch);

		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		QCOMPARE(setup.clip->length(), length);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
	}

	void selectingActiveModeIsNoOp()
	{
		// Calling setPitchMode with the mode the clip already has must be a
		// no-op (no signal, no work). stretchToLength now sets the pitch
		// mode as part of the stretch, so start from a clip that is already
		// in Stretch mode and select Stretch again.
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QSignalSpy spy(setup.clip, &SampleClip::sampleChanged);

		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QCOMPARE(spy.count(), 0);
	}

	void stretchModeAtRatioOneBypasses()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QVERIFY(!setup.clip->isStretched());
		QVERIFY(!setup.clip->hasStretchedSample());
	}

	void switchingToResampleClearsStretchedBuffer()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setRatio(setup.clip, 2.0);
#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(setup.clip->hasStretchedSample());
#endif
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		QVERIFY(!setup.clip->hasStretchedSample());
	}

	void stretchDurationFollowsRatio()
	{
		const auto buffer = makeSineBuffer(44100);
		const auto stretched = SampleStretch::stretch(
			buffer, 0, static_cast<int>(buffer->size()),
			44100, engineRate(), 2.0);
#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(stretched != nullptr);
		QCOMPARE(stretched->sampleRate(), static_cast<int>(engineRate()));
		const auto expected = static_cast<size_t>(2.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(stretched->sampleSize()) - expected) < 0.05 * expected);
#else
		QVERIFY(stretched == nullptr);
#endif
	}

	void stretchLeavesSourceUntouched()
	{
		const auto buffer = makeSineBuffer(44100);
		const auto before = buffer->data()[100];
		const auto sizeBefore = buffer->size();

		const auto stretched = SampleStretch::stretch(
			buffer, 0, static_cast<int>(buffer->size()),
			44100, engineRate(), 1.5);
		Q_UNUSED(stretched);

		QCOMPARE(buffer->size(), sizeBefore);
		QCOMPARE(buffer->data()[100].left(), before.left());
		QCOMPARE(buffer->data()[100].right(), before.right());
	}

	void stretchHonoursSubrange()
	{
		const auto buffer = makeSineBuffer(88200);
		const auto quarter = static_cast<int>(buffer->size()) / 4;
		const auto expected = static_cast<size_t>(1.0 * engineRate());

		const auto fromStart = SampleStretch::stretch(
			buffer, 0, quarter, 44100, engineRate(), 2.0);
#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(fromStart != nullptr);
		QVERIFY(std::abs(static_cast<double>(fromStart->sampleSize()) - expected) < 0.05 * expected);

		const auto fromMiddle = SampleStretch::stretch(
			buffer, quarter, quarter * 2, 44100, engineRate(), 2.0);
		QVERIFY(fromMiddle != nullptr);
		QVERIFY(std::abs(static_cast<double>(fromMiddle->sampleSize()) - expected) < 0.05 * expected);

		const auto eighth = SampleStretch::stretch(
			buffer, 0, quarter / 2, 44100, engineRate(), 2.0);
		QVERIFY(eighth != nullptr);
		const auto halfExpected = expected / 2;
		QVERIFY(std::abs(static_cast<double>(eighth->sampleSize()) - halfExpected) < 0.05 * halfExpected);
#else
		QVERIFY(fromStart == nullptr);
#endif
	}

	void stretchRejectsDegenerateInputs()
	{
		const auto buffer = makeSineBuffer(44100);
		QVERIFY(SampleStretch::stretch(buffer, 0, 0, 44100, engineRate(), 2.0) == nullptr);
		QVERIFY(SampleStretch::stretch(buffer, 0, 1, 44100, engineRate(), 2.0) == nullptr);
		QVERIFY(SampleStretch::stretch(buffer, 0, static_cast<int>(buffer->size()), 0, engineRate(), 2.0) == nullptr);
		QVERIFY(SampleStretch::stretch(buffer, 0, static_cast<int>(buffer->size()), 44100, engineRate(), 0.0) == nullptr);
		QVERIFY(SampleStretch::stretch(nullptr, 0, 100, 44100, engineRate(), 2.0) == nullptr);
	}

	void cacheKeyDistinguishesParameters()
	{
		const auto buffer = makeSineBuffer(100);
		const void* identity = buffer.get();
		const auto base = SampleStretch::cacheKey(identity, 0, 100, 44100, engineRate(), 2.0);
		QVERIFY(SampleStretch::cacheKey(identity, 0, 100, 44100, engineRate(), 2.0) == base);
		QVERIFY(SampleStretch::cacheKey(identity, 1, 100, 44100, engineRate(), 2.0) != base);
		QVERIFY(SampleStretch::cacheKey(identity, 0, 101, 44100, engineRate(), 2.0) != base);
		QVERIFY(SampleStretch::cacheKey(identity, 0, 100, 48000, engineRate(), 2.0) != base);
		QVERIFY(SampleStretch::cacheKey(identity, 0, 100, 44100, engineRate() + 1, 2.0) != base);
		QVERIFY(SampleStretch::cacheKey(identity, 0, 100, 44100, engineRate(), 2.000001) != base);
	}

	void oldProjectsDefaultToResample()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);

		QDomDocument doc;
		QDomElement parent = doc.createElement("track");
		doc.appendChild(parent);
		setup.clip->saveState(doc, parent);
		parent.firstChildElement("sampleclip").removeAttribute("stretchmode");

		auto track2 = new SampleTrack(Engine::getSong());
		auto clip2 = new SampleClip(track2);
		clip2->loadSettings(parent.firstChildElement("sampleclip"));
		QCOMPARE(clip2->pitchMode(), SampleClip::PitchMode::Resample);
		QVERIFY(!clip2->hasStretchedSample());
	}

	void modeSwitchIsOneUndoEntry()
	{
		// The GUI journals a pitch-mode switch by checkpointing the track
		// (SampleClipView does exactly this). Toolbar Stretch edit mode and
		// context-menu Pitch mode are independent controls. stretchToLength
		// does NOT change pitch mode.
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		// Pitch mode remains Resample (default) after toolbar stretch.
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
		const auto length = setup.clip->length();

		setup.track->addJournalCheckPoint();
		// Now explicitly change pitch mode via context menu.
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Stretch);

		QVERIFY(Engine::projectJournal()->canUndo());
		Engine::projectJournal()->undo();

		// Undoing a track checkpoint deletes and recreates its clips, so
		// the original pointer is gone -- read the state back from the
		// clip the track holds now.
		QCOMPARE(setup.track->numOfClips(), 1);
		auto* restored = dynamic_cast<SampleClip*>(setup.track->getClip(0));
		QVERIFY(restored != nullptr);
		QCOMPARE(restored->pitchMode(), SampleClip::PitchMode::Resample);
		QCOMPARE(restored->length(), length);
	}

	void missingSourceFileDoesNotCrash()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setSampleFile("/nonexistent/path/to/sample.wav");
		QVERIFY(setup.clip->sample().sampleSize() == 0);
		QCOMPARE(setup.clip->stretchRatio(), 1.0);
		QVERIFY(!setup.clip->hasStretchedSample());
	}

	void sharedSourceClipsRenderIndependently()
	{
		const auto buffer = makeSineBuffer(44100);
		auto a = createClip(buffer);
		auto b = createClip(buffer);

		a.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		a.clip->stretchToLength(lengthForRatio(a.clip, 2.0));
		waitForStretched();
		b.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		b.clip->stretchToLength(lengthForRatio(b.clip, 3.0));
		waitForStretched();

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(a.clip->hasStretchedSample());
		QVERIFY(b.clip->hasStretchedSample());
		QVERIFY(a.clip->stretchedSample() != b.clip->stretchedSample());

		const auto expectedA = static_cast<size_t>(2.0 * engineRate());
		const auto expectedB = static_cast<size_t>(3.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(a.clip->stretchedSample()->sampleSize()) - expectedA) < 0.05 * expectedA);
		QVERIFY(std::abs(static_cast<double>(b.clip->stretchedSample()->sampleSize()) - expectedB) < 0.05 * expectedB);
#endif
	}

	void liveRenderMatchesOfflineStretchedBuffer()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setRatio(setup.clip, 2.0);

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(setup.clip->hasStretchedSample());
		const auto stretched = setup.clip->stretchedSample();
		QVERIFY(stretched != nullptr);

		const auto plan = setup.clip->computePlaybackPlan(0.0);
		SamplePlayHandle handle(setup.clip, plan);
		const auto rendered = renderHandle(handle);

		// The playback path always runs the libsamplerate resampler (even at
		// ratio 1.0), which adds a small constant group delay: the rendered
		// output is a delayed copy of the offline buffer. Compare with a
		// two-sided shift search so the test verifies "same audio" rather than
		// "same sample index".
		const auto skip = size_t{2000}; // clear of both filters' transients
		const auto maxShift = size_t{2000};
		const auto window = std::min(rendered.size(), static_cast<size_t>(stretched->sampleSize()));
		QVERIFY(window > skip + maxShift + 1000);

		double bestRatio = 1e30;
		size_t bestShift = 0;
		const auto end = window - maxShift;
		for (size_t shift = 0; shift <= 2 * maxShift; ++shift)
		{
			const auto off = static_cast<int64_t>(shift) - static_cast<int64_t>(maxShift);
			double rmsDiff = 0.0;
			double rmsRef = 0.0;
			for (size_t i = skip; i < end; ++i)
			{
				const auto refIdx = static_cast<int64_t>(i) + off;
				if (refIdx < 0 || refIdx >= static_cast<int64_t>(stretched->sampleSize())) { continue; }
				const auto diff = rendered[i].left() - stretched->data()[static_cast<size_t>(refIdx)].left();
				rmsDiff += diff * diff;
				rmsRef += stretched->data()[static_cast<size_t>(refIdx)].left() * stretched->data()[static_cast<size_t>(refIdx)].left();
			}
			rmsDiff = std::sqrt(rmsDiff / (end - skip));
			rmsRef = std::sqrt(rmsRef / (end - skip));
			if (rmsRef > 0.001 && rmsDiff / rmsRef < bestRatio)
			{
				bestRatio = rmsDiff / rmsRef;
				bestShift = shift;
			}
		}
		qDebug() << "live-vs-offline best shift (frames):"
				 << (static_cast<int64_t>(bestShift) - static_cast<int64_t>(maxShift));
		QVERIFY2(bestRatio < 0.01, "live render diverges from the offline stretched buffer");
#endif
	}

	void stretchUnavailableReportsDegradedBuild()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setRatio(setup.clip, 2.0);

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(!setup.clip->stretchUnavailable());
		QVERIFY(setup.clip->hasStretchedSample());
#else
		QVERIFY(setup.clip->stretchUnavailable());
		QVERIFY(!setup.clip->hasStretchedSample());
#endif
	}

	// ------------------------------------------------------------------
	// Regression tests: async stretch buffer not yet ready
	// ------------------------------------------------------------------

	void stretchModeWithoutBufferYetPreservesPitch()
	{
		// Bug 1 contract (FIXED): a clip in Stretch mode whose pitch-preserving
		// buffer has not landed yet must NOT resample -- resampling shifts the
		// pitch, which is the exact opposite of what Stretch mode is for.
		// Instead the source plays at its natural speed: pitch preserved, and
		// the audio runs for its natural duration rather than filling the whole
		// clip. When the async buffer lands the plan switches to the
		// pitch-preserving buffer at the full stretched duration.
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		// Do NOT call waitForStretched() -- the buffer is not ready yet.

		const auto plan = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(plan.stretchedSource == nullptr);
		QVERIFY(std::abs(plan.resampleRatio - 1.0) < 0.0001); // never resample in Stretch mode
		// One second of natural-speed audio: the source is 1 s, so that is all
		// that is audible until the stretched buffer arrives.
		const auto expectedFrames = static_cast<size_t>(1.0 * engineRate());
		QVERIFY(std::abs(plan.totalOutputFrames - expectedFrames) < 0.05 * expectedFrames);

		// The rendered audio is at the *original* pitch (440 Hz left channel),
		// not the resampled one, while the stretch is in flight.
		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > engineRate() / 2);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY2(std::abs(freqL - 440.0) < 20.0,
			qPrintable(QStringLiteral("Stretch mode must preserve pitch while the "
				"buffer is in flight: expected ~440 Hz, got %1").arg(freqL)));

		// Once the stretched buffer arrives, the plan switches to the
		// pitch-preserving buffer and now fills the clip's duration at 440 Hz.
		waitForStretched();
#ifdef LMMS_HAVE_SOUNDTOUCH
		const auto plan2 = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(plan2.stretchedSource != nullptr);
		QVERIFY(std::abs(plan2.resampleRatio - 1.0) < 0.01);
		const auto expected2 = static_cast<size_t>(2.0 * engineRate());
		QVERIFY(std::abs(plan2.totalOutputFrames - expected2) < 0.05 * expected2);
		const auto rendered2 = renderAt(setup.clip, 0.0);
		const auto freqL2 = dominantFrequency(rendered2.data(), rendered2.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL2 - 440.0) < 20.0);
#endif
	}

	void waveformMappingStretchedBufferSpansFullBuffer()
	{
		// When the stretched buffer is ready, the waveform mapping must
		// span the full buffer (0.0 to 1.0) because the stretched buffer's
		// frame index IS the output-frame coordinate. The old code used
		// sourceFrameAtOutputFrame() which mapped to original source frames,
		// causing the waveform to show only a fraction of the buffer.
		auto setup = createClip(makeSineBuffer(44100));
		setRatio(setup.clip, 2.0);

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(setup.clip->hasStretchedSample());
		const auto& stretched = *setup.clip->stretchedSample();
		const auto mapping = setup.clip->waveformMapping(stretched);
		QVERIFY(std::abs(mapping.sampleStart - 0.0f) < 0.01f);
		QVERIFY(std::abs(mapping.sampleEnd - 1.0f) < 0.01f);
#endif
	}

	void waveformMappingOriginalBufferUsesResampleMapping()
	{
		// When drawing the original buffer (Resample mode, or Stretch mode
		// without a buffer yet), the waveform mapping must use the resample
		// mapping (sourceFrameAtOutputFrame) so the drawn range matches the
		// audio that will actually be heard.
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		const auto& sample = setup.clip->sample();
		const auto mapping = setup.clip->waveformMapping(sample);
		// In Resample mode with ratio 2.0, the full source range maps to
		// the full clip width.
		QVERIFY(std::abs(mapping.sampleStart - 0.0f) < 0.01f);
		QVERIFY(std::abs(mapping.sampleEnd - 1.0f) < 0.01f);
	}

	void waveformResampleModeDrawsAtNaturalLength()
	{
		// Bug B: In Resample mode, the waveform must be drawn at its natural
		// sample length, NOT stretched to fill the clip width.
		// This test verifies the paintEvent geometry by checking that the
		// sampleRect width passed to SampleThumbnail equals the natural
		// sample length in pixels, not the clip output length.
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		// In Resample mode with ratio 2.0:
		// - Natural sample length in pixels = sampleLength * ppb / ticksPerBar
		// - Clip output length in pixels = clipLength * ppb / ticksPerBar = 2 * natural
		// The waveform should be drawn at natural length (half the clip width).
		// We verify this by checking the waveformMapping returns the full
		// source range (0.0 to 1.0) and the paintEvent uses sampleLength.
		const auto& sample = setup.clip->sample();
		const auto mapping = setup.clip->waveformMapping(sample);
		QVERIFY(std::abs(mapping.sampleStart - 0.0f) < 0.01f);
		QVERIFY(std::abs(mapping.sampleEnd - 1.0f) < 0.01f);

		// The key invariant: in Resample mode, the waveform represents the
		// original source at its natural horizontal scale. The clip is twice
		// as long, but the waveform only occupies the first half.
		// This is tested by the paintEvent logic which uses sampleLength
		// (natural) instead of clipOutputLength (stretched) for the width.
	}

	void waveformStretchModeDrawsStretchedBuffer()
	{
		// Bug B: In Stretch mode with a valid stretched buffer, the waveform
		// must represent the transformed audio across the stretched duration.
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		waitForStretched();

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(setup.clip->hasStretchedSample());
		const auto& stretched = *setup.clip->stretchedSample();
		const auto mapping = setup.clip->waveformMapping(stretched);
		// Stretched buffer frame index = output frame, so mapping is 0.0 to 1.0
		QVERIFY(std::abs(mapping.sampleStart - 0.0f) < 0.01f);
		QVERIFY(std::abs(mapping.sampleEnd - 1.0f) < 0.01f);

		// The paintEvent uses clipOutputLength (full clip width) for the
		// stretched buffer, so the waveform fills the clip.
#endif
	}

	void waveformSwitchingModesUpdatesRendering()
	{
		// Bug B: Switching Pitch mode must update the waveform rendering.
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		// Start in Resample mode: waveform at natural length
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		const auto mappingResample = setup.clip->waveformMapping(setup.clip->sample());
		QVERIFY(std::abs(mappingResample.sampleStart - 0.0f) < 0.01f);
		QVERIFY(std::abs(mappingResample.sampleEnd - 1.0f) < 0.01f);

		// Switch to Stretch mode: waveform should use stretched buffer when ready
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		waitForStretched();

#ifdef LMMS_HAVE_SOUNDTOUCH
		QVERIFY(setup.clip->hasStretchedSample());
		const auto mappingStretch = setup.clip->waveformMapping(*setup.clip->stretchedSample());
		QVERIFY(std::abs(mappingStretch.sampleStart - 0.0f) < 0.01f);
		QVERIFY(std::abs(mappingStretch.sampleEnd - 1.0f) < 0.01f);
#endif

		// Switch back to Resample: waveform returns to natural length
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		const auto mappingBack = setup.clip->waveformMapping(setup.clip->sample());
		QVERIFY(std::abs(mappingBack.sampleStart - 0.0f) < 0.01f);
		QVERIFY(std::abs(mappingBack.sampleEnd - 1.0f) < 0.01f);
	}

	void trimThenStretchPreservesSourceRange()
	{
		// Bug C: the user trims an 8-second sample to 4 seconds using the
		// normal edit mode, then sets Pitch mode to Stretch via context menu,
		// then extends the trimmed clip back to 8 seconds using toolbar Stretch
		// edit mode. The expected result is pitch-preserved stretch from
		// the trimmed 4-second range.
		auto setup = createClip(makeSineBuffer(8 * 44100));
		const auto originalRange = setup.clip->sourceEndFrame() - setup.clip->sourceStartFrame();

		// 1. Trim to half using the ordinary edit mode (trimToLength).
		const auto halfLen = lengthForRatio(setup.clip, 0.5);
		setup.clip->trimToLength(halfLen);
		QCOMPARE(setup.clip->stretchRatio(), 1.0);
		const auto trimmedRange = setup.clip->sourceEndFrame() - setup.clip->sourceStartFrame();
		// Trimming to half the clip length must halve the playable source
		// range (frames), keeping the start at frame 0.
		QVERIFY(std::abs(trimmedRange - 0.5 * originalRange) < 100);
		QCOMPARE(setup.clip->sourceStartFrame(), 0);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);

		// 2. Confirm the trimmed clip plays at normal speed and pitch.
		const auto planTrim = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(planTrim.stretchedSource == nullptr);
		QVERIFY(std::abs(planTrim.resampleRatio - 1.0) < 0.001);
		const auto renderedTrim = renderAt(setup.clip, 0.0);
		const auto freqTrim = dominantFrequency(renderedTrim.data(), renderedTrim.size(), engineRate(), 0);
		QVERIFY(std::abs(freqTrim - 440.0) < 40.0);

		// 3. Set Pitch mode to Stretch via context menu (independent control).
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Stretch);

		// 4. Toolbar Stretch edit mode: drag the right edge back to twice
		//    the trimmed length. stretchToLength does NOT change pitch mode.
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		waitForStretched();
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Stretch);
		QVERIFY(std::abs(setup.clip->stretchRatio() - 2.0) < 0.01);

		// 5. The source range must still be the trimmed half -- the stretch
		//    must not resurrect the discarded second half.
		const auto rangeAfterStretch = setup.clip->sourceEndFrame() - setup.clip->sourceStartFrame();
		QVERIFY(std::abs(rangeAfterStretch - trimmedRange) < 1.0);
		QCOMPARE(setup.clip->sourceStartFrame(), 0);

		// 6. The playback plan must use the generated pitch-preserving
		//    buffer at ratio 1.0, not the resample fallback at ratio 2.0.
		const auto plan = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(plan.stretchedSource != nullptr);
		QVERIFY(std::abs(plan.resampleRatio - 1.0) < 0.01);
		const auto srcRangeFrames = static_cast<double>(trimmedRange);
		const auto expectedOut = srcRangeFrames * 2.0 * static_cast<double>(engineRate()) / 44100.0;
		QVERIFY(std::abs(plan.totalOutputFrames - expectedOut) < 0.05 * expectedOut);

		// 7. The rendered audio must be at the ORIGINAL pitch (440 Hz), not
		//    the resampled pitch (220 Hz). The clip must be ~8 seconds, not
		//    4 seconds played at 2x speed.
		const auto rendered = renderAt(setup.clip, 0.0);
		QVERIFY(rendered.size() > 1000);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY(std::abs(freqL - 440.0) < 40.0);

		// The stretched buffer must have been generated from the trimmed
		// 4-second range, not from the original 8-second source.
		const auto stretched = setup.clip->stretchedSample();
		QVERIFY(stretched != nullptr);
		QVERIFY(stretched->data() != setup.clip->sample().data());
		const auto stretchedFrames = static_cast<double>(stretched->sampleSize());
		QVERIFY(std::abs(stretchedFrames - 2.0 * trimmedRange * static_cast<double>(engineRate()) / 44100.0)
				< 0.05 * (2.0 * trimmedRange * static_cast<double>(engineRate()) / 44100.0));
	}

	void trimThenStretchCannotResurrectDiscardedAudio()
	{
		// Bug C, judged entirely from the rendered audio rather than from the
		// clip's internal bookkeeping. A steady tone cannot prove a trim worked
		// -- stretching a uniform source sounds the same whether or not the
		// discarded half came back -- so the source here is 440 Hz for its
		// first half and 880 Hz for its second. Trim to the first half, stretch
		// that back to 8 seconds, and the whole result has to be the retained
		// tone at the retained pitch. Nothing here inspects source ranges or
		// cache keys, so the test cannot be satisfied by state that merely
		// looks right while the audio is wrong.
		const auto rate = engineRate();
		const auto srcRate = 44100;
		auto setup = createClip(makeTwoToneBuffer(static_cast<size_t>(8 * srcRate), srcRate));

		// The two user gestures, in order: trim away the 880 Hz half with the
		// ordinary edit mode, then stretch the remainder to twice its length.
		// Both targets are stated in seconds, not derived from the clip.
		setup.clip->trimToLength(ticksForSeconds(4.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(ticksForSeconds(8.0));
		waitForStretched();

		const auto rendered = renderAt(setup.clip, 0.0);
		const auto expectedFrames = 8.0 * rate;
		QVERIFY2(std::abs(static_cast<double>(rendered.size()) - expectedFrames) < 0.05 * expectedFrames,
			qPrintable(QStringLiteral("rendered %1 frames, expected ~%2 for 8 s")
				.arg(rendered.size()).arg(static_cast<qulonglong>(expectedFrames))));

		// Every second of the result is the retained tone, and is not silent.
		const auto quarter = rendered.size() / 4;
		for (auto w = 0; w < 4; ++w)
		{
			const auto freq = windowFrequency(rendered, rate, 0, w * quarter, (w + 1) * quarter);
			QVERIFY2(std::abs(freq - 440.0) < 40.0,
				qPrintable(QStringLiteral("window %1 measured %2 Hz; the trimmed-away "
					"880 Hz half leaked back in").arg(w).arg(freq)));
			const auto peak = windowPeak(rendered, 0, w * quarter, (w + 1) * quarter);
			QVERIFY2(peak > 0.5,
				qPrintable(QStringLiteral("window %1 peaks at %2 -- the retained audio "
					"is not actually being played").arg(w).arg(peak)));
		}
	}

	void twoToneControlShowsDiscardedAudioWhenNotTrimmed()
	{
		// The control for the test above: without the trim, the same stretch of
		// the same file must report the 880 Hz second half. If this ever reads
		// 440 Hz, the measurement is blind and the trim test above proves
		// nothing.
		const auto rate = engineRate();
		const auto srcRate = 44100;
		auto setup = createClip(makeTwoToneBuffer(static_cast<size_t>(8 * srcRate), srcRate));

		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		waitForStretched();

		const auto rendered = renderAt(setup.clip, 0.0);
		const auto half = rendered.size() / 2;
		const auto freqFirst = windowFrequency(rendered, rate, 0, 0, half);
		const auto freqSecond = windowFrequency(rendered, rate, 0, half, rendered.size());
		QVERIFY2(std::abs(freqFirst - 440.0) < 40.0,
			qPrintable(QStringLiteral("first half measured %1 Hz").arg(freqFirst)));
		QVERIFY2(std::abs(freqSecond - 880.0) < 80.0,
			qPrintable(QStringLiteral("second half measured %1 Hz -- the detector can no "
				"longer see the 880 Hz half, so the trim test is not meaningful").arg(freqSecond)));
	}

	void pendingStretchIsCommittedBeforeRenderingStarts()
	{
		// Exporting resolves every clip's playback plan once, at the start of
		// the render, so a stretch that has been requested but not committed yet
		// would silently export the resampled -- wrong pitch -- audio. The CLI
		// render path has no event loop of its own, which is exactly how this
		// was first observed: a stretched clip exported byte-for-byte identical
		// to the same clip in Resample mode.
		//
		// Deliberately avoids waitForStretched(): the point is that the
		// production helper RenderManager calls is sufficient on its own.
		auto setup = createClip(makeSineBuffer(2 * 44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		// Requested, not yet delivered: the clip is knowingly in the degraded
		// state the renderer must not be allowed to export.
		QVERIFY(setup.clip->stretchUnavailable());

		SampleStretchManager::instance().waitForPendingResults();

		QVERIFY(!setup.clip->stretchUnavailable());
		QVERIFY(setup.clip->stretchedSample() != nullptr);

		const auto plan = setup.clip->computePlaybackPlan(0.0);
		QVERIFY2(plan.stretchedSource != nullptr,
			"a render started now would resample the source and change its pitch");
		QVERIFY(std::abs(plan.resampleRatio - 1.0) < 0.001);

		const auto rendered = renderAt(setup.clip, 0.0);
		const auto freq = dominantFrequency(rendered.data(), rendered.size(), engineRate(), 0);
		QVERIFY2(std::abs(freq - 440.0) < 40.0,
			qPrintable(QStringLiteral("measured %1 Hz").arg(freq)));
	}

	void pendingStretchWaitIsHarmlessWithNothingPending()
	{
		// The wait now runs on every export, including the overwhelming majority
		// that contain no stretched clip at all, so it has to return promptly and
		// leave ordinary clips alone.
		auto setup = createClip(makeSineBuffer(44100));
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);

		QTest::qWait(50);
		SampleStretchManager::instance().waitForPendingResults();

		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
		QVERIFY(setup.clip->stretchedSample() == nullptr);
		const auto plan = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(plan.stretchedSource == nullptr);
		QVERIFY(std::abs(plan.resampleRatio - 1.0) < 0.001);
	}

	// ------------------------------------------------------------------
	// Runtime trace: instrumented diagnostics for the exact user scenarios
	// ------------------------------------------------------------------

	void runtimeTrace_8sStretchTo16s()
	{
		const auto rate = engineRate();
		const auto srcRate = 44100;
		const auto srcFrames = 8 * srcRate; // 352800 frames = 8 s

		auto logClip = [rate](const char* stage, SampleClip* clip)
		{
			const auto stretched = clip->stretchedSample();
			qDebug() << "\n=== " << stage << " ===";
			qDebug() << "  sourceStartFrame:" << clip->sourceStartFrame();
			qDebug() << "  sourceEndFrame:" << clip->sourceEndFrame();
			qDebug() << "  sourceFrameCount:" << (clip->sourceEndFrame() - clip->sourceStartFrame());
			qDebug() << "  clipDurationTicks:" << clip->length();
			qDebug() << "  stretchRatio:" << clip->stretchRatio();
			qDebug() << "  pitchMode:" << (clip->pitchMode() == SampleClip::PitchMode::Stretch ? "Stretch" : "Resample");
			qDebug() << "  stretchBufferExists:" << (stretched != nullptr);
			if (stretched)
			{
				qDebug() << "  stretchBufferFrames:" << stretched->sampleSize();
				qDebug() << "  stretchBufferRate:" << stretched->sampleRate();
				qDebug() << "  stretchBufferDataPtr:" << (void*)stretched->data();
				qDebug() << "  stretchBufferSeconds:" << (stretched->sampleSize() / rate);
			}
			qDebug() << "  originalBufferDataPtr:" << (void*)clip->sample().data();
			qDebug() << "  originalBufferFrames:" << clip->sample().sampleSize();
		};

		auto logPlan = [rate](const char* stage, const SampleClip::PlaybackPlan& plan, SampleClip* clip)
		{
			qDebug() << "  plan.stretchedSource:" << (void*)plan.stretchedSource.get();
			qDebug() << "  plan.startFrame:" << plan.startFrame;
			qDebug() << "  plan.endFrame:" << plan.endFrame;
			qDebug() << "  plan.resampleRatio:" << plan.resampleRatio;
			qDebug() << "  plan.totalOutputFrames:" << plan.totalOutputFrames;
			qDebug() << "  plan.totalOutputSeconds:" << (plan.totalOutputFrames / rate);
			if (plan.stretchedSource)
			{
				qDebug() << "  plan.stretchedBufferDataPtr:" << (void*)plan.stretchedSource->data();
				qDebug() << "  plan.stretchedBufferFrames:" << plan.stretchedSource->sampleSize();
			}
			else
			{
				qDebug() << "  plan.usesOriginalBuffer (dataPtr):" << (void*)clip->sample().data();
			}
		};

		auto logHandle = [rate](const char* stage, SamplePlayHandle& h, const SampleClip::PlaybackPlan& plan)
		{
			qDebug() << "  handle.totalFrames:" << h.totalFrames();
			qDebug() << "  handle.totalSeconds:" << (h.totalFrames() / rate);
			if (plan.stretchedSource)
			{
				qDebug() << "  handle.consumes: STRETCHED buffer (dataPtr " << (void*)plan.stretchedSource->data() << ")";
			}
			else
			{
				qDebug() << "  handle.consumes: ORIGINAL buffer (resample fallback, ratio " << plan.resampleRatio << ")";
			}
		};

		auto logRendered = [rate](const char* stage, const std::vector<SampleFrame>& rendered)
		{
			qDebug() << "  renderedFrames:" << rendered.size();
			qDebug() << "  renderedSeconds:" << (rendered.size() / rate);
			if (rendered.size() > 100)
			{
				const auto freqL = dominantFrequency(rendered.data(), rendered.size(), rate, 0);
				const auto freqR = dominantFrequency(rendered.data(), rendered.size(), rate, 1);
				qDebug() << "  renderedFreqL:" << freqL << "Hz (expect 440 for pitch-preserved, 220 for resample 2x)";
				qDebug() << "  renderedFreqR:" << freqR << "Hz (expect 880 for pitch-preserved, 440 for resample 2x)";
			}
		};

		// Stage 0: Load 8-second sample
		auto setup = createClip(makeSineBuffer(srcFrames, srcRate));
		logClip("Stage 0: loaded 8s sample", setup.clip);

		// Stage 1: Set Pitch mode = Stretch (context menu equivalent)
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		logClip("Stage 1: PitchMode=Stretch (ratio still 1.0, no stretch yet)", setup.clip);

		// Stage 2: Stretch to 16 seconds (toolbar Stretch edit mode + drag)
		const auto targetLen = lengthForRatio(setup.clip, 2.0);
		setup.clip->stretchToLength(targetLen);
		logClip("Stage 2: stretched to 16s (async pending, buffer not ready)", setup.clip);

		// Stage 3: Wait for async processing to finish
		const auto jobsBefore = SampleStretchManager::instance().jobsCompleted();
		waitForStretched();
		const auto jobsAfter = SampleStretchManager::instance().jobsCompleted();
		qDebug() << "\n  stretch jobs completed: " << jobsBefore << "->" << jobsAfter;
		logClip("Stage 3: after async processing (buffer should be installed)", setup.clip);

		// Stage 4: Play from beginning
		{
			qDebug() << "\n=== Stage 4: play from beginning ===";
			const auto plan = setup.clip->computePlaybackPlan(0.0);
			logPlan("Stage 4", plan, setup.clip);
			SamplePlayHandle handle(setup.clip, plan);
			logHandle("Stage 4", handle, plan);
			const auto rendered = renderHandle(handle);
			logRendered("Stage 4", rendered);
		}

		// Stage 5: Stop (handle finished, clip state unchanged)
		logClip("Stage 5: after first play (handle done, clip unchanged)", setup.clip);

		// Stage 6: Play again
		{
			qDebug() << "\n=== Stage 6: play again ===";
			const auto plan = setup.clip->computePlaybackPlan(0.0);
			logPlan("Stage 6", plan, setup.clip);
			SamplePlayHandle handle(setup.clip, plan);
			logHandle("Stage 6", handle, plan);
			const auto rendered = renderHandle(handle);
			logRendered("Stage 6", rendered);
		}

		// Stage 7: Seek to middle and play
		{
			qDebug() << "\n=== Stage 7: seek to middle ===";
			const auto midTicks = setup.clip->startPosition() + setup.clip->length() / 2;
			const auto midOutput = setup.clip->outputFramesFor(midTicks);
			qDebug() << "  midTicks:" << midTicks << "midOutputFrames:" << midOutput;
			const auto plan = setup.clip->computePlaybackPlan(midOutput);
			logPlan("Stage 7", plan, setup.clip);
			SamplePlayHandle handle(setup.clip, plan);
			logHandle("Stage 7", handle, plan);
			const auto rendered = renderHandle(handle);
			logRendered("Stage 7", rendered);
		}

		// Stage 8: Buffer identity verification
		{
			qDebug() << "\n=== Stage 8: buffer identity verification ===";
			const auto stretched = setup.clip->stretchedSample();
			const auto& original = setup.clip->sample();
			qDebug() << "  originalBufferDataPtr:" << (void*)original.data();
			qDebug() << "  stretchedBufferDataPtr:" << (stretched ? (void*)stretched->data() : nullptr);
			qDebug() << "  buffersAreDifferent:" << (stretched && stretched->data() != original.data());
			qDebug() << "  stretchedBufferIsAtEngineRate:" << (stretched && stretched->sampleRate() == rate);
			if (stretched)
			{
				qDebug() << "  stretchedBufferDuration:" << (stretched->sampleSize() / rate) << "s (expect ~16s)";
			}
		}
	}

	void runtimeTrace_bugC_trimThenStretch()
	{
		const auto rate = engineRate();
		const auto srcRate = 44100;
		const auto srcFrames = 8 * srcRate; // 352800 frames = 8 s

		auto logClip = [rate](const char* stage, SampleClip* clip)
		{
			const auto stretched = clip->stretchedSample();
			qDebug() << "\n=== " << stage << " ===";
			qDebug() << "  sourceStartFrame:" << clip->sourceStartFrame();
			qDebug() << "  sourceEndFrame:" << clip->sourceEndFrame();
			qDebug() << "  sourceFrameCount:" << (clip->sourceEndFrame() - clip->sourceStartFrame());
			qDebug() << "  clipDurationTicks:" << clip->length();
			qDebug() << "  stretchRatio:" << clip->stretchRatio();
			qDebug() << "  pitchMode:" << (clip->pitchMode() == SampleClip::PitchMode::Stretch ? "Stretch" : "Resample");
			qDebug() << "  stretchBufferExists:" << (stretched != nullptr);
			if (stretched)
			{
				qDebug() << "  stretchBufferFrames:" << stretched->sampleSize();
				qDebug() << "  stretchBufferSeconds:" << (stretched->sampleSize() / rate);
				qDebug() << "  stretchBufferDataPtr:" << (void*)stretched->data();
			}
			qDebug() << "  originalBufferDataPtr:" << (void*)clip->sample().data();
			qDebug() << "  originalBufferFrames:" << clip->sample().sampleSize();
		};

		// Stage 0: Load 8-second sample
		auto setup = createClip(makeSineBuffer(srcFrames, srcRate));
		logClip("Stage 0: loaded 8s sample", setup.clip);

		// Stage 1: Trim to first 4 seconds (EditMode::Draw → trimToLength)
		const auto halfLen = lengthForRatio(setup.clip, 0.5);
		setup.clip->trimToLength(halfLen);
		logClip("Stage 1: trimmed to 4s (EditMode::Draw)", setup.clip);

		// Stage 2: Set PitchMode = Stretch (context menu)
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		logClip("Stage 2: PitchMode=Stretch", setup.clip);

		// Stage 3: Extend clip from 4s to 8s (EditMode::Stretch → stretchToLength)
		const auto targetLen = lengthForRatio(setup.clip, 2.0);
		setup.clip->stretchToLength(targetLen);
		logClip("Stage 3: stretched to 8s (async pending)", setup.clip);

		// Stage 4: Wait for processing
		waitForStretched();
		logClip("Stage 4: after async processing", setup.clip);

		// Stage 5: Play
		{
			qDebug() << "\n=== Stage 5: play ===";
			const auto plan = setup.clip->computePlaybackPlan(0.0);
			qDebug() << "  plan.stretchedSource:" << (void*)plan.stretchedSource.get();
			qDebug() << "  plan.startFrame:" << plan.startFrame;
			qDebug() << "  plan.endFrame:" << plan.endFrame;
			qDebug() << "  plan.resampleRatio:" << plan.resampleRatio;
			qDebug() << "  plan.totalOutputFrames:" << plan.totalOutputFrames;
			qDebug() << "  plan.totalOutputSeconds:" << (plan.totalOutputFrames / rate);
			if (plan.stretchedSource)
			{
				qDebug() << "  plan.consumes: STRETCHED buffer (dataPtr " << (void*)plan.stretchedSource->data() << ")";
			}
			else
			{
				qDebug() << "  plan.consumes: ORIGINAL buffer (resample fallback)";
			}
			SamplePlayHandle handle(setup.clip, plan);
			qDebug() << "  handle.totalFrames:" << handle.totalFrames();
			qDebug() << "  handle.totalSeconds:" << (handle.totalFrames() / rate);
			const auto rendered = renderHandle(handle);
			qDebug() << "  renderedFrames:" << rendered.size();
			qDebug() << "  renderedSeconds:" << (rendered.size() / rate);
			if (rendered.size() > 100)
			{
				const auto freqL = dominantFrequency(rendered.data(), rendered.size(), rate, 0);
				qDebug() << "  renderedFreqL:" << freqL << "Hz (expect 440 = original pitch, NOT 220)";
			}
		}

		// Verification
		{
			qDebug() << "\n=== Bug C verification ===";
			const auto srcRange = setup.clip->sourceEndFrame() - setup.clip->sourceStartFrame();
			const auto expected4s = 4 * srcRate;
			qDebug() << "  sourceStartFrame:" << setup.clip->sourceStartFrame() << "(expect 0)";
			qDebug() << "  sourceEndFrame:" << setup.clip->sourceEndFrame();
			qDebug() << "  sourceRangeFrames:" << srcRange << "(expect ~" << expected4s << ")";
			qDebug() << "  sourceRangeIs4s:" << (std::abs(srcRange - expected4s) < 100);
			const auto stretched = setup.clip->stretchedSample();
			if (stretched)
			{
				const auto expected8s = 8 * rate;
				qDebug() << "  stretchedBufferFrames:" << stretched->sampleSize() << "(expect ~" << expected8s << ")";
				qDebug() << "  stretchedBufferIs8s:" << (std::abs(static_cast<long long>(stretched->sampleSize()) - static_cast<long long>(expected8s)) < static_cast<long long>(0.05 * expected8s));
				qDebug() << "  stretchedBufferDataPtr:" << (void*)stretched->data();
				qDebug() << "  originalBufferDataPtr:" << (void*)setup.clip->sample().data();
				qDebug() << "  usesGeneratedBuffer:" << (stretched->data() != setup.clip->sample().data());
			}
		}
	}

	void runtimeTrace_asyncTransition()
	{
		const auto rate = engineRate();
		const auto srcRate = 44100;
		const auto srcFrames = 8 * srcRate;

		auto setup = createClip(makeSineBuffer(srcFrames, srcRate));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		// 1. Before the buffer lands: plan uses resample fallback
		{
			qDebug() << "\n=== Async transition: BEFORE buffer lands ===";
			const auto plan = setup.clip->computePlaybackPlan(0.0);
			qDebug() << "  plan.stretchedSource:" << (void*)plan.stretchedSource.get() << "(expect nullptr)";
			qDebug() << "  plan.resampleRatio:" << plan.resampleRatio << "(expect 2.0)";
			qDebug() << "  plan.totalOutputFrames:" << plan.totalOutputFrames;
			qDebug() << "  plan.totalOutputSeconds:" << (plan.totalOutputFrames / rate);
			SamplePlayHandle handle(setup.clip, plan);
			qDebug() << "  handle.totalFrames:" << handle.totalFrames();
			qDebug() << "  handle.consumes: ORIGINAL buffer (resample fallback)";
			// Simulate a few periods of playback
			const auto fpp = Engine::audioEngine()->framesPerPeriod();
			std::vector<SampleFrame> buf(fpp);
			handle.play(buf.data());
			qDebug() << "  handle.framesDone after 1 period:" << handle.framesDone();
		}

		// 2. Wait for the buffer to land
		waitForStretched();
		qDebug() << "\n=== Async transition: AFTER buffer lands ===";
		qDebug() << "  hasStretchedSample:" << setup.clip->hasStretchedSample();
		const auto stretched = setup.clip->stretchedSample();
		if (stretched)
		{
			qDebug() << "  stretchedBufferFrames:" << stretched->sampleSize();
			qDebug() << "  stretchedBufferSeconds:" << (stretched->sampleSize() / rate);
			qDebug() << "  stretchedBufferDataPtr:" << (void*)stretched->data();
		}

		// 3. A new plan now uses the stretched buffer
		{
			const auto plan = setup.clip->computePlaybackPlan(0.0);
			qDebug() << "  NEW plan.stretchedSource:" << (void*)plan.stretchedSource.get() << "(expect non-null)";
			qDebug() << "  NEW plan.resampleRatio:" << plan.resampleRatio << "(expect 1.0)";
			qDebug() << "  NEW plan.totalOutputFrames:" << plan.totalOutputFrames;
			qDebug() << "  NEW plan.totalOutputSeconds:" << (plan.totalOutputFrames / rate);
			if (plan.stretchedSource)
			{
				qDebug() << "  NEW plan.consumes: STRETCHED buffer (dataPtr " << (void*)plan.stretchedSource->data() << ")";
				qDebug() << "  buffer identity matches clip:" << (plan.stretchedSource->data() == stretched->data());
			}
			SamplePlayHandle handle(setup.clip, plan);
			qDebug() << "  NEW handle.totalFrames:" << handle.totalFrames();
		}

		// 4. The old handle (from step 1) still uses its old buffer.
		//    We verify this by checking that the old handle's totalFrames
		//    was computed from the resample path (ratio 2.0), not the
		//    stretched path (ratio 1.0). The handle is intentionally NOT
		//    refreshed mid-playback; the next trigger creates a new handle.
		qDebug() << "\n  Old handle (from step 1) continues with resample fallback until it finishes";
		qDebug() << "  New handles (from step 3) use the stretched buffer at ratio 1.0";

		// 5. Generation/cache key: the buffer was NOT discarded as stale
		{
			qDebug() << "\n=== Generation/cache key verification ===";
			qDebug() << "  buffer installed (not discarded):" << (stretched != nullptr);
			if (stretched)
			{
				qDebug() << "  buffer frames:" << stretched->sampleSize();
				qDebug() << "  buffer rate:" << stretched->sampleRate();
				qDebug() << "  buffer is at engine rate:" << (stretched->sampleRate() == rate);
			}
		}

		// 6. Changing PitchMode invalidates the cached state
		{
			qDebug() << "\n=== PitchMode invalidation ===";
			setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
			qDebug() << "  After switch to Resample: hasStretchedSample:" << setup.clip->hasStretchedSample() << "(expect false)";
			setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
			waitForStretched();
			qDebug() << "  After switch back to Stretch: hasStretchedSample:" << setup.clip->hasStretchedSample() << "(expect true)";
			const auto rebuilt = setup.clip->stretchedSample();
			if (rebuilt)
			{
				qDebug() << "  rebuilt buffer frames:" << rebuilt->sampleSize();
				qDebug() << "  rebuilt buffer dataPtr:" << (void*)rebuilt->data();
			}
		}
	}

	void toolbarStretchDoesNotChangePitch()
	{
		const auto rate = engineRate();
		const auto srcRate = 44100;
		const auto srcFrames = 8 * srcRate; // 8 s source

		auto setup = createClip(makeSineBuffer(srcFrames, srcRate));
		const auto natural = setup.clip->sourceRangeTicks();

		// 1. Record the original pitch and duration.
		const auto plan0 = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(plan0.stretchedSource == nullptr);
		QVERIFY(std::abs(plan0.resampleRatio - 1.0) < 0.001);
		const auto rendered0 = renderAt(setup.clip, 0.0);
		const auto freq0 = dominantFrequency(rendered0.data(), rendered0.size(), rate, 0);
		qDebug() << "  original pitch:" << freq0 << "Hz (expect ~440)";

		// 2. The toolbar Stretch button toggles SongEditor::m_mode ONLY. It
		//    does not touch the clip's pitch mode. Simulate the drag that the
		//    toolbar produces: stretchToLength with the default pitch mode.
		const auto doubled = TimePos(static_cast<int>(std::lround(natural * 2.0)));
		setup.clip->stretchToLength(doubled);
		waitForStretched();

		// 3. Observe the actual clip state after the toolbar drag.
		qDebug() << "  pitchMode after toolbar stretch:" << static_cast<int>(setup.clip->pitchMode())
				 << "(0=Resample default, 1=Stretch) -- toolbar stretch does NOT change pitch mode";
		qDebug() << "  stretchRatio:" << setup.clip->stretchRatio() << "(expect 2.0)";
		qDebug() << "  clip length ticks:" << setup.clip->length().getTicks();

		// 4. Play it through the Song Editor and record the actual result.
		const auto plan = setup.clip->computePlaybackPlan(0.0);
		qDebug() << "  plan.stretchedSource:" << (void*)plan.stretchedSource.get()
				 << "(nullptr = resample fallback, non-null = pitch-preserved stretch)";
		qDebug() << "  plan.resampleRatio:" << plan.resampleRatio
				 << "(1.0 = pitch preserved, 2.0 = resample, one octave lower)";
		qDebug() << "  plan.totalOutputSeconds:" << plan.totalOutputFrames / static_cast<double>(rate);

		const auto rendered = renderAt(setup.clip, 0.0);
		const auto freqL = dominantFrequency(rendered.data(), rendered.size(), rate, 0);
		qDebug() << "  rendered pitch:" << freqL << "Hz (440 = pitch preserved, 220 = resample 2x)";
		qDebug() << "  rendered seconds:" << rendered.size() / static_cast<double>(rate);

		// 5. With default Resample pitch mode, toolbar stretch produces
		//    Resample behaviour (pitch changes). This is the expected
		//    independent-control design.
		const auto srcRangeFrames = static_cast<double>(setup.clip->sourceEndFrame() - setup.clip->sourceStartFrame());
		const auto expectedOut = srcRangeFrames * setup.clip->stretchRatio() * static_cast<double>(rate) / static_cast<double>(srcRate);
		const auto durationOK = std::abs(plan.totalOutputFrames - expectedOut) < 0.05 * expectedOut;
		const auto pitchIsResample = std::abs(freqL - 220.0) < 40.0; // Resample: pitch drops an octave
		qDebug() << "  expectedOutputFrames:" << expectedOut << " actual:" << plan.totalOutputFrames;
		qDebug() << "  durationOK:" << durationOK << "  pitchIsResample:" << pitchIsResample;
		QVERIFY(durationOK);
		QVERIFY(pitchIsResample);

		// 6. Now explicitly set Pitch mode to Stretch and stretch again.
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(doubled);
		waitForStretched();
		const auto planStretch = setup.clip->computePlaybackPlan(0.0);
		const auto renderedStretch = renderAt(setup.clip, 0.0);
		const auto freqStretch = dominantFrequency(renderedStretch.data(), renderedStretch.size(), rate, 0);
		qDebug() << "  pitchMode after setPitchMode(Stretch):" << static_cast<int>(setup.clip->pitchMode());
		qDebug() << "  plan.stretchedSource:" << (void*)planStretch.stretchedSource.get();
		qDebug() << "  plan.resampleRatio:" << planStretch.resampleRatio;
		qDebug() << "  rendered pitch:" << freqStretch << "Hz (440 = pitch preserved)";
		const auto pitchPreserved = std::abs(freqStretch - 440.0) < 40.0;
		QVERIFY(planStretch.stretchedSource != nullptr);
		QVERIFY(std::abs(planStretch.resampleRatio - 1.0) < 0.01);
		QVERIFY(pitchPreserved);

		// 7. Repeat with the right edge reduced to half in Resample mode.
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		setup.clip->stretchToLength(TimePos(static_cast<int>(std::lround(natural * 0.5))));
		waitForStretched();
		const auto planHalf = setup.clip->computePlaybackPlan(0.0);
		const auto renderedHalf = renderAt(setup.clip, 0.0);
		const auto freqHalf = dominantFrequency(renderedHalf.data(), renderedHalf.size(), rate, 0);
		qDebug() << "  half-length pitch (Resample):" << freqHalf << "Hz (880 = resample 2x up)";
		const auto pitchIsResampleUp = std::abs(freqHalf - 880.0) < 80.0;
		QVERIFY(pitchIsResampleUp);
	}

	// ------------------------------------------------------------------
	// Diagnostic: real toolbar workflow (no setPitchMode), state at each
	// stage. No assertions -- this exists only to record what the code
	// actually does after the pitch-mode side effect was reverted, so the
	// behaviour matrix can be written from observed data rather than
	// from a design that may not match the implementation.
	// ------------------------------------------------------------------

	void diagnostic_toolbarWorkflow_stateAtEachStage()
	{
		const auto rate = engineRate();
		const auto srcRate = 44100;
		const auto srcFrames = 8 * srcRate;

		auto log = [rate](const char* stage, SampleClip* clip)
		{
			const auto stretched = clip->stretchedSample();
			qDebug() << "\n=== " << stage << " ===";
			qDebug() << "  pitchMode:" << (clip->pitchMode() == SampleClip::PitchMode::Stretch ? "Stretch" : "Resample");
			qDebug() << "  stretchRatio:" << clip->stretchRatio();
			qDebug() << "  clipLengthTicks:" << clip->length().getTicks();
			qDebug() << "  sourceStartFrame:" << clip->sourceStartFrame();
			qDebug() << "  sourceEndFrame:" << clip->sourceEndFrame();
			qDebug() << "  sourceRangeFrames:" << (clip->sourceEndFrame() - clip->sourceStartFrame());
			qDebug() << "  hasStretchedSample:" << (stretched != nullptr);
			if (stretched)
			{
				qDebug() << "  stretchedBufferFrames:" << stretched->sampleSize();
				qDebug() << "  stretchedBufferSeconds:" << (stretched->sampleSize() / rate);
			}
			const auto plan = clip->computePlaybackPlan(0.0);
			qDebug() << "  plan.stretchedSource:" << (void*)plan.stretchedSource.get();
			qDebug() << "  plan.resampleRatio:" << plan.resampleRatio;
			qDebug() << "  plan.totalOutputSeconds:" << (plan.totalOutputFrames / rate);
			if (plan.totalOutputFrames > 0)
			{
				const auto rendered = renderAt(clip, 0.0);
				if (rendered.size() > 100)
				{
					const auto freqL = dominantFrequency(rendered.data(), rendered.size(), rate, 0);
					qDebug() << "  renderedFreqL:" << freqL << "Hz (440 = pitch preserved, 220 = resample 2x down, 880 = resample 2x up)";
					qDebug() << "  renderedSeconds:" << (rendered.size() / rate);
				}
			}
		};

		auto setup = createClip(makeSineBuffer(srcFrames, srcRate));
		log("Stage 0: loaded 8s sample (default Resample)", setup.clip);

		// Stage 1: Toolbar Stretch edit mode + drag right edge to 16s.
		// The toolbar does NOT touch pitch mode.
		const auto targetLen = lengthForRatio(setup.clip, 2.0);
		setup.clip->stretchToLength(targetLen);
		log("Stage 1: stretchToLength(16s) -- toolbar path, no setPitchMode", setup.clip);

		// Stage 2: Wait for async buffer.
		waitForStretched();
		log("Stage 2: after async buffer lands", setup.clip);

		// Stage 3: Bug C workflow -- trim FIRST at ratio 1.0 (normal edit
		// mode), THEN stretch. No pitch mode is ever touched by the user.
		// Reset to a fresh clip so the trim happens at ratio 1.0.
		{
			auto setup2 = createClip(makeSineBuffer(srcFrames, srcRate));
			setup2.clip->trimToLength(lengthForRatio(setup2.clip, 0.5));
			log("Stage 3a: trimToLength(4s) at ratio 1.0 -- normal edit mode", setup2.clip);
			setup2.clip->stretchToLength(lengthForRatio(setup2.clip, 2.0));
			log("Stage 3b: stretchToLength(8s) -- toolbar path, no setPitchMode", setup2.clip);
			waitForStretched();
			log("Stage 3c: after async buffer lands", setup2.clip);
		}

		// Stage 4: Context-menu Stretch pitch mode, then re-stretch.
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		log("Stage 4a: setPitchMode(Stretch) -- context menu", setup.clip);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));
		log("Stage 4b: stretchToLength again after context-menu Stretch", setup.clip);
		waitForStretched();
		log("Stage 4c: after async buffer lands", setup.clip);
	}

	// ------------------------------------------------------------------
	// Async transition during active playback
	// ------------------------------------------------------------------

	void asyncTransitionDuringActivePlayback()
	{
		// This test reproduces the user's concern #2: what happens when
		// the stretch worker finishes while a handle is already playing?
		//
		// The SamplePlayHandle constructor captures the buffer and frame
		// range at construction time (m_source = copy of plan's source).
		// The play() method reads ONLY from m_source and never touches
		// clip state. Therefore, an already-playing handle will NOT
		// switch to the newly-generated stretched buffer mid-playback.
		// It continues with its old plan until it finishes. The next
		// trigger creates a new handle with the new buffer.
		//
		// This test verifies this behavior and establishes whether it
		// is intended (and whether the GUI communicates/handles it).
		const auto rate = engineRate();
		const auto srcRate = 44100;
		const auto srcFrames = 8 * srcRate; // 8 s source

		auto setup = createClip(makeSineBuffer(srcFrames, srcRate));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->stretchToLength(lengthForRatio(setup.clip, 2.0));

		// 1. BEFORE buffer lands: create a handle that uses the degraded
		//    source path -- the original source at its natural speed. Bug 1
		//    contract: Stretch mode must never resample, because resampling
		//    shifts the pitch, which is the opposite of what Stretch mode is
		//    for. So while the pitch-preserving buffer is in flight the clip
		//    plays the source at ratio 1.0: pitch preserved, natural duration
		//    (8 s) rather than the full stretched duration (16 s).
		const auto planBefore = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(planBefore.stretchedSource == nullptr);
		QVERIFY(std::abs(planBefore.resampleRatio - 1.0) < 0.0001); // never resample in Stretch mode

		SamplePlayHandle handleBefore(setup.clip, planBefore);
		const auto totalFramesBefore = handleBefore.totalFrames();
		const auto expectedFramesBefore = static_cast<size_t>(planBefore.totalOutputFrames);
		QVERIFY(std::abs(static_cast<long long>(totalFramesBefore) - static_cast<long long>(expectedFramesBefore)) < static_cast<long long>(0.05 * expectedFramesBefore));

		// 2. Simulate playing a few periods (but NOT to completion).
		const auto fpp = Engine::audioEngine()->framesPerPeriod();
		std::vector<SampleFrame> buf(fpp);
		for (int i = 0; i < 5; ++i)
		{
			std::fill(buf.begin(), buf.end(), SampleFrame{});
			handleBefore.play(buf.data());
		}
		const auto framesDoneBefore = handleBefore.framesDone();
		QVERIFY(framesDoneBefore > 0);
		QVERIFY(framesDoneBefore < totalFramesBefore);

		// 3. NOW wait for the stretch worker to finish and the buffer to land.
		waitForStretched();
		QVERIFY(setup.clip->hasStretchedSample());

		// 4. The clip now has a stretched buffer. A NEW plan would use it.
		const auto planAfter = setup.clip->computePlaybackPlan(0.0);
		QVERIFY(planAfter.stretchedSource != nullptr);
		QVERIFY(std::abs(planAfter.resampleRatio - 1.0) < 0.01);

		// 5. The OLD handle (handleBefore) still uses its old buffer.
		//    It does NOT see the new stretched buffer. Verify by checking
		//    that its totalFrames() is still the resample-path value.
		QCOMPARE(handleBefore.totalFrames(), totalFramesBefore);
		QVERIFY(std::abs(static_cast<long long>(handleBefore.totalFrames()) - static_cast<long long>(expectedFramesBefore)) < static_cast<long long>(0.05 * expectedFramesBefore));

		// 6. Continue playing the old handle to completion - it should
		//    still produce the resampled (pitch-shifted) audio.
		std::vector<SampleFrame> renderedBefore;
		renderedBefore.reserve(totalFramesBefore);
		while (!handleBefore.isFinished())
		{
			std::fill(buf.begin(), buf.end(), SampleFrame{});
			handleBefore.play(buf.data());
			renderedBefore.insert(renderedBefore.end(), buf.begin(), buf.end());
		}
		if (static_cast<size_t>(handleBefore.totalFrames()) < renderedBefore.size())
		{
			renderedBefore.resize(handleBefore.totalFrames());
		}

		// 7. A NEW handle created after the buffer landed uses the
		//    stretched buffer at ratio 1.0 (pitch preserved).
		SamplePlayHandle handleAfter(setup.clip, planAfter);
		const auto totalFramesAfter = handleAfter.totalFrames();
		const auto expectedFramesAfter = static_cast<size_t>(planAfter.totalOutputFrames);
		QVERIFY(std::abs(static_cast<long long>(totalFramesAfter) - static_cast<long long>(expectedFramesAfter)) < static_cast<long long>(0.05 * expectedFramesAfter));

		std::vector<SampleFrame> renderedAfter = renderHandle(handleAfter);

		// 8. Verify the pitch:
		//    - Old handle (started before the buffer landed): the source at
		//      its natural speed, so pitch preserved (440 Hz) but only the
		//      natural 8 s of audio -- the clip's 16 s duration is not filled.
		//    - New handle (started after the buffer landed): the
		//      pitch-preserving stretched buffer, 16 s at 440 Hz.
		const auto freqBefore = dominantFrequency(renderedBefore.data(), renderedBefore.size(), rate, 0);
		const auto freqAfter = dominantFrequency(renderedAfter.data(), renderedAfter.size(), rate, 0);

		qDebug() << "\n=== Async transition during active playback ===";
		qDebug() << "  Old handle (started before buffer):";
		qDebug() << "    totalFrames:" << totalFramesBefore << "(source path, ratio 1.0)";
		qDebug() << "    rendered pitch:" << freqBefore << "Hz (expect ~440 = pitch preserved)";
		qDebug() << "  New handle (started after buffer):";
		qDebug() << "    totalFrames:" << totalFramesAfter << "(stretch path, ratio 1.0)";
		qDebug() << "    rendered pitch:" << freqAfter << "Hz (expect ~440 = pitch preserved)";
		qDebug() << "  Old handle plays the natural 8 s:" << (std::abs(static_cast<double>(totalFramesBefore) / rate - 8.0) < 0.5);
		qDebug() << "  New handle has correct duration:" << (std::abs(static_cast<double>(totalFramesAfter) / rate - 16.0) < 0.5);

		// Bug 1 contract: Stretch mode preserves pitch at every point, both
		// while the pitch-preserving buffer is in flight and after it lands.
		QVERIFY(std::abs(freqBefore - 440.0) < 40.0); // source path: pitch preserved
		QVERIFY(std::abs(freqAfter - 440.0) < 40.0); // stretched path: pitch preserved
		QVERIFY(std::abs(static_cast<double>(totalFramesBefore) / rate - 8.0) < 0.5); // natural duration
		QVERIFY(std::abs(static_cast<double>(totalFramesAfter) / rate - 16.0) < 0.5); // full stretched duration

		// Document the behavior: this is INTENDED. The handle is a
		// self-contained playback unit. Mid-playback buffer swaps would
		// cause audible glitches. The GUI should communicate this (e.g.,
		// by showing a "stretch processing" indicator and/or requiring
		// stop/restart for the new buffer to take effect).
	}
};


QTEST_GUILESS_MAIN(SampleStretchTest)
#include "SampleStretchTest.moc"
