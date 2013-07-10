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

#ifndef CUSTOMSQLMODEL_H
#define CUSTOMSQLMODEL_H

#include <QSqlQueryModel>

class QDbfSqlModel : public QSqlQueryModel
{
    Q_OBJECT

public:
    QDbfSqlModel(QObject *parent = 0);
    void addCharField(int i);
    void addCurrencyField(int i);
    void addNumericField(int i);
    void addDateField(int i);
    void addTimeField(int i);
    void addDoubleField(int i);
    void addIntField(int i);
    void addLogicalField(int i);
    void addMemoField(int i);
    void addMemo4Field(int i);
    void addGeneralField(int i);

    QVariant data(const QModelIndex &item, int role) const;

private:
    /*
    C   –   Character
            255 bytes ASCII
    Y   –   Currency
            8 bytes binary ?
    N   –   Numeric
    F   –   Float
            Same as numeric 1 to 20 bytes in table
    D   –   Date
            yyyymmdd
    T   –   DateTime
            It's stored as an 8 byte field.
            The first 4 bytes stores the number of days since SQL Server's epoch (1st Jan 1900).
            The second 4 bytes stores the number of milliseconds after midnight.
    B   –   Double
            8 bytes
    I   –   Integer
            4 bytes
    L   –   Logical
    M   –   Memo
            10 bytes ASCII integer in dBase FoxPro
            4 bytes binary integer in Visual FoxPro
    G   –   General
            4 byte reference to an OLE object
    C   –   Character (binary)
    M   –   Memo (binary)
    P   –   Picture
    */
    QList<int> charFields;
    QList<int> currencyFields;
    QList<int> numericFields;
    QList<int> dateFields;
    QList<int> timeFields;
    QList<int> doubleFields;
    QList<int> intFields;
    QList<int> logicalFields;
    QList<int> memoFields;
    QList<int> memo4Fields;
    QList<int> generalFields;

};


#endif
