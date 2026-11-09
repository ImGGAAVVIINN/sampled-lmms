/*
 * SampleStretch.h
 *
 * Copyright (c) 2025 saker <sakertooth@gmail.com>
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

#ifndef LMMS_SAMPLE_STRETCH_H
#define LMMS_SAMPLE_STRETCH_H

#include <cstdint>
#include <memory>

#include <QObject>

#include "LmmsTypes.h"
#include "Sample.h"
#include "SampleBuffer.h"

namespace lmms
{

/**
 * @class SampleStretch
 * @brief Offline, non-real-time time-stretch engine for sample clips.
 *
 * Produces a brand-new @ref Sample whose buffer is the time-stretched
 * (pitch-preserving) version of a source @ref SampleBuffer subrange. The
 * subrange is resampled from the source rate to the audio engine's output
 * sample rate first, so the result can be fed straight into the existing
 * playback path with ratio 1.0.
 *
 * SoundTouch (LGPLv2.1) is used when LMMS_HAVE_SOUNDTOUCH is defined;
 * otherwise stretch() returns nullptr and callers must fall back to
 * traditional resampling. The source buffer is never modified.
 */
class SampleStretch
{
public:
	/**
	 * @brief Compute a stable cache key for the given stretch parameters.
	 *
	 * The key mixes the buffer's identity pointer (so clips sharing one
	 * source file, or a clip whose buffer was replaced, never reuse a
	 * stretched buffer computed from different data) plus every parameter
	 * that affects the output.
	 */
	static uint64_t cacheKey(
		const void* bufferIdentity,
		int startFrame, int endFrame,
		sample_rate_t sourceRate,
		sample_rate_t engineRate,
		double ratio);

	/**
	 * @brief Stretch the given source buffer subrange into a new Sample.
	 *
	 * Runs offline -- never call this from the real-time audio thread. The
	 * source subrange [startFrame, endFrame) is resampled from sourceRate
	 * to engineRate, then time-stretched by `ratio` (the output is `ratio`
	 * times as long as the input, with pitch preserved).
	 *
	 * @param progressCallback Optional callback invoked periodically with
	 *        (processedFrames, totalFrames) during the stretch phase.
	 * @return A sample at the engine output sample rate, or nullptr when
	 *         SoundTouch is unavailable or the inputs are degenerate.
	 */
	static std::shared_ptr<Sample> stretch(
		const std::shared_ptr<const SampleBuffer>& buffer,
		int startFrame, int endFrame,
		sample_rate_t sourceRate,
		sample_rate_t engineRate,
		double ratio,
		std::function<void(int, int)> progressCallback = nullptr);

private:
	SampleStretch() = default;
};

/**
 * @class SampleStretchResult
 * @brief Delivery point for one clip's asynchronous stretch results.
 *
 * Owned (as a child) by the object that requested the work, so it is
 * destroyed together with that object. The worker thread reaches it only
 * through a queued invocation, which Qt drops if the receiver is gone; a
 * result that arrives after its clip was destroyed is therefore discarded
 * rather than written into freed memory.
 */
class SampleStretchResult : public QObject
{
	Q_OBJECT
public:
	explicit SampleStretchResult(QObject* owner)
		: QObject(owner)
	{
	}

	~SampleStretchResult() override;

public slots:
	/// Invoked on the owner's thread with the result computed for it.
	void deliver(uint64_t generation, uint64_t key, std::shared_ptr<Sample> stretched)
	{
		emit ready(generation, key, std::move(stretched));
	}

signals:
	void ready(
		uint64_t generation,
		uint64_t key,
		std::shared_ptr<Sample> stretched);
};

/**
 * @class SampleStretchManager
 * @brief Asynchronous job manager for sample-clip time-stretch processing.
 *
 * Owns a single worker thread. Clips request jobs through request(); the
 * worker computes the stretched sample off-thread and hands the result to the
 * request's receiver on that receiver's own thread. Nothing about a request
 * ever blocks the calling thread, so the GUI stays responsive while a stretch
 * is computed and the real-time audio thread is never involved at all.
 *
 * A caller still has to verify the generation id it passed in before applying
 * a result, so that a result superseded by a newer request is never committed.
 */
