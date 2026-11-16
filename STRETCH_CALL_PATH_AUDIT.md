# Call-Path Audit — Sample-Clip Waveform / Stretch Separation

Produced **before** any code change, per the directive. Every claim cites exact
source locations in this workspace (`src/`, `include/`).

## 1. Triggering-event call paths

### 1.1 Toolbar Stretch ON, right-edge resize drag

| Item | Value |
|---|---|
| Triggering event | `mouseMoveEvent` with `m_action == Action::Stretch` |
| Entry point | `ClipView::mouseMoveEvent()` — `src/gui/clips/ClipView.cpp:775` |
| Call chain | `ClipView::mousePressEvent` (`ClipView.cpp:440`, opens `beginStretchRequestBatch()` at `ClipView.cpp:561`) → `mouseMoveEvent` → `SampleClip::stretchToLength()` (`src/core/SampleClip.cpp:857`) → `materialiseAudibleRange()` → ratio set → `Clip::changeLength` → `refreshStretchBuffer()` (`SampleClip.cpp:497`) → batch open ⇒ request **deferred** (`SampleClip.cpp:530`) → `mouseReleaseEvent` (`ClipView.cpp:905`, `endStretchRequestBatch()` at `ClipView.cpp:922`) → `refreshStretchBuffer()` issues `SampleStretchManager::request()` (`src/core/SampleStretch.cpp:437`) → worker `SampleStretch::stretch()` (`SampleStretch.cpp:57`) → `applyStretchResult()` (`SampleClip.cpp:560`) → `emit sampleChanged()` → `SampleClipView::updateSample()` (`src/gui/clips/SampleClipView.cpp:57`) → `paintEvent` → `waveformPlan()` → `waveformGeometry()` |
| Processing scheduled? | **Yes** — one request, at mouse release |
| Algorithm executes? | **Yes** — exactly once, after release |
| Buffer changes? | Yes — new `m_stretchedSample` committed under `m_stretchMutex` |
| Geometry/mapping changes? | Yes — toolbar ON ⇒ `spansClip=true`, waveform spans clip |

**Verdict: compliant.** This is the one path that may run the algorithm.

### 1.2 Toolbar ON→OFF toggle (the click itself)

| Item | Value |
|---|---|
| Triggering event | Toolbar button → `SongEditor::setEditMode()` — `src/gui/editors/SongEditor.cpp:440` |
| Entry point | `SongEditor::editModeChanged` signal |
| Call chain | `editModeChanged` → `SampleClipView::updateSample()` (connected in ctor, `SampleClipView.cpp:73–77`) → `m_sampleThumbnail = SampleThumbnail{*waveformBuffer()}` → `update()` → `paintEvent` → `waveformPlan()` → `waveformGeometry()` |
| Processing scheduled? | No |
| Algorithm executes? | No |
| Buffer changes? | No |
| Geometry/mapping changes? | **YES — VIOLATION.** `waveformBuffer()` (`SampleClipView.cpp:100`) re-derives the buffer from live state on every call, and `updateSample()` rebuilds the thumbnail from it. The displayed mapping is re-derived, not frozen. Any change in `stretchedSample()` validity (e.g. a cache-key mismatch) silently swaps the displayed buffer. |

### 1.3 Toolbar OFF, right-edge resize (trim/extend)

| Item | Value |
|---|---|
| Triggering event | `mouseMoveEvent` with `m_action == Action::Resize` |
| Entry point | `ClipView::mouseMoveEvent()` — `ClipView.cpp:838` |
| Call chain | `mousePressEvent` (`ClipView.cpp:440` — `Action::Resize`, but the batch is still opened for sample clips at `ClipView.cpp:561`) → `mouseMoveEvent` → `SampleClip::trimToLength()` (`SampleClip.cpp:796`) → `Clip::changeLength` → `m_sourceEndFrame` reassigned (`SampleClip.cpp:843`) → `emit sampleChanged()` → **`refreshStretchBuffer()` (`SampleClip.cpp:851`, when `pitchMode==Stretch`)** → key mismatch (source range changed) → request queued (deferred by batch, then **issued at mouse release** via `endStretchRequestBatch`, `ClipView.cpp:922`) → worker → `applyStretchResult` → `sampleChanged` → `updateSample` → `paintEvent` |
| Processing scheduled? | **YES — VIOLATION.** A toolbar-off resize queues stretch work. |
| Algorithm executes? | **YES — VIOLATION.** The pitch-mode Stretch algorithm runs on the worker thread. |
| Buffer changes? | **YES — VIOLATION.** `m_stretchedSample` is replaced with a buffer for the trimmed range. |
| Geometry/mapping changes? | **YES — VIOLATION (the visible bug).** While the job is in flight `stretchedSample()` returns `nullptr` (key mismatch), so `waveformBuffer()` falls back to the original source; when the job lands the display swaps to the new stretched buffer. The waveform visibly jumps/rescales during a toolbar-off resize. |

### 1.4 Context menu Pitch mode → Stretch (no drag)

