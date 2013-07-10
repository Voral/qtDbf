/****************************************************************************
**
** Copyright (C) 2009 Hevele Hegyi Istvan.
**
** This file is part of the qtDbf project.
**
** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.0, included in the file LGPL_EXCEPTION.txt in this
** package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at http://www.qtsoftware.com/contact.
** $QT_END_LICENSE$
**
****************************************************************************/
#include <QtGui>
#include <QtSvg>
#include <QtSql>

#include "mainwindow.h"
#include "dbfeditor.h"
#include "globals.h"

extern QString generalTextCodec = "";
extern MainWindow *mainWindow;

MainWindow::MainWindow(QString dbfFileName)
{
    QSettings settings;
    resize(settings.value("mainwindow/size",QSize(880,650)).toSize());

    charFieldColorString = settings.value("charFieldColor","000000").toString();
    currencyFieldColorString = settings.value("currencyFieldColor","007600").toString();
    numericFieldColorString = settings.value("numericFieldColor","007600").toString();
    dateFieldColorString = settings.value("dateFieldColor","AA0000").toString();
    timeFieldColorString = settings.value("timeFieldColor","AA0000").toString();
    doubleFieldColorString = settings.value("doubleFieldColor","007600").toString();
    intFieldColorString = settings.value("intFieldColor","007600").toString();
    logicalFieldColorString = settings.value("logicalFieldColor","550000").toString();
    memoFieldColorString = settings.value("memoFieldColor","009696").toString();
    memo4FieldColorString = settings.value("memo4FieldColor","009696").toString();
    generalFieldColorString = settings.value("generalFieldColor","000000").toString();
	generalTextCodec =  settings.value("generalTextCodec","Windows-1251").toString();

    mainWindow = this;

    QString windowTitle = "DBF Viewer - ";

    dbfEditor = new QDbfEditor(dbfFileName, "", this);
    setCentralWidget(dbfEditor);

    windowTitle.append(dbfFileName);

    setWindowIcon(QIcon(":images/qtdbf.svg"));
    setWindowTitle(windowTitle);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("mainwindow/size", size());
    settings.setValue("charFieldColor",charFieldColorString);
    settings.setValue("currencyFieldColor",currencyFieldColorString);
    settings.setValue("numericFieldColor",numericFieldColorString);
    settings.setValue("dateFieldColor",dateFieldColorString);
    settings.setValue("timeFieldColor",timeFieldColorString);
    settings.setValue("doubleFieldColor",doubleFieldColorString);
    settings.setValue("intFieldColor",intFieldColorString);
    settings.setValue("logicalFieldColor",logicalFieldColorString);
    settings.setValue("memoFieldColor",memoFieldColorString);
    settings.setValue("memo4FieldColor",memo4FieldColorString);
    settings.setValue("generalFieldColor",generalFieldColorString);
	settings.setValue("generalTextCodec",generalTextCodec);
	dbfEditor->close();
}
