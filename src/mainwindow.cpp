#/********************************************************************************/
#/*                                                                              */
#/*    Copyright 2011 Alexander Vorobyev (Voral)                                 */
#/*    http://va-soft.ru/                                                        */
#/*                                                                              */
#/*    Copyright (C) 2009 Hevele Hegyi Istvan.                                   */
#/*                                                                              */
#/*    This file is part of qtDbf.                                               */
#/*                                                                              */
#/*    Basetest is free software: you can redistribute it and/or modify          */
#/*    it under the terms of the GNU General Public License as published by      */
#/*    the Free Software Foundation, either version 3 of the License, or         */
#/*    (at your option) any later version.                                       */
#/*                                                                              */
#/*    Basetest is distributed in the hope that it will be useful,               */
#/*    but WITHOUT ANY WARRANTY; without even the implied warranty of            */
#/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
#/*    GNU General Public License for more details.                              */
#/*                                                                              */
#/*    You should have received a copy of the GNU General Public License         */
#/*    along with protime.  If not, see <http://www.gnu.org/licenses/>.          */
#/*                                                                              */
#/********************************************************************************/
#include <QtGui>
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

    dbfEditor = new QDbfEditor(dbfFileName, "", this);
    setCentralWidget(dbfEditor);
    setWindowIcon(QIcon(":/qtdbf.png"));
    setTitle(dbfFileName);

    connect(dbfEditor,SIGNAL(fileOpened(QString)),this,SLOT(setTitle(QString)));
    connect(dbfEditor,SIGNAL(modifiedChanged(bool)),this,SLOT(setModified(bool)));

}
void MainWindow::setModified(bool value)
{
    setWindowModified(value);
}

void MainWindow::setTitle(QString title)
{
    QString windowTitle = "DBF Viewer - [*] ";
    windowTitle.append(title);
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
