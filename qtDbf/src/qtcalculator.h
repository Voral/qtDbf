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
#ifndef QTCALCULATOR_H
#define QTCALCULATOR_H

#include <QDialog>
#include "widgets.h"

class QVBoxLayout;
class QHBoxLayout;
class QGroupBox;
class QLineEdit;
class QLabel;
class QRadioButton;
class QTextEdit;

class QCalculatorFormulaEdit : public QTextEdit
{
    Q_OBJECT

public:
    QCalculatorFormulaEdit(const QString &text, QWidget *parent = 0);

signals:
     void okSignal();

private:
     void keyPressEvent(QKeyEvent *);

};

class QCalculatorDialog : public QDbfDialog
{
    Q_OBJECT

public:
    QCalculatorDialog(const QString &title, QWidget *parent = 0);
    ~QCalculatorDialog();

public slots:
    void refreshResult();

public:
    void setFormula(const QString &formula);
    QString getFormula();
    QString getValue();

private slots:
    void insertNum1();
    void insertNum2();
    void insertNum3();
    void insertNum4();
    void insertNum5();
    void insertNum6();
    void insertNum7();
    void insertNum8();
    void insertNum9();
    void insertNum0();
    void qtCalcDivide();
    void qtCalcTimes();
    void qtCalcPlus();
    void qtCalcMinus();
    void qtCalcComma();
    void qtCalcBraceOpen();
    void qtCalcBraceClose();
    void qtCalcPercent();

private:
    QGroupBox *editareGroupBox;
    QGroupBox *optionsGroupBox;

    QLabel *formulaLabel;
    QTextEdit *formulaEdit;
    QLabel *resultLabel;
    QDbfLineEdit *resultEdit;

    QCheckBox *thousandCheckBox;
    QLabel *decimalLabel;
    QSpinBox *decimalSpinBox;

    double termen();
    double factor();
    double eval();
    bool thousandSeparator;
    int numberOfDecimals;

    double d;
    int p;
    QString formula;
};

class QCalculatorToolButton : public QToolButton
{
    Q_OBJECT

public:
    QCalculatorToolButton(QWidget *parent = 0);
    ~QCalculatorToolButton();

    QSize sizeHint() const;

public slots:
    void setIconSize1(int);
};

#endif
