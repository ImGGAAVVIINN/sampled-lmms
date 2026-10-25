/*
 * SampleRecordingTest.cpp - tests for sample-recording state transitions and
 *                           captured input-buffer handling
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

#include <QtTest>

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "Engine.h"
#include "Song.h"

#include "AudioDevice.h"
#include "AudioEngine.h"
#include "SampleBuffer.h"
#include "SampleClip.h"
#include "SampleFrame.h"
#include "SampleRecordHandle.h"
#include "SampleTrack.h"

using namespace lmms;


namespace
{

/**
 * \brief Stand-in for a real capture backend.
 *
 * Periods are rendered by hand through AudioEngine::renderNextPeriod(), so the
 * processing hooks are inert. All that matters is whether the device advertises
 * capture support, since that is what gates the whole recording path.
 */
class FakeAudioDevice : public AudioDevice
{
public:
	FakeAudioDevice(bool supportsCapture, AudioEngine* engine) :
		AudioDevice(DEFAULT_CHANNELS, engine)
	{
		m_supportsCapture = supportsCapture;
	}

protected:
	void startProcessingImpl() override {}
	void stopProcessingImpl() override {}
};


//! Replace the current audio device with a fake one with the given capture support.
void installCaptureDevice(bool supportsCapture)
{
	Engine::audioEngine()->setAudioDevice(
		new FakeAudioDevice(supportsCapture, Engine::audioEngine()), false);
}


//! Hand frames to the engine the way a backend's real-time callback would.
void feedInput(const std::vector<SampleFrame>& frames)
{
	// pushInputFrames() only ever reads from the buffer, but takes a non-const pointer.
	Engine::audioEngine()->pushInputFrames(const_cast<SampleFrame*>(frames.data()),
		static_cast<f_cnt_t>(frames.size()));
}


std::vector<SampleFrame> makeFrames(size_t count, sample_t value)
{
	std::vector<SampleFrame> frames;
	frames.reserve(count);
	for (size_t i = 0; i < count; ++i)
	{
		frames.emplace_back(value, value);
	}
	return frames;
}


//! A sample track with a record clip spanning the whole first bar.
struct RecordingSetup
{
	SampleTrack* track;
	SampleClip* clip;
};


RecordingSetup createRecordingClip()
{
	auto track = new SampleTrack(Engine::getSong());
	auto clip = new SampleClip(track);
	clip->changeLength(TimePos(1440));
	clip->setRecord(true);
	return {track, clip};
}


//! Render periods until the recording clip has produced a record handle.
SampleRecordHandle* startRecordingHandle()
{
	for (int i = 0; i < 4; ++i)
	{
		Engine::audioEngine()->renderNextPeriod();
		if (!Engine::audioEngine()->playHandles().isEmpty())
		{
			return static_cast<SampleRecordHandle*>(Engine::audioEngine()->playHandles().at(0));
		}
	}
	return nullptr;
}

} // namespace


