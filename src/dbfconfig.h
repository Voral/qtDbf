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

#ifndef DBFCONFIG_H
#define DBFCONFIG_H

#include <QDialog>
#include <QSqlQueryModel>

class QDialogButtonBox;
class QFileInfo;
class QTabWidget;

#include "widgets.h"
#include "structures.h"

class QDetaliiBaseTab : public QWidget
{
    Q_OBJECT

public:
    QDetaliiBaseTab(QWidget *parent = 0);

    virtual void createInterface();
    virtual void saveEditedData();

};

class QConfigAppTab : public QDetaliiBaseTab
{
    Q_OBJECT

public:
    QConfigAppTab(QWidget *parent = 0);

    virtual void createInterface();
    virtual void saveEditedData();

private:
    QComboBox *languages;
    QComboBox *codecs;

    QPushButton *restoreDefaultButton;
};

class QIconSizeTab : public QDetaliiBaseTab
{
    Q_OBJECT

public:
    QIconSizeTab(QWidget *parent = 0);

    virtual void createInterface();
    virtual void saveEditedData();

public slots:
    void backToDefault();

private:
    QSpinBox *toolBarSpinBox;
    QSlider *toolBarSlider;
    QSpinBox *toolButtonSpinBox;
    QSlider *toolButtonSlider;

};

class QDbfStructureTab : public QDetaliiBaseTab
{
    Q_OBJECT

public:
    QDbfStructureTab(QString &tableName, QWidget *parent = 0);

    virtual void createInterface();

private:
    QSqlQueryModel *model;
    QTableView *view;

    QString strTableName;
};

class QDbfFieldColorsTab : public QDetaliiBaseTab
{
    Q_OBJECT

public:
    QDbfFieldColorsTab(QWidget *parent = 0);
    virtual void createInterface();

public slots:
    void charFieldColor();
    void currencyFieldColor();
    void numericFieldColor();
    void dateFieldColor();
    void timeFieldColor();
    void doubleFieldColor();
    void intFieldColor();
    void logicalFieldColor();
    void memoFieldColor();
    void memo4FieldColor();
    void generalFieldColor();

private:
    QLabel *charFieldColorLabel;
    QLabel *currencyFieldColorLabel;
    QLabel *numericFieldColorLabel;
    QLabel *dateFieldColorLabel;
    QLabel *timeFieldColorLabel;
    QLabel *doubleFieldColorLabel;
    QLabel *intFieldColorLabel;
    QLabel *logicalFieldColorLabel;
    QLabel *memoFieldColorLabel;
    QLabel *memo4FieldColorLabel;
    QLabel *generalFieldColorLabel;
};

class QDetaliiTabWidget: public QTabWidget
{
    Q_OBJECT

public:
    QDetaliiTabWidget(QWidget *parent = 0);

};

class QDetaliiTabDialog : public QDialog
{
    Q_OBJECT

public:
    QDetaliiTabDialog(QString &tableName, QWidget *parent = 0);
    ~QDetaliiTabDialog();

public slots:
    void changePicture(int i);

private slots:
    void saveConfiguration();
    void loadConfiguration();

private:
    QTabWidget *tabWidget;
    //QSvgWidget *picture;
    QLabel *picture;

    QList<QDetaliiBaseTab *> detaliiTabList;
    QStringList pictures;

    int currentTab;
};

#endif
