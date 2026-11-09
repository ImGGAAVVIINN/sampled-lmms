/*
 * StretchProgressDialog.cpp
 *
 * Copyright (c) 2025 LMMS Team
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

#include "StretchProgressDialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

namespace lmms::gui {

StretchProgressDialog::StretchProgressDialog(QWidget* parent)
	: QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
	, m_label(new QLabel(tr("Stretching audio...")))
	, m_progressBar(new QProgressBar())
	, m_cancelButton(new QPushButton(tr("Cancel")))
	, m_uiUpdateTimer(new QTimer(this))
{
	setWindowTitle(tr("Stretching Audio"));
	setModal(true);
	setMinimumWidth(400);

	auto* layout = new QVBoxLayout(this);
	layout->addWidget(m_label);
	layout->addWidget(m_progressBar);
	layout->addWidget(m_cancelButton);

	m_progressBar->setRange(0, 100);
	m_progressBar->setValue(0);
	m_progressBar->setTextVisible(true);
	m_progressBar->setFormat(tr("%p%"));

	m_cancelButton->setDefault(true);
	connect(m_cancelButton, &QPushButton::clicked, this, &StretchProgressDialog::onCancelClicked);

	// Timer to process events and keep UI responsive
	m_uiUpdateTimer->setInterval(50);
	connect(m_uiUpdateTimer, &QTimer::timeout, this, [this]() {
		QApplication::processEvents(QEventLoop::AllEvents, 10);
	});
}

void StretchProgressDialog::startStretch(uint64_t key, int totalFrames)
{
	m_currentKey = key;
	m_totalFrames = totalFrames;
	m_progressBar->setValue(0);
	m_progressBar->setFormat(tr("%p%"));
	m_label->setText(tr("Stretching audio..."));
	m_cancelButton->setEnabled(true);
	m_uiUpdateTimer->start();
	show();
	raise();
	activateWindow();
}

void StretchProgressDialog::updateProgress(uint64_t key, int processedFrames, int totalFrames)
{
	if (key != m_currentKey) { return; }

	if (totalFrames > 0)
	{
		const int percent = std::min(100, static_cast<int>((static_cast<double>(processedFrames) / totalFrames) * 100));
		m_progressBar->setValue(percent);
		m_progressBar->setFormat(tr("%p% (%1 of %2 frames)").arg(processedFrames).arg(totalFrames));
	}
	else
	{
		// Indeterminate progress
		m_progressBar->setRange(0, 0);
		m_progressBar->setFormat(tr("Processing..."));
	}

	// Process events to keep UI responsive
	QApplication::processEvents(QEventLoop::AllEvents, 10);
}

void StretchProgressDialog::finishStretch(uint64_t key, bool success)
{
	if (key != m_currentKey) { return; }

	m_uiUpdateTimer->stop();
	m_progressBar->setRange(0, 100);
	m_progressBar->setValue(100);
	m_progressBar->setFormat(tr("Complete"));

	if (success)
	{
		m_label->setText(tr("Stretching complete"));
	}
	else
	{
		m_label->setText(tr("Stretching cancelled"));
	}

	m_cancelButton->setText(tr("Close"));
	m_cancelButton->setEnabled(true);
	disconnect(m_cancelButton, &QPushButton::clicked, this, &StretchProgressDialog::onCancelClicked);
	connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::accept);
}

void StretchProgressDialog::onCancelClicked()
{
	if (m_currentKey != 0)
	{
		emit cancelled(m_currentKey);
		m_cancelButton->setEnabled(false);
		m_label->setText(tr("Cancelling..."));
	}
}

} // namespace lmms::gui