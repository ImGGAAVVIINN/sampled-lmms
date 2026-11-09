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
#include "StretchDebug.h"

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
	/// Owning object's delivery point, or null once it has gone away. Only
	/// ever read or written with the manager's mutex held, which is also what
	/// ~SampleStretchResult() takes to cancel, so a receiver is never used
	/// after it was destroyed.
	lmms::SampleStretchResult* receiver = nullptr;
	uint64_t generation = 0;
	uint64_t key = 0;
	std::shared_ptr<const lmms::SampleBuffer> buffer;
	int startFrame = 0;
	int endFrame = 0;
	lmms::sample_rate_t sourceRate = 0;
	lmms::sample_rate_t engineRate = 0;
	double ratio = 1.0;
};

/// The one and only manager, or null before it is first needed. Kept as a
/// plain pointer so that a receiver destroyed without ever having requested
/// work does not start the worker thread just to cancel nothing.
SampleStretchManager* s_manager = nullptr;

} // namespace

struct SampleStretchManager::Impl
{
	QMutex mutex;
	QWaitCondition waitCondition;
	/// Jobs waiting to be computed, oldest first. At most one per receiver.
	std::vector<QueuedJob> queue;
	/// The job the worker is inside SampleStretch::stretch() with, while there
	/// is one; `cancelled` is set if its receiver went away in the meantime.
	QueuedJob active;
	bool computing = false;
	bool quit = false;
	int jobsCompleted = 0;
	std::unique_ptr<SampleStretchManager::Worker> worker;
};

/// Worker thread draining the manager's job queue. Runs entirely off the GUI
/// and audio threads; results are handed back through a queued invocation on
/// the requesting object's own thread.
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
			m_impl->active = job;
			m_impl->computing = true;
		}

		// Log job start
		if (job.receiver)
		{
			QObject* parent = job.receiver->parent();
			if (parent)
			{
				const auto clipId = makeClipId(parent);
				StretchDebug::instance().logStretchJobStarted(clipId, job.generation, job.key);
			}
		}

		// The expensive part, with no lock held: neither the GUI thread nor
		// the audio thread is involved here.
		auto stretched = SampleStretch::stretch(job.buffer, job.startFrame,
			job.endFrame, job.sourceRate, job.engineRate, job.ratio);

		const auto locker = QMutexLocker{&m_impl->mutex};
		m_impl->computing = false;
		++m_impl->jobsCompleted;
		// Null if ~SampleStretchResult() ran while this was being computed.
		auto* receiver = m_impl->active.receiver;
		m_impl->active = QueuedJob{};
		if (receiver != nullptr)
		{
			// Log job completion
			QObject* parent = receiver->parent();
			if (parent)
			{
				const auto clipId = makeClipId(parent);
				int outputFrames = stretched ? static_cast<int>(stretched->sampleSize()) : 0;
				StretchDebug::instance().logStretchJobCompleted(clipId, job.generation, job.key, outputFrames);
			}

			// Queued, and posted with the manager's mutex held so that
			// ~SampleStretchResult() cannot run between the check above and this
			// call. The slot runs on the receiver's thread; if the receiver is
			// destroyed before then, Qt discards the pending event.
			//
			// Posting happens *before* the idle broadcast below on purpose: a
			// thread waiting in waitUntilIdle() is told the manager is done, and
			// by then the result is guaranteed to be sitting in the receiver's
			// event queue rather than still in flight. waitForPendingResults()
			// relies on that ordering to know that an idle manager has nothing
			// left to deliver.
			QMetaObject::invokeMethod(receiver, "deliver", Qt::QueuedConnection,
				Q_ARG(uint64_t, job.generation),
				Q_ARG(uint64_t, job.key),
				Q_ARG(std::shared_ptr<Sample>, stretched));
		}
		else
		{
			// Job was discarded because receiver was destroyed
			if (job.receiver)
			{
				QObject* parent = job.receiver->parent();
				if (parent)
				{
					const auto clipId = makeClipId(parent);
					StretchDebug::instance().logStretchJobDiscarded(clipId, job.generation, job.key, "receiver destroyed");
				}
			}
		}
		m_impl->waitCondition.wakeAll();
	}
}

SampleStretchManager::SampleStretchManager()
	: m_impl(std::make_unique<Impl>())
{
	// Both argument types must be registered so that a result can be delivered
	// across threads through a queued invocation. Note that uint64_t is not
	// the same C++ type as quint64 on LP64 platforms, so Qt's built-in
	// QMetaType::ULongLong does not cover it.
	qRegisterMetaType<uint64_t>("uint64_t");
	qRegisterMetaType<std::shared_ptr<Sample>>("std::shared_ptr<Sample>");
	// The manager lives on the GUI thread; the worker thread only computes.
	// Published before the worker starts so that a receiver destroyed at any
	// point after this finds a manager to cancel with.
	s_manager = this;
	m_impl->worker = std::make_unique<Worker>(this, m_impl.get());
	m_impl->worker->start();
}

