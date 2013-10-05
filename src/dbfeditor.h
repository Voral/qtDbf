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
    void openNewFile();
    void openDbfFile();
    void editRecord();
    void insertRecord();
    void deleteRecord();
    void filter(bool on);
    //void sqlCommand();
    void fillCells();
    void saveDbfFile();
    void helpDbf();
    void configApp();
    void calculator();
    void about();
    void agregat();

    //void readMemoFile(int);

signals:
    void modelIsEmpty(bool);
    void showWaitDialog();
    void hideWaitDialog();
    void fileOpened(QString);
    void modifiedChanged(bool);

protected:
    void closeEvent(QCloseEvent *event);

private:
    void setModified(bool value);
    void readDbtFile(int);
    void readFptFile(int);
    void readDbt4File(int);
    void openFile(QString &a_dbfFileName, bool fresh);

    quint32 numberOfRecords;
    quint16 headerLength;
    quint16 recordLength;
    quint16 numberOfFields;

    QByteArray sizesHeader;
    QByteArray fieldDescriptions;
    QByteArray dbfFileHeader;
    QByteArray recordData;


    QString where;
    QString order;
    QString dbfFileName;
    QString tableName;
    QString strTableName;

    QFieldsItem* fieldsItem;
    QList<QFieldsItem*> fieldsCollection;

    void readSettings();
    void writeSettings();

    QToolButton *editButton;
    QToolButton *openButton;
    QToolButton *insertButton;
    QToolButton *deleteButton;
    QToolButton *fillButton;
    QToolButton *saveButton;
    QToolButton *configButton;
    QToolButton *helpButton;
    QToolButton *calcButton;
    QToolButton *quitButton;
    QToolButton *filterButton;
    QToolButton *agregatButton;

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
    QAction *openAction;
    QAction *filterAction;
    QAction *agregatAction;

    QSize editDialogSize;

    QString recordId;
    bool modified;
};

#endif
