/*
 * SampleStretchTest.cpp - tests for the sample-clip time-stretch feature:
 *   - stretch ratio math (clip length vs. sample length)
 *   - Resample vs. Stretch pitch modes (mutually exclusive, no length change)
 *   - offline stretch engine (duration, source untouched, cache key)
 *   - async stretch pipeline (generation ids, stale results dropped)
 *   - serialization round-trip (stretchmode attribute, old projects default)
 *   - undo journaling (one entry per mode switch)
 *   - playback duration (SamplePlayHandle totalFrames)
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

#include <QDomDocument>
#include <QEventLoop>
#include <QSignalSpy>
#include <QTest>
#include <QTimer>

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

//! Engine output sample rate, fixed for the whole test run.
sample_rate_t engineRate()
{
	return Engine::audioEngine()->outputSampleRate();
}

//! A 44100 Hz stereo buffer of `frames` frames: a 440 Hz sine on the left
//! channel and a 880 Hz sine on the right channel, so that pitch changes
//! (Resample mode) are detectable per channel while the two channels stay
//! phase-coherent in Stretch mode.
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

//! A sample track with a clip whose sample is `buffer`.
struct ClipSetup
{
	SampleTrack* track;
	SampleClip* clip;
};

ClipSetup createClip(std::shared_ptr<const SampleBuffer> buffer)
{
	auto track = new SampleTrack(Engine::getSong());
	auto clip = new SampleClip(track);
	clip->setSampleBuffer(std::move(buffer));
	return {track, clip};
}

//! Clip length in ticks that makes the clip exactly `ratio` times the
//! sample's natural length.
TimePos lengthForRatio(const SampleClip* clip, double ratio)
{
	return static_cast<int>(std::lround(clip->sampleLength() * ratio));
}

//! Position the clip's sample the way SampleTrack::play() does right before
//! it constructs a SamplePlayHandle: the clip's whole remaining frame length,
//! clamped to the source buffer's size.
void positionSample(SampleClip* clip)
{
	const auto bufferFramesPerTick = Engine::framesPerTick(clip->sample().sampleRate());
	const auto clipFrameLength = static_cast<f_cnt_t>(
		bufferFramesPerTick * (clip->endPosition() - clip->startPosition() - clip->startTimeOffset()));
	const auto sampleBufferLength = static_cast<f_cnt_t>(clip->sample().sampleSize());
	clip->setSampleStartFrame(0);
	clip->setSamplePlayLength(std::min(clipFrameLength, sampleBufferLength));
}

//! Pump the event loop until the clip has (or has not) a stretched sample.
bool waitForStretchedSample(SampleClip* clip, bool expect, int timeoutMs = 10000)
{
	QEventLoop loop;
	QTimer::singleShot(timeoutMs, &loop, &QEventLoop::quit);
	QObject::connect(clip, &SampleClip::sampleChanged, &loop, [&loop, clip, expect]()
	{
		if (clip->hasStretchedSample() == expect) { loop.quit(); }
	});
	if (clip->hasStretchedSample() == expect) { return true; }
	loop.exec();
	return clip->hasStretchedSample() == expect;
}

//! Dominant frequency of a mono channel, in Hz (zero-crossing count).
double dominantFrequency(const SampleFrame* data, size_t frames, int rate, int channel)
{
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
	// Ratio math
	// ------------------------------------------------------------------

	//! A clip at its natural sample length has ratio 1.0 and is not stretched.
	void ratioIsOneAtNaturalLength()
	{
		auto setup = createClip(makeSineBuffer(44100)); // 1 s at 44100 Hz
		QCOMPARE(setup.clip->stretchRatio(), 1.0);
		QVERIFY(!setup.clip->isStretched());
	}

	//! Dragging the clip to twice the sample length gives ratio 2.0.
	void ratioFollowsClipLength()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		QVERIFY(std::abs(setup.clip->stretchRatio() - 2.0) < 0.01);
		QVERIFY(setup.clip->isStretched());

		// Back to the natural length: ratio 1.0 again, original path.
		setup.clip->changeLength(lengthForRatio(setup.clip, 1.0));
		QVERIFY(std::abs(setup.clip->stretchRatio() - 1.0) < 0.01);
		QVERIFY(!setup.clip->isStretched());
	}

	//! A shorter clip gives a ratio below 1.0.
	void ratioBelowOneWhenShortened()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 0.5));
		QVERIFY(std::abs(setup.clip->stretchRatio() - 0.5) < 0.01);
		QVERIFY(setup.clip->isStretched());
	}


	// ------------------------------------------------------------------
	// Pitch modes
	// ------------------------------------------------------------------

	//! New clips default to Resample (the traditional behaviour).
	void defaultModeIsResample()
	{
		auto setup = createClip(makeSineBuffer(44100));
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
	}

	//! Switching to Stretch must not change the clip's length.
	void modeSwitchKeepsLength()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		const auto length = setup.clip->length();

		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QCOMPARE(setup.clip->length(), length);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Stretch);

		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		QCOMPARE(setup.clip->length(), length);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
	}

	//! Selecting the already-active mode is a no-op.
	void selectingActiveModeIsNoOp()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		const auto length = setup.clip->length();

		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		QCOMPARE(setup.clip->length(), length);
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
	}

	//! Stretch mode at ratio 1.0 bypasses processing entirely.
	void stretchModeAtRatioOneBypasses()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QVERIFY(!setup.clip->isStretched());
		QVERIFY(!setup.clip->hasStretchedSample());
	}

	//! Switching back to Resample clears any stretched buffer.
	void switchingToResampleClearsStretchedBuffer()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QVERIFY(waitForStretchedSample(setup.clip, true));

		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);
		QVERIFY(!setup.clip->hasStretchedSample());
	}


	// ------------------------------------------------------------------
	// Offline stretch engine
	// ------------------------------------------------------------------

	//! The stretched buffer is `ratio` times as long as the input.
	void stretchDurationFollowsRatio()
	{
		const auto buffer = makeSineBuffer(44100); // 1 s
		const auto stretched = SampleStretch::stretch(
			buffer, 0, static_cast<int>(buffer->size()),
			44100, engineRate(), 2.0);
		QVERIFY(stretched != nullptr);
		QCOMPARE(stretched->sampleRate(), static_cast<int>(engineRate()));
		// 1 s of input stretched by 2.0 => ~2 s of output at engine rate.
		const auto expected = static_cast<size_t>(2.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(stretched->sampleSize()) - expected)
			< 0.05 * expected);
	}

	//! The source buffer is never modified by stretching.
	void stretchLeavesSourceUntouched()
	{
		const auto buffer = makeSineBuffer(44100);
		const auto before = buffer->data()[100];
		const auto sizeBefore = buffer->size();

		const auto stretched = SampleStretch::stretch(
			buffer, 0, static_cast<int>(buffer->size()),
			44100, engineRate(), 1.5);
		QVERIFY(stretched != nullptr);

		QCOMPARE(buffer->size(), sizeBefore);
		QCOMPARE(buffer->data()[100].left(), before.left());
		QCOMPARE(buffer->data()[100].right(), before.right());
	}

	//! Stretching a subrange only stretches that subrange, wherever it sits
	//! inside the source buffer.
	void stretchHonoursSubrange()
	{
		const auto buffer = makeSineBuffer(88200); // 2 s
		const auto quarter = static_cast<int>(buffer->size()) / 4; // 0.5 s

		// 0.5 s of input stretched by 2.0 => ~1 s of output.
		const auto expected = static_cast<size_t>(1.0 * engineRate());

		const auto fromStart = SampleStretch::stretch(
			buffer, 0, quarter, 44100, engineRate(), 2.0);
		QVERIFY(fromStart != nullptr);
		QVERIFY(std::abs(static_cast<double>(fromStart->sampleSize()) - expected)
			< 0.05 * expected);

		// The same span taken from the middle of the buffer gives the same
		// amount of audio, so the start offset is honoured too.
		const auto fromMiddle = SampleStretch::stretch(
			buffer, quarter, quarter * 2, 44100, engineRate(), 2.0);
		QVERIFY(fromMiddle != nullptr);
		QVERIFY(std::abs(static_cast<double>(fromMiddle->sampleSize()) - expected)
			< 0.05 * expected);

		// And a shorter span really does give proportionally less audio, i.e.
		// the whole buffer is not being stretched behind our back.
		const auto eighth = SampleStretch::stretch(
			buffer, 0, quarter / 2, 44100, engineRate(), 2.0);
		QVERIFY(eighth != nullptr);
		const auto halfExpected = expected / 2;
		QVERIFY(std::abs(static_cast<double>(eighth->sampleSize()) - halfExpected)
			< 0.05 * halfExpected);
	}

	//! Degenerate inputs return nullptr instead of crashing.
	void stretchRejectsDegenerateInputs()
	{
		const auto buffer = makeSineBuffer(44100);
		QVERIFY(SampleStretch::stretch(buffer, 0, 0, 44100, engineRate(), 2.0) == nullptr);
		QVERIFY(SampleStretch::stretch(buffer, 0, 1, 44100, engineRate(), 2.0) == nullptr);
		QVERIFY(SampleStretch::stretch(buffer, 0, static_cast<int>(buffer->size()), 0, engineRate(), 2.0) == nullptr);
		QVERIFY(SampleStretch::stretch(buffer, 0, static_cast<int>(buffer->size()), 44100, engineRate(), 0.0) == nullptr);
		QVERIFY(SampleStretch::stretch(nullptr, 0, 100, 44100, engineRate(), 2.0) == nullptr);
	}

	//! The cache key changes with every parameter that affects the output.
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


	// ------------------------------------------------------------------
	// Async pipeline
	// ------------------------------------------------------------------

	//! A stretched clip eventually gets its stretched sample, and the
	//! stretched buffer preserves pitch (unlike Resample mode).
	void asyncStretchProducesPitchPreservingBuffer()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);

		QVERIFY(waitForStretchedSample(setup.clip, true));

		const auto stretched = setup.clip->stretchedSample();
		QVERIFY(stretched != nullptr);
		QCOMPARE(stretched->sampleRate(), static_cast<int>(engineRate()));

		// Pitch must be preserved: the left channel still dominates at 440 Hz.
		const auto* data = stretched->data();
		const auto frames = stretched->sampleSize();
		const auto freq = dominantFrequency(data, frames, stretched->sampleRate(), 0);
		QVERIFY(std::abs(freq - 440.0) < 40.0);
	}

	//! Changing the length while a stretch is in flight must not apply the
	//! stale result: the committed buffer matches the final ratio.
	void staleResultsAreDiscarded()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QVERIFY(waitForStretchedSample(setup.clip, true));

		// Now drag to a different length; the in-flight/previous result must
		// be superseded and a new one committed for the new ratio.
		setup.clip->changeLength(lengthForRatio(setup.clip, 3.0));
		QVERIFY(waitForStretchedSample(setup.clip, true));

		const auto stretched = setup.clip->stretchedSample();
		QVERIFY(stretched != nullptr);
		// 1 s of input stretched by 3.0 => ~3 s of output.
		const auto expected = static_cast<size_t>(3.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(stretched->sampleSize()) - expected)
			< 0.05 * expected);
	}

	//! Two clips sharing one source buffer must not interfere: each gets its
	//! own stretched buffer for its own ratio.
	void sharedSourceClipsDoNotInterfere()
	{
		const auto buffer = makeSineBuffer(44100);
		auto a = createClip(buffer);
		auto b = createClip(buffer);

		a.clip->changeLength(lengthForRatio(a.clip, 2.0));
		a.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		b.clip->changeLength(lengthForRatio(b.clip, 3.0));
		b.clip->setPitchMode(SampleClip::PitchMode::Stretch);

		QVERIFY(waitForStretchedSample(a.clip, true));
		QVERIFY(waitForStretchedSample(b.clip, true));

		const auto sa = a.clip->stretchedSample();
		const auto sb = b.clip->stretchedSample();
		QVERIFY(sa != nullptr);
		QVERIFY(sb != nullptr);
		QVERIFY(sa->buffer() != sb->buffer());

		const auto expectedA = static_cast<size_t>(2.0 * engineRate());
		const auto expectedB = static_cast<size_t>(3.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(sa->sampleSize()) - expectedA) < 0.05 * expectedA);
		QVERIFY(std::abs(static_cast<double>(sb->sampleSize()) - expectedB) < 0.05 * expectedB);
	}


	// ------------------------------------------------------------------
	// Serialization
	// ------------------------------------------------------------------

	//! The pitch mode is saved and restored; the length is unchanged.
	void serializationRoundTrip()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		const auto length = setup.clip->length();

		QDomDocument doc;
		QDomElement parent = doc.createElement("track");
		doc.appendChild(parent);
		setup.clip->saveState(doc, parent);

		const auto saved = parent.firstChildElement("sampleclip");
		QVERIFY(!saved.isNull());
		QCOMPARE(saved.attribute("stretchmode").toInt(),
			static_cast<int>(SampleClip::PitchMode::Stretch));

		auto track2 = new SampleTrack(Engine::getSong());
		auto clip2 = new SampleClip(track2);
		clip2->loadSettings(saved);
		QCOMPARE(clip2->pitchMode(), SampleClip::PitchMode::Stretch);
		QCOMPARE(clip2->length(), length);
	}

	//! A project without the stretchmode attribute (old project) keeps the
	//! Resample default.
	void oldProjectsDefaultToResample()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));

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


	// ------------------------------------------------------------------
	// Undo journaling
	// ------------------------------------------------------------------

	//! One mode switch produces exactly one undo entry, and undo restores
	//! the previous mode without touching the length.
	void modeSwitchIsOneUndoEntry()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		const auto length = setup.clip->length();

		// The context menu wraps the switch in a journal checkpoint.
		setup.track->addJournalCheckPoint();
		setup.clip->setJournalling(false);
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		setup.clip->setJournalling(true);

		QVERIFY(Engine::projectJournal()->canUndo());
		Engine::projectJournal()->undo();
		QCOMPARE(setup.clip->pitchMode(), SampleClip::PitchMode::Resample);
		QCOMPARE(setup.clip->length(), length);
	}


	// ------------------------------------------------------------------
	// Playback duration
	// ------------------------------------------------------------------

	//! A Resample-mode handle plays the clip's duration (ratio applied to
	//! the original sample).
	void resampleHandleDurationMatchesClip()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Resample);

		// Position the sample the way SampleTrack::play() does.
		positionSample(setup.clip);

		SamplePlayHandle handle(setup.clip);
		// The handle must render ~2 s of audio at the engine rate.
		const auto expected = static_cast<f_cnt_t>(2.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(handle.totalFrames()) - expected)
			< 0.05 * expected);
	}

	//! A Stretch-mode handle with a ready stretched buffer plays the
	//! stretched buffer at ratio 1.0 for the same clip duration.
	void stretchHandleDurationMatchesClip()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->changeLength(lengthForRatio(setup.clip, 2.0));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QVERIFY(waitForStretchedSample(setup.clip, true));

		positionSample(setup.clip);

		SamplePlayHandle handle(setup.clip);
		const auto expected = static_cast<f_cnt_t>(2.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(handle.totalFrames()) - expected)
			< 0.05 * expected);
	}

	//! At ratio 1.0 the handle uses the original playback path (no
	//! stretched buffer, ratio 1.0).
	void ratioOneUsesOriginalPath()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setPitchMode(SampleClip::PitchMode::Stretch);
		QVERIFY(!setup.clip->hasStretchedSample());

		positionSample(setup.clip);

		SamplePlayHandle handle(setup.clip);
		const auto expected = static_cast<f_cnt_t>(1.0 * engineRate());
		QVERIFY(std::abs(static_cast<double>(handle.totalFrames()) - expected)
			< 0.05 * expected);
	}

	//! A missing source file must not crash: the clip stays usable with an
	//! empty sample and ratio 1.0.
	void missingSourceFileDoesNotCrash()
	{
		auto setup = createClip(makeSineBuffer(44100));
		setup.clip->setSampleFile("/nonexistent/path/to/sample.wav");
		QVERIFY(setup.clip->sample().sampleSize() == 0);
		QCOMPARE(setup.clip->stretchRatio(), 1.0);
		QVERIFY(!setup.clip->hasStretchedSample());
	}
};


QTEST_GUILESS_MAIN(SampleStretchTest)
#include "SampleStretchTest.moc"
