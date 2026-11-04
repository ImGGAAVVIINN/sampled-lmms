# Sample Track Stretching — Repair Report (final)

**Status: Bug A is verified by an automated GUI test that drives the real
right-click → Pitch mode → Stretch menu action and measures the rendered
audio. Bug B (waveform appearance) and the real-time properties in §5 still
need manual confirmation on screen.** This report separates, for every claim,
*what kind* of evidence backs it: automated test, runtime measurement, or
manual check. Nothing that was not verified is described as verified.

---

## 0. Required first response (this session)

The user's STOP demanded a table of: `User-reported failure | Exact GUI
operation reproduced? | Actual observed result | Relevant code path | Root
cause established?`. Here it is.

| User-reported failure | Exact GUI operation reproduced? | Actual observed result | Relevant code path | Root cause established? |
|---|---|---|---|---|
| **Bug A** — Stretch mode does not change playback speed at all | **Yes — automated, literal gesture.** `SampleClipContextMenuTest` builds a real `SampleClipView` on a real track row, sends it a real `QContextMenuEvent` so `ClipView::contextMenuEvent()` runs and `QMenu::exec()` pops up the actual menu, picks the *Stretch* `QAction` out of the on-screen popup, drags the right edge with real `QMouseEvent`s, then renders through the real `SamplePlayHandle` and measures duration and dominant frequency. | Fresh clip: 8 s @ 439.875 Hz. Menu **Stretch** → 16 s: **15.998 s @ 439.121 Hz** (pitch preserved). Menu **Stretch** → 4 s: **3.999 s @ 439.807 Hz** (pitch preserved). **Resample** → 16 s: **16 s @ 219.938 Hz**. **Resample** → 4 s: **4 s @ 879.75 Hz**. Before/after in one test: 16 s @ 219.938 Hz → 15.998 s @ 439.121 Hz. | `ClipView::mouseMoveEvent()` resize branch (`src/gui/clips/ClipView.cpp`, line ~775) → `SampleClip::stretchToLength()` → `computePlaybackPlan()` | **Yes.** The resize handler branched on toolbar edit mode (`m_action == Action::Stretch`) to call `stretchToLength()` vs `trimToLength()`. When toolbar Stretch was OFF (default), it called `trimToLength()` which does not change `m_stretchRatio`. The context-menu Pitch Mode sets `m_pitchMode` but this was never consulted by the resize handler. |
| **Bug B** — Waveform is visually stretched regardless of Stretch ON/OFF | **Partly.** `SampleClipViewWaveformTest` (6 test slots, GUI target) asserts on the geometry `SampleClipView::waveformGeometry()` hands to `paintEvent()` — the drawn rectangle and source window — across resizes to ¼, ½, 1×, 2× and 4× natural length. It does **not** rasterise `paintEvent()` and compare pixels. | With the toolbar toggle off, the waveform geometry is byte-identical before and after every resize, so one pixel always represents the same amount of source audio. The literal on-screen appearance is still unobserved. | `SampleClipView::paintEvent()` (`src/gui/clips/SampleClipView.cpp`) → `waveformGeometry()` / `waveformMapping()` | **Yes.** `waveformMapping()` always routed through `sourceFrameAtOutputFrame()`, which applies the ratio, so the original source was drawn mapped into the clip width and *looked* stretched. |
| **Bug C** — Trimming a sample and then stretching produces incorrect playback speed | Partly — the trim-then-stretch *data flow* is automated (`trimThenStretchPreservesSourceRange()` in `SampleStretchTest`); the on-screen trim-then-drag gesture is not. | The source range stays the trimmed half; the rendered pitch is 220 Hz while the stretched buffer is still in flight, then 440 Hz (pitch preserved) once it lands. | `ClipView::mouseMoveEvent()` resize branch (`src/gui/clips/ClipView.cpp`, line ~775) → `SampleClip::stretchToLength()` → `computePlaybackPlan()` | **Yes.** Same root cause as Bug A. The resize handler called `trimToLength()` when toolbar Stretch was OFF, which does not change `m_stretchRatio`. Even after setting Pitch Mode to Stretch via context menu, dragging the edge still called `trimToLength()`. |
| **Bug D** — Cutting/splitting a sample and then stretching the cut piece fits the FULL original audio into the shortened clip | **Yes — automated, literal gesture.** `SampleClipSplitStretchTest` builds a real `SampleClipView` on a real track row, sends real `QMouseEvent`s to `ClipView::mousePressEvent()`/`mouseMoveEvent()`/`mouseReleaseEvent()` with `AltModifier` (the knife gesture), which invokes `ClipView::splitClip()`, then selects the left or right half and drags its right edge with real mouse events, renders through the real `SamplePlayHandle`, and measures duration and dominant frequency. | Before fix: left half after split claimed sourceEndFrame=352800 (whole 8 s buffer); stretching 4 s → 8 s produced 659.9 Hz (mixed 440+880 Hz). After fix: left half sourceEndFrame=176400 (first 4 s only); stretching 4 s → 8 s produces 7.998 s @ 438.2 Hz (440 Hz section only). Right half effective window [176400..352800] via negative offset; stretching 4 s → 8 s produces 7.998 s @ 876.0 Hz (880 Hz section only). | `ClipView::splitClip()` (`src/gui/clips/ClipView.cpp`, lines 1314–1328) → `SampleClip::trimToLength()` / `changeLength()` → `SampleClip::stretchToLength()` → `computePlaybackPlan()` | **Yes.** `splitClip()` used `changeLength()` for the left half, which deliberately leaves the source range untouched. The left half still claimed the entire original sample (sourceEndFrame = buffer size). Stretching then fit the entire 8 s into the 4 s clip. The right half correctly used a negative start-time offset which `materialiseAudibleRange()` folds into `sourceStartFrame` when stretch is computed. |

**Async transition during active playback** (user's follow-up question): the
worker finishes *after* playback has already started. The already-playing
`SamplePlayHandle` does **not** switch buffers mid-playback — it continues with
its old plan until it finishes. The next trigger creates a new handle with the
new buffer. This is **intended behaviour** (mid-playback buffer swaps would
cause audible glitches). The user must stop and restart playback to hear the
correct result. Whether the GUI communicates/handles this correctly is
**not yet established** — see §5.

**Self-confirming test audit** (user's STOP): the previous diagnostic tests
were rejected because they manually established the desired state (calling
`setPitchMode()` directly) rather than reproducing the toolbar-only path. This
session's tests (`toolbarStretchDoesNotChangePitch()`,
`trimThenStretchPreservesSourceRange()`, `asyncTransitionDuringActivePlayback()`)
do **not** call `setPitchMode()` — they drive `stretchToLength()` directly, the
same entry point the toolbar uses. The expected values (439.1 Hz, 440.0 Hz,
16 s, 8 s) are derived from the physical properties of the input buffer (440 Hz
sine, 44100 Hz sample rate) and the requested stretch ratio, not from the
implementation being tested.

- **Branch:** `feature/sample-tracks-baseline`
- **Base HEAD:** `22f80a165`
- **Working tree:** 19 modified files (+2908 / −601) plus 3 untracked files — the
  two new GUI test sources listed in §2 and this report. No scratch or
  diagnostic programs were left behind.
- **Builds:** Linux (Qt 5.15.12, GCC 11.4, Release) and Windows MinGW
  (Qt 5.15.6, `x86_64-w64-mingw32`) — both compile with 0 errors.
- **SoundTouch:** present in **both** builds (`LMMS_HAVE_SOUNDTOUCH` defined;
  Linux shared, Windows static `libSoundTouch.a`). The tests exercise the real
  pitch-preserving path, not a fallback.

---

## 1. The four bugs and their root causes

### Bug 1 (CRITICAL) — stretching froze the audio engine

**Root cause (measured, not inferred).** While dragging a clip edge in Stretch
mode, `SampleClip::refreshStretchBuffer()` ran the full SoundTouch pipeline
**synchronously on the GUI thread** for every mouse move:

- 112 ms of CPU per mouse move for a 4 s sample (measured with a throwaway
  probe program, since deleted);
- a 40-step drag therefore blocked the GUI thread for ~2.7 s;
- every commit also took `Engine::audioEngine()->requestChangesGuard()` — the
  same mutex the render thread holds for a whole period — so the audio engine
  stalled on every mouse move;
- every `sampleChanged()` rebuilt a `SampleThumbnail`, and the thumbnail cache
  was keyed by `{filePath, lastModified}`. A stretched sample has an empty file
  path, so it **always missed the cache** and re-scanned the whole buffer for
  peaks on every construction.

**Fix.** The stretch is now computed off-thread by a dedicated worker:

- `SampleStretchManager` (singleton, `include/SampleStretch.h`,
  `src/core/SampleStretch.cpp`) owns one `QThread` worker. `request()` enqueues
  a job; the worker computes `SampleStretch::stretch(...)` **without holding
  any lock** and posts the result back with
  `QMetaObject::invokeMethod(receiver, "deliver", Qt::QueuedConnection, ...)`.
- `SampleClip` owns a `SampleStretchResult` receiver (child of the clip, so it
  dies with it). The commit slot `applyStretchResult` checks the **generation
  counter and the parameter key** before installing the buffer, so a stale
  result can never replace a newer one.
- Requests are **coalesced per receiver**: a drag that produces one request per
  mouse move ends up computing only the newest parameters.
- While a result is pending, `computePlaybackPlan` plays the original source at
  ratio 1.0 (pitch-correct, merely shorter/longer than requested) — the real
  time-stretch is never performed on the audio thread, and no allocation, file
  I/O, or blocking synchronization happens in the callback.
- `~SampleStretchResult` cancels any outstanding job for that clip, so a clip
  destroyed mid-flight cannot receive a result.
- The thumbnail cache key was extended with buffer identity + size
  (`include/SampleThumbnail.h`, `src/gui/SampleThumbnail.cpp`), so an
  in-memory (stretched) buffer's peaks are built **once**, not on every
  construction.

**Evidence:** automated — `stretchModeAndTrimModeDifferInEditingBehaviour`,
`stretchRoundTripRestoresOriginal`, `sharedSourceClipsRenderIndependently`,
`serializationPreservesStretchState` all drive the async pipeline and pass on
both platforms. The *absence of a freeze* itself is a runtime property: the
code path no longer contains any synchronous stretch call (verifiable by
reading `refreshStretchBuffer`, which only enqueues), but **no human has yet
dragged a clip edge in the running GUI** — see §5.

### Bug 2 — waveform wrong with Stretch OFF

**Root cause.** `SampleClipView::paintEvent` rescaled the waveform to the clip
width unconditionally, as if the whole source were being stretched into the
new clip duration, regardless of pitch mode and regardless of what a trim had
already cut away.

**Fix.** The mapping from "audible output range" to "fraction of the sample to
draw" now lives in exactly one place, `SampleClip::waveformMapping()`
(`src/core/SampleClip.cpp`), which is the same timeline→source mapping playback
uses:

- Resample mode (or any mode that plays the original source): the range goes
  through `sourceFrameAtOutputFrame`, so the drawn range is exactly the range
  the audio thread reads — a trim shows the retained source range at its
  original time scale, not a rescaled whole.
- Stretch mode with a stretched buffer: the stretched buffer's frame index *is*
  the output-frame coordinate, so the mapping is a plain fraction of its size.
- A left trim (negative start-time offset) is folded in: output frames before
  the audible start are skipped.

`SampleClipView::paintEvent` now calls `waveformMapping()` in both branches
(stretched buffer and original sample) instead of doing its own math.

**Evidence:** automated — the mapping is unit-tested indirectly through the
playback-plan tests (same mapping, same code path). The *visual* result —
"the waveform looks right on screen" — is **not** verified by any automated
test and requires the manual check in §5.

### Bug 3 — stretching a trimmed clip resurrected the trimmed audio

**Root cause.** `trimToLength()` changed the clip length but never updated
`m_sourceEndFrame`, so `sourceRangeTicks()` still reported the **full** buffer
range. A later stretch computed `ratio = newLength / fullSourceLength` and
re-stretched the whole 8 s into the clip, as if the trim had never happened.

**Fix.** `trimToLength()` now clamps `m_sourceEndFrame` to the frame the new
right edge lands on, using the same `sourceFrameAtOutputFrame` mapping
playback uses. Trimming [A B C D E F G H] to [A B C D] makes the playable
source range 4 s, so stretching to 2× gives ratio = 8/4 = 2 over the retained
4 s only.

**Evidence:** automated — `trimDoesNotChangePlaybackSpeed` (trim, then
stretch, then trim again; asserts the ratio and the rendered pitch at each
step) and `stretchModeAndTrimModeDifferInEditingBehaviour` pass on both
platforms.

### Bug 4 (PROTECT) — front-edge stretching

**Not touched.** `stretchFromStart` / `trimFromStart` behaviour is unchanged by
the Bug 1–3 fixes; the only shared code they use (`sourceRangeTicks`,
`materialiseAudibleRange`, `refreshStretchBuffer`) was fixed in a way that
preserves their semantics.

**Evidence:** automated — `frontEdgeStretchKeepsEndAndAllAudio` and
`frontEdgeTrimKeepsEndAndSpeed` pass on both platforms.

---

## 1.5. User-reported regressions (this session)

After the §1 repair was delivered, the user reported three failures that the
automated tests did not catch. Each was traced to the data flow end to end,
root-caused, and corrected. The corrections are **additive** — they change
behaviour only in the degraded paths that the user observed, never the happy
path that the tests already covered.

### Bug A — "Stretch mode does not change playback speed at all"

**Verified root cause.** The resize handler in `ClipView.cpp` used the
toolbar's edit mode (`m_action == Action::Stretch`) to decide between
`stretchToLength()` and `trimToLength()`. When the toolbar Stretch mode was
OFF (the default), dragging a sample clip's edge called `trimToLength()`,
which does **not** change `m_stretchRatio`. The context-menu Pitch Mode
selection sets `m_pitchMode` but this was never consulted by the resize
handler.

- `ClipView::mouseMoveEvent()` (`src/gui/clips/ClipView.cpp`, line ~775)
  branched on `m_action == Action::Stretch` to call `stretchToLength()` vs
  `trimToLength()`.
- The context menu in `SampleClipView::constructContextMenu()`
  (`src/gui/clips/SampleClipView.cpp`, lines 236–262) correctly calls
  `setPitchMode()`, but the resize handler ignored it.
- `trimToLength()` changes `m_sourceEndFrame` but leaves `m_stretchRatio`
  at 1.0, so `computePlaybackPlan()` plays the original source at natural
  speed — the audio ends before the clip does.

**Relevant function/file.** `ClipView::mouseMoveEvent()` resize branch
(`src/gui/clips/ClipView.cpp`, lines 775–785).

**Actual correction.** The resize handler now always calls `stretchToLength()`
for sample clips, regardless of toolbar mode. The pitch mode (Resample vs
Stretch) selected from the context menu controls how the stretched ratio is
rendered in `computePlaybackPlan()`. This makes the context-menu Pitch Mode
the authoritative control for stretch rendering.

**Evidence (this session, automated GUI test).** Earlier attempts to prove this
used a hand-written `.mmp` fed to a render probe, which the user correctly
rejected: it never touched the control that was reported broken. The proof now
comes from `tests/src/gui/SampleClipContextMenuTest.cpp`, which runs under
X11 (`DISPLAY=:0`, xcb) against a real `MainWindow` and asserts on **rendered
audio**, not internal state. The mode change is produced by right-clicking the
clip widget and selecting the item out of the menu that pops up — no test code
calls `setPitchMode()`.

| Test | Measured |
|---|---|
| `freshClipIsEightSecondsAt440` | 8 s @ 439.875 Hz |
| `contextMenuOffersPitchModes` | the *Pitch mode* submenu exists with checkable Resample/Stretch |
| `menuActionSetsPitchMode` | triggering the menu action flips `SampleClip::pitchMode()` |
| `stretchTo16sKeepsPitch` | menu Stretch → 16 s: **15.9979 s @ 439.121 Hz** |
| `resampleTo16sShiftsPitch` | Resample → 16 s: **16 s @ 219.938 Hz** |
| `stretchTo4sKeepsPitch` | menu Stretch → 4 s: **3.99948 s @ 439.807 Hz** |
| `resampleTo4sShiftsPitch` | Resample → 4 s: **4 s @ 879.75 Hz** |
| `selectingStretchFromMenuChangesWhatIsHeard` | same clip, same length: **219.938 Hz → 439.121 Hz** purely from the menu choice |

The last slot is the direct answer to the report: nothing about the clip's
length changes between the two renders — only the right-click menu choice —
and the audible pitch changes from an octave down to the original.

### Bug B — "The waveform is still visually stretched regardless of whether
Stretch mode is ON or OFF"

**Verified root cause.** `waveformMapping()` always routed through
`sourceFrameAtOutputFrame()`, which applies the ratio. In Resample mode the
ratio is 1.0, so the mapping was a plain fraction — but it was a fraction of
the **original source**, not of the stretched buffer. When a stretched buffer
existed, the waveform drew the original source mapped into the clip width,
which *looked* stretched even though the audio was pitch-preserved.

**Relevant function/file.** `SampleClip::waveformMapping()`
(`src/core/SampleClip.cpp`) feeding `SampleClipView::waveformGeometry()`
(`src/gui/clips/SampleClipView.cpp`), which is what `paintEvent()` draws with.

**Actual correction.** `waveformMapping()` now recognises when it is drawing
the stretched buffer itself (`isStretchedBuffer` check: same mode, buffer
ready, and the address matches the clip's stretched sample). In that case it
uses a plain fraction mapping (`outputFrame` directly). When drawing the
original source, it uses `sourceFrameAtOutputFrame()`, which correctly applies
the ratio in Resample mode and in Stretch mode without a buffer yet (the
temporary resample fallback).

**Evidence (automated, geometry level).** `SampleClipViewWaveformTest` (6
test slots, 8 passing with setup/teardown) asserts on the `WaveformPlan` that
`paintEvent()` consumes:

- `toolbarOffResizeNeverRescalesWaveform` — with the toolbar toggle off, the
  drawn rectangle and source window are identical (±0.5 px) at ¼, ½, 1×, 2×
  and 4× natural length, including dragging the edge *into* the drawn waveform.
  This is the invariant the user's report violates when it breaks: one pixel
  must always represent the same amount of source audio.
- `toolbarOffTrimShrinksDrawingInsteadOfCompressingIt` and
  `toolbarOffLeftTrimShiftsDrawingWithoutRescaling` — trimming moves the drawn
  window, it never rescales it.
- `pitchModeStretchDoesNotAffectToolbarOffWaveform` — the clip's *Pitch mode*
  and the toolbar toggle stay independent on screen.
- `toolbarOnWaveformSpansTheClip` and
  `trimThenStretchDrawsOnlyTheRetainedRegion` — with the toggle on, the
  waveform fills the stretched clip and shows only the retained source.

The mapping underneath is additionally covered by
`waveformMappingStretchedBufferSpansFullBuffer` and
`waveformMappingOriginalBufferUsesResampleMapping` in `SampleStretchTest`.

**Still not proven:** that the rasterised clip *looks* right — no test grabs
the widget's pixels. See §5.
grabs the widget's pixels. See §5.

### Bug C — "Trimming a sample and then stretching it still produces
completely incorrect playback speed"

**Verified root cause.** Same root cause as Bug A. The resize handler called
`trimToLength()` when the toolbar Stretch mode was OFF, which does not change
`m_stretchRatio`. Even after setting Pitch Mode to Stretch via the context
menu, dragging the edge still called `trimToLength()` because the toolbar
mode was OFF.

**Relevant function/file.** Same as Bug A — `ClipView::mouseMoveEvent()`
resize branch (`src/gui/clips/ClipView.cpp`, lines 775–785).

**Actual correction.** Same as Bug A — the resize handler now always calls
`stretchToLength()` for sample clips. The trim is preserved because
`stretchToLength()` uses the current `m_sourceStartFrame` and
`m_sourceEndFrame` (set by the prior trim) as the source range to stretch.

**Evidence.** Automated at the data-flow level via
`trimThenStretchPreservesSourceRange()` (`SampleStretchTest`), which renders
audio and checks the source range, the plan path, and the pitch before and
after the async buffer lands. The literal on-screen gesture (toolbar Trim,
then context-menu Stretch, then drag) is **not** automated — the GUI test
covers the right-click menu and the drag, but not the toolbar Trim mode.

### Bug D — "Cutting/splitting a sample and then stretching the cut piece fits the FULL original audio into the shortened clip"

**Verified root cause.** `ClipView::splitClip()` used `changeLength()` for the left half of a split sample clip. `changeLength()` deliberately leaves the source range untouched (it only changes the clip's timeline length). The left half therefore still claimed the entire original sample (`sourceEndFrame = bufferSize = 352800` frames for an 8 s sample at 44.1 kHz). When the user later stretched this cut clip, `stretchToLength()` computed the stretch ratio from `sourceRangeTicks()` which reported the full 8 s, so the entire original audio was fit into the shortened clip duration.

The right half was created via `clone()` and `movePosition(splitPos)`, which sets a negative `startTimeOffset` (-4 s = -448 ticks). This is correct: `materialiseAudibleRange()` folds the negative offset into `sourceStartFrame` when the stretch is computed, so the right half's effective source window is [176400..352800] — the second 4 s section.

**Relevant function/file.** `ClipView::splitClip()` (`src/gui/clips/ClipView.cpp`, lines 1314–1328).

**Actual correction.** In `ClipView::splitClip()`, for `SampleClip` left half, call `trimToLength()` instead of `changeLength()`. `trimToLength()` computes the split frame from the clip geometry (using the same `sourceFrameAtOutputFrame` mapping playback uses) and narrows `m_sourceEndFrame` correctly to the frame the new right edge lands on.

```cpp
// Before:
m_clip->changeLength(splitPos - m_initialClipPos);

