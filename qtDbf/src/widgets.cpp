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
#include <QtSql>

#include "widgets.h"
#include "globals.h"
#include "qtcalculator.h"

// QDbfDialog

QDbfDialog::QDbfDialog(const QString &title, QWidget *parent)
    : QDialog(parent)
{
  setWindowTitle(title);
  connect(this, SIGNAL(endVerifyDbfInputLines()), this, SLOT(accept()));
}

void QDbfDialog::verifyDbfInputLines()
{
     int v = 1;

     QListIterator<QDbfLineEdit *> i(lineEditsToVerify);
     while (i.hasNext())
           {
            int tv;
            tv =i.next()->valid();
            if (tv == 0)
               {
                v = 0;
                break;
               }
           }

     if (v == 1)
         emit endVerifyDbfInputLines();
}

void QDbfDialog::insertLineEditToVerify(QDbfLineEdit* dbfLineEdit)
{
     lineEditsToVerify.append(dbfLineEdit);
}

QDbfDialog::~QDbfDialog()
{
     lineEditsToVerify.clear();
}

// QDbfLineEdit

QDbfLineEdit::QDbfLineEdit(const QString &contents, QWidget *parent) :
    QLineEdit(contents, parent)
{
    QFont font = this->font();
    font.setPointSize(font.pointSize() + 5);
    setFont(font);

    QCompleter *dbfLineEditCompleter = new QCompleter(wordList, this);
    dbfLineEditCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    setCompleter(dbfLineEditCompleter);
}

void QDbfLineEdit::focusOutEvent(QFocusEvent *event)
{
     if (!wordList.contains(text()))
        wordList << text();
     QString t= text();
     t.replace("'","''");
     setText(t);
     QLineEdit::focusOutEvent(event);
}

int QDbfLineEdit::valid()
{
     return 1;
}

void QDbfLineEdit::mouseDoubleClickEvent(QMouseEvent *event)
{
    searchItem();
}

void QDbfLineEdit::search()
{
     searchItem();
}

void QDbfLineEdit::searchItem()
{
}

void QDbfLineEdit::keyPressEvent(QKeyEvent *event)
{
     switch (event->key())
            {
             case Qt::Key_F9:
                  searchItem();
                  break;
             default:
                  QLineEdit::keyPressEvent(event);
        }
}

QDbfLineEdit::~QDbfLineEdit()
{


}

// QNoEmptyLineEdit

QNoEmptyLineEdit::QNoEmptyLineEdit(bool show_message, const QString &contents, QWidget *parent) :
    QDbfLineEdit(contents, parent)
{
    showMessage = show_message;
}

int QNoEmptyLineEdit::valid()
{
     if (text().isEmpty())
        {
         setFocus(Qt::OtherFocusReason);
         if (showMessage)
            {
                QMessageBox::critical(this, tr("Error"),tr("This field cannot be empty."));
            }
         else
            {
                setToolTip(tr("This field cannot be empty."));
                setStatusTip(tr("This field cannot be empty."));
            }
         return 0;
        }

     return 1;
}

void QNoEmptyLineEdit::searchItem()
{
}

QNoEmptyLineEdit::~QNoEmptyLineEdit()
{
}

// QDateTimeLineEdit

QDateTimeLineEdit::QDateTimeLineEdit(bool v, const QString &contents, QWidget *parent) :
    QDbfLineEdit(contents, parent)
{
    verify = v;
}

int QDateTimeLineEdit::valid()
{
    if (!verify)
        return 1;
    QDate date;
    date = QDate::fromString(text(), Qt::ISODate);
    if (date.isValid())
        return 1;
    else
        {
            QMessageBox::critical(this, tr("Error"),tr("Enter a valid date"));
            setFocus(Qt::OtherFocusReason);
            return 0;
        }
}

