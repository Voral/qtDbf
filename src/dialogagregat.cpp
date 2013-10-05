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

#include "dialogagregat.h"

DialogAgregat::DialogAgregat(const FieldList fields, const int index, QWidget *parent) :
    QDbfDialog(tr("Aggregate functions"),parent),
    fieldsCollection(fields)
{
    laMain = new QGridLayout(this);
    lbField = new QLabel(tr("Field Name"));
    lbFunction = new QLabel(tr("Function"));
    cbField = new QComboBox();
    cbField->setMinimumWidth(130);
    cbFunction = new QComboBox();

    laButtons = new QVBoxLayout();
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    laButtons->addWidget(buttonBox);
    setLayout(laMain);
    laMain->addWidget(lbField,0,0,1,1,Qt::AlignLeft);
    laMain->addWidget(cbField,0,1,1,2);
    laMain->addWidget(lbFunction,1,0,1,1,Qt::AlignLeft);
    laMain->addWidget(cbFunction,1,1,1,1);
    laMain->addLayout(laButtons,2,0,1,3);

    cbFunction->addItem(tr("Sum"),QVariant("SUM"));
    cbFunction->addItem(tr("Count"),QVariant("COUNT"));
    cbFunction->addItem(tr("Average"),QVariant("AVG"));
    cbFunction->addItem(tr("Min"),QVariant("MIN"));
    cbFunction->addItem(tr("Max"),QVariant("MAX"));
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QString enabled("NFI");
    for(int i = 0; i < fieldsCollection.count();++i)
    {
        if (enabled.indexOf(fieldsCollection.at(i)->fieldType)==-1) continue;
        cbField->addItem(fieldsCollection.at(i)->fieldName);
        cbField->setItemData(cbField->count()-1,i);
    }
    cbField->setCurrentIndex(index);
    if (cbField->count()==0)
    {
        QMessageBox::warning(this,tr("Error"),tr("Sorry! No supported fields for average functions"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
    }
    adjustSize();
    setMaximumHeight(height());
}
QString DialogAgregat::getFieldPart()
{
    return QString("%1(`%2`)").arg(cbFunction->itemData(cbFunction->currentIndex()).toString()).arg(fieldsCollection.at(cbField->itemData(cbField->currentIndex()).toInt())->fieldName);

}
