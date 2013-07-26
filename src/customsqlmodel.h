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