void QDateTimeLineEdit::searchItem()
{
    QDate datum;
    datum = QDate::fromString(text(), Qt::ISODate);

    QDialog *calendarDialog = new QDialog(this);
    calendarDialog->setWindowTitle(tr("Data"));

    QVBoxLayout *verticalLayout = new QVBoxLayout(calendarDialog);

    QCalendarWidget *calendarWidget = new QCalendarWidget(calendarDialog);
    calendarWidget->setFirstDayOfWeek(Qt::DayOfWeek(1));
    calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->setGridVisible(true);
    calendarWidget->setSelectedDate(datum);

    verticalLayout->addWidget(calendarWidget);

    QPushButton *okButton = new QPushButton(QIcon(":images/ok.svg"),tr("OK"), this);
    QPushButton *cancelButton = new QPushButton(QIcon(":images/cancel.svg"),tr("Cancel"), this);

    connect(okButton, SIGNAL(clicked()), calendarDialog, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), calendarDialog, SLOT(reject()));
    connect(calendarWidget, SIGNAL(activated(QDate)), calendarDialog, SLOT(accept()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    verticalLayout->addLayout(buttonLayout);

    calendarDialog->setLayout(verticalLayout);
    calendarDialog->resize(300, 200);

    if (calendarDialog->exec())
       {
        setText(calendarWidget->selectedDate().toString(Qt::ISODate));
       }
}

QDateTimeLineEdit::~QDateTimeLineEdit()
{
}

// QDateLineEdit

QDateLineEdit::QDateLineEdit(bool v, const QString &contents, QWidget *parent) :
    QDbfLineEdit(contents, parent)
{
    verify = v;
}

int QDateLineEdit::valid()
{
    if (!verify)
        return 1;
    QDate date;
    date = QDate::fromString(text(), Qt::ISODate);
    if (date.isValid())
        return 1;
    else
        {
            QMessageBox::critical(this, tr("Error"),tr("Enter a valid date"));
            setFocus(Qt::OtherFocusReason);
            return 0;
        }
}

void QDateLineEdit::searchItem()
{
    QDate datum;
    datum = QDate::fromString(text(), Qt::ISODate);

    QDialog *calendarDialog = new QDialog(this);
    calendarDialog->setWindowTitle(tr("Data"));

    QVBoxLayout *verticalLayout = new QVBoxLayout(calendarDialog);

    QCalendarWidget *calendarWidget = new QCalendarWidget(calendarDialog);
    calendarWidget->setFirstDayOfWeek(Qt::DayOfWeek(1));
    calendarWidget->setHorizontalHeaderFormat(QCalendarWidget::SingleLetterDayNames);
    calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendarWidget->setGridVisible(true);
    calendarWidget->setSelectedDate(datum);

    verticalLayout->addWidget(calendarWidget);

    QPushButton *okButton = new QPushButton(QIcon(":images/ok.svg"),tr("OK"), this);
    QPushButton *cancelButton = new QPushButton(QIcon(":images/cancel.svg"),tr("Cancel"), this);

    connect(okButton, SIGNAL(clicked()), calendarDialog, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), calendarDialog, SLOT(reject()));
    connect(calendarWidget, SIGNAL(activated(QDate)), calendarDialog, SLOT(accept()));

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    verticalLayout->addLayout(buttonLayout);

    calendarDialog->setLayout(verticalLayout);
    calendarDialog->resize(300, 200);

    if (calendarDialog->exec())
       {
        setText(calendarWidget->selectedDate().toString(Qt::ISODate));
       }
}

QDateLineEdit::~QDateLineEdit()
{
}

// QDoubleLineEdit

QDoubleLineEdit::QDoubleLineEdit(const QString &contents, QWidget *parent) :
    QDbfLineEdit(contents, parent)
{
    setCompleter(0);
    QDoubleValidator *dv = new QDoubleValidator(this);
    setValidator(dv);
}

int QDoubleLineEdit::valid()
{
     return 1;
}

void QDoubleLineEdit::searchItem()
{
    QCalculatorDialog *d = new QCalculatorDialog(tr("Calculator"), this);

    if (d->exec())
        {
         if (d->result() == QDialog::Accepted )
            {
                setText(d->getValue());
            }
        }
     delete d;

}

QDoubleLineEdit::~QDoubleLineEdit()
{
}

// QNoZeroDoubleLineEdit

QNoZeroDoubleLineEdit::QNoZeroDoubleLineEdit(const QString &contents, QWidget *parent) :
    QDbfLineEdit(contents, parent)
{
    setCompleter(0);
    QDoubleValidator *dv = new QDoubleValidator(this);
    setValidator(dv);
}

int QNoZeroDoubleLineEdit::valid()
{
     double i;
     i = text().toDouble();

     if (i == 0)
        {
         //QMessageBox::critical(this, tr("Error"),tr("This value cannot be null."));
         setFocus(Qt::OtherFocusReason);
         return 0;
        }

     return 1;
}

void QNoZeroDoubleLineEdit::searchItem()
{
    QCalculatorDialog *d = new QCalculatorDialog(tr("Calculator"), this);

    if (d->exec())
        {
         if (d->result() == QDialog::Accepted )
            {
                setText(d->getValue());
            }
        }
     delete d;
}

QNoZeroDoubleLineEdit::~QNoZeroDoubleLineEdit()
{
}

//QDbfToolButton

QDbfToolButton::QDbfToolButton(QWidget *parent)
    : QToolButton(parent)
{
    QSettings settings;
    QSize toolButtonSize = settings.value("toolbuttonsize", QSize(37,37)).toSize();
    setIconSize(toolButtonSize);
}

QSize QDbfToolButton::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 5;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

void QDbfToolButton::setIconSize1(int i)
{
    QSize size = QSize(i,i);
    setIconSize(size);
}

QDbfToolButton::~QDbfToolButton()
{
}

//QDbfTableView

QDbfTableView::QDbfTableView(QWidget *parent)
     : QTableView(parent)
{
}

void QDbfTableView::keyPressEvent(QKeyEvent *event)
{
     switch (event->key())
            {
             case Qt::Key_Return:
             case Qt::Key_Enter:
                  if ( model()->rowCount() != 0 )
                     emit editSignal();
                  break;
             case Qt::Key_F9:
                  emit searchSignal();
                  break;
             case Qt::Key_Insert:
                  emit insertSignal();
                  break;
             case Qt::Key_Delete:
                  if ( model()->rowCount() != 0 )
                     emit deleteSignal();
                  break;
             case Qt::Key_Escape:
                  emit quitSignal();
                  break;
             default:
                  QTableView::keyPressEvent(event);
        }
}

//QDbfPushButton

QDbfPushButton::QDbfPushButton(const QIcon &icon, const QString &text , QWidget *parent)
   : QPushButton(icon, text, parent)
{
}

QSize QDbfPushButton::sizeHint() const
{
    return iconSize();
}

//QFieldColorLabel

QFieldColorLabel::QFieldColorLabel(QWidget *parent) :
    QLabel(parent)
{
    QFont font = this->font();
    font.setPointSize(font.pointSize() + 2);
    font.setBold(true);
    setFont(font);
}

void QFieldColorLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit changeColor();
}
