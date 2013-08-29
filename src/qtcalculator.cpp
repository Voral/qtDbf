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

#include "qtcalculator.h"

//QCalculatorFormulaEdit

QCalculatorFormulaEdit::QCalculatorFormulaEdit(const QString &text, QWidget *parent)
     : QTextEdit(text, parent)
{
}

void QCalculatorFormulaEdit::keyPressEvent(QKeyEvent *event)
{
     switch (event->key())
            {
             case Qt::Key_Enter:
             case Qt::Key_Return:
                  if (event->modifiers() & Qt::ControlModifier)
                     {
            emit okSignal();
                     }
                  else
             {
                        QTextEdit::keyPressEvent(event);
                     }
                  break;
             default:
                  QTextEdit::keyPressEvent(event);
        }
}

// QCalculatorDialog

QCalculatorDialog::QCalculatorDialog(const QString &title, QWidget *parent)
      : QDbfDialog(title, parent)
{
    QSettings settings;
    QSize size = settings.value("qtcalculator/Size", QSize(684, 360)).toSize();
    formula = settings.value("qtcalculator/formula", "").toString();
    numberOfDecimals = settings.value("qtcalculator/numberofdecimals",2).toInt();
    thousandSeparator = settings.value("qtcalculator/thousandseparator",true).toBool();

    resize(size);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QVBoxLayout *svgLayout = new QVBoxLayout;

    editareGroupBox = new QGroupBox(this);

    QGridLayout *editareLayout = new QGridLayout(editareGroupBox);

    formulaLabel = new QLabel(editareGroupBox);
    formulaEdit = new QCalculatorFormulaEdit(formula, editareGroupBox);
    formulaLabel->setBuddy(formulaEdit);
    formulaLabel->setAlignment(Qt::AlignTop);

    QFont font = formulaEdit->font();
    font.setPointSize(font.pointSize() + 5);
    formulaEdit->setFont(font);

    resultLabel = new QLabel(editareGroupBox);
    resultEdit = new QDbfLineEdit("",editareGroupBox);
    insertLineEditToVerify(resultEdit);
    resultLabel->setBuddy(resultEdit);

    editareLayout->addWidget(formulaLabel,0,0);
    editareLayout->addWidget(formulaEdit,0,1);

    editareLayout->addWidget(resultLabel,1,0);
    editareLayout->addWidget(resultEdit,1,1);

    verticalLayout->addWidget(editareGroupBox);

    optionsGroupBox = new QGroupBox(this);

    QHBoxLayout *optionsLayout = new QHBoxLayout(optionsGroupBox);

    thousandCheckBox = new QCheckBox(tr("Thousands separator"), optionsGroupBox);
    thousandCheckBox->setChecked(thousandSeparator);

    decimalLabel = new QLabel(optionsGroupBox);
    decimalSpinBox = new QSpinBox(optionsGroupBox);
    decimalSpinBox->setRange(0,7);
    decimalSpinBox->setValue(numberOfDecimals);
    decimalLabel->setBuddy(decimalSpinBox);

    optionsLayout->addWidget(decimalLabel);
    optionsLayout->addWidget(decimalSpinBox);
    optionsLayout->addWidget(thousandCheckBox);
    optionsLayout->addStretch(1);

    verticalLayout->addWidget(optionsGroupBox);
    QGroupBox *buttonsGroupBox = new QGroupBox(this);

    QGridLayout *toolButtonsLayout = new QGridLayout(buttonsGroupBox);

    QAction *num1Action = new QAction(tr("1"),this);
    connect(num1Action, SIGNAL(triggered()), this, SLOT(insertNum1()));
    addAction(num1Action);
    QAction *num2Action = new QAction(tr("2"),this);
    connect(num2Action, SIGNAL(triggered()), this, SLOT(insertNum2()));
    addAction(num2Action);
    QAction *num3Action = new QAction(tr("3"),this);
    connect(num3Action, SIGNAL(triggered()), this, SLOT(insertNum3()));
    addAction(num3Action);
    QAction *num4Action = new QAction(tr("4"),this);
    connect(num4Action, SIGNAL(triggered()), this, SLOT(insertNum4()));
    addAction(num4Action);
    QAction *num5Action = new QAction(tr("5"),this);
    connect(num5Action, SIGNAL(triggered()), this, SLOT(insertNum5()));
    addAction(num5Action);
    QAction *num6Action = new QAction(tr("6"),this);
    connect(num6Action, SIGNAL(triggered()), this, SLOT(insertNum6()));
    addAction(num6Action);
    QAction *num7Action = new QAction(tr("7"),this);
    connect(num7Action, SIGNAL(triggered()), this, SLOT(insertNum7()));
    addAction(num7Action);
    QAction *num8Action = new QAction(tr("8"),this);
    connect(num8Action, SIGNAL(triggered()), this, SLOT(insertNum8()));
    addAction(num8Action);
    QAction *num9Action = new QAction(tr("9"),this);
    connect(num9Action, SIGNAL(triggered()), this, SLOT(insertNum9()));
    addAction(num9Action);
    QAction *num0Action = new QAction(tr("0"),this);
    connect(num0Action, SIGNAL(triggered()), this, SLOT(insertNum0()));
    addAction(num0Action);

    QAction *divideAction = new QAction(tr("/"),this);
    connect(divideAction, SIGNAL(triggered()), this, SLOT(qtCalcDivide()));
    addAction(divideAction);
    QAction *timesAction = new QAction(tr("*"),this);
    connect(timesAction, SIGNAL(triggered()), this, SLOT(qtCalcTimes()));
    addAction(timesAction);
    QAction *minusAction = new QAction(tr("-"),this);
    connect(minusAction, SIGNAL(triggered()), this, SLOT(qtCalcMinus()));
    addAction(minusAction);
    QAction *plusAction = new QAction(tr("+"),this);
    connect(plusAction, SIGNAL(triggered()), this, SLOT(qtCalcPlus()));
    addAction(plusAction);
    QAction *commaAction = new QAction(tr("."),this);
    connect(commaAction, SIGNAL(triggered()), this, SLOT(qtCalcComma()));
    addAction(commaAction);
    QAction *clearAction = new QAction(tr("C"),this);
    connect(clearAction, SIGNAL(triggered()), formulaEdit, SLOT(clear()));
    addAction(clearAction);
    QAction *braceOpenAction = new QAction(tr("("),this);
    connect(braceOpenAction, SIGNAL(triggered()), this, SLOT(qtCalcBraceOpen()));
    addAction(braceOpenAction);
    QAction *braceCloseAction = new QAction(tr(")"),this);
    connect(braceCloseAction, SIGNAL(triggered()), this, SLOT(qtCalcBraceClose()));
    addAction(braceCloseAction);

    QAction *percentAction = new QAction(tr("%"),this);
    connect(percentAction, SIGNAL(triggered()), this, SLOT(qtCalcPercent()));
    addAction(percentAction);

    QToolButton *num1 = new QCalculatorToolButton(buttonsGroupBox);
    num1->setDefaultAction(num1Action);
    QToolButton *num2 = new QCalculatorToolButton(buttonsGroupBox);
    num2->setDefaultAction(num2Action);
    QToolButton *num3 = new QCalculatorToolButton(buttonsGroupBox);
    num3->setDefaultAction(num3Action);
    QToolButton *num4 = new QCalculatorToolButton(buttonsGroupBox);
    num4->setDefaultAction(num4Action);
    QToolButton *num5 = new QCalculatorToolButton(buttonsGroupBox);
    num5->setDefaultAction(num5Action);
    QToolButton *num6 = new QCalculatorToolButton(buttonsGroupBox);
    num6->setDefaultAction(num6Action);
    QToolButton *num7 = new QCalculatorToolButton(buttonsGroupBox);
    num7->setDefaultAction(num7Action);
    QToolButton *num8 = new QCalculatorToolButton(buttonsGroupBox);
    num8->setDefaultAction(num8Action);
    QToolButton *num9 = new QCalculatorToolButton(buttonsGroupBox);
    num9->setDefaultAction(num9Action);
    QToolButton *num0 = new QCalculatorToolButton(buttonsGroupBox);
    num0->setDefaultAction(num0Action);
    QToolButton *divideButton = new QCalculatorToolButton(buttonsGroupBox);
    divideButton->setDefaultAction(divideAction);
    QToolButton *timesButton = new QCalculatorToolButton(buttonsGroupBox);
    timesButton->setDefaultAction(timesAction);
    QToolButton *minusButton = new QCalculatorToolButton(buttonsGroupBox);
    minusButton->setDefaultAction(minusAction);
    QToolButton *plusButton = new QCalculatorToolButton(buttonsGroupBox);
    plusButton->setDefaultAction(plusAction);
    QToolButton *commaButton = new QCalculatorToolButton(buttonsGroupBox);
    commaButton->setDefaultAction(commaAction);
    QToolButton *clearButton = new QCalculatorToolButton(buttonsGroupBox);
    clearButton->setDefaultAction(clearAction);
    QToolButton *braceOpenButton = new QCalculatorToolButton(buttonsGroupBox);
    braceOpenButton->setDefaultAction(braceOpenAction);
    QToolButton *braceCloseButton = new QCalculatorToolButton(buttonsGroupBox);
    braceCloseButton->setDefaultAction(braceCloseAction);
    QToolButton *percentButton = new QCalculatorToolButton(buttonsGroupBox);
    percentButton->setDefaultAction(percentAction);

    toolButtonsLayout->addWidget(num7, 0, 0);
    toolButtonsLayout->addWidget(num8, 0, 1);
    toolButtonsLayout->addWidget(num9, 0, 2);

    toolButtonsLayout->addWidget(num4, 1, 0);
    toolButtonsLayout->addWidget(num5, 1, 1);
    toolButtonsLayout->addWidget(num6, 1, 2);

    toolButtonsLayout->addWidget(num1, 2, 0);
    toolButtonsLayout->addWidget(num2, 2, 1);
    toolButtonsLayout->addWidget(num3, 2, 2);

    toolButtonsLayout->addWidget(num0, 3, 0);
    toolButtonsLayout->addWidget(commaButton, 3, 1);
    toolButtonsLayout->addWidget(plusButton, 3, 2);

    toolButtonsLayout->addWidget(minusButton, 4, 0);
    toolButtonsLayout->addWidget(timesButton, 4, 1);
    toolButtonsLayout->addWidget(divideButton, 4, 2);

    toolButtonsLayout->addWidget(braceOpenButton, 5, 0);
    toolButtonsLayout->addWidget(braceCloseButton, 5, 1);
    toolButtonsLayout->addWidget(percentButton, 5, 2);

    toolButtonsLayout->addWidget(clearButton, 6, 1);


    svgLayout->addWidget(buttonsGroupBox);
    svgLayout->addStretch(1);

    mainLayout->addLayout(svgLayout);

    QPushButton *okButton = new QPushButton(tr("OK"), this);
    QPushButton *cancelButton = new QPushButton(tr("Cancel"), this);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), this, SLOT(verifyDbfInputLines()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    verticalLayout->addLayout(buttonLayout);

    mainLayout->addLayout(verticalLayout);

    setLayout(mainLayout);

    editareGroupBox->setTitle(QApplication::translate("Dialog", "Supports elementary operations and brackets", 0, QApplication::UnicodeUTF8));
    optionsGroupBox->setTitle(QApplication::translate("Dialog", "Options", 0, QApplication::UnicodeUTF8));

    formulaLabel->setText(QApplication::translate("Dialog", "&Formula", 0, QApplication::UnicodeUTF8));
    resultLabel->setText(QApplication::translate("Dialog", "&Result", 0, QApplication::UnicodeUTF8));
    decimalLabel->setText(QApplication::translate("Dialog", "&Decimal places", 0, QApplication::UnicodeUTF8));

    connect(formulaEdit, SIGNAL(textChanged()), this, SLOT(refreshResult()));
    connect(thousandCheckBox, SIGNAL(stateChanged(int)), this, SLOT(refreshResult()));
    connect(decimalSpinBox, SIGNAL(valueChanged(int)), this, SLOT(refreshResult()));
    connect(formulaEdit, SIGNAL(okSignal()), this, SLOT(accept()));

    refreshResult();
    formulaEdit->setFocus();
}