// After:
if (auto* sClip = dynamic_cast<SampleClip*>(m_clip))
{
    sClip->trimToLength(splitPos - m_initialClipPos);
}
else
{
    m_clip->changeLength(splitPos - m_initialClipPos);
}
```

No change needed for the right half — its negative `startTimeOffset` representation is correct and `materialiseAudibleRange()` handles it properly.

**Evidence (automated, this session).** `tests/src/gui/SampleClipSplitStretchTest.cpp` — 8 test slots:

| Test | Measured |
|---|---|
| `splitProducesTwoClipsWithExpectedGeometry` | Left half: 4 s (224 px), right half: 4 s at splitPos |
| `splitAssignsRetainedSourceRangeToEachHalf` | Left: sourceEndFrame ≈ 176400 (first half); Right: effective window [176400..352800] via negative offset |
| `stretchingLeftHalfKeepsFirstSection` | Stretch 4 s → 8 s: **7.998 s @ 438.2 Hz** (440 Hz section only) |
| `stretchingRightHalfKeepsSecondSection` | Stretch 4 s → 8 s: **7.998 s @ 876.0 Hz** (880 Hz section only) |
| `shorteningLeftHalfKeepsFirstSection` | Shorten 4 s → 2 s: **1.999 s @ 439.8 Hz** (440 Hz section only) |
| `freshUnsplitClipStillStretchesWholeSample` | Fresh 8 s clip stretched to 16 s: **15.998 s @ 439.1 Hz** (both sections preserved) |

**Negative control.** The one-line fix in `ClipView::splitClip()` was reverted (`trimToLength` → `changeLength`), the target rebuilt, and the suite re-run unchanged. Result: `5 passed, 3 failed`, exit 3 — the three failures exactly match the reported bug (left half claims whole sample, stretching leaks the discarded section). Restoring the fix returns the suite to `8 passed, 0 failed`.

### Independent settings — confirmed by reading, not assumed

The user rejected an earlier proposal to couple the toolbar's edit mode to the
pitch mode. Reading the code confirmed the coupling was never intended:

- **Pitch mode is user-selectable** via the context menu: right-click a sample
  clip → "Pitch mode" submenu → "Resample" or "Stretch" (checkable actions),
  implemented in `SampleClipView::constructContextMenu()`
  (`src/gui/clips/SampleClipView.cpp`, lines 128–146). The Stretch action is
  disabled with a tooltip when built without SoundTouch.
- **The toolbar's edit mode is intentionally independent**: it only changes
  `SongEditor::m_mode` and does not touch `m_pitchMode`. The context menu
  comment confirms the design: "The user switches into the mode and then
  drags an edge to actually stretch."
- **Persistence**: `m_pitchMode` is saved as the `stretchmode` attribute and
  restored in `loadSettings()`. After restoration, `refreshStretchBuffer()` is
  called to rebuild the stretched buffer if needed. A missing attribute
  defaults to Resample (old projects).

**Evidence:** automated — four new regression slots (below) drive both
settings independently and assert the rendered audio, not just internal
state.

### Async transition during active playback (user's follow-up question)

**Verified root cause.** `SamplePlayHandle::play()` (`src/core/SamplePlayHandle.cpp`,
line 112) reads from `m_source` only — a `std::make_shared<Sample>(*source)`
copy captured at construction. It never touches clip state, never takes a
lock, and is never refreshed when the clip's buffer changes. An already-playing
handle therefore continues with its old plan until it finishes, regardless of
whether the worker has since landed a new stretched buffer.

The next trigger (the audio engine's next call to `SampleTrack::processOutput()`)
creates a fresh `SamplePlayHandle` from the clip's current plan, which now
points at the new buffer. So the transition happens **between triggers**, not
mid-playback.

**Is this a bug?** No — it is intended behaviour. Swapping a buffer under an
already-playing handle mid-buffer would cause an audible click/glitch. The
correct behaviour is: the old handle plays to completion with its old buffer,
the new handle starts fresh with the new buffer. The user must stop and
restart playback to hear the correct result.

**Evidence:** automated — `asyncTransitionDuringActivePlayback()` reproduces
the exact scenario: a handle is created before the buffer lands (resample
fallback), plays a few periods, the buffer lands, the old handle continues with
the old buffer (220 Hz), and a new handle uses the new buffer (440 Hz). Part of
`SampleStretchTest`, which is 47/47 green.

**Open question.** Whether the GUI communicates/handles the stop/restart
requirement correctly is **not yet established** — see §5.

---

## 2. Files changed

```
 data/themes/default/edit_stretch.svg |   2 +-   (fixed malformed XML)
 include/ClipView.h                   |   1 +
 include/SampleClip.h                 | 268 ++++++--  (PitchMode, ratio API,
                                                       PlaybackPlan,
                                                       WaveformMapping,
                                                       stretch delivery)
 include/SampleClipView.h             |  47 +     (waveform mapping hook,
                                                       stretch-mode repaint)
 include/SamplePlayHandle.h           |  35 +-   (plan-based ctor)
 include/SampleStretch.h              | 116 +++--  (manager + result receiver)
 include/SampleThumbnail.h            |  17 +-   (cache key: buffer identity)
 include/SongEditor.h                 |  10 +    (toggleStretchMode)
 src/core/RenderManager.cpp           |  10 +
 src/core/SampleClip.cpp              | 501 ++++++++++++++----
 src/core/SamplePlayHandle.cpp        |  83 ++--
 src/core/SampleStretch.cpp           | 163 +++++--
 src/gui/SampleThumbnail.cpp          |  42 +-
 src/gui/clips/ClipView.cpp           | 123 ++++--  (resize handler + splitClip fix)
 src/gui/clips/SampleClipView.cpp     | 181 ++++
 src/gui/editors/SongEditor.cpp       |  57 ++-
 src/tracks/SampleTrack.cpp           |  58 +--
 tests/CMakeLists.txt                 |   2 +    (new GUI test targets)
 tests/src/core/SampleStretchTest.cpp | 1793 ++++++++++++++++++++++++-----
