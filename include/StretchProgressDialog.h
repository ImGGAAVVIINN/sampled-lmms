/*
 * StretchProgressDialog.h
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

#ifndef LMMS_STRETCH_PROGRESS_DIALOG_H
#define LMMS_STRETCH_PROGRESS_DIALOG_H

#include <QDialog>
#include <QProgressBar>
#include <QLabel>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>

namespace lmms::gui {

/**
 * @class StretchProgressDialog
 * @brief A modal dialog showing the progress of a sample stretch operation.
 *
 * Displays a progress bar with "Stretching audio..." text. The dialog is
 * modal to prevent user interaction with the main window during stretching,
 * but uses a timer to keep the UI responsive.
 */
class StretchProgressDialog : public QDialog
{
	Q_OBJECT
public:
	explicit StretchProgressDialog(QWidget* parent = nullptr);
	~StretchProgressDialog() override = default;

	/// Show the dialog for a new stretch operation
	void startStretch(uint64_t key, int totalFrames);

	/// Update progress
	void updateProgress(uint64_t key, int processedFrames, int totalFrames);

	/// Finish the stretch operation
	void finishStretch(uint64_t key, bool success);

signals:
	/// Emitted when the stretch operation is cancelled by the user
	void cancelled(uint64_t key);

private slots:
	void onCancelClicked();

private:
	QLabel* m_label;
	QProgressBar* m_progressBar;
	QPushButton* m_cancelButton;
	uint64_t m_currentKey = 0;
	int m_totalFrames = 0;
	QTimer* m_uiUpdateTimer;
};

} // namespace lmms::gui

#endif // LMMS_STRETCH_PROGRESS_DIALOG_H