void QCalculatorDialog::setFormula(const QString &formula)
{
    formulaEdit->setText(formula);
}

QString QCalculatorDialog::getFormula()
{
    return formulaEdit->toPlainText().simplified();
}

QString QCalculatorDialog::getValue()
{
    return QString::number(d,'f',numberOfDecimals);
}

void QCalculatorDialog::refreshResult()
{
    QString result;
    QLocale clocale(QLocale::German);
    formula = formulaEdit->toPlainText().simplified().remove(" ");
    p = 0;

    d = eval();
    p = 0;

    if (thousandCheckBox->isChecked())
        {
            result = clocale.toString(d,'f',decimalSpinBox->value());
        }
    else
        {
            result = QString::number(d,'f',decimalSpinBox->value());
        }

    resultEdit->setText(result);
}

double QCalculatorDialog::eval()
{
    double r = termen();
    while ( (formula.data()[p] =='+') || (formula.data()[p]=='-') )
        {
            if (formula.data()[p] == '+')
                {
                    ++p;
                    r += termen();
                }
            if (formula.data()[p] == '-')
                {
                    ++p;
                    r -= termen();
                }
        }

    return r;
}

double QCalculatorDialog::termen()
{
    double r = factor();
    while ((formula.data()[p] == '*') || (formula.data()[p] == '/') || (formula.data()[p] == '%'))
        {
        if (formula.data()[p] == '%')
            {
                ++p;
                r = r / 100 * factor();
            }
            if (formula.data()[p] == '*')
                {
                    ++p;
                    r *= factor();
                }
            if (formula.data()[p] == '/')
                {
                    ++p;
                    r /= factor();
                }
        }
    return r;
}