| Item | Value |
|---|---|
| Triggering event | Menu action → `setMode` lambda (`SampleClipView.cpp:243`) |
| Entry point | `SampleClip::setPitchMode()` — `SampleClip.cpp:625` |
| Call chain | `setPitchMode` → `refreshStretchBuffer()` (`SampleClip.cpp:631`) → (if `isStretched()`, ratio ≠ 1) `SampleStretchManager::request()` → worker → `applyStretchResult` |
| Processing scheduled? | **YES — VIOLATION** whenever ratio ≠ 1.0. |
| Algorithm executes? | **YES — VIOLATION.** |
| Buffer changes? | Yes. |
| Geometry/mapping changes? | Yes — via `sampleChanged` → `updateSample`. |

### 1.5 Project load

| Item | Value |
|---|---|
| Triggering event | `loadSettings()` — `SampleClip.cpp:1030` |
| Call chain | restores `m_pitchMode`, `m_sourceStartFrame/EndFrame`, `m_stretchRatio` → `refreshStretchBuffer()` (`SampleClip.cpp:1063`) → request → worker |
| Processing scheduled? | Yes (legitimate: the project asked for a stretched clip) |
| Algorithm executes? | Yes |
| Buffer changes? | Yes |
| Geometry/mapping changes? | Yes — via `sampleChanged` |

**Verdict: compliant** — a loaded stretch is an explicit stretch.

### 1.6 New sample set

| Item | Value |
|---|---|
| Triggering event | `setSampleBuffer()` (`SampleClip.cpp:180`) / `setSampleFile()` (`SampleClip.cpp:199`) |
| Call chain | resets `m_sourceStartFrame=0; m_sourceEndFrame=0; m_stretchRatio=1.0` → `refreshStretchBuffer()` |
| Processing scheduled? | No (ratio 1.0 ⇒ early return, `SampleClip.cpp:466`) |
| Algorithm executes? | No |
| Buffer changes? | Source buffer replaced; stretched buffer cleared |
| Geometry/mapping changes? | Yes — new source, new mapping (legitimate) |

**Verdict: compliant.**

### 1.7 Rendering (`paintEvent`)

| Item | Value |
|---|---|
| Triggering event | Qt paint |
| Entry point | `SampleClipView::paintEvent()` — `SampleClipView.cpp:411` |
| Call chain | `paintEvent` → `waveformPlan()` (`SampleClipView.cpp:196`) → `m_clip->stretchedSample()` (query, takes `m_stretchMutex`) → `waveformGeometry()` |
| Processing scheduled? | No |
| Algorithm executes? | No |
| Buffer changes? | No |
| Geometry/mapping changes? | No mutation — but the decision inputs are re-derived from live mutable state on every paint, so rendering is not observational against a frozen mapping. |

### 1.8 Playback (`computePlaybackPlan`)

| Item | Value |
|---|---|
| Triggering event | Audio engine tick → `SampleTrack::play()` — `src/tracks/SampleTrack.cpp:73` |
| Entry point | `SampleClip::computePlaybackPlan()` — `SampleClip.cpp:660` |
| Call chain | `SampleTrack::play` → `computePlaybackPlan` → (Stretch + valid buffer) read stretched buffer at ratio 1.0; (Stretch, no buffer) degraded natural-speed source path; (Resample) source at `ratio` |
| Processing scheduled? | No |
| Algorithm executes? | No |
| Buffer changes? | No |
| Geometry/mapping changes? | No |

**Verdict: compliant** — playback is already observational.

## 2. The architectural flaw

**There is no display-mapping state.** The waveform's buffer and geometry are
re-derived from live model state on every paint and every `sampleChanged()`:

1. `SampleClipView::waveformBuffer()` (`SampleClipView.cpp:100`) couples display
   to `stretchedSample()` validity — a cache-key mismatch (caused by any trim)
   silently swaps the displayed buffer (§1.3's visible bug).
2. `SampleClip::trimToLength()` (`SampleClip.cpp:851`) treats a model edit as a
   stretch trigger — event ownership violated; the algorithm executes on a
   toolbar-off resize.
3. `SampleClip::setPitchMode()` (`SampleClip.cpp:631`) also triggers
   computation — mode selection is not an explicit stretch trigger.
4. `SampleClipView::updateSample()` connected to `editModeChanged`
   (`SampleClipView.cpp:73`) rebuilds the thumbnail on a pure view-state change.

`waveformPlan()` / `waveformGeometry()` / `spansClip` are **not** the flaw —
`spansClip = toolbarStretch` is already correct. The flaw is upstream: who owns
the mapping and who may update it.

## 3. Structural redesign (implemented after this audit)

Three separated owners:

- **A. Stretch processing** — triggered *only* by `stretchToLength()` /
  `stretchFromStart()` (explicit stretch edits, committed at mouse release via
  the existing batch). `trimToLength()` and `setPitchMode()` never call
  `refreshStretchBuffer()`. Rendering never schedules work.
- **B. Buffer selection** — `stretchedSample()` remains playback state; its
  existence no longer feeds display. Display reads the frozen mapping's buffer.
- **C. Display mapping** — new `m_displayMapping` in `SampleClipView` (buffer
  pointer + sampleStart/sampleEnd + x/width + validity). Updated only by:
  explicit stretch commit, source-space edits while toolbar OFF, toolbar
  OFF→ON transition. **Toolbar ON→OFF freezes it byte-for-byte.** Rendering
  only reads it.