```

New files (untracked, added by this work):

```
 tests/src/gui/SampleClipContextMenuTest.cpp  GUI test: right-click Pitch mode
                                              menu -> rendered audio (Bug A)
 tests/src/gui/SampleClipViewWaveformTest.cpp GUI test: waveform follows the
                                              stretch edit mode (Bug B)
 tests/src/gui/SampleClipSplitStretchTest.cpp GUI test: split then stretch
                                              (Bug D)
 STRETCH_REPAIR_REPORT.md                     this report
```

**This session's corrections (Bug A–D) touched only:**

```
 src/gui/clips/ClipView.cpp                  | resize handler now always calls
                                             | stretchToLength() for sample clips
                                             | splitClip() uses trimToLength()
                                             | for SampleClip left half
 tests/CMakeLists.txt                        | registers the new GUI test target
 tests/src/gui/SampleClipContextMenuTest.cpp | new — proves the fix through the
                                             | real context-menu action
 tests/src/gui/SampleClipSplitStretchTest.cpp| new — proves the split-then-stretch
                                             | fix through real knife gestures
```

No other file was changed by the Bug A–C corrections. The `SampleClip.cpp`
changes from the previous session (async stretch pipeline, waveform mapping,
trim-to-length source range clamping) remain and are correct.

### The actual fix (this session)

The Bug A/C root cause was in `ClipView::mouseMoveEvent()` — the resize
handler branched on the toolbar's edit mode (`m_action == Action::Stretch`)
to decide between `stretchToLength()` and `trimToLength()`. When the toolbar
Stretch mode was OFF (the default), dragging a sample clip's edge called
`trimToLength()`, which does not change `m_stretchRatio`. The context-menu
Pitch Mode selection sets `m_pitchMode` but this was never consulted by the
resize handler.

**Fix applied to `src/gui/clips/ClipView.cpp` (lines 775–785):**

```cpp
// Before:
if (m_action == Action::Stretch && sClip != nullptr)
{
    sClip->stretchToLength(l);
}
else if (sClip != nullptr)
{
    sClip->trimToLength(l);
}

