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

#ifndef WIDGETS_H
#define WIDGETS_H

#include <QtGui>

class QTableView;
class QLineEdit;
class QAction;
class QDialog;
class QToolButton;

class QDbfLineEdit : public QLineEdit
{
    Q_OBJECT

public:
     QDbfLineEdit(const QString &contents, QWidget *parent = 0);
     ~QDbfLineEdit();

     virtual int valid();
     virtual void searchItem();

public slots:
     void search();

protected:
     void focusOutEvent(QFocusEvent *event);
     void keyPressEvent(QKeyEvent *);
     virtual void mouseDoubleClickEvent(QMouseEvent *);
};

class QNoEmptyLineEdit : public QDbfLineEdit
{
    Q_OBJECT

public:
     QNoEmptyLineEdit(bool show_message, const QString &contents, QWidget *parent = 0);
     ~QNoEmptyLineEdit();

     virtual int valid();
     virtual void searchItem();

private:
     bool showMessage;

};

class QDoubleLineEdit : public QDbfLineEdit
{
    Q_OBJECT

public:
     QDoubleLineEdit(const QString &contents, QWidget *parent = 0);
     ~QDoubleLineEdit();

     virtual int valid();
     virtual void searchItem();

};

class QNoZeroDoubleLineEdit : public QDbfLineEdit
{
    Q_OBJECT

public:
     QNoZeroDoubleLineEdit(const QString &contents, QWidget *parent = 0);
     ~QNoZeroDoubleLineEdit();

     virtual int valid();
     virtual void searchItem();

};

class QDateLineEdit : public QDbfLineEdit
{
    Q_OBJECT

public:
     QDateLineEdit(bool v, const QString &contents, QWidget *parent = 0);
     ~QDateLineEdit();

     virtual int valid();
     virtual void searchItem();

 private:
     bool verify;

};

class QDateTimeLineEdit : public QDbfLineEdit
{
    Q_OBJECT

public:
     QDateTimeLineEdit(bool v, const QString &contents, QWidget *parent = 0);
     ~QDateTimeLineEdit();

     virtual int valid();
     virtual void searchItem();

 private:
     bool verify;

};

class QDbfToolButton : public QToolButton
{
    Q_OBJECT

public:
    QDbfToolButton(QWidget *parent = 0);
    ~QDbfToolButton();

    QSize sizeHint() const;

public slots:
    void setIconSize1(int);
};

class QDbfTableView : public QTableView
{
    Q_OBJECT

signals:
    void editSignal();
    void insertSignal();
    void deleteSignal();
    void searchSignal();
    void quitSignal();

public:
    QDbfTableView(QWidget *parent = 0);

private:
    void keyPressEvent(QKeyEvent *);

};

class QDbfPushButton : public QPushButton
{
    Q_OBJECT

public:
    QDbfPushButton(const QIcon &, const QString & , QWidget *parent = 0);

    QSize sizeHint() const;
};

class QDbfDialog : public QDialog
{
    Q_OBJECT

public:
    QDbfDialog(const QString &title, QWidget *parent = 0);
    ~QDbfDialog();

signals:
    void endVerifyDbfInputLines();

public slots:
    void verifyDbfInputLines();

public:
    QList<QDbfLineEdit*> lineEditsToVerify;
    void insertLineEditToVerify(QDbfLineEdit*);

};

class QFieldColorLabel : public QLabel
{
    Q_OBJECT

public:
    QFieldColorLabel(QWidget *parent = 0);

signals:
    void changeColor();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *);

};

#endif
