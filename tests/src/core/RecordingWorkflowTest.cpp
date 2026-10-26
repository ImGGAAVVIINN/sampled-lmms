/*
 * RecordingWorkflowTest.cpp - tests for the recording workflow entry points
 *                             (recordSelectedTrack / recordNewTrack / ensureRecordClip)
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

#include "Engine.h"
#include "Song.h"
#include "SampleClip.h"
#include "SampleTrack.h"
#include "AudioDevice.h"
#include "AudioEngine.h"

using namespace lmms;


namespace
{

/**
 * \brief Stand-in audio device whose only job is to advertise (or not) capture
 * support so Song::playAndRecord() either arms or refuses to arm.
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


void installCaptureDevice(bool supportsCapture)
{
	Engine::audioEngine()->setAudioDevice(
		new FakeAudioDevice(supportsCapture, Engine::audioEngine()), false);
}


//! Count how many SampleClips on `track` are armed for recording.
int countRecordClips(SampleTrack* track)
{
	int n = 0;
	for (auto* clip : track->getClips())
	{
		if (auto* sc = qobject_cast<SampleClip*>(clip))
		{
			if (sc->isRecord()) { ++n; }
		}
	}
	return n;
}


//! Find the first SampleClip on `track` that is armed for recording, or nullptr.
SampleClip* findRecordClip(SampleTrack* track)
{
	for (auto* clip : track->getClips())
	{
		if (auto* sc = qobject_cast<SampleClip*>(clip))
		{
			if (sc->isRecord()) { return sc; }
		}
	}
	return nullptr;
}

} // namespace


class RecordingWorkflowTest : public QObject
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
		Engine::getSong()->setSelectedTrack(nullptr);
	}


	// ------------------------------------------------------------------
	// (a) Recording creates a SampleClip when none exists yet.
	// ------------------------------------------------------------------
	void recordSelectedTrackCreatesClipWhenNoneExists()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* track = new SampleTrack(song);
		song->setSelectedTrack(track);
		QCOMPARE(countRecordClips(track), 0);

		song->recordSelectedTrack();

		QCOMPARE(countRecordClips(track), 1);
		auto* clip = findRecordClip(track);
		QVERIFY(clip != nullptr);
		QVERIFY(clip->isRecord());
	}


	// ------------------------------------------------------------------
	// (b) The created clip belongs to the selected Sample Track.
	// ------------------------------------------------------------------
	void recordSelectedTrackUsesSelectedSampleTrack()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* a = new SampleTrack(song);
		auto* b = new SampleTrack(song);
		song->setSelectedTrack(b);

		song->recordSelectedTrack();

		QCOMPARE(countRecordClips(a), 0);
		QCOMPARE(countRecordClips(b), 1);
	}


	// ------------------------------------------------------------------
	// (c) The record clip starts at the requested playhead position.
	// ------------------------------------------------------------------
	void recordClipStartsAtPlayhead()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* track = new SampleTrack(song);
		song->setSelectedTrack(track);
		song->setPlayPos(384); // bar 2, beat 1

		song->recordSelectedTrack();

		auto* clip = findRecordClip(track);
		QVERIFY(clip != nullptr);
		QCOMPARE(clip->startPosition().getTicks(), tick_t{384});
	}


	// ------------------------------------------------------------------
	// (d) An existing non-recording audio clip is not overwritten.
	// ------------------------------------------------------------------
	void existingNonRecordClipIsNotOverwritten()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* track = new SampleTrack(song);
		song->setSelectedTrack(track);

		// Pre-existing playback clip at bar 0.
		auto* existing = new SampleClip(track);
		existing->movePosition(TimePos(0));
		existing->changeLength(TimePos(192));
		existing->setRecord(false);
		QVERIFY(!existing->isRecord());

		song->setPlayPos(384);
		song->recordSelectedTrack();

		// The pre-existing clip must still be a plain playback clip.
		QVERIFY(!existing->isRecord());
		// And there must now be exactly one record clip, distinct from the old one.
		QCOMPARE(countRecordClips(track), 1);
		auto* rec = findRecordClip(track);
		QVERIFY(rec != nullptr);
		QVERIFY(rec != existing);
		QCOMPARE(rec->startPosition().getTicks(), tick_t{384});
	}


	// ------------------------------------------------------------------
	// (e) record-to-new-track creates and selects a new Sample Track.
	// ------------------------------------------------------------------
	void recordNewTrackCreatesAndSelectsSampleTrack()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		const auto before = song->tracks().size();

		song->recordNewTrack();

		QCOMPARE(static_cast<int>(song->tracks().size()), static_cast<int>(before + 1));
		auto* last = dynamic_cast<SampleTrack*>(song->tracks().back());
		QVERIFY(last != nullptr);
		QCOMPARE(song->selectedTrack(), static_cast<Track*>(last));
		QCOMPARE(countRecordClips(last), 1);
		auto* clip = findRecordClip(last);
		QVERIFY(clip != nullptr);
		QVERIFY(clip->isRecord());
	}
};


QTEST_GUILESS_MAIN(RecordingWorkflowTest)
#include "RecordingWorkflowTest.moc"
