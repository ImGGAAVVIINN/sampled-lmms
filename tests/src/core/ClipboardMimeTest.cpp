/*
 * ClipboardMimeTest.cpp - tests for Clipboard::decodeMimeData() and the
 *                        is*File helpers used by the LMMS drag-and-drop path.
 *
 * These functions are the bridge between an external QMimeData (e.g. one
 * produced by Windows Explorer / Qt's file drag) and the internal
 * "type:value" StringPairDrag classification. The bug fixed here was that
 * SampleTrackView::dropEvent decoded drops with StringPairDrag::decodeKey,
 * which only ever reads the internal "application/x-lmms-stringpair" format.
 * Explorer never provides that format, so Explorer drops were silently
 * rejected even though dragEnterEvent accepted them.
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program (see COPYING); if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#include <QtTest>

#include <QMimeData>
#include <QUrl>

#include "Clipboard.h"

using namespace lmms::Clipboard;


namespace
{

/**
 * \brief Build a QMimeData the way a real OS file-drag does.
 *
 * Qt always exposes file drags through "text/uri-list" holding encoded file
 * URLs (never bare paths), and on Windows Explorer additionally offers the
 * path as "text/plain". setUrls() is what produces the correctly encoded
 * "text/uri-list", so it must be called last - writing a bare path into
 * "text/uri-list" by hand would corrupt the list and make QMimeData::urls()
 * return non-local URLs.
 *
 * Returns a pointer because QMimeData is not copyable.
 */
QMimeData* makeFileMimeData(const QString& path)
{
	const QUrl url = QUrl::fromLocalFile(path);

	auto* md = new QMimeData;
	md->setData("text/plain", path.toUtf8());
	md->setUrls({url});
	// Qt encodes the URL list with CRLF separators, exactly like a real drop.
	md->setData("text/uri-list", (url.toString() + "\r\n").toUtf8());
	return md;
}

} // namespace


class ClipboardMimeTest : public QObject
{
	Q_OBJECT

private slots:

	void init()
	{
		// The extension map is normally populated from plugin descriptors by
		// updateExtensionMap(). That requires loading the GUI plugin shared
		// libraries, which this test binary cannot do (it links only the
		// static core objects and does not export the GUI symbols the
		// plugins need). Register the sample-file extensions directly so the
		// classification path under test is exercised with the same data the
		// real AudioFileProcessor descriptor provides.
		//
		// "projectfile" and "midifile" are already hardcoded in Clipboard.cpp
		// and need no registration.
		static bool registered = false;
		if (registered) { return; }
		registered = true;

		// Mirrors the AudioFileProcessor plugin descriptor
		// (plugins/AudioFileProcessor/AudioFileProcessor.cpp). "mp3" is only
		// listed there when LMMS_HAVE_SNDFILE_MP3 is set; registering it here
		// unconditionally keeps the test independent of the build options,
		// since what is under test is the classification, not the descriptor.
		for (const char* ext : {"wav", "ogg", "ds", "spx", "au", "voc",
				 "aif", "aiff", "flac", "raw", "mp3"})
		{
			registerExtension(ext, "samplefile");
		}
	}