double QCalculatorDialog::factor()
{
    double r=0;
    double t=0;
    int i = 0;
    QString convert;
    bool ok;
    if ( formula.data()[p] == '(' )
        {
            ++p;
            r = eval();
            ++p;
        }
    else
       {
            while ( (formula.data()[p]>='0') && (formula.data()[p]<='9') )
                {
                    convert = formula[p];
                    r = r*10 + convert.toInt(&ok, 10);
                    ++p;
                }
            if ( formula.data()[p] == '.' )
                {
                    ++p;
                    i = 0;
                    while ( (formula.data()[p] >='0') && (formula.data()[p]<='9') )
                        {
                            convert = formula[p];
                            t = t*10 + convert.toInt(&ok, 10);
                            ++p;
                            ++i;
                        }
                }
            long x = 1;
            for (int j=0;j<i;j++)
                {
                    x *= 10;
                }
            r = r + t/x;
        }
    return r;
}

void QCalculatorDialog::insertNum1()
{
    formulaEdit->insertPlainText("1");
}

void QCalculatorDialog::insertNum2()
{
    formulaEdit->insertPlainText("2");
}

void QCalculatorDialog::insertNum3()
{
    formulaEdit->insertPlainText("3");
}

void QCalculatorDialog::insertNum4()
{
    formulaEdit->insertPlainText("4");
}

