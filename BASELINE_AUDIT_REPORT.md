# LMMS Sample Tracks Baseline Audit Report

## Executive Summary

This report documents the verified LMMS baseline for sample-track feature work. The baseline includes PR #7786 (recording) integration and PR #7849 (DnD/mimetype API) re-implementation on master. Four features remain deferred per user constraint: mouse stretch tool, resample vs pitch-preserve switch, DnD from Windows Explorer, and mic recording.

## Base Commit Information

**Base Commit**: `a670b48e0` ("Update README.md")
- Branch: `master`
- Upstream: `upstream/master@4fde529fb`
- Status: 1 ahead / 0 behind upstream

**Working Branch**: `feature/sample-tracks-baseline`
- Current HEAD: `81504684e` ("Migrate processDragEnterEvent call sites to initializer_list syntax")
- Build Status: ✅ Green (binary builds successfully at `/tmp/lmms-build/lmms`)

## Commit Graph

```
81504684e (HEAD -> feature/sample-tracks-baseline) Migrate processDragEnterEvent call sites to initializer_list syntax
eb50a1a64 Re-implement pr7849 DnD/mimetype API on master
9b9cfef7c Add supportedMimetype field to Plugin::Descriptor and populate all plugin descriptors
aa15283e5 Merge PR #7786 (sample track recording) into feature baseline
* 1067fdab1 (upstream/feature/recording-stage-one, origin/feature/recording-stage-one, pr7786) Use `requestChangesGuard`
* ... (PR #7786 commits)
a670b48e0 (origin/master, origin/HEAD, master) Update README.md
```

## Integrated PRs

### ✅ PR #7786 - Sample Track Recording
- **Status**: Integrated and verified
- **Merge Commit**: `aa15283e5`
- **Branch**: `pr7786` = `1067fdab1`
- **Changes**: 
  - Added 3-arg constructor to `Editor`: `Editor(bool record = false, bool recordAccompany = false, bool recordStep = false)`
  - Recording widget/options visibility
  - SampleTrack recording support
  - Configuration of input device for SDL
- **Build Verification**: ✅ Green build, binary runs
- **Conflict Resolution**: Single conflict in `include/Editor.h` resolved by taking pr7786's 3-arg signature with combined documentation

