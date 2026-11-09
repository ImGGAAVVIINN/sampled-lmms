/*
 * StretchDebug.h - Thread-safe diagnostic logging for sample stretch investigation
 *
 * Copyright (c) 2025
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

#ifndef LMMS_STRETCH_DEBUG_H
#define LMMS_STRETCH_DEBUG_H

#include <atomic>
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

namespace lmms
{

/**
 * @class StretchDebug
 * @brief Thread-safe, non-blocking diagnostic logger for stretch investigation.
 *
 * Uses a lock-free queue for the audio thread and a background writer thread
 * to flush to disk. Safe to call from real-time audio callbacks.
 */
class StretchDebug
{
public:
    enum class EventType
    {
        PitchModeChanged,
        StretchToLength,
        TrimToLength,
        RefreshStretchBuffer,
        ComputePlaybackPlan,
        ApplyStretchResult,
        StretchRequestQueued,
        StretchJobStarted,
        StretchJobCompleted,
        StretchJobRejected,
        StretchJobDiscarded,
        StretchProgress,
        PlayHandleCreated,
        PlayHandlePlay,
        BufferStateChange,
        Error,
        EarlyReturn,
        CacheInvalidation
    };

    struct Event
    {
        EventType type;
        std::chrono::steady_clock::time_point timestamp;
        std::thread::id threadId;
        std::string clipId;
        std::string message;
        // Structured fields for key events
        int sampleRate = 0;
        int originalFrames = 0;
        int clipLength = 0;
        int sourceStartFrame = 0;
        int sourceEndFrame = 0;
        double stretchRatio = 0.0;
        int pitchMode = 0; // 0=Resample, 1=Stretch
        int oldPitchMode = 0;
        int newPitchMode = 0;
        // Stretch request params
        int reqStartFrame = 0;
        int reqEndFrame = 0;
        int reqSourceRate = 0;
        int reqEngineRate = 0;
        double reqRatio = 0.0;
        // Stretch result
        int resultFrames = 0;
        uint64_t generation = 0;
        uint64_t key = 0;
        // Playback plan
        int planStartFrame = 0;
        int planEndFrame = 0;
        double planResampleRatio = 0.0;
        double planTotalOutputFrames = 0.0;
        bool planHasStretchedSource = false;
        // Play handle
        int handleFramesDone = 0;
        int handleTotalFrames = 0;
        double handlePlaybackRatio = 0.0;
        int handleConsumedFrames = 0;
    };

    static StretchDebug& instance();

    // Initialize the logger (call once at startup)
    void initialize(const std::string& logPath = "/tmp/lmms-stretch-debug.log");

    // Shutdown the logger
    void shutdown();

    // Log an event (thread-safe, non-blocking)
    void log(const Event& event);

    // Convenience logging functions
    void logPitchModeChanged(const std::string& clipId, int oldMode, int newMode);
    void logStretchToLength(const std::string& clipId, int clipLength, int sourceStart, int sourceEnd, double ratio);
    void logTrimToLength(const std::string& clipId, int newLength, int sourceStart, int sourceEnd);
    void logRefreshStretchBuffer(const std::string& clipId, int pitchMode, double ratio, int sourceStart, int sourceEnd, bool hasSample);
    void logComputePlaybackPlan(const std::string& clipId, const Event& plan);
    void logApplyStretchResult(const std::string& clipId, uint64_t generation, uint64_t key, int resultFrames, bool success);
    void logStretchRequestQueued(const std::string& clipId, uint64_t generation, uint64_t key, int startFrame, int endFrame, int sourceRate, int engineRate, double ratio);
    void logStretchJobStarted(const std::string& clipId, uint64_t generation, uint64_t key);
    void logStretchJobCompleted(const std::string& clipId, uint64_t generation, uint64_t key, int outputFrames);
    void logStretchJobRejected(const std::string& clipId, uint64_t generation, uint64_t key, const std::string& reason);
    void logStretchJobDiscarded(const std::string& clipId, uint64_t generation, uint64_t key, const std::string& reason);
    void logStretchProgress(uint64_t key, int processedFrames, int totalFrames);
    void logPlayHandleCreated(const std::string& clipId, const Event& plan);
    void logPlayHandlePlay(const std::string& clipId, int framesDone, int totalFrames, double playbackRatio, int consumedFrames);
    void logBufferStateChange(const std::string& clipId, const std::string& change);
    void logError(const std::string& clipId, const std::string& error);
    void logEarlyReturn(const std::string& clipId, const std::string& location, const std::string& reason);
    void logCacheInvalidation(const std::string& clipId, const std::string& reason);

private:
    StretchDebug();
    ~StretchDebug();

    void writerThread();
    void writeEvent(const Event& event);

    std::atomic<bool> m_running{false};
    std::thread m_writerThread;
    std::mutex m_queueMutex;
    std::queue<Event> m_eventQueue;
    std::string m_logPath;
    FILE* m_logFile = nullptr;
    std::chrono::steady_clock::time_point m_startTime;
    std::atomic<uint64_t> m_eventCounter{0};
};

// Helper to generate a unique clip identifier
inline std::string makeClipId(const void* clipPtr)
{
    return "clip@" + std::to_string(reinterpret_cast<uintptr_t>(clipPtr));
}

// Helper to get current timestamp as string
inline std::string timestampString(std::chrono::steady_clock::time_point tp, std::chrono::steady_clock::time_point start)
{
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(tp - start).count();
    double seconds = elapsed / 1000000.0;
    char buf[32];
    snprintf(buf, sizeof(buf), "%.6f", seconds);
    return std::string(buf);
}

} // namespace lmms

#endif // LMMS_STRETCH_DEBUG_H