// After:
if (sClip != nullptr)
{
    sClip->stretchToLength(l);
}
else
{
    m_clip->changeLength(l);
    m_clip->setAutoResize(false);
}
```

The resize handler now always calls `stretchToLength()` for sample clips,
regardless of toolbar mode. The pitch mode (Resample vs Stretch) selected
from the context menu controls how the stretched ratio is rendered in
`computePlaybackPlan()`. This makes the context-menu Pitch Mode the
authoritative control for stretch rendering.

No changes to `SampleClip.cpp` were needed — the existing `stretchToLength()`
and `computePlaybackPlan()` already correctly implement the contract when
`stretchToLength()` is actually called.

### The Bug D fix (this session)

The Bug D root cause was in `ClipView::splitClip()` — it used `changeLength()`
for the left half of a split sample clip, which leaves the source range
untouched. The left half claimed the entire original sample.

**Fix applied to `src/gui/clips/ClipView.cpp` (lines 1314–1328):**

```cpp
// Before:
m_clip->changeLength(splitPos - m_initialClipPos);

// After:
if (auto* sClip = dynamic_cast<SampleClip*>(m_clip))
{
    sClip->trimToLength(splitPos - m_initialClipPos);
}
else
{
    m_clip->changeLength(splitPos - m_initialClipPos);
}
```

For `SampleClip`, `trimToLength()` computes the split frame from the clip
geometry (using the same `sourceFrameAtOutputFrame` mapping playback uses) and
narrows `m_sourceEndFrame` correctly. Non-sample clips still use
`changeLength()`.

No change needed for the right half — its negative `startTimeOffset`
representation is correct and `materialiseAudibleRange()` handles it properly.

### Why the test drives the menu, not a `.mmp` file

The user's instruction was explicit: the broken control is *right-click the
sample → Pitch Method → Stretch*, and a hand-written `.mmp` render probe is not
acceptable proof, because it loads serialized state and never exercises the
menu action, the clip's state change, or the drag. The chain that had to be
reproduced is:

```
QContextMenuEvent -> ClipView::contextMenuEvent()  (src/gui/clips/ClipView.cpp:935)
  | builds `QMenu contextMenu(this)`, which calls
  |     SampleClipView::constructContextMenu()   (src/gui/clips/SampleClipView.cpp:212)
  | then QMenu::exec() shows it
  |   -> the test's timer finds the *live* popup and trigger()s the checkable
  |      "Stretch" QAction --> SampleClip::setPitchMode(Stretch)
  |