SampleStretchManager::~SampleStretchManager()
{
	s_manager = nullptr;
	{
		const auto locker = QMutexLocker{&m_impl->mutex};
		m_impl->quit = true;
		m_impl->queue.clear();
		m_impl->waitCondition.wakeAll();
	}
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
	SampleStretchResult* receiver,
	uint64_t generation,
	uint64_t key,
	std::shared_ptr<const SampleBuffer> buffer,
	int startFrame, int endFrame,
	sample_rate_t sourceRate,
	sample_rate_t engineRate,
	double ratio)
{
	auto job = QueuedJob{};
	job.receiver = receiver;	job.generation = generation;
	job.key = key;
	job.buffer = std::move(buffer);
	job.startFrame = startFrame;
	job.endFrame = endFrame;
	job.sourceRate = sourceRate;
	job.engineRate = engineRate;
	job.ratio = ratio;

	// Log the request (we need a clip ID - use the receiver's parent which is the clip)
	QObject* parent = receiver->parent();
	if (parent)
	{
		const auto clipId = makeClipId(parent);
		StretchDebug::instance().logStretchRequestQueued(
			clipId, generation, key, startFrame, endFrame,
			sourceRate, engineRate, ratio);
	}

	{
		const auto locker = QMutexLocker{&m_impl->mutex};
		// One pending job per receiver, always the newest: a request supersedes
		// whatever the same receiver asked for but has not started yet.
		std::erase_if(m_impl->queue,
			[&](const QueuedJob& queued) { return queued.receiver == receiver; });
		m_impl->queue.push_back(std::move(job));
	}
	// The worker and any waitUntilIdle() caller block on the same condition,
	// so wake everything: a wakeOne() could otherwise be consumed by an
	// idle-waiter and leave the new job sitting in the queue.
	m_impl->waitCondition.wakeAll();
}

void SampleStretchManager::waitUntilIdle()
{
	// Qt 5's wait(QMutex*, predicate) is not available, so loop: the worker
	// wakes on every state change and the destructor wakes on shutdown.
	{
		const auto locker = QMutexLocker{&m_impl->mutex};
		while (!m_impl->queue.empty() || m_impl->computing)
		{
			m_impl->waitCondition.wait(&m_impl->mutex);
		}
	}
}

void SampleStretchManager::waitForPendingResults()
{
	// The worker posts each result to this thread's event queue before it
	// announces that it went idle, so once the queue is empty every result
	// this thread is owed is either already applied or already queued here.
	// Draining the event loop dispatches those deliveries; a delivery can in
	// principle make a clip ask for more work, so re-check afterwards and only
	// stop when a whole pass leaves the manager idle with nothing new computed.
	// The pass limit keeps an unrelated event storm (the export progress timer
	// fires every 200 ms, so `processEvents` alone can never look idle) from
	// turning this into an endless loop.
	for (auto pass = 0; pass < 8; ++pass)
	{
		waitUntilIdle();
		const auto completed = jobsCompleted();
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
		waitUntilIdle();
		if (jobsCompleted() == completed) { return; }
	}
}

auto SampleStretchManager::jobsCompleted() const -> int
{
	const auto locker = QMutexLocker{&m_impl->mutex};
	return m_impl->jobsCompleted;
}

void SampleStretchManager::cancelPending(SampleStretchResult* receiver)
{
	auto* manager = ifExists();
	if (manager == nullptr) { return; }
	const auto locker = QMutexLocker{&manager->m_impl->mutex};
	std::erase_if(manager->m_impl->queue,
		[&](const QueuedJob& queued) { return queued.receiver == receiver; });
	if (manager->m_impl->computing && manager->m_impl->active.receiver == receiver)
	{
		// Computation is already under way; the worker will drop the result.
		manager->m_impl->active.receiver = nullptr;
	}
}

SampleStretchManager* SampleStretchManager::ifExists() { return s_manager; }

SampleStretchResult::~SampleStretchResult()
{
	// Stop the worker from delivering into this object as it disappears. Either
	// this runs first, in which case the worker finds the receiver nulled out
	// and posts nothing, or the worker wins the mutex and its queued invocation
	// is already posted -- which is still safe, because ~QObject() discards
	// events posted to an object that is going away.
	if (auto* manager = SampleStretchManager::ifExists())
	{
		manager->cancelPending(this);
	}
}

} // namespace lmms
