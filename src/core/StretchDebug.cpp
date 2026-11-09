/*
 * StretchDebug.cpp - Thread-safe diagnostic logging for sample stretch investigation
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

#include "StretchDebug.h"

#include <cstdio>
#include <cstring>
#include <iomanip>
#include <sstream>

namespace lmms
{

StretchDebug& StretchDebug::instance()
{
    static StretchDebug inst;
    return inst;
}

StretchDebug::StretchDebug()
{
}

StretchDebug::~StretchDebug()
{
    shutdown();
}

void StretchDebug::initialize(const std::string& logPath)
{
    if (m_running.load()) { return; }

    m_logPath = logPath;
    m_startTime = std::chrono::steady_clock::now();

    m_logFile = std::fopen(m_logPath.c_str(), "w");
    if (!m_logFile)
    {
        // Fallback to stderr if file can't be opened
        m_logFile = stderr;
    }

    // Write header
    std::fprintf(m_logFile, "# LMMS Stretch Debug Log\n");
    std::fprintf(m_logFile, "# Started at: %s\n", timestampString(m_startTime, m_startTime).c_str());
    std::fprintf(m_logFile, "# Format: timestamp(sec) | thread | event_type | clip_id | message | structured_data\n");
    std::fflush(m_logFile);

    m_running.store(true);
    m_writerThread = std::thread(&StretchDebug::writerThread, this);
}

void StretchDebug::shutdown()
{
    if (!m_running.load()) { return; }

    m_running.store(false);
    if (m_writerThread.joinable())
    {
        m_writerThread.join();
    }

    if (m_logFile && m_logFile != stderr)
    {
        std::fclose(m_logFile);
        m_logFile = nullptr;
    }
}

void StretchDebug::log(const Event& event)
{
    if (!m_running.load()) { return; }

    std::lock_guard<std::mutex> lock(m_queueMutex);
    m_eventQueue.push(event);
}

void StretchDebug::writerThread()
{
    while (m_running.load())
    {
        Event event;
        bool hasEvent = false;

        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            if (!m_eventQueue.empty())
            {
                event = std::move(m_eventQueue.front());
                m_eventQueue.pop();
                hasEvent = true;
            }
        }

        if (hasEvent)
        {
            writeEvent(event);
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    // Flush remaining events
    while (true)
    {
        Event event;
        bool hasEvent = false;
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            if (!m_eventQueue.empty())
            {
                event = std::move(m_eventQueue.front());
                m_eventQueue.pop();
                hasEvent = true;
            }
        }
        if (!hasEvent) { break; }
        writeEvent(event);
    }
}

void StretchDebug::writeEvent(const Event& event)
{
    if (!m_logFile) { return; }

    uint64_t seq = m_eventCounter.fetch_add(1);
    std::string ts = timestampString(event.timestamp, m_startTime);
    // std::thread::id doesn't have a portable way to get numeric ID, hash it instead
    std::size_t threadHash = std::hash<std::thread::id>{}(event.threadId);
    std::string threadId = std::to_string(threadHash);

    const char* typeStr = "Unknown";
    switch (event.type)
    {
        case EventType::PitchModeChanged: typeStr = "PitchModeChanged"; break;
        case EventType::StretchToLength: typeStr = "StretchToLength"; break;
        case EventType::TrimToLength: typeStr = "TrimToLength"; break;
        case EventType::RefreshStretchBuffer: typeStr = "RefreshStretchBuffer"; break;
        case EventType::ComputePlaybackPlan: typeStr = "ComputePlaybackPlan"; break;
        case EventType::ApplyStretchResult: typeStr = "ApplyStretchResult"; break;
        case EventType::StretchRequestQueued: typeStr = "StretchRequestQueued"; break;
        case EventType::StretchJobStarted: typeStr = "StretchJobStarted"; break;
        case EventType::StretchJobCompleted: typeStr = "StretchJobCompleted"; break;
        case EventType::StretchJobRejected: typeStr = "StretchJobRejected"; break;
        case EventType::StretchJobDiscarded: typeStr = "StretchJobDiscarded"; break;
        case EventType::PlayHandleCreated: typeStr = "PlayHandleCreated"; break;
        case EventType::PlayHandlePlay: typeStr = "PlayHandlePlay"; break;
        case EventType::BufferStateChange: typeStr = "BufferStateChange"; break;
        case EventType::Error: typeStr = "Error"; break;
        case EventType::EarlyReturn: typeStr = "EarlyReturn"; break;
        case EventType::CacheInvalidation: typeStr = "CacheInvalidation"; break;
    }

    // Build structured data string
    std::ostringstream structured;
    structured << "seq=" << seq;

    if (event.sampleRate) structured << " sampleRate=" << event.sampleRate;
    if (event.originalFrames) structured << " originalFrames=" << event.originalFrames;
    if (event.clipLength) structured << " clipLength=" << event.clipLength;
    if (event.sourceStartFrame >= 0) structured << " sourceStart=" << event.sourceStartFrame;
    if (event.sourceEndFrame >= 0) structured << " sourceEnd=" << event.sourceEndFrame;
    if (event.stretchRatio != 0.0) structured << " ratio=" << event.stretchRatio;
    if (event.pitchMode >= 0) structured << " pitchMode=" << event.pitchMode;
    if (event.oldPitchMode >= 0) structured << " oldPitchMode=" << event.oldPitchMode;
    if (event.newPitchMode >= 0) structured << " newPitchMode=" << event.newPitchMode;
    if (event.reqStartFrame >= 0) structured << " reqStart=" << event.reqStartFrame;
    if (event.reqEndFrame >= 0) structured << " reqEnd=" << event.reqEndFrame;
    if (event.reqSourceRate) structured << " reqSrcRate=" << event.reqSourceRate;
    if (event.reqEngineRate) structured << " reqEngRate=" << event.reqEngineRate;
    if (event.reqRatio != 0.0) structured << " reqRatio=" << event.reqRatio;
    if (event.resultFrames) structured << " resultFrames=" << event.resultFrames;
    if (event.generation) structured << " gen=" << event.generation;
    if (event.key) structured << " key=" << event.key;
    if (event.planStartFrame >= 0) structured << " planStart=" << event.planStartFrame;
    if (event.planEndFrame >= 0) structured << " planEnd=" << event.planEndFrame;
    if (event.planResampleRatio != 0.0) structured << " planRatio=" << event.planResampleRatio;
    if (event.planTotalOutputFrames != 0.0) structured << " planTotalFrames=" << event.planTotalOutputFrames;
    if (event.planHasStretchedSource) structured << " planHasStretched=1";
    if (event.handleFramesDone >= 0) structured << " handleDone=" << event.handleFramesDone;
    if (event.handleTotalFrames >= 0) structured << " handleTotal=" << event.handleTotalFrames;
    if (event.handlePlaybackRatio != 0.0) structured << " handleRatio=" << event.handlePlaybackRatio;
    if (event.handleConsumedFrames >= 0) structured << " handleConsumed=" << event.handleConsumedFrames;

    std::fprintf(m_logFile, "%s | %s | %s | %s | %s | %s\n",
        ts.c_str(), threadId.c_str(), typeStr, event.clipId.c_str(),
        event.message.c_str(), structured.str().c_str());
    std::fflush(m_logFile);
}

// Convenience functions
void StretchDebug::logPitchModeChanged(const std::string& clipId, int oldMode, int newMode)
{
    Event e;
    e.type = EventType::PitchModeChanged;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Pitch mode changed";
    e.oldPitchMode = oldMode;
    e.newPitchMode = newMode;
    log(e);
}

void StretchDebug::logStretchToLength(const std::string& clipId, int clipLength, int sourceStart, int sourceEnd, double ratio)
{
    Event e;
    e.type = EventType::StretchToLength;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "stretchToLength called";
    e.clipLength = clipLength;
    e.sourceStartFrame = sourceStart;
    e.sourceEndFrame = sourceEnd;
    e.stretchRatio = ratio;
    log(e);
}

void StretchDebug::logTrimToLength(const std::string& clipId, int newLength, int sourceStart, int sourceEnd)
{
    Event e;
    e.type = EventType::TrimToLength;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "trimToLength called";
    e.clipLength = newLength;
    e.sourceStartFrame = sourceStart;
    e.sourceEndFrame = sourceEnd;
    log(e);
}

void StretchDebug::logRefreshStretchBuffer(const std::string& clipId, int pitchMode, double ratio, int sourceStart, int sourceEnd, bool hasSample)
{
    Event e;
    e.type = EventType::RefreshStretchBuffer;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "refreshStretchBuffer called";
    e.pitchMode = pitchMode;
    e.stretchRatio = ratio;
    e.sourceStartFrame = sourceStart;
    e.sourceEndFrame = sourceEnd;
    e.originalFrames = hasSample ? 1 : 0; // reuse field for hasSample flag
    log(e);
}

void StretchDebug::logComputePlaybackPlan(const std::string& clipId, const Event& plan)
{
    Event e = plan;
    e.type = EventType::ComputePlaybackPlan;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "computePlaybackPlan";
    log(e);
}

void StretchDebug::logApplyStretchResult(const std::string& clipId, uint64_t generation, uint64_t key, int resultFrames, bool success)
{
    Event e;
    e.type = EventType::ApplyStretchResult;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = success ? "applyStretchResult: SUCCESS" : "applyStretchResult: FAILED (nullptr)";
    e.generation = generation;
    e.key = key;
    e.resultFrames = resultFrames;
    log(e);
}

void StretchDebug::logStretchRequestQueued(const std::string& clipId, uint64_t generation, uint64_t key, int startFrame, int endFrame, int sourceRate, int engineRate, double ratio)
{
    Event e;
    e.type = EventType::StretchRequestQueued;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Stretch request queued";
    e.generation = generation;
    e.key = key;
    e.reqStartFrame = startFrame;
    e.reqEndFrame = endFrame;
    e.reqSourceRate = sourceRate;
    e.reqEngineRate = engineRate;
    e.reqRatio = ratio;
    log(e);
}

void StretchDebug::logStretchJobStarted(const std::string& clipId, uint64_t generation, uint64_t key)
{
    Event e;
    e.type = EventType::StretchJobStarted;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Stretch job started";
    e.generation = generation;
    e.key = key;
    log(e);
}

void StretchDebug::logStretchJobCompleted(const std::string& clipId, uint64_t generation, uint64_t key, int outputFrames)
{
    Event e;
    e.type = EventType::StretchJobCompleted;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Stretch job completed";
    e.generation = generation;
    e.key = key;
    e.resultFrames = outputFrames;
    log(e);
}

void StretchDebug::logStretchJobRejected(const std::string& clipId, uint64_t generation, uint64_t key, const std::string& reason)
{
    Event e;
    e.type = EventType::StretchJobRejected;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Stretch job rejected: " + reason;
    e.generation = generation;
    e.key = key;
    log(e);
}

void StretchDebug::logStretchJobDiscarded(const std::string& clipId, uint64_t generation, uint64_t key, const std::string& reason)
{
    Event e;
    e.type = EventType::StretchJobDiscarded;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Stretch job discarded: " + reason;
    e.generation = generation;
    e.key = key;
    log(e);
}

void StretchDebug::logPlayHandleCreated(const std::string& clipId, const Event& plan)
{
    Event e = plan;
    e.type = EventType::PlayHandleCreated;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "SamplePlayHandle created";
    log(e);
}

void StretchDebug::logPlayHandlePlay(const std::string& clipId, int framesDone, int totalFrames, double playbackRatio, int consumedFrames)
{
    Event e;
    e.type = EventType::PlayHandlePlay;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "SamplePlayHandle::play";
    e.handleFramesDone = framesDone;
    e.handleTotalFrames = totalFrames;
    e.handlePlaybackRatio = playbackRatio;
    e.handleConsumedFrames = consumedFrames;
    log(e);
}

void StretchDebug::logBufferStateChange(const std::string& clipId, const std::string& change)
{
    Event e;
    e.type = EventType::BufferStateChange;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Buffer state: " + change;
    log(e);
}

void StretchDebug::logError(const std::string& clipId, const std::string& error)
{
    Event e;
    e.type = EventType::Error;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "ERROR: " + error;
    log(e);
}

void StretchDebug::logEarlyReturn(const std::string& clipId, const std::string& location, const std::string& reason)
{
    Event e;
    e.type = EventType::EarlyReturn;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Early return at " + location + ": " + reason;
    log(e);
}

void StretchDebug::logCacheInvalidation(const std::string& clipId, const std::string& reason)
{
    Event e;
    e.type = EventType::CacheInvalidation;
    e.timestamp = std::chrono::steady_clock::now();
    e.threadId = std::this_thread::get_id();
    e.clipId = clipId;
    e.message = "Cache invalidated: " + reason;
    log(e);
}

} // namespace lmms