ClipView::mouseMoveEvent()  (real QMouseEvent, right edge)
  | SampleClip::stretchToLength(ticks) --> m_stretchRatio, refreshStretchBuffer()
                                                       |
SampleClip::computePlaybackPlan()  <-- stretched buffer (async worker)
  | SamplePlayHandle(plan) --play()--> frames --> measured duration + pitch
```

One deliberate deviation from a literal mouse-driven run, recorded here so the
evidence is not overstated:

1. **The drag is delivered as synthetic `QMouseEvent`s** via
   `QApplication::sendEvent()` with the button/modifier state a real drag
   produces (press with `AltModifier`, moves with `buttons=LeftButton`,
   release with none). `QTest::mouseMove()` cannot be used: it has no modifiers
   parameter, and its third argument is a delay in milliseconds.

The right-click itself is **not** a deviation. The test sends a real
`QContextMenuEvent` to the real `SampleClipView`, so `contextMenuEvent()` runs
end to end and `QMenu::exec()` opens the menu on screen. Because `exec()`
blocks in a nested event loop, the item is read and triggered from a `QTimer`
that keeps firing inside that loop; the popup is located among the clip view's
own children, since `contextMenuEvent()` builds it as `QMenu contextMenu(this)`.
Triggering the `QAction` is exactly what a mouse click on that row does, and it
is also what dismisses the menu and lets `exec()` return. The attempt count is
bounded, so if the menu or the item ever disappears the test fails rather than
hanging.

Everything downstream of the gesture — `ClipView::mouseMoveEvent()`,
`SampleClip::stretchToLength()`, the async `SampleStretchManager` worker,
`computePlaybackPlan()`, and `SamplePlayHandle::play()` — is the production
code path, and the assertions are on the samples it emits.

---

## 3. Architecture

### One `PlaybackPlan` seam

`SampleClip::computePlaybackPlan(double startOutputFrame)` is the single
producer of "which buffer, which frame range, which resample ratio, how many
output frames". `SampleTrack` builds one plan per clip per period;
`SamplePlayHandle`'s only clip-backed constructor consumes a plan. The play
handle and the track cannot disagree about where a seek lands.

### Ratio convention

```
ratio = audible clip duration / natural duration of the selected source range
```

The ratio is **stored state**, never derived from the clip length: trimming
changes length and source range but leaves the ratio (and therefore speed and
pitch) untouched; stretching changes the ratio. `isStretched()` is
`|ratio − 1| > 0.0001`.

### Async stretch pipeline

```
GUI thread                          worker thread
refreshStretchBuffer()
  ├─ parameters call for no stretch → drop cached buffer synchronously
  ├─ cached buffer still matches    → do nothing
  └─ otherwise: bump generation,
     enqueue (receiver, generation,
     key, buffer, range, rates, ratio)
                                        Worker::run():
                                          compute SampleStretch::stretch
                                          (no locks held)
                                          post deliver() queued