void QCalculatorDialog::insertNum5()
{
    formulaEdit->insertPlainText("5");
}

void QCalculatorDialog::insertNum6()
{
    formulaEdit->insertPlainText("6");
}

void QCalculatorDialog::insertNum7()
{
    formulaEdit->insertPlainText("7");
}

void QCalculatorDialog::insertNum8()
{
    formulaEdit->insertPlainText("8");
}

void QCalculatorDialog::insertNum9()
{
    formulaEdit->insertPlainText("9");
}

void QCalculatorDialog::insertNum0()
{
    formulaEdit->insertPlainText("0");
}

void QCalculatorDialog::qtCalcDivide()
{
    formulaEdit->insertPlainText("/");
}

void QCalculatorDialog::qtCalcTimes()
{
    formulaEdit->insertPlainText("*");
}

void QCalculatorDialog::qtCalcPlus()
{
    formulaEdit->insertPlainText("+");
}

void QCalculatorDialog::qtCalcMinus()
{
    formulaEdit->insertPlainText("-");
}

void QCalculatorDialog::qtCalcComma()
{
    formulaEdit->insertPlainText(".");
}

void QCalculatorDialog::qtCalcBraceOpen()
{
    formulaEdit->insertPlainText("(");
}

void QCalculatorDialog::qtCalcPercent()
{
    formulaEdit->insertPlainText("%");
}

void QCalculatorDialog::qtCalcBraceClose()
{
    formulaEdit->insertPlainText(")");
}

QCalculatorDialog::~QCalculatorDialog()
{
    QSettings settings;
    settings.setValue("qtcalculator/Size", size());
    settings.setValue("qtcalculator/formula", getFormula());
    settings.setValue("qtcalculator/numberofdecimals",decimalSpinBox->value());
    settings.setValue("qtcalculator/thousandseparator",thousandCheckBox->isChecked());
}

//QCalculatorToolButton

QCalculatorToolButton::QCalculatorToolButton(QWidget *parent)
    : QToolButton(parent)
{
    QFont font = this->font();
    font.setBold(true);
    font.setPointSize(font.pointSize()+2);
    setFont(font);
}

QSize QCalculatorToolButton::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 10;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

void QCalculatorToolButton::setIconSize1(int i)
{
    QSize size = QSize(i,i);
    setIconSize(size);
}

QCalculatorToolButton::~QCalculatorToolButton()
{
}
