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
	 * @return A sample at the engine output sample rate, or nullptr when
	 *         SoundTouch is unavailable or the inputs are degenerate.
	 */
	static std::shared_ptr<Sample> stretch(
		const std::shared_ptr<const SampleBuffer>& buffer,
		int startFrame, int endFrame,
		sample_rate_t sourceRate,
		sample_rate_t engineRate,
		double ratio);

private:
	SampleStretch() = default;
};

/**
 * @class SampleStretchManager
 * @brief Asynchronous job manager for sample-clip time-stretch processing.
 *
 * Owns a single worker thread. Clips request jobs through request(); the
 * worker computes the stretched sample off-thread and emits resultReady(),
 * which is delivered on the requesting clip's thread (the GUI thread) thanks
 * to Qt's queued connections. If the clip is destroyed before the result
 * arrives, the connection is torn down automatically and the result is
 * dropped. Callers must still verify the generation id before committing so
 * that stale results (superseded by a newer request) are never applied.
 */
class SampleStretchManager : public QObject
{
	Q_OBJECT
public:
	static SampleStretchManager& instance();

	/**
	 * @brief Request an asynchronous stretch job.
	 *
	 * @param owner Context object that receives resultReady() on its own thread.
	 * @param generation Caller-chosen id echoed back with the result.
	 * @param key Cache key of the requested result, echoed back with the result.
	 */
	void request(
		QObject* owner,
		uint64_t generation,
		uint64_t key,
		std::shared_ptr<const SampleBuffer> buffer,
		int startFrame, int endFrame,
		sample_rate_t sourceRate,
		sample_rate_t engineRate,
		double ratio);

	/// Number of jobs computed so far (for tests/diagnostics).
	auto jobsCompleted() const -> int;

	/// Compute one job and emit resultReady(). Internal: called by the
	/// manager's worker thread only.
	void processJob(
		QObject* owner,
		uint64_t generation,
		uint64_t key,
		const std::shared_ptr<const SampleBuffer>& buffer,
		int startFrame, int endFrame,
		sample_rate_t sourceRate,
		sample_rate_t engineRate,
		double ratio);

	~SampleStretchManager() override;

signals:
	void resultReady(
		uint64_t generation,
		uint64_t key,
		std::shared_ptr<Sample> stretched);

private:
	SampleStretchManager();
	SampleStretchManager(const SampleStretchManager&) = delete;
	SampleStretchManager& operator=(const SampleStretchManager&) = delete;

	struct Impl;
	class Worker;
	std::unique_ptr<Impl> m_impl;
};

} // namespace lmms

Q_DECLARE_METATYPE(std::shared_ptr<lmms::Sample>)

#endif // LMMS_SAMPLE_STRETCH_H