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
