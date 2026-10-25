/*
 * AudioPortAudio.h - device-class that performs PCM-output via PortAudio
 *
 * Copyright (c) 2008 Csaba Hruska <csaba.hruska/at/gmail.com>
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

#ifndef LMMS_AUDIO_PORTAUDIO_H
#define LMMS_AUDIO_PORTAUDIO_H

#include "lmmsconfig.h"

#ifdef LMMS_HAVE_PORTAUDIO

#include <QComboBox>
#include <QFormLayout>
#include <QString>
#include <QWidget>
#include <portaudio.h>

#include <vector>

#include "AudioDevice.h"
#include "AudioDeviceSetupWidget.h"
#include "SampleFrame.h"

namespace lmms {

namespace detail {
class PortAudioInitializationGuard
{
public:
	PortAudioInitializationGuard()
		: m_error(Pa_Initialize())
	{
		if (m_error != paNoError) { throw std::runtime_error{"PortAudio: could not initialize"}; }
	}

	~PortAudioInitializationGuard()
	{
		if (m_error == paNoError) { Pa_Terminate(); }
	}

	PortAudioInitializationGuard(const PortAudioInitializationGuard&) = delete;
	PortAudioInitializationGuard(PortAudioInitializationGuard&&) = delete;
	PortAudioInitializationGuard& operator=(const PortAudioInitializationGuard&) = delete;
	PortAudioInitializationGuard& operator=(PortAudioInitializationGuard&&) = delete;

private:
	PaError m_error = paNoError;
};
} // namespace detail

class AudioPortAudio : public AudioDevice
{
public:
	AudioPortAudio(bool& successful, AudioEngine* engine);
	~AudioPortAudio() override;

	AudioPortAudio(const AudioPortAudio&) = delete;
	AudioPortAudio(AudioPortAudio&&) = delete;
	AudioPortAudio& operator=(const AudioPortAudio&) = delete;
	AudioPortAudio& operator=(AudioPortAudio&&) = delete;

	static auto name() -> QString { return QT_TRANSLATE_NOOP("AudioDeviceSetupWidget", "PortAudio"); }

private:
	void startProcessingImpl() override;
	void stopProcessingImpl() override;

	static int processCallback(const void* input, void* output, unsigned long frameCount,
		const PaStreamCallbackTimeInfo* timeInfo, PaStreamCallbackFlags statusFlags, void* userData);

	//! Convert interleaved PortAudio input to the engine's sample format and hand it over.
	//! Must not allocate, as it runs on the real-time audio thread.
	void pushInputFrames(const float* input, unsigned long frameCount);

	detail::PortAudioInitializationGuard m_initGuard;
	PaStream* m_paStream = nullptr;

	// Channel count of the opened input device, or 0 when there is no usable input.
	ch_cnt_t m_inputChannels = 0;
	// Staging buffer for the interleaved input, sized for the largest callback we can get.
	std::vector<SampleFrame> m_inputFrameBuffer;
};
} // namespace lmms

namespace lmms::gui {
class AudioPortAudioSetupWidget : public AudioDeviceSetupWidget
{
public:
	AudioPortAudioSetupWidget(QWidget* parent);

	void show() override;
	void saveSettings() override;

private:
	class DeviceSelectorWidget;
	QComboBox* m_backendComboBox = nullptr;
	DeviceSelectorWidget* m_inputDevice = nullptr;
	DeviceSelectorWidget* m_outputDevice = nullptr;
};
} // namespace lmms::gui

#endif // LMMS_HAVE_PORTAUDIO

#endif // LMMS_AUDIO_PORTAUDIO_H