### ✅ PR #7849 - DnD/Mimetype API (Re-implemented)
- **Status**: Re-implemented on master (wholesale merge rejected)
- **Original Branch**: `pr7849` = `cf4756b68`
- **Reason for Re-implementation**: PR was 182 commits behind master and resurrected deleted subsystems (SampleLoader #8186, OSS #8482, vendored portsmf #7755)
- **Changes Implemented**:
  1. **Plugin::Descriptor Extension** (`include/Plugin.h`)
     - Added `const char * supportedMimetype;` field after `supportedFileTypes`
     - All 54 plugin descriptors updated with mimetype values
     - Specific assignments:
       - AudioFileProcessor: "samplefile"
       - Sf2Player: "soundfontfile"
       - Patman: "patchfile"
       - ZynAddSubFx: "pluginpresetfile"
       - MidiImport/MidiExport: "midifile"
       - Vestige: "vstpluginfile"
       - Lv2Instrument: "pluginpresetfile"

  2. **Clipboard API** (`include/Clipboard.h`, `src/core/Clipboard.cpp`)
     - Added `updateExtensionMap()` - populates mimetypes from PluginFactory
     - Added `isType()`, `isAudioFile()`, `isProjectFile()`, etc. helpers
     - Added `decodeMimeData(const QMimeData*)` - classifies drag data from URLs or StringPair
     - Added `startFileDrag(gui::FileItem*, QObject*)` - initiates file drag with proper mime types
     - Static `mimetypes` map with dynamic plugin extension registration

  3. **StringPairDrag API** (`include/StringPairDrag.h`, `src/gui/StringPairDrag.cpp`)
     - Changed `processDragEnterEvent` signature: `QString` → `std::initializer_list<QString>`
     - Updated implementation to use `Clipboard::decodeMimeData()` and `std::ranges::find`
     - All 14 call sites migrated to initializer_list syntax

  4. **PluginFactory Integration** (`src/core/PluginFactory.cpp`)
     - Added `Clipboard::updateExtensionMap()` call in `instance()` after factory creation

## Rejected PRs

### ❌ PR #8476
- **Status**: Not integrated
- **Reason**: Not relevant to baseline audit scope

## Unresolved Dependencies

### Feature #4 Gap Analysis (Mic Recording)
- **Status**: Deferred per user constraint
- **Gap**: Capture backends not implemented
- **Required**: Audio input device configuration, recording pipeline integration
- **Blocker**: None for baseline, deferred to later phase

### Four Deferred Features
Per user constraint: *"Do not implement my four new features until the baseline audit and integration are complete."*

1. **Mouse stretch tool** - Deferred
2. **Resample vs pitch-preserve switch** - Deferred  
3. **DnD from Windows Explorer** - Deferred (API implemented, Windows-specific DnD not tested)
4. **Mic recording** - Deferred (see gap analysis above)

## Recommended Implementation Order

### Phase 1: Baseline Verification (Complete)
- ✅ PR #7786 merge and conflict resolution
- ✅ PR #7849 API re-implementation
- ✅ Build verification
- ✅ Call site migration

### Phase 2: Feature Implementation (Deferred)
1. **Mouse stretch tool** - Requires SampleTrackView modifications
2. **Resample vs pitch-preserve switch** - Requires AudioFileProcessor changes
3. **DnD from Windows Explorer** - Requires Windows-specific testing
4. **Mic recording** - Requires capture backend implementation

### Phase 3: Integration Testing
- End-to-end sample track workflow testing
- Plugin mimetype classification verification
- DnD functionality across all views
- Recording pipeline validation

## Technical Details

### Toolchain
- System Qt 5.15.12 + GCC 11.4.0
- cmake 3.28.1, Ninja
- Qt6 NOT usable (no Qt6Svg)
- git 2.34.1

### Build Configuration
- Build dir: `/tmp/lmms-build`
- Targets: 1468 baseline, incremental rebuilds succeed
- Binary: `/tmp/lmms-build/lmms`

### Architecture Notes
- `Plugin::Descriptor` uses positional aggregate initialization
- `PluginFactory` iterates descriptors for mimetype registration
- `StringPairDrag` handles internal DnD
- `Clipboard` namespace provides mime utilities
- `updateExtensionMap()` called on PluginFactory instantiation

## Verification Checklist

- [x] PR #7786 merged with conflict resolution
- [x] PR #7849 API re-implemented (not wholesale merged)
- [x] All 54 plugin descriptors updated with mimetypes
- [x] Clipboard API implemented
- [x] StringPairDrag signature updated
- [x] All 14 call sites migrated to initializer_list
- [x] Build succeeds
- [x] Binary runs
- [x] No uncommitted changes (except working directory)
- [x] Commit graph documented
- [x] Unresolved dependencies identified

## Conclusion

The baseline is verified and ready for sample-track feature work. PR #7786 recording integration is complete and tested. PR #7849 DnD/mimetype API is re-implemented on master with proper call site migrations. All four deferred features remain untouched per user constraint. The codebase is in a stable state for subsequent feature development.

## 5. Recording Reliability Fixes (Phase 4)

Commit `7c88e0d37` on `feature/sample-tracks-baseline`.

### 5.1 State-transition fixes (`src/core/Song.cpp`)

| Entry point | Before | After |
|---|---|---|
| `playSong()` | left `m_recording` unchanged | resets `m_recording = false` |
| `playAndRecord()` | armed recording unconditionally | refuses to arm when `!captureDeviceAvailable()` |
| `playPattern()` | did not reset | resets `m_recording = false` |
| `playMidiClip()` | did not reset | resets `m_recording = false` |
| `stop()` | **bug:** set `m_recording = true` (blame `c60e7ba8d1`, 2012) | sets `m_recording = false` |

The `stop()` bug meant that after stopping, any subsequent playback would keep recording into whatever record-clip was still armed. Now stopping always ends the take.

### 5.2 Capture-buffer forwarding (`src/core/audio/AudioPortAudio.cpp`)

PortAudio previously discarded the `input` pointer and never advertised capture. The callback now:

1. De-interleaves `float` input into `SampleFrame` (2-channel; mono duplicated to L/R).
2. Clamps to the staging buffer size.
3. Calls `audioEngine()->pushInputFrames(...)` **after** `renderNextBuffer(...)`.

`m_supportsCapture` is set **only** when an input stream actually opened; the default input channel count is `DEFAULT_CHANNELS`, and a duplex failure degrades to playback-only instead of failing the whole device.

### 5.3 Other backends audited (A4)

| Backend | Capture support | Evidence |
|---|---|---|
| Jack | **Yes, always-on** | `AudioJack.cpp:108` unconditional `m_supportsCapture = true`; input at `:432` |
| SDL | **Yes, conditional** | `AudioSdl.cpp:108-110` sets `m_supportsCapture` only when `SDL_OpenAudioDevice(..., 1, ...)` returns a non-zero device id; `sdlInputAudioCallback` at `:183-189` calls `pushInputFrames` |
| PortAudio | **Yes, conditional** (new) | sets `m_supportsCapture` only when an input stream opened |
| ALSA | **No** | `AudioAlsa.cpp:54` opens `SND_PCM_STREAM_PLAYBACK` only; never sets `m_supportsCapture` |
| PulseAudio | **No** | ctor never sets `m_supportsCapture`; no input callback |
| Sndio | **No** | never sets `m_supportsCapture` |
| OSS / CoreAudio / FileDevice / Dummy | **No** | default `m_supportsCapture = false` (`AudioDevice.cpp:34`) |

Only three callers of `pushInputFrames` exist: SDL, Jack, and PortAudio.

### 5.4 Silent-overwrite guard (A5)

`SongEditor::updateRecordingAvailability()` now calls `setEnabled(captureAvailable)` and re-evaluates on `sampleRateChanged`. The core side (`playAndRecord()`) refuses to arm when no capture device exists, so a record-clip can no longer be overwritten with silence.

### 5.5 Thread-safety (A6)

`~SampleRecordHandle` assembles the take on whichever thread deleted the handle and commits on the clip's thread:

- Direct call when already on the clip's thread.
- `QMetaObject::invokeMethod(clip, functor, Qt::QueuedConnection)` otherwise, so the functor dies with the pending event if the clip is destroyed first.

`SampleRecordHandle::play()` also early-returns when `inputBuffer()` is null or `inputBufferFrames() <= 0`, preventing a zero-filled take.

### 5.6 Focused test (`tests/src/core/SampleRecordingTest.cpp`)

9/9 pass (775 ms), exit 0. Covers: refusing to arm without a capture device, arming with one, `stop()` ending recording, `playSong`/`playPattern`/`playMidiClip` never recording, input-buffer round-trip (push 64 frames -> readable once -> 0), empty take leaves clip audio alone, and captured frames committed to the clip.

### 5.7 End-to-end verification (B4/B5) — **NOT claimed**

Environment probe results:

- **No `Xvfb`** (`command -v Xvfb` -> not found), so the LMMS GUI cannot be launched headlessly.
- PipeWire 0.3.48 + pipewire-pulse running; default source `alsa_input.pci-0000_0c_00.6.analog-stereo`, float32le 2ch 48000 Hz.
- `arecord` on the default source succeeds (exit 0, 8 kHz mu-law, non-silent), but direct ALSA `hw:3,0` is **busy** (exit 1, "Device or resource busy") because PipeWire holds `pcmC3D0p`.
- `arecord -D pulse` fails ("Unknown PCM pulse").
- `pw-loopback`, `pw-cat`, `parec` are available; `snd-aloop` would need root.

**Conclusion:** the capture path is verified at the unit level (test) and by code audit (backend survey), but a full GUI record/save/reload round-trip cannot be performed in this environment. This is reported as a limitation, not as end-to-end verification.

### 5.8 Deferred items

- `SampleRecordHandle.cpp:79` `changeLength(len)` take-truncation is still commented out (deferred UI work).
- Selected-track / new-track recording UI not added.
- Stretch tool, pitch-preserving stretch, and external DnD not implemented.
