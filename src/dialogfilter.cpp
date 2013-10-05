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

#include "dialogfilter.h"

DialogFilter::DialogFilter(const FieldList fields, const QString &title, const QString &field = "", QWidget *parent) :
    QDbfDialog(title,parent),
    fieldsCollection(fields)
{
    validator = 0;
    laMain = new QGridLayout(this);
    lbField = new QLabel(tr("Field Name"));
    lbExpression = new QLabel(tr("Expression"));
    cbField = new QComboBox();
    cbExpression = new QComboBox();
    edExpression = new QLineEdit();

    laButtons = new QVBoxLayout();
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    laButtons->addWidget(buttonBox);

    setLayout(laMain);
    laMain->addWidget(lbField,0,0,1,1,Qt::AlignLeft);
    laMain->addWidget(cbField,0,1,1,2);
    laMain->addWidget(lbExpression,1,0,1,1,Qt::AlignLeft);
    laMain->addWidget(cbExpression,1,1,1,1);
    laMain->addWidget(edExpression,1,2,1,1);
    laMain->addLayout(laButtons,2,0,1,3);

    cbExpression->addItem(tr("contain"),QVariant("like"));
    cbExpression->addItem(tr("equal"),QVariant("="));
    cbExpression->addItem(tr("not equal"),QVariant("<>"));
    cbExpression->addItem(tr("greater than"),QVariant(">"));
    cbExpression->addItem(tr("equal or greater than"),QVariant(">="));
    cbExpression->addItem(tr("less than"),QVariant("<"));
    cbExpression->addItem(tr("equal or less than"),QVariant("<="));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(cbField,SIGNAL(currentIndexChanged(int)),this,SLOT(onFieldChange(int)));

    QString enabled("CLDNFI");
    for(int i = 0; i < fieldsCollection.count();++i)
    {
        if (enabled.indexOf(fieldsCollection.at(i)->fieldType)==-1) continue;
        cbField->addItem(fieldsCollection.at(i)->fieldName);
        cbField->setItemData(cbField->count()-1,i);
    }
    cbField->setCurrentIndex(cbField->findText(field));
    if (cbField->count()==0)
    {
        QMessageBox::warning(this,tr("Error"),tr("Sorry! No supported fields for filter"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
    }
    edExpression->setMinimumWidth(200);
    adjustSize();
    setMaximumHeight(height());
}
QString DialogFilter::getWhere()
{
    QString result = prepare(fieldsCollection.at(cbField->itemData(cbField->currentIndex()).toInt()),cbExpression->itemData(cbExpression->currentIndex()).toString(),edExpression->text());
    if (result == "") result =  "1 = 2";
    return result;
}
void DialogFilter::onFieldChange(int index)
{
    if (cbExpression->itemData(0) == "like") cbExpression->removeItem(0);
    edExpression->setInputMask("");
    edExpression->setMaxLength(32767);
    if (validator!=0)
    {
        delete validator;
        validator = 0;
    }
    if (fieldsCollection.at(index)->fieldType == "C")
    {
        cbExpression->insertItem(0,tr("contain"),QVariant("like"));
        cbExpression->setCurrentIndex(0);
        edExpression->setMaxLength(fieldsCollection.at(index)->fieldSize);
    }
    else if (fieldsCollection.at(index)->fieldType == "L")
    {
        QRegExp rx("[TtYyFfNn \?]");
        validator = new QRegExpValidator(rx, this);
        edExpression->setMaxLength(1);
        edExpression->setValidator(validator);
        edExpression->setInputMask("A");
    }
    else if (fieldsCollection.at(index)->fieldType == "D")
    {
        edExpression->setInputMask("00.00.0000");
    }
    else if ((fieldsCollection.at(index)->fieldType == "N") || (fieldsCollection.at(index)->fieldType == "F"))
    {
        QRegExp rx(QString("-?^[0-9]+(\\.|,[0-9]{0,%1})?$").arg(fieldsCollection.at(index)->fieldDecimals));
        validator = new QRegExpValidator(rx, this);
        edExpression->setMaxLength(fieldsCollection.at(index)->fieldSize);
        edExpression->setValidator(validator);
    }
/*    else if (fieldsCollection.at(index)->fieldType == "T")
    {
        edExpression->setInputMask("00.00.000 00:00:00.000");
    }
  */
    else if (fieldsCollection.at(index)->fieldType == "I")
    {
        QRegExp rx(QString("^[0-9-]{1,%1}$").arg(fieldsCollection.at(index)->fieldSize));
        validator = new QRegExpValidator(rx, this);
        edExpression->setMaxLength(fieldsCollection.at(index)->fieldSize);
    }
}
QString DialogFilter::prepare(QFieldsItem *item, QString expression,QString filter)
{
    QString result("`"+item->fieldName+"`");
    if (item->fieldType == "C")
    {
        if (expression=="like") filter = "%"+filter+"%";
        result.append(expression);
        result.append("'"+filter+"'");
    }
    else if (item->fieldType == "L")
    {
        if (expression=="like") return "";
        result.append(expression);
        result.append("'"+filter+"'");
    }
    else if (item->fieldType == "D")
    {
        if (expression=="like") return "";
        result.append(expression);
        result.append("'"+QDateTime::fromString(filter,"dd.MM.yyyy").toString("yyyy-MM-dd").toLocal8Bit()+"'");
    }
    if ((item->fieldType == "N") || (item->fieldType == "F"))
    {
        if (expression=="like") return "";
        double value;
        QString valueStr;
        bool ok;
        value=filter.toDouble(&ok);
        if (!ok) return "";
        valueStr.setNum(value,'f',item->fieldDecimals);
        result.append(expression);
        result.append(valueStr);
    };
    if (item->fieldType == "I")
    {
        if (expression=="like") return "";
        long value;
        QString valueStr;
        bool ok;
        value=filter.toLong(&ok,10);
        if (!ok) return "";
        valueStr.setNum(value);
        result.append(expression);
        result.append(valueStr);
    };
    return result;
}
