/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "exportdialog.h"
#include <QApplication>
#include <QLineEdit>
#include <QSpinBox>
#include <QImageWriter>
#include <QDir>
#include <QFileInfo>

//enum { exportMinimumSize = 1, exportMaximumSize = 2000 };

ExportDialog::ExportDialog(QWidget *parent)
    : QDialog(parent)
    , m_fileNameLineEdit(new QLineEdit(this))
    , m_widthSpinBox(new QSpinBox(this))
    , m_heightSpinBox(new QSpinBox(this))
{
//    m_widthSpinBox->setMinimum(exportMinimumSize);
//    m_widthSpinBox->setMaximum(exportMaximumSize);
//    m_heightSpinBox->setMinimum(exportMinimumSize);
//    m_heightSpinBox->setMaximum(exportMaximumSize);
}


QSize ExportDialog::exportSize() const
{
    QSize c=QSize(m_widthSpinBox->value(), m_heightSpinBox->value());
    return QSize(m_widthSpinBox->value(), m_heightSpinBox->value());
}

void ExportDialog::setExportSize(const QSize &size)
{
//    m_defaultSize = size;
    m_widthSpinBox->setValue(497);
    m_heightSpinBox->setValue(279);
//    setExportHeightBlocked(279);
}


//void ExportDialog::setExportWidthBlocked(int width)
//{
//    int a=width;
//        m_widthSpinBox->setValue(width);
//}

//void ExportDialog::setExportHeightBlocked(int height)
//{
//        int a=height;
//        m_heightSpinBox->setValue(height);
//}

QString ExportDialog::exportFileName() const
{
    QString str=QDir::cleanPath(m_fileNameLineEdit->text().trimmed());
    eturn QDir::cleanPath(m_fileNameLineEdit->text().trimmed());
}

void ExportDialog::setExportFileName(const QString &f)
{
    QString str=QDir::toNativeSeparators(f);
    m_fileNameLineEdit->setText(QDir::toNativeSeparators(f));
}
