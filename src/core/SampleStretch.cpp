/*
 * SampleStretch.cpp
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

#include "SampleStretch.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <vector>

#include <QCoreApplication>
#include <QMetaType>
#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "AudioResampler.h"
#include "lmmsconfig.h"

#ifdef LMMS_HAVE_SOUNDTOUCH
#include <soundtouch/SoundTouch.h>
#endif

namespace lmms
{

uint64_t SampleStretch::cacheKey(
	const void* bufferIdentity,
	int startFrame, int endFrame,
	sample_rate_t sourceRate,
	sample_rate_t engineRate,
	double ratio)
{
	// FNV-1a 64-bit over the parameter byte representations.
	auto hash = uint64_t{0xcbf29ce484222325};
	const auto mix = [&hash](uint64_t value)
	{
		for (auto i = 0; i < 8; ++i)
		{
			hash ^= (value >> (i * 8)) & 0xff;
			hash *= 0x100000001b3;
		}
	};

	mix(reinterpret_cast<uintptr_t>(bufferIdentity));
	mix(static_cast<uint32_t>(startFrame));
	mix(static_cast<uint32_t>(endFrame));
	mix(static_cast<uint32_t>(sourceRate));
	mix(static_cast<uint32_t>(engineRate));

	// Mix the ratio's exact bit pattern (bit_cast keeps -0.0/NaN distinct,
	// which is fine since we never feed those in).
	double bits = 0.0;
	static_assert(sizeof(double) == 8);
	std::memcpy(&bits, &ratio, sizeof(double));
	uint64_t ratioBits = 0;
	std::memcpy(&ratioBits, &bits, sizeof(uint64_t));
	mix(ratioBits);

	return hash;
}

std::shared_ptr<Sample> SampleStretch::stretch(
	const std::shared_ptr<const SampleBuffer>& buffer,
	int startFrame, int endFrame,
	sample_rate_t sourceRate,
	sample_rate_t engineRate,
	double ratio)
{
#ifndef LMMS_HAVE_SOUNDTOUCH
	Q_UNUSED(buffer)
	Q_UNUSED(startFrame)
	Q_UNUSED(endFrame)
	Q_UNUSED(sourceRate)
	Q_UNUSED(engineRate)
	Q_UNUSED(ratio)
	return nullptr;
#else
	if (!buffer || buffer->empty() || !(ratio > 0.0) || !std::isfinite(ratio)
		|| sourceRate <= 0 || engineRate <= 0)
	{
		return nullptr;
	}

	const auto size = static_cast<int>(buffer->size());
	const auto first = std::clamp(startFrame, 0, size);
	const auto last = std::clamp(endFrame, first, size);
	const auto numFrames = last - first;
	if (numFrames < 2) { return nullptr; }

	// Step 1: resample the selected subrange from the source rate to the
	// engine output rate, so the stretched result can be played back with
	// ratio 1.0 through the existing playback path.
	const auto sourceScale = static_cast<double>(engineRate) / sourceRate;
	auto resampled = std::vector<SampleFrame>(
		static_cast<size_t>(numFrames * sourceScale) + 16);
	{
		AudioResampler resampler(AudioResampler::Mode::SincMedium);
		resampler.setRatio(sourceScale);
		const auto in = InterleavedBufferView<const float>{
			&buffer->data()[first][0], 2, static_cast<size_t>(numFrames)};
		const auto out = InterleavedBufferView<float>{
			&resampled[0][0], 2, resampled.size()};
		const auto result = resampler.process(in, out);
		resampled.resize(static_cast<size_t>(
			std::max<f_cnt_t>(result.outputFramesGenerated, 0)));
	}
	if (resampled.size() < 2) { return nullptr; }

	// Step 2: time-stretch with SoundTouch. setTempo(1/ratio) makes the
	// output `ratio` times as long while preserving pitch. Stereo channels
	// are processed together by SoundTouch itself, which keeps the two
	// channels phase-coherent.
	auto stretched = std::vector<SampleFrame>(
		static_cast<size_t>(resampled.size() * ratio) + 1024);

	soundtouch::SoundTouch st;
	st.setChannels(2);
	st.setSampleRate(static_cast<uint>(engineRate));
	st.setTempo(1.0 / ratio);
	st.setRate(1.0);
	st.setPitch(1.0);

	const float* input = &resampled[0][0];
	auto inputFramesLeft = static_cast<uint>(resampled.size());
	auto outputFilled = size_t{0};
	const auto chunk = static_cast<uint>(std::max<size_t>(resampled.size(), 1));
	auto scratch = std::vector<SampleFrame>(chunk);

	while (inputFramesLeft > 0)
	{
		const auto toPut = std::min(inputFramesLeft, chunk);
		st.putSamples(reinterpret_cast<const soundtouch::SAMPLETYPE*>(input), toPut);
		input += toPut * 2;
		inputFramesLeft -= toPut;

		uint received = 0;
		do
		{
			received = st.receiveSamples(
				reinterpret_cast<soundtouch::SAMPLETYPE*>(&scratch[0][0]), chunk);
			if (outputFilled + received > stretched.size())
			{
				stretched.resize(outputFilled + received + 1024);
			}
			std::memcpy(&stretched[outputFilled][0], &scratch[0][0],
				static_cast<size_t>(received) * sizeof(SampleFrame));
			outputFilled += received;
		} while (received > 0);
	}

	// Flush any samples still queued inside SoundTouch. Without this the
	// engine's internal latency buffers (~0.1 s per ratio step) would be
	// dropped, so the output would come out shorter than ratio * input.
	st.flush();
	for (;;)
	{
		const auto received = st.receiveSamples(
			reinterpret_cast<soundtouch::SAMPLETYPE*>(&scratch[0][0]), chunk);
		if (received == 0) { break; }
		if (outputFilled + received > stretched.size())
		{
			stretched.resize(outputFilled + received + 1024);
		}
		std::memcpy(&stretched[outputFilled][0], &scratch[0][0],
			static_cast<size_t>(received) * sizeof(SampleFrame));
		outputFilled += received;
	}

	stretched.resize(outputFilled);
	if (stretched.size() < 2) { return nullptr; }

	// The stretched buffer is brand new; the source buffer is untouched.
	return std::make_shared<Sample>(std::make_shared<SampleBuffer>(
		std::move(stretched), static_cast<int>(engineRate)));
#endif // LMMS_HAVE_SOUNDTOUCH
}

// ---------------------------------------------------------------------------
// SampleStretchManager
// ---------------------------------------------------------------------------

namespace
{

struct QueuedJob
{
	QObject* owner = nullptr;
	uint64_t generation = 0;
	uint64_t key = 0;
	std::shared_ptr<const SampleBuffer> buffer;
	int startFrame = 0;
	int endFrame = 0;
	sample_rate_t sourceRate = 0;
	sample_rate_t engineRate = 0;
	double ratio = 1.0;
};

} // namespace

struct SampleStretchManager::Impl
{
	QMutex mutex;
	QWaitCondition waitCondition;
	std::vector<QueuedJob> queue;
	bool quit = false;
	int jobsCompleted = 0;
	std::unique_ptr<SampleStretchManager::Worker> worker;
};

/// Worker thread draining the manager's job queue. Runs entirely off the GUI
/// and audio threads; results are emitted back via queued signal connections.
class SampleStretchManager::Worker : public QThread
{
public:
	Worker(SampleStretchManager* manager, Impl* impl)
		: m_manager(manager), m_impl(impl)
	{
	}

protected:
	void run() override;

private:
	SampleStretchManager* m_manager;
	Impl* m_impl;
};

void SampleStretchManager::Worker::run()
{
	for (;;) {
		auto job = QueuedJob{};
		{
			const auto locker = QMutexLocker{&m_impl->mutex};
			while (!m_impl->quit && m_impl->queue.empty())
			{
				m_impl->waitCondition.wait(&m_impl->mutex);
			}
			if (m_impl->quit) { return; }
			job = std::move(m_impl->queue.front());
			m_impl->queue.erase(m_impl->queue.begin());
		}
		m_manager->processJob(job.owner, job.generation, job.key, job.buffer,
			job.startFrame, job.endFrame, job.sourceRate, job.engineRate, job.ratio);
	}
}

SampleStretchManager::SampleStretchManager()
	: m_impl(std::make_unique<Impl>())
{
	// Both argument types must be registered so that resultReady() can be
	// delivered across threads through a queued connection. Note that
	// uint64_t is not the same C++ type as quint64 on LP64 platforms, so
	// Qt's built-in QMetaType::ULongLong does not cover it.
	qRegisterMetaType<uint64_t>("uint64_t");
	qRegisterMetaType<std::shared_ptr<Sample>>("std::shared_ptr<Sample>");
	// The manager lives on the GUI thread; the worker thread only computes.
	m_impl->worker = std::make_unique<Worker>(this, m_impl.get());
	m_impl->worker->start();
}

SampleStretchManager::~SampleStretchManager()
{
	{
		const auto locker = QMutexLocker{&m_impl->mutex};
		m_impl->quit = true;
		m_impl->queue.clear();
	}
	m_impl->waitCondition.wakeAll();
	m_impl->worker->wait();
}

SampleStretchManager& SampleStretchManager::instance()
{
	// Leaked on purpose: the worker thread must outlive static destruction
	// order issues, and the manager is needed for the whole application run.
	static auto* s_instance = new SampleStretchManager();
	return *s_instance;
}

void SampleStretchManager::request(
	QObject* owner,
	uint64_t generation,
	uint64_t key,
	std::shared_ptr<const SampleBuffer> buffer,
	int startFrame, int endFrame,
	sample_rate_t sourceRate,
	sample_rate_t engineRate,
	double ratio)
{
	auto job = QueuedJob{};
	job.owner = owner;
	job.generation = generation;
	job.key = key;
	job.buffer = std::move(buffer);
	job.startFrame = startFrame;
	job.endFrame = endFrame;
	job.sourceRate = sourceRate;
	job.engineRate = engineRate;
	job.ratio = ratio;

	{
		const auto locker = QMutexLocker{&m_impl->mutex};
		m_impl->queue.push_back(std::move(job));
	}
	m_impl->waitCondition.wakeOne();
}

auto SampleStretchManager::jobsCompleted() const -> int
{
	const auto locker = QMutexLocker{&m_impl->mutex};
	return m_impl->jobsCompleted;
}

void SampleStretchManager::processJob(
	QObject* owner,
	uint64_t generation,
	uint64_t key,
	const std::shared_ptr<const SampleBuffer>& buffer,
	int startFrame, int endFrame,
	sample_rate_t sourceRate,
	sample_rate_t engineRate,
	double ratio)
{
	auto stretched = SampleStretch::stretch(buffer, startFrame, endFrame, sourceRate, engineRate, ratio);

	{
		const auto locker = QMutexLocker{&m_impl->mutex};
		++m_impl->jobsCompleted;
	}

	// Emitted from the worker thread; delivered on the owner's thread via a
	// queued connection (the owner is used as the connection context). If the
	// owner was destroyed, nothing is delivered and the result is dropped.
	Q_UNUSED(owner)
	emit resultReady(generation, key, std::move(stretched));
}

} // namespace lmms
