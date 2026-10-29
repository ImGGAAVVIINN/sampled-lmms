/*
 * RecordingWorkflowTest.cpp - tests for the recording workflow entry points
 *                             (record / recordSelectedTrack / recordNewTrack /
 *                              ensureRecordClip) and for the "last-interacted
 *                              Sample Track" selection semantics behind them.
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

#include <QtTest>

#include "Engine.h"
#include "Song.h"
#include "SampleClip.h"
#include "SampleTrack.h"
#include "AudioDevice.h"
#include "AudioEngine.h"
#include "Track.h"

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


//! Count every armed clip in the song, used to prove recording did nothing.
int countAllRecordClips()
{
	int n = 0;
	for (auto* track : Engine::getSong()->tracks())
	{
		if (auto* st = dynamic_cast<SampleTrack*>(track)) { n += countRecordClips(st); }
	}
	return n;
}


//! Add a Sample Track the way the GUI does, ie. through Track::create(), which
//! is what tells the song that the new track is the one the user is working on.
SampleTrack* addSampleTrackViaGui(Song* song)
{
	return dynamic_cast<SampleTrack*>(Track::create(Track::Type::Sample, song));
}


//! Add a track of another kind, which must never become a recording target.
Track* addTrackOfType(Song* song, Track::Type type)
{
	return Track::create(type, song);
}

} // namespace


class RecordingWorkflowTest : public QObject
{
	Q_OBJECT

private slots:

	void initTestCase()
	{
		Engine::init(true);
		// QSignalSpy needs to be able to store a `recordModeChanged` argument.
		qRegisterMetaType<Song::RecordMode>("Song::RecordMode");
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
		Engine::getSong()->setRecordMode(Song::RecordMode::NewTrack);
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


	// ==================================================================
	// Selection semantics: "selected" means the Sample Track the user last
	// interacted with, not a Qt selection flag.
	//
	// The GUI reports an interaction through TrackView, which ends up calling
	// Song::setSelectedTrack(); these tests drive that same entry point, which
	// is the whole contract between the views and the model.
	// ==================================================================

	// ------------------------------------------------------------------
	// (f) Interacting with a Sample Track makes it the recording target.
	// ------------------------------------------------------------------
	void interactingWithTrackRetargetsRecording()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* a = new SampleTrack(song);
		auto* b = new SampleTrack(song);

		song->setSelectedTrack(a);
		QCOMPARE(song->selectedTrack(), static_cast<Track*>(a));
		song->recordSelectedTrack();
		QCOMPARE(countRecordClips(a), 1);
		QCOMPARE(countRecordClips(b), 0);

		song->stop();
		song->setSelectedTrack(b);
		QCOMPARE(song->selectedTrack(), static_cast<Track*>(b));
		song->recordSelectedTrack();
		QCOMPARE(countRecordClips(a), 1);
		QCOMPARE(countRecordClips(b), 1);
	}


	// ------------------------------------------------------------------
	// (g) Reordering keeps the same logical track as the target.
	// ------------------------------------------------------------------
	void reorderingPreservesTarget()
	{
		auto* song = Engine::getSong();
		auto* a = new SampleTrack(song);
		auto* b = new SampleTrack(song);
		song->setSelectedTrack(a);

		// Drag `a` to the bottom of the list: same object, different index.
		song->moveTrack(a, static_cast<int>(song->tracks().size()) - 1);

		QCOMPARE(song->selectedTrack(), static_cast<Track*>(a));
		QVERIFY(std::find(song->tracks().begin(), song->tracks().end(), a)
			== song->tracks().end() - 1);
		QCOMPARE(countRecordClips(a), 0);

		installCaptureDevice(true);
		song->recordSelectedTrack();
		QCOMPARE(countRecordClips(a), 1);
		QCOMPARE(countRecordClips(b), 0);
	}


	// ------------------------------------------------------------------
	// (h) Adding a Sample Track through the GUI makes it the target.
	// ------------------------------------------------------------------
	void addingSampleTrackSelectsIt()
	{
		auto* song = Engine::getSong();
		auto* first = new SampleTrack(song);
		song->setSelectedTrack(first);

		auto* added = addSampleTrackViaGui(song);
		QVERIFY(added != nullptr);
		QCOMPARE(song->selectedTrack(), static_cast<Track*>(added));
	}


	// ------------------------------------------------------------------
	// (i) Adding a track that cannot record must not steal the target.
	// ------------------------------------------------------------------
	void addingNonSampleTrackKeepsTarget()
	{
		auto* song = Engine::getSong();
		auto* sample = new SampleTrack(song);
		song->setSelectedTrack(sample);

		auto* pattern = addTrackOfType(song, Track::Type::Pattern);
		QVERIFY(pattern != nullptr);
		QCOMPARE(song->selectedTrack(), static_cast<Track*>(sample));

		// Interacting with it directly is ignored too: it can hold no take.
		song->setSelectedTrack(pattern);
		QCOMPARE(song->selectedTrack(), static_cast<Track*>(sample));

		auto* automation = addTrackOfType(song, Track::Type::Automation);
		song->setSelectedTrack(automation);
		QCOMPARE(song->selectedTrack(), static_cast<Track*>(sample));
	}


	// ------------------------------------------------------------------
	// (j) Removing the target moves the target to a surviving Sample Track.
	// ------------------------------------------------------------------
	void removingTargetMovesTargetToNeighbour()
	{
		auto* song = Engine::getSong();
		auto* a = new SampleTrack(song);
		auto* b = new SampleTrack(song);
		auto* c = new SampleTrack(song);
		Q_UNUSED(c)
		song->setSelectedTrack(b);

		delete b;

		// `b` sat between `a` and `c`; either neighbour is a fair answer, but it
		// must be one of the surviving Sample Tracks and never the dead one.
		QVERIFY(song->selectedTrack() == static_cast<Track*>(a)
			|| song->selectedTrack() == c);
		QCOMPARE(static_cast<int>(song->tracks().size()), 2);
	}


	// ------------------------------------------------------------------
	// (k) Removing some other track leaves the target alone.
	// ------------------------------------------------------------------
	void removingOtherTrackKeepsTarget()
	{
		auto* song = Engine::getSong();
		auto* a = new SampleTrack(song);
		auto* b = new SampleTrack(song);
		song->setSelectedTrack(a);

		delete b;

		QCOMPARE(song->selectedTrack(), static_cast<Track*>(a));
	}


	// ------------------------------------------------------------------
	// (l) Removing the last Sample Track clears the target instead of leaving
	// it pointing at freed memory.
	// ------------------------------------------------------------------
	void removingLastSampleTrackClearsTarget()
	{
		auto* song = Engine::getSong();
		auto* only = new SampleTrack(song);
		song->setSelectedTrack(only);

		delete only;

		QVERIFY(song->selectedTrack() == nullptr);
	}


	// ------------------------------------------------------------------
	// (m) With no Sample Track, "record into selected track" fails cleanly:
	// nothing is recorded, nothing is played, and no track is invented.
	// ------------------------------------------------------------------
	void recordSelectedTrackWithoutSampleTrackDoesNothing()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		QCOMPARE(static_cast<int>(song->tracks().size()), 0);
		QVERIFY(song->selectedTrack() == nullptr);
		const auto tracksBefore = song->tracks().size();

		song->recordSelectedTrack();

		QCOMPARE(static_cast<int>(song->tracks().size()), static_cast<int>(tracksBefore));
		QCOMPARE(countAllRecordClips(), 0);
		QVERIFY(!song->isRecording());
		QVERIFY(!song->isPlaying());
	}


	// ------------------------------------------------------------------
	// (n) A stale target is never used: after the target dies, recording
	// refuses rather than falling back to an unrelated track.
	// ------------------------------------------------------------------
	void recordSelectedTrackAfterTargetRemovedDoesNothing()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* only = new SampleTrack(song);
		song->setSelectedTrack(only);
		delete only;

		auto* leftover = addTrackOfType(song, Track::Type::Pattern);
		Q_UNUSED(leftover)
		QVERIFY(song->selectedTrack() == nullptr);

		song->recordSelectedTrack();

		QCOMPARE(countAllRecordClips(), 0);
		QVERIFY(!song->isRecording());
	}


	// ------------------------------------------------------------------
	// (o) Without a capture device, arming is refused even when a target exists.
	// ------------------------------------------------------------------
	void recordSelectedTrackWithoutCaptureDeviceDoesNothing()
	{
		installCaptureDevice(false);
		auto* song = Engine::getSong();
		auto* track = new SampleTrack(song);
		song->setSelectedTrack(track);

		song->recordSelectedTrack();

		QCOMPARE(countRecordClips(track), 0);
		QVERIFY(!song->isRecording());
	}


	// ------------------------------------------------------------------
	// (p) The target is announced so the editor can highlight it.
	// ------------------------------------------------------------------
	void selectedTrackChangedIsEmitted()
	{
		auto* song = Engine::getSong();
		auto* a = new SampleTrack(song);
		auto* b = new SampleTrack(song);

		QSignalSpy spy(song, &Song::selectedTrackChanged);
		song->setSelectedTrack(a);
		QCOMPARE(spy.count(), 1);

		// Re-reporting the same track is not a change and must not spam the UI.
		song->setSelectedTrack(a);
		QCOMPARE(spy.count(), 1);

		song->setSelectedTrack(b);
		QCOMPARE(spy.count(), 2);
	}


	// ==================================================================
	// The single record control: the mode chosen from the dropdown is
	// remembered and replayed by the main button.
	// ==================================================================

	// ------------------------------------------------------------------
	// (q) The default mode is deterministic.
	// ------------------------------------------------------------------
	void defaultRecordModeIsNewTrack()
	{
		QCOMPARE(Engine::getSong()->recordMode(), Song::RecordMode::NewTrack);
	}


	// ------------------------------------------------------------------
	// (r) Choosing "new Sample Track" makes repeated clicks create tracks.
	// ------------------------------------------------------------------
	void newTrackModeRepeatsTrackCreation()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		song->setRecordMode(Song::RecordMode::NewTrack);

		const auto before = song->tracks().size();
		song->record();
		song->stop();
		song->record();
		song->stop();

		QCOMPARE(static_cast<int>(song->tracks().size()), static_cast<int>(before + 2));
		QCOMPARE(countAllRecordClips(), 2);
	}


	// ------------------------------------------------------------------
	// (s) Choosing "selected Sample Track" makes repeated clicks arm that track.
	// ------------------------------------------------------------------
	void selectedTrackModeReusesTargetTrack()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* track = new SampleTrack(song);
		song->setSelectedTrack(track);
		song->setRecordMode(Song::RecordMode::SelectedTrack);

		const auto before = song->tracks().size();
		song->record();
		song->stop();
		song->record();
		song->stop();

		// Same track, and the second click reuses the armed clip covering the
		// playhead rather than stacking another one.
		QCOMPARE(static_cast<int>(song->tracks().size()), static_cast<int>(before));
		QCOMPARE(countRecordClips(track), 1);
	}


	// ------------------------------------------------------------------
	// (t) Changing the dropdown changes what the next click does.
	// ------------------------------------------------------------------
	void changingModeChangesNextClick()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		auto* track = new SampleTrack(song);
		song->setSelectedTrack(track);

		// Selected-track mode: the click arms the existing track.
		song->setRecordMode(Song::RecordMode::SelectedTrack);
		song->record();
		song->stop();
		QCOMPARE(countRecordClips(track), 1);
		QCOMPARE(static_cast<int>(song->tracks().size()), 1);

		// Switch to new-track mode: the next click makes a track instead.
		song->setRecordMode(Song::RecordMode::NewTrack);
		song->record();
		song->stop();
		QCOMPARE(static_cast<int>(song->tracks().size()), 2);
		QCOMPARE(countRecordClips(track), 1);
	}


	// ------------------------------------------------------------------
	// (u) Pressing the main button never resets the remembered mode.
	// ------------------------------------------------------------------
	void primaryClickKeepsRememberedMode()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		song->setRecordMode(Song::RecordMode::SelectedTrack);

		QSignalSpy spy(song, &Song::recordModeChanged);
		song->record();
		song->stop();

		QCOMPARE(spy.count(), 0);
		QCOMPARE(song->recordMode(), Song::RecordMode::SelectedTrack);

		// Setting the same mode again is not a change either.
		song->setRecordMode(Song::RecordMode::SelectedTrack);
		QCOMPARE(spy.count(), 0);
	}


	// ------------------------------------------------------------------
	// (v) Selected-track mode with no target still fails cleanly.
	// ------------------------------------------------------------------
	void selectedTrackModeWithoutTargetDoesNothing()
	{
		installCaptureDevice(true);
		auto* song = Engine::getSong();
		song->setRecordMode(Song::RecordMode::SelectedTrack);
		const auto tracksBefore = song->tracks().size();

		song->record();

		QCOMPARE(static_cast<int>(song->tracks().size()), static_cast<int>(tracksBefore));
		QCOMPARE(countAllRecordClips(), 0);
		QVERIFY(!song->isRecording());
	}
};


QTEST_GUILESS_MAIN(RecordingWorkflowTest)
#include "RecordingWorkflowTest.moc"