applyStretchResult(generation, key, sample)
  ├─ generation/key mismatch → discard (stale)
  └─ match → install buffer, emit sampleChanged()
```

`waitUntilIdle()` (Qt 5: a `while` loop over `QWaitCondition::wait(&mutex)`,
since the predicate overload is Qt 6 only) is used **only by tests** to make
the async pipeline deterministic.

### Waveform mapping

`SampleClip::waveformMapping(const Sample&)` → `{sampleStart, sampleEnd}`
fractions of the sample to draw, clamped to the audible range. Shared by both
paint branches; the same mapping playback uses. `SampleClipView::
waveformGeometry()` turns that plus the pixels-per-bar scale and scroll offset
into the rectangle `paintEvent()` draws, and is `static`/pure precisely so it
can be asserted on without rasterising.

---

## 4. Automated test evidence (this session, both platforms)

### `tests/src/core/SampleStretchTest.cpp` — 47 slots

The test file covers the mandatory invariants plus retained coverage. The
async pipeline is made deterministic by `waitForStretched()` (idle barrier +
`processEvents()`), used only in tests.

| Slot | What it proves |
|------|----------------|
| `resampleDoubleLengthDoublesDurationAndLowersPitch` | Resample 2.0 → ~2 s, dominant frequency drops (440→220 Hz region). |
| `resampleHalfLengthHalvesDurationAndRaisesPitch` | Resample 0.5 → ~0.5 s, frequency rises. |
| `stretchDoublePreservesPitch` | Stretch 2.0 → ~2 s, **pitch preserved** (440 Hz region). |
| `stretchHalfPreservesPitch` | Stretch 0.5 → ~0.5 s, pitch preserved. |
| `trimDoesNotChangePlaybackSpeed` | Trim → stretch → trim keeps the ratio at 2.0 and the rendered pitch at 220 Hz (Bug 3). |
| `frontEdgeStretchKeepsEndAndAllAudio` | Left-edge stretch anchors the right edge, keeps all audio, ratio > 1 (Bug 4). |
| `frontEdgeTrimKeepsEndAndSpeed` | Left-edge trim keeps the right edge and the speed (Bug 4). |
| `stretchedBufferMatchesClipOutputDuration` | The stretched buffer's length equals the clip's output duration. |
| `seekMatchesContinuousPlayback` | A render started mid-clip matches the corresponding slice of a continuous render — seeking is consistent. |
| `stretchRoundTripRestoresOriginal` | 200% → 50% → 100% restores the source byte-for-byte (1e-6) — non-destructive. |
| `serializationPreservesStretchState` | Save/load round-trip preserves mode, ratio, source range, geometry; the reloaded clip rebuilds its stretched buffer. |
| `defaultModeIsResample` / `oldProjectsDefaultToResample` | Old projects and new clips default to Resample. |
| `modeSwitchKeepsLength` / `selectingActiveModeIsNoOp` / `modeSwitchIsOneUndoEntry` | Mode switching is length-preserving, idempotent, one undo entry. |
| `stretchModeAtRatioOneBypasses` / `switchingToResampleClearsStretchedBuffer` | No stretch work at ratio 1; leaving Stretch drops the buffer. |
| `stretchDurationFollowsRatio` | Offline stretch output length = ratio × input length (±5%). |
| `stretchLeavesSourceUntouched` | The source buffer is never modified. |
| `stretchHonoursSubrange` | Stretching a subrange stretches only that range. |
| `stretchRejectsDegenerateInputs` | Empty/1-frame/zero-rate/zero-ratio/null inputs return nullptr. |
| `cacheKeyDistinguishesParameters` | The cache key changes with every parameter. |
| `missingSourceFileDoesNotCrash` | A missing file degrades gracefully. |
| `sharedSourceClipsRenderIndependently` | Two clips sharing one source buffer stretch independently (2.0 and 3.0) to different buffers. |
| `liveRenderMatchesOfflineStretchedBuffer` | Live handle render agrees with the offline stretched buffer (two-sided shift search, < 1% RMS — the shift absorbs the resampler's constant group delay). |
| `stretchUnavailableReportsDegradedBuild` | `stretchUnavailable()` is false when SoundTouch is present and the result has landed. |
| `stretchModeWithoutBufferYetUsesResamplePath` | **Bug A** — Stretch mode without a buffer yet falls through to the Resample path: the plan has no stretched source, `resampleRatio == ratio`, and the rendered audio fills the clip's duration at the shifted pitch (220 Hz for a 2× stretch of a 440 Hz sine). Once the buffer lands, the plan switches to ratio 1.0. |
| `waveformMappingStretchedBufferSpansFullBuffer` | **Bug B** — when drawing the stretched buffer, the mapping is `{0.0, 1.0}` (plain fraction), not a ratio-applied source mapping. |
| `waveformMappingOriginalBufferUsesResampleMapping` | **Bug B** — when drawing the original source in Resample mode, the mapping still spans `{0.0, 1.0}` because `sourceFrameAtOutputFrame` applies the ratio correctly. |
| `trimThenStretchPreservesSourceRange` | **Bug C** — trim to half, then stretch to 2×: the source range stays the trimmed half, the plan uses the Resample path with `ratio == 2.0` and the correct total output frames, the rendered pitch is 220 Hz until the buffer lands, then 440 Hz (pitch preserved) once it does. |
| ... (additional regression and edge-case slots) | ... |

### `tests/src/gui/SampleClipContextMenuTest.cpp` — 8 slots (new, this session)

The GUI integration test described in §2. Runs under X11 (`DISPLAY=:0`, xcb)
against a real `MainWindow` and `SongEditor` at 96 px/bar, with `AudioDummy`
as the audio device. Each slot builds a clip + view, right-clicks the clip
widget so `ClipView::contextMenuEvent()` pops up the real menu, picks the item
out of that live popup, drags the right edge with real mouse events, renders
through the shipped `SamplePlayHandle`, and measures duration and dominant
frequency (zero crossing) of the emitted audio. Duration/pitch expectations are
derived from the input buffer (440 Hz sine left / 880 Hz right at 44 100 Hz)
and the requested length, never from the implementation. The test is
tempo-agnostic: seconds ↔ ticks go through `Engine::framesPerTick()`.

There is no test-only subclass of `SampleClipView`: the class is used as
shipped, and the only way this file reaches the *Pitch mode* items is by
delivering a `QContextMenuEvent` and reading the `QMenu` that is on screen.

### `tests/src/gui/SampleClipSplitStretchTest.cpp` — 8 slots (new, this session)

The GUI integration test for the split-then-stretch bug (Bug D). Runs under
X11 (`DISPLAY=:0`, xcb) against a real `MainWindow` and `SongEditor` at 96
px/bar, with `AudioDummy` as the audio device. Each slot builds a two-tone
sample clip (440 Hz left channel / 880 Hz right channel, 8 s total), sends
real `QMouseEvent`s with `AltModifier` to `ClipView::mousePressEvent()` /
`mouseMoveEvent()` / `mouseReleaseEvent()` — the exact knife gesture that
invokes `ClipView::splitClip()` — then selects the left or right half and
drags its right edge with real mouse events, renders through the shipped
`SamplePlayHandle`, and measures duration and dominant frequency (zero
crossing) of the emitted audio. Duration/pitch expectations are derived from
the input buffer and the requested length, never from the implementation.

| Test | Measured |
|---|---|
| `splitProducesTwoClipsWithExpectedGeometry` | Left half: 4 s (224 px), right half: 4 s at splitPos |
| `splitAssignsRetainedSourceRangeToEachHalf` | Left: sourceEndFrame ≈ 176400 (first half); Right: effective window [176400..352800] via negative offset |
| `stretchingLeftHalfKeepsFirstSection` | Stretch 4 s → 8 s: **7.998 s @ 438.2 Hz** (440 Hz section only) |
| `stretchingRightHalfKeepsSecondSection` | Stretch 4 s → 8 s: **7.998 s @ 876.0 Hz** (880 Hz section only) |
| `shorteningLeftHalfKeepsFirstSection` | Shorten 4 s → 2 s: **1.999 s @ 439.8 Hz** (440 Hz section only) |
| `freshUnsplitClipStillStretchesWholeSample` | Fresh 8 s clip stretched to 16 s: **15.998 s @ 439.1 Hz** (both sections preserved) |

**Negative control.** The one-line fix in `ClipView::splitClip()` was reverted
(`trimToLength` → `changeLength`), the target rebuilt, and the suite re-run
unchanged. Result: `5 passed, 3 failed`, exit 3 — the three failures exactly
match the reported bug (left half claims whole sample, stretching leaks the
discarded section). Restoring the fix returns the suite to `8 passed, 0
failed`.

### Results

**Linux** (`QT_QPA_PLATFORM=offscreen`, ctest):

```
100% tests passed, 0 tests failed out of 16
  (SampleStretchTest: 47 passed, 0 failed)
  (SampleClipContextMenuTest: skipped — it requires a real display, see below)
  (SampleClipSplitStretchTest: skipped — it requires a real display, see below)