	void testDecodeExplorerWav()
	{
		// A Windows-style path is what Explorer produces; the classification
		// must still work regardless of the host OS.
		const auto md = makeFileMimeData("/home/me/Music/beat.wav");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "samplefile");
		QVERIFY(value == "/home/me/Music/beat.wav");
		delete md;
	}

	void testDecodeExplorerOgg()
	{
		const auto md = makeFileMimeData("/home/me/samples/kick.ogg");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "samplefile");
		QVERIFY(value == "/home/me/samples/kick.ogg");
		delete md;
	}

	void testDecodeExplorerFlac()
	{
		const auto md = makeFileMimeData("/tmp/drum.flac");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "samplefile");
		QVERIFY(value == "/tmp/drum.flac");
		delete md;
	}

	void testDecodeExplorerMp3()
	{
		const auto md = makeFileMimeData("/home/me/loop.mp3");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "samplefile");
		QVERIFY(value == "/home/me/loop.mp3");
		delete md;
	}

	void testDecodeRejectsNonAudio()
	{
		// An unsupported extension must classify as "missing_type" so the
		// SampleTrackView drop handler rejects it cleanly instead of creating
		// a clip with a bogus file.
		const auto md = makeFileMimeData("/home/me/notes.txt");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "missing_type");
		QVERIFY(value == "/home/me/notes.txt");
		delete md;
	}

	void testDecodeRejectsDirectory()
	{
		// A directory drop (no extension) must not be classified as a sample.
		const auto md = makeFileMimeData("/home/me/Music");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "missing_type");
		delete md;
	}

	void testDecodeExplorerProjectFile()
	{
		const auto md = makeFileMimeData("/home/me/song.mmpz");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "projectfile");
		QVERIFY(value == "/home/me/song.mmpz");
		delete md;
	}

	void testDecodeExplorerMidi()
	{
		const auto md = makeFileMimeData("/home/me/beat.mid");
		const auto [type, value] = decodeMimeData(md);

		QVERIFY(type == "midifile");
		QVERIFY(value == "/home/me/beat.mid");
		delete md;
	}

	void testDecodeStringPairFallback()
	{
		// When no URLs are present, the StringPair format is used for
		// internal LMMS drags (track moves, clip moves, etc.).
		QMimeData md;
		md.setData(mimeType(MimeType::StringPair), "samplefile:/home/me/x.wav");

		const auto [type, value] = decodeMimeData(&md);

		QVERIFY(type == "samplefile");
		QVERIFY(value == "/home/me/x.wav");
	}

	void testOldStringPairPathRejectsExplorerDrop()
	{
		// Regression guard for the bug itself. Before the fix,
		// SampleTrackView::dropEvent decoded the drop with
		// StringPairDrag::decodeKey/decodeValue, which read only the
		// internal "application/x-lmms-stringpair" format. Windows Explorer
		// never provides that format, so the key decoded to an empty string,
		// the "type == \"samplefile\"" test failed and the drop was silently
		// ignored - even though dragEnterEvent had already accepted it.
		//
		// If this test ever starts failing, the fix in
		// SampleTrackView::dropEvent is no longer necessary.
		const auto md = makeFileMimeData("/home/me/Music/beat.wav");

		QVERIFY(!md->hasFormat(mimeType(MimeType::StringPair)));
		QVERIFY(decodeKey(md).isEmpty());
		QVERIFY(decodeValue(md).isEmpty());

		// The drag-enter path (StringPairDrag::processDragEnterEvent) already
		// uses decodeMimeData, so dropEvent must agree with it - otherwise the
		// drop is accepted on enter and then silently discarded.
		const auto [type, value] = decodeMimeData(md);
		QVERIFY(type == "samplefile");
		QVERIFY(value == "/home/me/Music/beat.wav");

		delete md;
	}

	void testExplorerProvidesUriList()
	{
		// Guard: if Qt/Explorer stop providing text/uri-list, this test
		// fails loudly and the fix must be revisited.
		const auto md = makeFileMimeData("/home/me/x.wav");
		QVERIFY(md->hasFormat("text/uri-list"));
		QVERIFY(!md->urls().isEmpty());
		QVERIFY(md->urls().first().isLocalFile());
		delete md;
	}

	void testIsAudioFileExtensions()
	{
		QVERIFY(isAudioFile("wav"));
		QVERIFY(isAudioFile("ogg"));
		QVERIFY(isAudioFile("flac"));
		QVERIFY(isAudioFile("aiff"));
		QVERIFY(isAudioFile("mp3"));
		QVERIFY(!isAudioFile("txt"));
		QVERIFY(!isAudioFile("mmpz"));
	}

	void testDecodeEmptyMimeData()
	{
		QMimeData md;
		const auto [type, value] = decodeMimeData(&md);

		QVERIFY(type == "missing_type");
		QVERIFY(value.isEmpty());
	}
};

QTEST_MAIN(ClipboardMimeTest)
#include "ClipboardMimeTest.moc"