class SampleRecordingTest : public QObject
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

	//! Each test owns its device and its project, so recording state cannot leak.
	void cleanup()
	{
		Engine::getSong()->stop();
		Engine::getSong()->clearProject();
	}


	// ------------------------------------------------------------------
	// Recording-state transitions
	// ------------------------------------------------------------------

	//! Arming a take without a capture device must be refused: the only thing that
	//! could be recorded is the engine's empty input buffer, which would replace the
	//! clip's audio with silence.
	void refusesToArmRecordingWithoutCaptureDevice()
	{
		installCaptureDevice(false);
		QVERIFY(!Engine::audioEngine()->captureDeviceAvailable());

		Engine::getSong()->playAndRecord();

		QCOMPARE(Engine::getSong()->playMode(), Song::PlayMode::None);
		QVERIFY(!Engine::getSong()->isRecording());
	}

	//! With a capture device the same call arms recording as it always did.
	void armsRecordingWithCaptureDevice()
	{
		installCaptureDevice(true);
		QVERIFY(Engine::audioEngine()->captureDeviceAvailable());

		Engine::getSong()->playAndRecord();

		QCOMPARE(Engine::getSong()->playMode(), Song::PlayMode::Song);
		QVERIFY(Engine::getSong()->isRecording());
	}

	//! Regression guard for the bug where Song::stop() set m_recording instead of
	//! clearing it, which made every later playback keep recording into whatever
	//! record clip was still lying around in the project.
	void stopEndsRecording()
	{
		installCaptureDevice(true);
		Engine::getSong()->playAndRecord();
		QVERIFY(Engine::getSong()->isRecording());

		Engine::getSong()->stop();

		QVERIFY(!Engine::getSong()->isRecording());
		QCOMPARE(Engine::getSong()->playMode(), Song::PlayMode::None);
	}

	//! Plain playback must never record, whichever entry point starts it.
	void playbackNeverRecords()
	{
		installCaptureDevice(true);

		Engine::getSong()->playAndRecord();
		QVERIFY(Engine::getSong()->isRecording());
		Engine::getSong()->playSong();
		QVERIFY(!Engine::getSong()->isRecording());

		Engine::getSong()->playAndRecord();
		QVERIFY(Engine::getSong()->isRecording());
		Engine::getSong()->playPattern();
		QVERIFY(!Engine::getSong()->isRecording());

		Engine::getSong()->playAndRecord();
		QVERIFY(Engine::getSong()->isRecording());
		Engine::getSong()->playMidiClip(nullptr);
		QVERIFY(!Engine::getSong()->isRecording());

		Engine::getSong()->stop();
		QVERIFY(!Engine::getSong()->isRecording());
	}


	// ------------------------------------------------------------------
	// Captured-buffer handling
	// ------------------------------------------------------------------

	//! Frames pushed by a backend become readable from the next rendered period and
	//! are not duplicated after that. This is the contract the PortAudio forwarding
	//! added for this work relies on.
	void pushedFramesBecomeReadableOnce()
	{
		installCaptureDevice(true);

		feedInput(makeFrames(64, 0.5f));
		Engine::audioEngine()->renderNextPeriod();

		QCOMPARE(Engine::audioEngine()->inputBufferFrames(), 64);
		const auto* readable = Engine::audioEngine()->inputBuffer();
		QVERIFY(readable != nullptr);
		QCOMPARE(readable[0].left(), 0.5f);
		QCOMPARE(readable[63].right(), 0.5f);

		Engine::audioEngine()->renderNextPeriod();
		QCOMPARE(Engine::audioEngine()->inputBufferFrames(), 0);
	}

	//! A take with nothing in it must leave the clip's existing audio alone rather
	//! than overwrite it with an empty buffer.
	void emptyTakeLeavesClipAudioAlone()
	{
		installCaptureDevice(true);
		Engine::getSong()->playAndRecord();

		auto setup = createRecordingClip();
		setup.clip->setSampleBuffer(std::make_shared<const SampleBuffer>(makeFrames(100, 0.25f), 22050));
		QCOMPARE(setup.clip->sample().sampleSize(), size_t{100});

		// A few periods with no input at all: the handle exists but records nothing.
		auto* handle = startRecordingHandle();
		QVERIFY(handle != nullptr);
		QCOMPARE(handle->framesRecorded(), 0);

		Engine::getSong()->stop();

		QVERIFY(!Engine::getSong()->isRecording());
		QCOMPARE(setup.clip->sample().sampleSize(), size_t{100});
		QVERIFY(!setup.clip->isRecord());
	}

	//! End to end within the engine: captured frames flow through the record handle
	//! and are committed to the clip as a sample of the expected length and rate.
	void capturedFramesAreCommittedToClip()
	{
		installCaptureDevice(true);
		Engine::getSong()->playAndRecord();

		auto setup = createRecordingClip();

		auto* handle = startRecordingHandle();
		QVERIFY(handle != nullptr);

		const auto period = Engine::audioEngine()->framesPerPeriod();
		for (int i = 0; i < 4; ++i)
		{
			feedInput(makeFrames(period, 0.5f));
			Engine::audioEngine()->renderNextPeriod();
		}

		QCOMPARE(handle->framesRecorded(), 4 * period);

		Engine::getSong()->stop();

		// The take is committed on the clip's thread, which is this one, so it has
		// already happened by the time stop() returns.
		QCOMPARE(setup.clip->sample().sampleSize(), static_cast<size_t>(4 * period));
		QCOMPARE(setup.clip->sample().sampleRate(), Engine::audioEngine()->inputSampleRate());
		QVERIFY(std::all_of(setup.clip->sample().data(),
			setup.clip->sample().data() + 4 * period,
			[](const SampleFrame& frame) { return std::abs(frame.left() - 0.5f) < 1e-5f; }));
		QVERIFY(!setup.clip->isRecord());
	}
};


QTEST_GUILESS_MAIN(SampleRecordingTest)
#include "SampleRecordingTest.moc"