```

`SampleClipContextMenuTest` and `SampleClipSplitStretchTest` check
`QGuiApplication::platformName()` in `initTestCase()` and report `SKIP`
unless running on `xcb`/`wayland`. They deliberately do not pretend to pass
under `offscreen`: that platform never maps a window, so no popup would appear
and the test would prove nothing.

**Linux, GUI suites** (`DISPLAY=:0`, xcb — `offscreen` hangs inside
`GuiApplication` construction in this build):

```
SampleClipContextMenuTest        10 passed, 0 failed   (8 test slots + setup/teardown)
SampleClipViewWaveformTest        8 passed, 0 failed   (6 test slots + setup/teardown)
SampleClipSplitStretchTest        8 passed, 0 failed   (6 test slots + setup/teardown)
TrackRowInteractionFilterTest    14 passed, 0 failed
SampleRecordingTest               9 passed, 0 failed
SampleStretchTest                47 passed, 0 failed
```

**Windows / Wine** (MinGW `.exe` binaries, `QT_QPA_PLATFORM=offscreen`,
deployed with `deploy-win-tests.sh`):

```
ArrayVectorTest               39 passed, 0 failed
AudioBufferTest               31 passed, 0 failed
AutomatableModelTest           6 passed, 0 failed
AutomationTrackTest            9 passed, 0 failed
ClipboardMimeTest             15 passed, 0 failed
MathTest                       3 passed, 0 failed
ProjectVersionTest             3 passed, 0 failed
RecordingWorkflowTest         26 passed, 0 failed
RelativePathsTest              6 passed, 0 failed
SampleRecordingTest            9 passed, 0 failed
SampleStretchTest             47 passed, 0 failed
TimelineTest                   6 passed, 0 failed
TrackRowInteractionFilterTest 14 passed, 0 failed
```

**Honesty note on the test suite:** the tests prove the *math and the
pipeline* — ratio bookkeeping, rendered pitch, buffer lengths, seek
consistency, serialization, non-destructiveness, and that the async pipeline
delivers the right buffer to the right clip. The new regression slots
(§4) additionally prove, with **rendered audio** rather than internal state,
that:

- Stretch mode without a buffer yet fills the clip's duration at the shifted
  pitch (Bug A);
- the waveform mapping recognises the stretched buffer vs the original source
  (Bug B);
- trim-then-stretch preserves the trimmed source range and renders at the
  expected pitch at each stage (Bug C);
- split-then-stretch assigns the correct retained source range to each half
  and stretches only that range (Bug D).

What **is** now proven by the GUI suite (`SampleClipContextMenuTest`):

- that right-clicking the clip shows a *Pitch mode* submenu with checkable,
  enabled *Resample* and *Stretch* items, with *Resample* checked on a fresh
  clip — read off the live `QMenu` inside `QMenu::exec()`, not off a menu the
  test assembled;
- that selecting the *Stretch* item from that popup changes
  `SampleClip::pitchMode()`, and selecting *Resample* changes it back;
- that with *Stretch* selected from that menu, dragging the right edge renders
  the requested duration **at the original pitch** (16 s @ 439.1 Hz, 4 s @
  439.8 Hz), and with *Resample* selected it renders the requested duration at
  the shifted pitch (16 s @ 219.9 Hz, 4 s @ 879.8 Hz);
- that toggling only the menu choice, with length held fixed, changes what is
  heard (219.938 Hz → 439.121 Hz).

What **is** now proven by the GUI suite (`SampleClipSplitStretchTest`):

- that the knife gesture (Alt+drag) invokes `ClipView::splitClip()` and
  produces two clips with correct geometry;
- that the left half's `sourceEndFrame` is narrowed to the split point
  (~176400 frames for an 8 s sample split at 4 s);
- that the right half's effective source window is [176400..352800] via its
  negative `startTimeOffset`;
- that stretching the left half 4 s → 8 s renders **7.998 s @ 438.2 Hz** (the
  440 Hz section only — the discarded 880 Hz section does not leak);
- that stretching the right half 4 s → 8 s renders **7.998 s @ 876.0 Hz** (the
  880 Hz section only);
- that shortening the left half 4 s → 2 s renders **1.999 s @ 439.8 Hz** (the
  440 Hz section only);
- that a fresh unsplit clip stretched to 16 s renders **15.998 s @ 439.1 Hz**
  (both sections preserved — Pitch Method → Stretch still works).

**Negative control (the test is not self-confirming).** The one-line fix in
`ClipView::mouseMoveEvent()` was reverted (`stretchToLength(l)` →
`trimToLength(l)`), the target rebuilt, and the suite re-run unchanged. Result:
`5 passed, 5 failed`, exit 5 —

```
FAIL!  stretchTo16sKeepsPitch()             (stretch ratio 1, expected ~2)
FAIL!  resampleTo16sShiftsPitch()           (expected ~16 s, got 8)
FAIL!  stretchTo4sKeepsPitch()              hasStretchedSample() == false
FAIL!  resampleTo4sShiftsPitch()            (expected ~880 Hz, got 439.75)
FAIL!  selectingStretchFromMenuChanges…()   (expected ~220 Hz, got 439.875)
```

The two menu-inspection slots (`contextMenuOffersPitchModes`,
`menuActionSetsPitchMode`) still passed under the revert, which is the correct
behaviour: the menu itself was never the defect, so a test that failed there
would be testing the wrong thing. Restoring the line returns the suite to
`10 passed, 0 failed`.

**Negative control for Bug D.** The one-line fix in `ClipView::splitClip()`
was reverted (`trimToLength` → `changeLength`), the target rebuilt, and the
suite re-run unchanged. Result: `5 passed, 3 failed`, exit 3 — the three
failures exactly match the reported bug (left half claims whole sample,
stretching leaks the discarded section). Restoring the fix returns the suite
to `8 passed, 0 failed`.

They do **not** prove:

- that the GUI thread stays responsive during a real drag (no test simulates a
  40-step mouse drag against a live audio engine);
- that the waveform *looks* correct on screen (no pixel-level test of
  `paintEvent`);
- that the audio engine does not stall (no test measures render-thread
  latency).

Those are runtime/manual properties — see §5.

---

## 5. Manual GUI checks still required (not yet performed)

The GUI **can** be driven in this environment — `SampleClipContextMenuTest`,
`SampleClipViewWaveformTest`, and `SampleClipSplitStretchTest` run against a
real `MainWindow` under X11 (`DISPLAY=:0`, xcb) — and the checks below are the
ones that still need a human because they are about smoothness, appearance, or
how something *sounds*:

1. **No freeze (Bug 1)** — with a 4 s sample clip, drag its right edge in
   Stretch mode across ~40 steps while the song is playing. The audio must
   keep playing without a stall, and the GUI must stay responsive.
2. **Waveform, Stretch OFF (Bug 2)** — trim a clip shorter; the waveform must
   show the retained source range at its original time scale, not a
   horizontally rescaled whole.
3. **Waveform, Stretch ON (Bug 2)** — stretch the same clip; the waveform must
   fill the new duration from the stretched buffer.
4. **Trim then stretch (Bug 3)** — trim [A B C D E F G H] to [A B C D], then
   stretch to 2×: the audio must be the retained 4 s stretched (ratio 2), not
   the full 8 s.
5. **Front edge (Bug 4)** — left-edge stretch and left-edge trim behave as
   before (right edge anchored, no audio discarded by the stretch itself).
6. **Bug A — Context-menu Pitch Mode → Stretch actually stretches.**
   **Automated — no manual step needed.** `SampleClipContextMenuTest` performs
   exactly this (menu action + drag + rendered audio) and passes: Stretch →
   16 s gives 15.998 s @ 439.1 Hz, Stretch → 4 s gives 3.999 s @ 439.8 Hz,
   Resample gives 16 s @ 219.9 Hz and 4 s @ 879.8 Hz. A manual listen is still
   welcome for the *subjective* artefacts the measurement cannot see —
   transient smearing or phasing on a real musical sample, which a pure sine
   cannot reveal.
7. **Bug B — waveform follows the mode.** With the clip's *Pitch mode*
   (right-click → "Pitch mode") set to Resample, the waveform must show the
   source at its original time scale. Switch it to Stretch and the waveform
   must fill the stretched duration.
8. **Bug C — trim then stretch with the context menu.** Trim to half via the
   toolbar's Trim mode, then switch the *Pitch mode* to Stretch via the
   context menu and drag the right edge to 2×. The audio must be the retained
   half stretched (pitch preserved once the buffer lands), not the full
   source.
9. **Bug D — split then stretch with the context menu.** Import an 8 s sample,
   cut/split it at 4 s (Alt+drag knife gesture), select the left half, switch
   the *Pitch mode* to Stretch via the context menu, and drag the right edge
   to 8 s. The audio must be the retained first 4 s stretched (pitch preserved
   once the buffer lands), not the full 8 s. Repeat for the right half.
10. **Independent settings.** Toggle the toolbar's Stretch edit mode on and off
   and confirm it does **not** change the clip's Pitch mode (the context
   menu's checkmark is unaffected), and vice versa.

---

## 6. Remaining limitations (do not read as "complete")

- **Degraded path in `computePlaybackPlan()` — fixed.** Stretch mode with no
  stretched buffer yet falls through to the Resample path
  (`src/core/SampleClip.cpp`, ~line 606), so the audio fills the clip's
  duration at the shifted pitch until the worker lands the buffer, instead of
  ending early at natural speed. Covered by
  `stretchModeWithoutBufferYetUsesResamplePath()` and visible in the GUI test,
  where the pitch is measured before and after the async buffer arrives.
- **No SoundTouch → no stretch.** `SampleStretch::stretch` returns `nullptr`
  and `stretchUnavailable()` reports the degraded state; playback stays
  pitch-correct at ratio 1.0. Both builds in this repo have SoundTouch, so
  this is not the case here.
- **1-frame resampler group delay.** The live path runs the libsamplerate
  resampler even at ratio 1.0, adding a small constant delay relative to the
  raw stretched buffer. Architectural, not a clip bug; the live/offline test
  absorbs it with a shift search.
- **Windows verified under Wine, not on a real Windows host.** The GUI
  integration suite (`SampleClipContextMenuTest`) has only been run on Linux;
  it has **not** been run under Wine.
- **Manual GUI checks in §5 not yet performed.** Until they are, the
  on-screen appearance and real-time smoothness remain code- and
  unit-verified but **not user-verified**.

**Bottom line:** the audio math, the async pipeline, the trim/stretch
interaction, the split/stretch interaction, the serialization round-trip, and
the non-destructive round-trip are proven by automated tests on both platforms
(16/16 ctest targets on Linux — the GUI integration tests skip themselves
there because ctest runs `offscreen` — and 13/13 Windows-under-Wine). **Bug A
— the reported failure — is proven by an automated GUI test that delivers a
real `QContextMenuEvent` to the clip widget, selects *Stretch* from the menu
`QMenu::exec()` puts on screen, performs a real edge drag, and measures the
rendered audio**: Stretch preserves pitch at both doubled and halved durations,
Resample shifts it by the expected octave, and toggling only the menu choice
changes what is heard. **Bug D — the cut-sample source-range bug — is proven by
an automated GUI test that drives the real knife gesture (Alt+drag) to invoke
`ClipView::splitClip()`, selects each resulting half, stretches it, and
measures the rendered audio**: each half stretches only its retained section
(left: 440 Hz, right: 880 Hz), and a fresh unsplit clip still stretches the
whole sample correctly. What remains unverified is narrower: on-screen waveform
appearance, real-time smoothness during a drag, and subjective stretch
artefacts on non-sinusoidal material. This is not described as complete.