class SampleStretchManager : public QObject
{
	Q_OBJECT
public:
	static SampleStretchManager& instance();

	/**
	 * @brief Request an asynchronous stretch job.
	 *
	 * Returns as soon as the job is queued. At most one job per receiver is
	 * kept waiting: requesting again before the previous job started replaces
	 * it, so dragging a clip edge -- which produces a request per mouse-move,
	 * far faster than any one of them can be computed -- costs one computation
	 * for the latest parameters instead of one per event.
	 */
	void request(
		SampleStretchResult* receiver,
		uint64_t generation,
		uint64_t key,
		std::shared_ptr<const SampleBuffer> buffer,
		int startFrame, int endFrame,
		sample_rate_t sourceRate,
		sample_rate_t engineRate,
		double ratio);

	/**
	 * @brief Block until no job is queued or running.
	 *
	 * A result travels back through a queued invocation, so this only
	 * guarantees that the computation finished -- the receiver's slot still has
	 * to be dispatched by its thread's event loop. For tests and shutdown only;
	 * editing code must never wait on it.
	 */
	void waitUntilIdle();

	/**
	 * @brief Block until every outstanding result has reached its receiver.
	 *
	 * Like @ref waitUntilIdle, but also runs the calling thread's event loop so
	 * that the queued deliveries are actually dispatched and the callers see
	 * their stretched buffers. Use this wherever work must not begin before the
	 * pitch-preserving audio exists -- exporting a project is the case that
	 * matters: the renderer resolves every clip's playback plan once, at the
	 * start of the export, and a clip whose stretch has not landed yet would be
	 * rendered through the resampling fallback, changing its pitch.
	 *
	 * Must be called from a thread with an event loop, and never from the real
	 * time audio thread or a worker thread.
	 */
	void waitForPendingResults();

	/// Number of jobs computed so far (for tests/diagnostics).
	auto jobsCompleted() const -> int;

	/**
	 * @brief Forget any work still outstanding for @a receiver.
	 *
	 * Called from ~SampleStretchResult(). Queued jobs are dropped outright; a
	 * job already being computed is marked cancelled so that the worker skips
	 * delivery instead of posting to a dead object.
	 */
	void cancelPending(SampleStretchResult* receiver);

	/// The running manager, or nullptr if none was ever created. Lets
	/// cancelPending() stay cheap and safe for a receiver whose clip never
	/// requested any work.
	static SampleStretchManager* ifExists();

	~SampleStretchManager() override;

signals:
	/**
	 * @brief Emitted when a stretch job starts processing.
	 * @param key The cache key of the job.
	 * @param totalFrames The total number of frames to process (for progress calculation).
	 */
	void stretchStarted(quint64 key, int totalFrames);

	/**
	 * @brief Emitted periodically during stretch processing with progress update.
	 * @param key The cache key of the job.
	 * @param processedFrames The number of frames processed so far.
	 * @param totalFrames The total number of frames to process.
	 */
	void stretchProgress(quint64 key, int processedFrames, int totalFrames);

	/**
	 * @brief Emitted when a stretch job completes (successfully or cancelled).
	 * @param key The cache key of the job.
	 * @param success True if the job completed successfully, false if cancelled/failed.
	 */
	void stretchFinished(quint64 key, bool success);

private:
	SampleStretchManager();
	SampleStretchManager(const SampleStretchManager&) = delete;
	SampleStretchManager& operator=(const SampleStretchManager&) = delete;

	struct Impl;
	class Worker;
	std::unique_ptr<Impl> m_impl;

	friend class Worker;
};

} // namespace lmms

Q_DECLARE_METATYPE(std::shared_ptr<lmms::Sample>)

#endif // LMMS_SAMPLE_STRETCH_H