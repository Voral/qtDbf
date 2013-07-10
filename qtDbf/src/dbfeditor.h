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

#ifndef DBFEDITOR_H
#define DBFEDITOR_H

#include <QDialog>
#include <QSqlQueryModel>
#include "customsqlmodel.h"
#include "structures.h"

class QSplitter;
class QToolButton;
class QSqlTableModel;
class QTableView;
class QAction;
class QModelIndex;

class QDbfEditor : public QWidget
{
    Q_OBJECT

public:
    QDbfEditor(QString &a_dbfFileName, const QString &title, QWidget *parent = 0);
    ~QDbfEditor();

public slots:
    void refresh(int);
    void sortDbf(const QModelIndex&);
    void setToolButtonIconSize(int);

private slots:
    void openDbfFile();
    void editRecord();
    void insertRecord();
    void deleteRecord();
    //void sqlCommand();
    void fillCells();
    void saveDbfFile();
    void helpDbf();
    void configApp();
    void calculator();
    void about();

    //void readMemoFile(int);

signals:
    void modelIsEmpty(bool);
    void showWaitDialog();
    void hideWaitDialog();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void readDbtFile(int);
    void readFptFile(int);
    void readDbt4File(int);

    quint32 numberOfRecords;
    quint16 headerLength;
    quint16 recordLength;
    quint16 numberOfFields;

    QByteArray sizesHeader;
    QByteArray fieldDescriptions;
    QByteArray dbfFileHeader;
    QByteArray recordData;

    QString dbfFileName;
    QString tableName;
    QString strTableName;

    QFieldsItem* fieldsItem;
    QList<QFieldsItem*> fieldsCollection;

    void readSettings();
    void writeSettings();

    QToolButton *editButton;
    QToolButton *insertButton;
    QToolButton *deleteButton;
    QToolButton *fillButton;
    QToolButton *saveButton;
    QToolButton *configButton;
    QToolButton *helpButton;
    QToolButton *calcButton;
    QToolButton *quitButton;

    QDbfSqlModel *model;
    QTableView *view;

    QAction *editAction;
    QAction *insertAction;
    QAction *deleteAction;
    QAction *saveAction;
    QAction *fillAction;
    QAction *configAction;
    QAction *helpAction;
    QAction *calcAction;
    QAction *quitAction;

    QSize editDialogSize;

    QString recordId;
    bool modified;
};

#endif
