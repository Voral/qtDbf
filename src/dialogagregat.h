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
#ifndef DIALOGAGREGAT_H
#define DIALOGAGREGAT_H

#include "widgets.h"
#include "structures.h"


typedef QList<QFieldsItem*> FieldList;
class DialogAgregat : public QDbfDialog
{
    Q_OBJECT
private:
    FieldList fieldsCollection;
    QGridLayout *laMain;
    QVBoxLayout *laButtons;
    QLabel *lbField;
    QLabel *lbFunction;
    QComboBox *cbField;
    QComboBox *cbFunction;
    QDialogButtonBox *buttonBox;
//    QValidator *validator;

public:
    explicit DialogAgregat(const FieldList fields, const int index, QWidget *parent = 0);
    QString getFieldPart();

signals:

public slots:

};

#endif // DIALOGAGREGAT_H
