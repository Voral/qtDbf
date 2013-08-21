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

#include "structures.h"
#include "dbfeditor.h"
#include "widgets.h"
#include "customsqlmodel.h"
#include "qtcalculator.h"
#include "dbfconfig.h"
#include "globals.h"
#include "dialogfilter.h"
QDbfEditor::QDbfEditor(QString &a_dbfFileName, const QString &title, QWidget *parent)
    : QWidget(parent)
{
    modified = false;
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    view = new QDbfTableView(this);

    openAction = new QAction(QIcon(":images/document_open.png"),tr("Open").append(" Ctrl + O"), this);
    openAction->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(openAction, SIGNAL(triggered()), this, SLOT(openNewFile()));
    addAction(openAction);

    fillAction = new QAction(QIcon(":images/fill.svg"),tr("Fill"), this);
    connect(fillAction, SIGNAL(triggered()), this, SLOT(fillCells()));
    addAction(fillAction);

    editAction = new QAction(QIcon(":images/edit.svg"),tr("Edit").append(" Enter"), this);
    editAction->setShortcut(Qt::Key_Return);
    connect(editAction, SIGNAL(triggered()), this, SLOT(editRecord()));
    addAction(editAction);

    insertAction = new QAction(QIcon(":images/add.svg"),tr("Add").append(" Ins"), this);
    insertAction->setShortcut(Qt::Key_Insert);
    connect(insertAction, SIGNAL(triggered()), this, SLOT(insertRecord()));
    addAction(insertAction);

    deleteAction = new QAction(QIcon(":images/delete.svg"),tr("Delete").append(" Del"), this);
    deleteAction->setShortcut(Qt::Key_Delete);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteRecord()));
    addAction(deleteAction);

    saveAction = new QAction(QIcon(":images/save.svg"),tr("Save").append(" Ctrl + S"), this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveDbfFile()));
    saveAction->setShortcut(Qt::CTRL + Qt::Key_S);
    addAction(saveAction);
    configAction = new QAction(QIcon(":images/config.svg"),tr("Configure"), this);
    connect(configAction, SIGNAL(triggered()), this, SLOT(configApp()));
    addAction(configAction);

    helpAction = new QAction(QIcon(":images/help.svg"),tr("Help").append(" F1"), this);
    helpAction->setShortcut(Qt::Key_F1);
    connect(helpAction, SIGNAL(triggered()), this, SLOT(helpDbf()));
    addAction(helpAction);

    calcAction = new QAction(QIcon(":images/calc.svg"),tr("Calculator").append(" Ctrl + E"), this);
    saveAction->setShortcut(Qt::CTRL + Qt::Key_E);
    connect(calcAction, SIGNAL(triggered()), this, SLOT(calculator()));
    addAction(calcAction);

    quitAction = new QAction(QIcon(":images/quit.svg"),tr("Close").append(" Esc"), this);
    saveAction->setShortcut(Qt::Key_Escape);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    addAction(quitAction);

    filterAction = new QAction(QIcon(":images/filter.png"),tr("Set filter").append(" Ctrl + F"), this);
    filterAction->setShortcut(Qt::CTRL + Qt::Key_F);
    filterAction->setCheckable(true);
    connect(filterAction, SIGNAL(triggered(bool)), this, SLOT(filter(bool)));
    addAction(filterAction);

    openButton = new QDbfToolButton(this);
    openButton->setDefaultAction(openAction);
    editButton = new QDbfToolButton(this);
    editButton->setDefaultAction(editAction);
    insertButton = new QDbfToolButton(this);
    insertButton->setDefaultAction(insertAction);
    deleteButton = new QDbfToolButton(this);
    deleteButton->setDefaultAction(deleteAction);
    saveButton = new QDbfToolButton(this);
    saveButton->setDefaultAction(saveAction);
    fillButton = new QDbfToolButton(this);
    fillButton->setDefaultAction(fillAction);
    configButton = new QDbfToolButton(this);
    configButton->setDefaultAction(configAction);
    helpButton = new QDbfToolButton(this);
    helpButton->setDefaultAction(helpAction);
    calcButton = new QDbfToolButton(this);
    calcButton->setDefaultAction(calcAction);
    quitButton = new QDbfToolButton(this);
    quitButton->setDefaultAction(quitAction);
    filterButton = new QDbfToolButton(this);
    filterButton->setDefaultAction(filterAction);

    openButton->setFocusPolicy(Qt::NoFocus);
    editButton->setFocusPolicy(Qt::NoFocus);
    insertButton->setFocusPolicy(Qt::NoFocus);
    deleteButton->setFocusPolicy(Qt::NoFocus);
    fillButton->setFocusPolicy(Qt::NoFocus);
    saveButton->setFocusPolicy(Qt::NoFocus);
    configButton->setFocusPolicy(Qt::NoFocus);
    helpButton->setFocusPolicy(Qt::NoFocus);
    calcButton->setFocusPolicy(Qt::NoFocus);
    quitButton->setFocusPolicy(Qt::NoFocus);
    filterButton->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *buttonLayout = new QVBoxLayout;

    buttonLayout->addWidget(openButton);
    buttonLayout->addWidget(fillButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(insertButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(filterButton);
    buttonLayout->addWidget(configButton);
    buttonLayout->addWidget(calcButton);
    buttonLayout->addWidget(helpButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(quitButton);

    mainLayout->addWidget(view);
    mainLayout->addLayout(buttonLayout);
    setWindowTitle(title);

    connect(this, SIGNAL(modelIsEmpty(bool)), editAction, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(modelIsEmpty(bool)), deleteAction, SLOT(setDisabled(bool)));
    connect(this, SIGNAL(modelIsEmpty(bool)), fillAction, SLOT(setDisabled(bool)));

    connect(view, SIGNAL(editSignal()), this, SLOT(editRecord()));
    connect(view, SIGNAL(insertSignal()), this, SLOT(insertRecord()));
    connect(view, SIGNAL(deleteSignal()), this, SLOT(deleteRecord()));

    connect(view, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(editRecord()));
    connect(view, SIGNAL(quitSignal()), qApp, SLOT(closeAllWindows()));
    connect(parent, SIGNAL(setToolButtonIconSize(int)), this, SLOT(setToolButtonIconSize(int)));

    openFile(a_dbfFileName,false);

    if (model->rowCount() == 0)
        emit modelIsEmpty(true);
    else
        emit modelIsEmpty(false);

    view->setFocus();
}
void QDbfEditor::openFile(QString &a_dbfFileName,bool fresh = false)
{
    where = "";
    order = "";
    filterAction->setChecked(false);
    if (fresh)
    {
        delete this->model;
        delete fieldsItem;
        while (fieldsCollection.count()>0)
            {
                fieldsCollection.removeLast();
            }
    }
    modified = false;
    dbfFileName = a_dbfFileName;
    int current;

    readSettings();
    openDbfFile();

    QString query;
    QSqlQuery getData(QSqlDatabase::database("dbfEditor"));

    int i;
    query = "SELECT id_";
    query += tableName;
    query += ",";
    for (i=0;i<fieldsCollection.count();i++)
        {
        query += ("`"+fieldsCollection.at(i)->fieldName+"`");
            if (i<fieldsCollection.count()-1)
                query += ",";
        }
    query +=" FROM ";
    query += tableName;

    model = new QDbfSqlModel(this);

    for (i=0;i<fieldsCollection.count();i++)
        {
            if (fieldsCollection.at(i)->fieldType == "C")
                model->addCharField(i+1);
            if (fieldsCollection.at(i)->fieldType == "Y")
                model->addCurrencyField(i+1);
            if (fieldsCollection.at(i)->fieldType == "N")
                model->addNumericField(i+1);
            if (fieldsCollection.at(i)->fieldType == "F")
                model->addNumericField(i+1);
            if (fieldsCollection.at(i)->fieldType == "D")
                model->addDateField(i+1);
            if (fieldsCollection.at(i)->fieldType == "T")
                model->addTimeField(i+1);
            if (fieldsCollection.at(i)->fieldType == "B")
                model->addDoubleField(i+1);
            if (fieldsCollection.at(i)->fieldType == "I")
                model->addIntField(i+1);
            if (fieldsCollection.at(i)->fieldType == "L")
                model->addLogicalField(i+1);
            if ((fieldsCollection.at(i)->fieldType == "M") && (fieldsCollection.at(i)->fieldSize == 10))
                model->addMemoField(i+1);
            if ((fieldsCollection.at(i)->fieldType == "M") && (fieldsCollection.at(i)->fieldSize == 4))
                model->addMemo4Field(i+1);
            if (fieldsCollection.at(i)->fieldType == "G")
                model->addGeneralField(i+1);
        }

    model->setQuery(query, QSqlDatabase::database("dbfEditor"));
    if (model->lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), model->lastError().text());
        }

    QString tempChar;
    QString tempValue;

    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    for (int i=0; i<fieldsCollection.count(); ++i)
        {
            tempValue = fieldsCollection.at(i)->fieldName;
            tempValue += " (";
            tempValue += fieldsCollection.at(i)->fieldType;
            tempChar.setNum(fieldsCollection.at(i)->fieldSize);
            tempValue += tempChar;
            if (fieldsCollection.at(i)->fieldDecimals != 0)
                {
                    tempValue += ",";
                    tempChar.setNum(fieldsCollection.at(i)->fieldDecimals);
                    tempValue += tempChar;
                }
            tempValue += ")";
            model->setHeaderData(i+1, Qt::Horizontal, tempValue);
        }
    view->setModel(model);

    refresh(0);

    current = view->currentIndex().row();
    QSqlRecord record = model->record(current);
    recordId = record.value(0).toString();
}

void QDbfEditor::writeSettings()
{
    QSettings settings;
    settings.setValue("dbfeditor/Size", size());
    settings.setValue("dbfeditor/edSize", editDialogSize);
}

void QDbfEditor::readSettings()
{
    QSettings settings;
    QSize size = settings.value("dbfeditor/Size", QSize(900, 600)).toSize();
    resize(size);
    editDialogSize = settings.value("dbfeditor/edSize", QSize(400,217)).toSize();
}
void QDbfEditor::filter(bool on)
{
    if (on)
    {
        DialogFilter *dlg = new DialogFilter(fieldsCollection,tr("Filter"),this);
        if (dlg->exec() == QDialog::Accepted) where = dlg->getWhere();
        else filterAction->setChecked(false);
        dlg->deleteLater();
    }
    else
    {
        filterAction->setChecked(false);
        where = "";
    }

    QString query;
    query = "SELECT * FROM ";
    query += tableName;
    if (where != "") query += " WHERE " + where;
    if (order != "") query += " ORDER BY " + order;

    qDebug() << query;
    model->setQuery(query, QSqlDatabase::database("dbfEditor"));
    if (model->lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), model->lastError().text());
            return;
        }

    refresh(0);

}
void QDbfEditor::editRecord()
{
    QModelIndexList currentSelection = view->selectionModel()->selectedIndexes();
    QModelIndex currentIndex = view->currentIndex();
    //int i;
    QDate tempDate;

    if (currentSelection.count() == 0)
        {
            QMessageBox::critical(this, tr("Error"), tr("Select at least a cell"));
            return;
        }

    int r = view->currentIndex().row();
    int c = view->currentIndex().column();

    QSqlRecord record = model->record(r);
    recordId = record.value(0).toString();

    QSqlQuery modelQuery = model->query();
    QString oldQuery = modelQuery.lastQuery();

    QSqlQuery getData(QSqlDatabase::database("dbfEditor"));
    QString query;

    QString editValue;
    QByteArray editByteArray;

    query = "SELECT ";
    query += ("`"+fieldsCollection.at(c-1)->fieldName+"`");

    query += " FROM ";
    query += tableName;
    query += " WHERE id_";
    query += tableName;
    query += "=";
    query += recordId;
    query += "";

    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), getData.lastError().text());
            return;
        }

    while (getData.next())
         {
                editByteArray =  getData.value(0).toByteArray();
                editValue =  getData.value(0).toString().simplified();
                tempDate = getData.value(0).toDate();
         }

    bool ok;

    if (fieldsCollection.at(c-1)->fieldType == "M")
        {
            /*
            0x02   FoxBASE
            0x03   FoxBASE+/Dbase III plus, no memo
            0x30   Visual FoxPro
            0x31   Visual FoxPro, autoincrement enabled
            0x32   Visual FoxPro with field type Varchar or Varbinary
            0x43   dBASE IV SQL table files, no memo
            0x63   dBASE IV SQL system files, no memo
            0x83   FoxBASE+/dBASE III PLUS, with memo
            0x8B   dBASE IV with memo
            0xCB   dBASE IV SQL table files, with memo
            0xF5   FoxPro 2.x (or earlier) with memo
            0xE5   HiPer-Six format with SMT memo file
            0xFB   FoxBASE
            */

            //0x83   FoxBASE+/dBASE III PLUS, with memo
            if ((dbfFileHeader[0] == '\x83'))
                readDbtFile(editValue.toInt(&ok,10));

            //0xF5   FoxPro 2.x (or earlier) with memo
            if (dbfFileHeader[0] == '\xF5')
                (editValue.toInt(&ok,10));
            /*
            0x30   Visual FoxPro
            0x31   Visual FoxPro, autoincrement enabled
            0x32   Visual FoxPro with field type Varchar or Varbinary
            */
            if ((dbfFileHeader[0] == '\x30') ||(dbfFileHeader[0] == '\x31') || (dbfFileHeader[0] == '\x32'))
                {
                    editByteArray = QByteArray::fromHex(editByteArray);
                    quint32 l = *(quint32 *)editByteArray.data();
                    readFptFile(l);
                }

            //0x8B   dBASE IV with memo
            if (dbfFileHeader[0] == '\x8B')
                readDbt4File(editValue.toInt(&ok,10));

            return;
        }

    QDbfDialog *d = new QDbfDialog(tr("Edit"), this);
    QSettings settings;

    d->resize(settings.value("dbfeditor/edsize", QSize(140,40)).toSize());
    d->setWindowIcon(QIcon(":images/edit.svg"));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QString labelText;
    QString tempValue;
    tempValue = "";

    labelText = "<b>";
    labelText += fieldsCollection.at(c-1)->fieldName;
    labelText += " ";
    labelText += fieldsCollection.at(c-1)->fieldType;
    labelText += "(";
    tempValue.setNum(fieldsCollection.at(c-1)->fieldSize);
    labelText += tempValue;
    if (fieldsCollection.at(c-1)->fieldDecimals != 0)
        {
            labelText += ",";
            tempValue.clear();
            tempValue.setNum(fieldsCollection.at(c-1)->fieldDecimals);
            labelText += tempValue;
        }
    labelText += ")</b>";

    QLabel *label = new QLabel(labelText, d);

    QDbfLineEdit *l;
    QDateTimeEdit *dte;
    QDateEdit *de;
    QString inputMaskFormat;
    QTime tempTime;
    quint32 l1;
    qint32 l2;
    qint64 l3;
    double db;
    quint8 tempByte;

    if (fieldsCollection.at(c-1)->fieldType == "C")
        {
            l = new QDbfLineEdit(editValue,d);
            l->setMaxLength(fieldsCollection.at(c-1)->fieldSize);
            l->selectAll();
        }
    else if (fieldsCollection.at(c-1)->fieldType == "L")
        {
            l = new QDbfLineEdit(editValue,d);
            l->setMaxLength(fieldsCollection.at(c-1)->fieldSize);
        }
    else if (fieldsCollection.at(c-1)->fieldType == "D")
        {

            de = new QDateEdit(tempDate, d);
            QFont font = de->font();
            font.setPointSize(font.pointSize() + 5);
            de->setFont(font);
            de->setCalendarPopup(true);
            de->setDisplayFormat("dd.MM.yyyy");
        }
    else if (fieldsCollection.at(c-1)->fieldType == "Y")
        {
            editByteArray = QByteArray::fromHex(editByteArray);

            l3 = *(qint64 *)editByteArray.data();

            db = l3;

            tempValue.setNum(db/10000,'f',4);

            l = new QDoubleLineEdit(tempValue,d);
            l->selectAll();
        }

    else if (fieldsCollection.at(c-1)->fieldType == "T")
        {
            editByteArray = QByteArray::fromHex(editByteArray);

            l1 = *(quint32 *)editByteArray.data();

            tempDate = QDate::fromJulianDay(l1);

            l1 = *(quint32 *)(editByteArray.data()+4);

            tempTime.setHMS(0,0,0);
            tempTime = tempTime.addMSecs(l1);

            QDateTime dt(tempDate,tempTime);

            dte = new QDateTimeEdit(dt,d);
            dte->setDisplayFormat("dd.MM.yyyy hh:mm:ss.zzz");
            QFont font = dte->font();
            font.setPointSize(font.pointSize() + 5);
            dte->setFont(font);
            dte->setCalendarPopup(true);
        }
    else if (fieldsCollection.at(c-1)->fieldType == "I")
        {
            editByteArray = QByteArray::fromHex(editByteArray);

            l2 = *(qint32 *)editByteArray.data();

            tempValue.setNum(l2, 10);

            l = new QDoubleLineEdit(tempValue,d);
            l->setMaxLength(fieldsCollection.at(c-1)->fieldSize);
            l->selectAll();
        }
    else if (fieldsCollection.at(c-1)->fieldType == "B")
        {
            editByteArray = QByteArray::fromHex(editByteArray);

            db = *(double *)editByteArray.data();

            tempValue.setNum(db);

            l = new QDoubleLineEdit(tempValue,d);
            l->selectAll();
        }
    else if ((fieldsCollection.at(c-1)->fieldType == "N") || (fieldsCollection.at(c-1)->fieldType == "F"))
        {
            l = new QDoubleLineEdit(editValue,d);
            l->setMaxLength(fieldsCollection.at(c-1)->fieldSize);
            l->selectAll();
        }
    else
        {
            QMessageBox::information(this, tr("Edit"), tr("Unsupported field (yet)"));
            return;
        }

    if (fieldsCollection.at(c-1)->fieldType == "T")
        {
            label->setBuddy(dte);
        }
    else if (fieldsCollection.at(c-1)->fieldType == "D")
        {
            label->setBuddy(de);
        }
    else
        {
            d->insertLineEditToVerify(l);
            label->setBuddy(l);
        }

    QPushButton *okButton = new QPushButton(QIcon(":images/ok.svg"),tr("OK"), d);
    QPushButton *cancelButton = new QPushButton(QIcon(":images/cancel.svg"),tr("Cancel"), d);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addWidget(label);
    if (fieldsCollection.at(c-1)->fieldType == "T")
        {
            mainLayout->addWidget(dte);
        }
    else if (fieldsCollection.at(c-1)->fieldType == "D")
        {
            mainLayout->addWidget(de);
        }
    else
        {
            mainLayout->addWidget(l);
        }

    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, SIGNAL(clicked()), d, SLOT(verifyDbfInputLines()));
    connect(cancelButton, SIGNAL(clicked()), d, SLOT(reject()));

    d->setLayout(mainLayout);

    if (d->exec())
       {
         if (d->result() == QDialog::Accepted)
            {
                if (fieldsCollection.at(c-1)->fieldType == "T")
                    {
                        modified = true;
                    }
                else if (fieldsCollection.at(c-1)->fieldType == "D")
                    {
                        modified = true;
                    }
                else
                    {
                        if (l->text() != editValue)
                            modified = true;
                    }

                query = "UPDATE ";
                query += tableName;
                query += " SET ";
                query += ("`"+fieldsCollection.at(c-1)->fieldName+"`");
                query += "='";
                if ((fieldsCollection.at(c-1)->fieldType == "N") || ((fieldsCollection.at(c-1)->fieldType == "F")))
                    {
                        db = l->text().toDouble(&ok);
                        tempValue.setNum(db,'f',fieldsCollection.at(c-1)->fieldDecimals);
                        query += tempValue;
                    }
                else if (fieldsCollection.at(c-1)->fieldType == "T")
                    {
                        editByteArray.clear();
                        l1 = dte->dateTime().date().toJulianDay();
                        tempByte = l1;
                        editByteArray.append(tempByte);
                        tempByte = l1 >> 8;
                        editByteArray.append(tempByte);
                        tempByte = l1 >> 16;
                        editByteArray.append(tempByte);
                        tempByte = l1 >> 24;
                        editByteArray.append(tempByte);

                        l1 = dte->dateTime().time().msecsTo(QTime(0,0,0));
                        l1 = l1*(-1);
                        tempByte = l1;
                        editByteArray.append(tempByte);
                        tempByte = l1 >> 8;
                        editByteArray.append(tempByte);
                        tempByte = l1 >> 16;
                        editByteArray.append(tempByte);
                        tempByte = l1 >> 24;
                        editByteArray.append(tempByte);

                        query += editByteArray.toHex().toUpper();
                    }
                else if (fieldsCollection.at(c-1)->fieldType == "D")
                    {
                        query+= de->date().toString("yyyy-MM-dd");
                    }
                else if (fieldsCollection.at(c-1)->fieldType == "I")
                    {
                        l2 = l->text().toLong(&ok, 10);

                        editByteArray.clear();
                        editByteArray = editByteArray.fromRawData((const char*)&l2,4);

                        query += editByteArray.toHex().toUpper();
                    }
                else if (fieldsCollection.at(c-1)->fieldType == "Y")
                    {
                        db = l->text().toDouble(&ok);
                        db = db*10000;
                        tempValue.setNum(db,'f',0);
                        l3 = tempValue.toLongLong(&ok, 10);

                        editByteArray.clear();
                        editByteArray = editByteArray.fromRawData((const char*)&l3,8);

                        query += editByteArray.toHex().toUpper();
                    }
                else if (fieldsCollection.at(c-1)->fieldType == "B")
                    {
                        db = l->text().toDouble(&ok);

                        editByteArray.clear();
                        editByteArray = editByteArray.fromRawData((const char*)&db,8);

                        query += editByteArray.toHex().toUpper();
                    }
                else
                    {
                        query += l->text();
                    }
                query += "' WHERE id_";
                query += tableName;
                query += "='";
                query += recordId;
                query += "'";

                getData.prepare(query);
                getData.exec();
                if (getData.lastError().isValid())
                    {
                        QMessageBox::critical(this, tr("Error"), getData.lastError().text());
                        return;
                    }

                model->setQuery(oldQuery, QSqlDatabase::database("dbfEditor"));
                if (model->lastError().isValid())
                    {
                        QMessageBox::critical(this, tr("Error"), model->lastError().text());
                        return;
                    }

                refresh(c);
                view->setCurrentIndex(currentIndex);

            }
        }
    settings.setValue("dbfeditor/edsize", d->size());

    delete d;
}

void QDbfEditor::insertRecord()
{
    QSqlQuery modelQuery = model->query();
    QString oldQuery = modelQuery.lastQuery();

    QSqlQuery getData(QSqlDatabase::database("dbfEditor"));
    QString query;
    int j;

    QStringList fieldTypes;

    bool ok = true;
    for (j = 0;j<fieldsCollection.count();j++)
        {
            fieldsItem = fieldsCollection.at(j);
            //if ((fieldsItem->fieldType == "M") && (fieldsItem->fieldSize == 4))
            //    ok = false;
            if (!fieldTypes.contains(fieldsItem->fieldType))
                fieldTypes.append(fieldsItem->fieldType);
        }

    if (fieldTypes.contains("0"))
        {
            ok = false;
        }

    if (!ok)
        {
            QMessageBox::information(this, tr("Insert"), tr("The file contains unsupported fields."));
            return;
        }

    query = "INSERT INTO ";
    query += tableName;
    query += " (";
    for (j=0; j<fieldsCollection.count(); ++j)
        {
        query += ("`"+fieldsCollection.at(j)->fieldName+"`");
            if (j<fieldsCollection.count()-1)
                query += ",";
        }
    query += ") VALUES (";

    QString tempValue;

    for (j=0; j<fieldsCollection.count(); j++)
        {
            fieldsItem = fieldsCollection.at(j);
            if (fieldsItem->fieldType == "D")
                {
                    query += "' '";
                }
            else if (fieldsItem->fieldType == "L")
                {
                    query += "'F'";
                }
            else if (fieldsItem->fieldType == "C")
                {
                    query += "' '";
                }
            else if (fieldsItem->fieldType == "N")
                {
                    query += "0";
                }
            else if ((fieldsItem->fieldType == "Y") ||
                     (fieldsItem->fieldType == "T") ||
                     (fieldsItem->fieldType == "B") ||
                     (fieldsItem->fieldType == "I") ||
                     (fieldsItem->fieldType == "G") ||
                     ((fieldsItem->fieldType == "M") && (fieldsItem->fieldSize == 4)))
                {
                    query += "'";
                    for (int i=0;i<fieldsItem->fieldSize;i++)
                        query += "00";
                    query += "'";
                }
            else
                {
                    query += "''";
                }

            if (j<fieldsCollection.count()-1)
                        query += ",";
        }

    query += ")";

    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), getData.lastError().text());
            return;
        }

    model->setQuery(oldQuery, QSqlDatabase::database("dbfEditor"));
    if (model->lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), model->lastError().text());
            return;
        }

    if (model->rowCount() == 0)
        emit modelIsEmpty(true);
    else
        emit modelIsEmpty(false);

    modified = true;
}

void QDbfEditor::deleteRecord()
{
    int current;

    QModelIndexList currentSelection = view->selectionModel()->selectedIndexes();

    if (currentSelection.count() == 0)
        {
            QMessageBox::critical(this, tr("Error"), tr("Select at least a row"));
            return;
        }

    QString ids;

    int i;
    int k;

    QList <int> rowCollection;

    ids = "(";

    for (i = 0; i < currentSelection.count(); i++)
        {
            current = currentSelection.at(i).row();
            if (!rowCollection.contains(current))
                    rowCollection.append(current);
        }

    for (i=0;i<rowCollection.count();i++)
        {
            QSqlRecord record = model->record(rowCollection.at(i));
            ids += record.value(0).toString();
            ids += ",";
        }

    k = ids.length();
    ids.truncate(k-1);
    ids += ")";

    QSqlQuery modelQuery = model->query();
    QString oldQuery = modelQuery.lastQuery();

    QSqlRecord record = model->record(current);

    recordId = record.value(0).toString();
    QString query;

    QSqlQuery getData(QSqlDatabase::database("dbfEditor"));

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete current row"),tr("<center><h1><font color='red'>Warning !</font></h1>"
                                                                "<h3>You are about to delete the current record</h3>"
                                                                "<h2>Are you sure?</h2></center>"),
                                     QMessageBox::Yes | QMessageBox::No );
    if (reply == QMessageBox::Yes)
        {
            query = "DELETE FROM ";
            query += tableName;
            query += " WHERE id_";
            query += tableName;
            query += " IN ";
            query += ids;

            getData.prepare(query);
            getData.exec();
            if (getData.lastError().isValid())
                {
                    QMessageBox::critical(this, tr("Eroare"), getData.lastError().text());
                    return;
                }

            model->setQuery(oldQuery, QSqlDatabase::database("dbfEditor"));
            if (model->lastError().isValid())
                {
                    QMessageBox::critical(this, tr("Eroare"), model->lastError().text());
                    return;
                }

            if (model->rowCount() != 0)
                {
                    current--;
                }

            refresh(current);
            QSqlRecord record = model->record(current);
            recordId = record.value(0).toString();

            modified = true;
        }

    if (model->rowCount() == 0)
        emit modelIsEmpty(true);
    else
        emit modelIsEmpty(false);
}

void QDbfEditor::openNewFile()
{
    // Временная мера. Пока не сделан рефактоинг кода.
    if (modified)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, tr("Save"),tr("<center><h2>Do you want to save the changes?</h2></center>"),
                                      QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes );
        if (reply == QMessageBox::Yes)
        {
            saveDbfFile();
        }
    }
    QString currentDirectory;
    QSettings settings;
    currentDirectory= settings.value("dbfeditor/currentdir", "./").toString();

    dbfFileName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"),currentDirectory,"DBF Files(*.dbf);;All Files (*)");
    if (dbfFileName.isEmpty())
        {
            return;
        }

    QFileInfo fileInfo(dbfFileName);
    currentDirectory = fileInfo.absolutePath();
    settings.setValue("dbfeditor/currentdir", currentDirectory);
    openFile(dbfFileName,true);
}

void QDbfEditor::openDbfFile()
{
    /*
    DBF File Header
    Byte offset 	Description
    0                   File type:
                        0x02   FoxBASE
                        0x03   FoxBASE+/Dbase III plus, no memo
                        0x30   Visual FoxPro
                        0x31   Visual FoxPro, autoincrement enabled
                        0x32   Visual FoxPro with field type Varchar or Varbinary
                        0x43   dBASE IV SQL table files, no memo
                        0x63   dBASE IV SQL system files, no memo
                        0x83   FoxBASE+/dBASE III PLUS, with memo
                        0x8B   dBASE IV with memo
                        0xCB   dBASE IV SQL table files, with memo
                        0xF5   FoxPro 2.x (or earlier) with memo
                        0xE5   HiPer-Six format with SMT memo file
                        0xFB   FoxBASE

    1 - 3               Last update (YYMMDD)
    4 – 7               Number of records in file
    8 – 9               Position of first data record
    10 – 11             Length of one data record, including delete flag
    12 – 27             Reserved
    28                  Table flags:
                        0x01   file has a structural .cdx
                        0x02   file has a Memo field
                        0x04   file is a database (.dbc)

                        This byte can contain the sum of any of the above values.
                        For example, the value 0x03 indicates the table has a structural .cdx and a Memo field.

    29                  Code page mark
    30 – 31             Reserved, contains 0x00
    32 – n              Field subrecords
                        The number of fields determines the number of field subrecords.
                        One field subrecord exists for each field in the table.
    n+1                 Header record terminator (0x0D)
    n+2 to n+264 	A 263-byte range that contains the backlink, which is the relative path of an
                        associated database (.dbc) file, information. If the first byte is 0x00, the
                        file is not associated with a database. Therefore, database files always contain 0x00.

    Field Subrecords Structure

    Byte offset 	Description
    0 – 10              Field name with a maximum of 10 characters. If less than 10, it is padded with null characters (0x00).
    11                  Field type:
                        C   –   Character
                                255 bytes ASCII
                        Y   –   Currency
                                8 bytes 64 bit integer, allways 4 decimal points
                        N   –   Numeric
                        F   –   Float
                                Same as numeric 1 to 20 bytes in table
                        D   –   Date
                                yyyymmdd
                        T   –   DateTime
                                It's stored as an 8 byte field.
                                The first 4 bytes stores the date as julian day number.
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

    12 – 15             Displacement of field in record
    16                  Length of field (in bytes)
    17                  Number of decimal places
    18                  Field flags:
                        0x01   System Column (not visible to user)
                        0x02   Column can store null values
                        0x04   Binary column (for CHAR and MEMO only)
                        0x06   (0x02+0x04) When a field is NULL and binary (Integer, Currency, and Character/Memo fields)
                        0x0C   Column is autoincrementing
    19 - 22             Value of autoincrement Next value
    23                  Value of autoincrement Step value
    24 – 31             Reserved
    */

    QString query;
    QFile file;
    QByteArray fieldDescription;
    int i;
    int j;
    unsigned char a,b,c,d,e,f,g,h;
    double db;

    tableName = "d_table";
    strTableName = "s_table";
    file.setFileName(dbfFileName);

    if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("DBF open error"));
            return;
        }
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(generalTextCodec.toAscii().data()));

    sizesHeader.clear();

    sizesHeader = file.read(16);

    a = sizesHeader.at(4);
    b = sizesHeader.at(5);
    c = sizesHeader.at(6);
    d = sizesHeader.at(7);
    e = sizesHeader.at(8);
    f = sizesHeader.at(9);
    g = sizesHeader.at(10);
    h = sizesHeader.at(11);

    numberOfRecords = a + (b << 8) + (c << 16) + (d << 24);
    headerLength = e + (f << 8);
    recordLength = g + (h << 8);

    file.seek(0);
    dbfFileHeader = file.read(headerLength);

    file.seek(32);
    fieldDescriptions.clear();
    fieldDescriptions = file.read(headerLength - 32);
    fieldDescriptions.truncate(fieldDescriptions.lastIndexOf('\x0D'));

    numberOfFields = fieldDescriptions.count() >> 5;

    qint16 tempOffset = 1;

    for (i=0;i<numberOfFields;i++)
        {
            fieldDescription = fieldDescriptions.mid(i*32,32);
            fieldsItem = new QFieldsItem;
            fieldsItem->fieldName = "";
            j = 0;
            while (fieldDescription[j] != '\x00')
                {
                    fieldsItem->fieldName += fieldDescription[j];
                    j++;
                }

            a = fieldDescription.at(12);
            b = fieldDescription.at(13);
            c = fieldDescription.at(14);
            d = fieldDescription.at(15);
            e = fieldDescription.at(16);
            f = fieldDescription.at(17);

            fieldsItem->fieldType = fieldDescription[11];
            fieldsItem->fieldOffset = a + (b << 8) + (c << 16) + (d << 24);

            fieldsItem->fieldOffset = tempOffset;

            tempOffset += e;

            fieldsItem->fieldSize = e;
            fieldsItem->fieldDecimals = f;
            fieldsCollection.append(fieldsItem);


        }

    QSqlQuery getData(QSqlDatabase::database("dbfEditor"));

    query = "DROP TABLE IF EXISTS '";
    query += tableName;
    query += "'";
    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), getData.lastError().text());
            return;
        }

    QString tempValue;

    query = "CREATE TABLE '";
    query += tableName;
    query += "' ( 'id_";
    query += tableName;
    query += "' integer primary key autoincrement,";
    for (i=0; i<fieldsCollection.count(); ++i)
        {
            query += ("`"+fieldsCollection.at(i)->fieldName+"`");

            if (fieldsCollection.at(i)->fieldType == "C")
                {
                    query += " text";
                }
            else if (fieldsCollection.at(i)->fieldType == "L")
                {
                    query += " text";
                }
            else if (fieldsCollection.at(i)->fieldType == "M")
                {
                    if (fieldsCollection.at(i)->fieldSize == 10)
                        {
                            query += " numeric";
                        }
                    if (fieldsCollection.at(i)->fieldSize == 4)
                        {
                            query += " blob";
                        }

                }
            else if (fieldsCollection.at(i)->fieldType == "N")
                {
                    query += " text";
                }
            else if (fieldsCollection.at(i)->fieldType == "F")
                {
                    query += " text";
                }
            else if (fieldsCollection.at(i)->fieldType == "D")
                {
                    query += " text";
                }
            else
                {
                    query += " blob";
                }

            if (i<(fieldsCollection.count()-1))
                query += ",\n";
        }
    query += ")";
    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), getData.lastError().text());
            return;
        }
    quint32 q;
    bool ok;
    for (q=0;q<numberOfRecords;q++)
        {
            query = "INSERT INTO ";
            query += tableName;
            query += " (";
            for (j=0; j<fieldsCollection.count(); ++j)
                {
                query += ("`"+fieldsCollection.at(j)->fieldName+"`");

                    if (j<fieldsCollection.count()-1)
                        query += ",";
                }
            query += ") VALUES (";

            recordData.clear();
            file.seek(headerLength + q*recordLength);
            recordData=file.read(recordLength);
            if (recordData.at(0) == '*')
                continue;

            QString tempDate;
            QString tempString;

            for (j=0; j<fieldsCollection.count(); j++)
                {
                    fieldsItem = fieldsCollection.at(j);
                    fieldsItem->fields = "'";
                    if (fieldsItem->fieldType == "D")
                        {
                            tempDate = recordData.mid(fieldsItem->fieldOffset,fieldsItem->fieldSize);
                            if (tempDate == "        ")
                                fieldsItem->fields+="";
                            else
                                {
                                    fieldsItem->fields += tempDate.mid(0,4);
                                    fieldsItem->fields += "-";
                                    fieldsItem->fields += tempDate.mid(4,2);
                                    fieldsItem->fields += "-";
                                    fieldsItem->fields += tempDate.mid(6,2);
                                }
                        }
                    else if (fieldsItem->fieldType == "C")
                        {
                            tempString = recordData.mid(fieldsItem->fieldOffset,fieldsItem->fieldSize);
                            fieldsItem->fields += tempString.replace("'","''");
                        }
                    else if ((fieldsItem->fieldType == "N") || (fieldsItem->fieldType == "F"))
                        {
                            tempString = recordData.mid(fieldsItem->fieldOffset,fieldsItem->fieldSize);
                            db = tempString.toDouble(&ok);
                            tempString.setNum(db,'f',fieldsItem->fieldDecimals);
                            fieldsItem->fields += tempString;
                        }
                    else if (fieldsItem->fieldType == "L")
                        {
                            tempString = recordData.mid(fieldsItem->fieldOffset,fieldsItem->fieldSize);
                            fieldsItem->fields += tempString;
                        }
                    else if ((fieldsItem->fieldType == "M") && (fieldsItem->fieldSize == 10))
                        {
                            tempString = recordData.mid(fieldsItem->fieldOffset,fieldsItem->fieldSize);
                            fieldsItem->fields += tempString;
                        }
                    else
                        {
                            tempString = recordData.mid(fieldsItem->fieldOffset,fieldsItem->fieldSize).toHex().toUpper();
                            fieldsItem->fields += tempString;
                        }
                    fieldsItem->fields += "'";

                    query += fieldsItem->fields;

                    if (j<fieldsCollection.count()-1)
                        query += ",";
                }
            query += ")";

            getData.prepare(query);
            getData.exec();
            if (getData.lastError().isValid())
                {
                    QMessageBox::critical(this, tr("Error"), getData.lastError().text());
                    return;
                }
        }

    query = "DROP TABLE IF EXISTS ";
    query += strTableName;

    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), getData.lastError().text());
            return;
        }

    query = "CREATE TABLE ";
    query += strTableName;
    query += " ( id_";
    query += strTableName;
    query += " integer primary key autoincrement, \n";
    query += "fieldName text, \n";
    query += "fieldType text, \n";
    query += "fieldLength numeric, \n";
    query += "fieldDecimals numeric)";

    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), getData.lastError().text());
            return;
        }

    for (i=0; i<fieldsCollection.count(); i++)
        {
            query = "INSERT INTO ";
            query += strTableName;
            query += " (fieldName, fieldType, fieldLength, fieldDecimals) VALUES ('";
            query += ("`"+fieldsCollection.at(i)->fieldName+"`");
            query += "','";
            query += fieldsCollection.at(i)->fieldType;
            query += "','";
            tempValue.setNum(fieldsCollection.at(i)->fieldSize,10);
            query += tempValue;
            query += "','";
            tempValue.setNum(fieldsCollection.at(i)->fieldDecimals,10);
            query += tempValue;
            query += "')";

            getData.prepare(query);
            getData.exec();
            if (getData.lastError().isValid())
                {
                    QMessageBox::critical(this, tr("Error"), getData.lastError().text());
                    return;
                }
        }

    file.close();
}

void QDbfEditor::saveDbfFile()
{
    qint32 nr;
    QSqlQuery getData(QSqlDatabase::database("dbfEditor"));
    QString query;
    bool ok;
    int i;

    nr = 0;

    query = "SELECT count(*) FROM ";
    query += tableName;

    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), getData.lastError().text());
            return;
        }

    while (getData.next())
            nr = getData.value(0).toString().toULong(&ok, 10);

    qint16 lnrt = nr;
    qint16 hnrt = nr >> 16;

    qint8 llnrt = lnrt ;
    qint8 hlnrt = lnrt >> 8;
    qint8 lhnrt = hnrt;
    qint8 hhnrt = hnrt >> 8;

    dbfFileHeader[4]= llnrt;
    dbfFileHeader[5]= hlnrt;
    dbfFileHeader[6]= lhnrt;
    dbfFileHeader[7]= hhnrt;

    QFile dbfFile;

    dbfFile.setFileName(dbfFileName+".temp");

    if (!dbfFile.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(0, tr("Error"), tr("DBF write error"));
            return;
        }

    dbfFile.write(dbfFileHeader);

    QString tempValue;
    QTextStream textStream(&tempValue);

    query = "SELECT ";
    for (i=0;i<fieldsCollection.size();i++)
        {
            fieldsItem = fieldsCollection.at(i);
            query += ("`"+fieldsItem->fieldName+"`");
            if ( i != fieldsCollection.size()-1 )
                    query += ",";
            else
                    query += " ";
        }

    query += " FROM ";
    query += tableName;

    getData.prepare(query);
    getData.exec();
    if (getData.lastError().isValid())
        {
            QMessageBox::critical(0, tr("Error"), getData.lastError().text());
            return;
        }

    int l,l1,j;
    QString tempNumericValue;
    QDate tempDateValue;
    QString tempCharValue;
    QByteArray tempBinaryValue;
    while (getData.next())
        {
            recordData.clear();
            recordData.append(QChar(' '));

            for (i=0;i<fieldsCollection.size();i++)
                {
                    if ((fieldsCollection.at(i)->fieldType == "C") || (fieldsCollection.at(i)->fieldType == "L"))
                        {
                            tempCharValue = getData.value(i).toString();
                            tempValue = "";
                            l = fieldsCollection.at(i)->fieldSize;
                            l1 = tempCharValue.length();
                            tempCharValue.truncate(l);

                            tempValue = tempCharValue;

                            for (j=0;j<l-l1;j++)
                                tempValue+=" ";
                            recordData.append(tempValue);
                        }
                    else if ((fieldsCollection.at(i)->fieldType == "N") ||
                             (fieldsCollection.at(i)->fieldType == "F") ||
                             ((fieldsCollection.at(i)->fieldType == "M") && (fieldsCollection.at(i)->fieldSize == 10)))
                        {
                            tempNumericValue = getData.value(i).toString().simplified();
                            tempValue = "";
                            l = fieldsCollection.at(i)->fieldSize;
                            l1 = tempNumericValue.length();
                            tempNumericValue.truncate(l);

                            for (j=0;j<l-l1;j++)
                                tempValue+=" ";

                            tempValue += tempNumericValue;

                            recordData.append(tempValue);
                        }
                    else if (fieldsCollection.at(i)->fieldType == "D")
                        {
                            tempDateValue = getData.value(i).toDate();
                            if (tempDateValue.isNull())
                                tempValue = "        ";
                            else
                                tempValue = tempDateValue.toString("yyyyMMdd");

                            recordData.append(tempValue);
                        }
                    else
                        {
                            tempBinaryValue = getData.value(i).toByteArray();
                            tempBinaryValue = tempBinaryValue.fromHex(tempBinaryValue);

                            recordData.append(tempBinaryValue);
                        }
                }

            dbfFile.write(recordData);
        }

    recordData.clear();
    recordData.append('\x1A');

    dbfFile.write(recordData);

    dbfFile.close();
    QFile oldFile;
    oldFile.setFileName(dbfFileName);
    oldFile.remove();
    dbfFile.rename(dbfFileName);
    modified = false;
}

void QDbfEditor::fillCells()
{
    QSqlQuery modelQuery = model->query();
    QString oldQuery = modelQuery.lastQuery();

    QSqlQuery getData(QSqlDatabase::database("dbfEditor"));
    QString query;

    QModelIndexList currentSelection = view->selectionModel()->selectedIndexes();
    QModelIndexList currentRowSelection = view->selectionModel()->selectedRows();
    QModelIndexList currentColumnSelection = view->selectionModel()->selectedColumns();

    if (currentSelection.count() == 0)
        {
            QMessageBox::critical(this, tr("Error"), tr("Select at least a cell"));
            return;
        }

    QDbfDialog *d = new QDbfDialog(tr("Fill"), this);
    QSettings settings;

    d->resize(settings.value("dbfeditor/filledsize", QSize(140,40)).toSize());
    d->setWindowIcon(QIcon(":images/fill.svg"));

    QString sql = settings.value("dbfeditor/fillcommand", "").toString();

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QString labelText;
    QLabel *label = new QLabel(tr("Fill value or expression"), d);

    QDbfLineEdit *t = new QDbfLineEdit(sql,d);
    label->setBuddy(t);

    QPushButton *okButton = new QPushButton(QIcon(":images/ok.svg"),tr("OK"), d);
    QPushButton *cancelButton = new QPushButton(QIcon(":images/cancel.svg"),tr("Cancel"), d);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addWidget(label);
    mainLayout->addWidget(t);
    mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, SIGNAL(clicked()), d, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), d, SLOT(reject()));

    d->setLayout(mainLayout);
    int i;

    if (d->exec())
       {
         if (d->result() == QDialog::Accepted)
            {
                for (i=0;i<currentSelection.count();i++)
                    {
                        if (currentSelection.at(i).column() == 0)
                            continue;
                        fieldsItem = fieldsCollection.at(currentSelection.at(i).column()-1);

                        if ((fieldsItem->fieldType == "M") ||
                            (fieldsItem->fieldType == "Y") ||
                            (fieldsItem->fieldType == "T") ||
                            (fieldsItem->fieldType == "B") ||
                            (fieldsItem->fieldType == "I") ||
                            (fieldsItem->fieldType == "G"))
                            continue;

                        query = "UPDATE ";
                        query += tableName;
                        query += " SET ";

                        query += ("`"+fieldsItem->fieldName+"`");

                        query += "=";

                        query += t->text().simplified();

                        QSqlRecord record = model->record(currentSelection.at(i).row());

                        query += " WHERE id_";
                        query += tableName;
                        query += "=";
                        query += record.value(0).toString();

                        getData.prepare(query);
                        getData.exec();

                        if (getData.lastError().isValid())
                            {
                                QMessageBox::critical(this, tr("Error"), getData.lastError().text());
                                return;
                            }
                    }

                model->setQuery(oldQuery, QSqlDatabase::database("dbfEditor"));
                if (model->lastError().isValid())
                    {
                        QMessageBox::critical(this, tr("Error"), model->lastError().text());
                        return;
                    }

                refresh(1);
                view->selectRow(0);
                modified = true;
            }
        }

    settings.setValue("dbfeditor/fillcommand", t->text().simplified());
    settings.setValue("dbfeditor/filledsize", d->size());

    delete d;

}

void QDbfEditor::refresh(int current)
{
    view->hideColumn(0);
    view->setAlternatingRowColors(true);
    view->resizeColumnsToContents();
    view->selectColumn(0);
    view->selectRow(current);
}


void QDbfEditor::closeEvent(QCloseEvent *event)
{
    if (modified)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, tr("Save"),tr("<center><h2>Do you want to save the changes?</h2></center>"),
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes );
            if (reply == QMessageBox::Yes)
                {
                    saveDbfFile();
                }
        }
    writeSettings();
    event->accept();
}

void QDbfEditor::readDbtFile(int i)
{
    /*
        dBASE III+
        _______________________  _______
     0 | Number of next        |  ^  ^
     1 | available block       |  |  |
     2 | for appending data    |  | Header
     3 | (binary)              |  |  |
       |-----------------------| _|__v__
     4 | ( Reserved )          |  |
       |                       |  |
       |                       |  |
     7 |                       |  |
       |-----------------------|  |
     8 | ( Reserved )          |  |
       :                       :  |
    15 |                       |  |
       |-----------------------|  |
    16 | Version no.  (03h)    |  |
       |-----------------------|  |
    17 | (i.e. garbage)        |  |
       :                       : First block
       :                       :  |
    511|                       |  |
       |=======================| _v_____
    512|                       |  ^
       |                       |  |
       |                       | 512 Bytes
       |                       | text blocks
       :                       :  |
       :                       :  |
       |                       |  |
       |-----------------------| _|_____
       | Field terminator (1Ah)|  |  ^
       |-----------------------|  |  |Terminating field
       | Field terminator (1Ah)|  |  |within the block *1
       |-----------------------| _|__v__
       : ( Unused )            :  |
    1023                       :  |
       |=======================| _v_____
       |                       |  ^
       |                       |  |
       |                       | 512 Bytes
       |                       | text blocks
       :                       :  |
       :                       :  |
       |                       |  |
       |                       | _v_____
       |=======================|

        *1 - field terminator Is reported to use only one field terminator (1Ah) - (FoxPro, Fox??)
    */

    QByteArray memoData;
    QString dbtFileName = dbfFileName;

    int k = dbtFileName.length();
    dbtFileName.truncate(k-1);
    dbtFileName += "t";

    QFile file;

    file.setFileName(dbtFileName);
    if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("DBT open error"));
            return;
        }

    file.seek(i << 9);
    memoData = file.read(512);

    int p = memoData.indexOf('\x1A');
    int q=1;
    while (p == -1)
        {
            file.seek((i+q) << 9);
            memoData.append(file.read(512));
            p = memoData.indexOf('\x1A');
            q++;
        }

    if (p==-1)
        p=0;

    memoData.truncate(p);

    //QString memoText = QString(memoData).toAscii();

    //QByteArray encodedString = "...";
    QTextCodec *codec = QTextCodec::codecForName("IBM850");
    QString memoText = codec->toUnicode(memoData);

    QDbfDialog *dialog = new QDbfDialog(tr("Memo data"), this);
    QSettings settings;

    dialog->resize(settings.value("dbfeditor/memoedsize", QSize(880,560)).toSize());
    dialog->setWindowIcon(QIcon(":images/edit.svg"));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QString labelText;
    QLabel *label = new QLabel(tr("The text from the memo file"), dialog);

    //QPlainTextEdit *t = new QPlainTextEdit(memoText,dialog);
    QTextEdit *t = new QTextEdit(dialog);
    t->setPlainText(memoText);
    t->setReadOnly(true);
    t->setWordWrapMode(QTextOption::NoWrap);
    label->setBuddy(t);

    QFont font=t->font();
#ifdef UNIX
    font.setFamily("Monospace");
#else
    font.setFamily("Lucida Console");
#endif
    font.setItalic(false);
    t->setFont(font);

    QPushButton *closeButton = new QPushButton(QIcon(":images/ok.svg"),tr("Close"), dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(closeButton);

    mainLayout->addWidget(label);
    mainLayout->addWidget(t);
    //mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    connect(closeButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    dialog->setLayout(mainLayout);

    dialog->exec();

    settings.setValue("dbfeditor/memoedsize", dialog->size());

    delete dialog;

}

void QDbfEditor::readFptFile(int i)
{
    /*
        Xbase: FoxPro Object and Memo Field Files (*.fpt)
        The file format is used by Fox Pro 2.x and later The size of the header is 512 bytes

           _______________________  _______
        00h /   0 | Number of next        |  ^
        00h /   1 | available block       |  |
        00h /   2 | for appending data    | Header
        00h /   3 | (binary)            *1|  |
                  |-----------------------|  |
        00h /   4 | ( Reserved )          |  |
        00h /   5 |                       |  |
                  |-----------------------|  |
        00h /   6 | Size of blocks N    *1|  |
        00h /   7 |                     *2|  |
                  |-----------------------|  |
        00h /   8 | ( Reserved )          |  |
                  |                       |  |
                  |                       |  |
                  | (i.e. garbage)        |  |
                  :                       :  |
                  :                       :  |
        00h /  511|                       |  |
                  |=======================| _v_____
        00h /    0|                       |  ^                 Used block
                  |                       |  |           __  |=======================|
                  |                       |  |          /   0| Record type         *3|
                  :                       :  |         /    1|                     *1|
                  :                       :  |        /     2|                       |
                  |                       |  |       /      3|                       |
        00h /    N|                       |  |      /        |-----------------------|
                  |=======================| _|_____/        4| Length of memo field  |
        00h /    0|                       |  |              5|                     *1|
                  :                       :  |              6|                       |
                  :                       :  |              7|                       |
                  |                       |  |               |-----------------------|
        00h /    N|                       | _|_____         8| Memo data             |
                  |=======================|  |     \         :                       :
                 0|                       |  |      \       N|                       |
                  |                       |  |       \_____  |=======================|
                  |                       |  |
                  :                       :  |
        00h /    N|                       | _v_____
                  |=======================|

           *1. Big-endian. Binary value with high byte first.
           *2. Size of blocks in memo file (SET BLOCKSIZE). Default is 512 bytes.
           *3. Record type
              Value 	Description
              00h 	Picture. This normally indicates that file is produced on a MacIntosh,
                        since pictures on the DOS/Windows platform are "objects".
              01h 	Memo
              02h 	Object
    */

    QByteArray memoData;
    QString dbtFileName = dbfFileName;
    unsigned char a,b,c,d;
    quint32 tipMemo;
    quint32 lengthMemo;
    quint32 memoBlockLength;

    int k = dbtFileName.length();
    dbtFileName.truncate(k-3);
    if (dbfFileName.endsWith(".dbf"))
        dbtFileName += "fpt";
    if (dbfFileName.endsWith(".DBF"))
        dbtFileName += "FPT";

    QFile file;

    file.setFileName(dbtFileName);
    if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("FPT open error"));
            return;
        }

    file.seek(0);
    memoData = file.read(8);

    a = memoData.at(7);
    b = memoData.at(6);
    c = memoData.at(5);
    d = memoData.at(4);

    memoBlockLength = a + (b << 8) + (c << 16) + (d << 24);

    file.seek(i*memoBlockLength);
    memoData = file.read(8);

    a = memoData.at(3);
    b = memoData.at(2);
    c = memoData.at(1);
    d = memoData.at(0);

    tipMemo = a + (b << 8) + (c << 16) + (d << 24);

    a = memoData.at(7);
    b = memoData.at(6);
    c = memoData.at(5);
    d = memoData.at(4);

    lengthMemo = a + (b << 8) + (c << 16) + (d << 24);

    file.seek(i*memoBlockLength+8);
    memoData = file.read(lengthMemo);

    QString memoText = QString(memoData);

    QDbfDialog *dialog = new QDbfDialog(tr("Memo data"), this);
    QSettings settings;

    dialog->resize(settings.value("dbfeditor/memoedsize", QSize(880,560)).toSize());
    dialog->setWindowIcon(QIcon(":images/edit.svg"));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QString labelText;
    QLabel *label = new QLabel(tr("The text from the memo file"), dialog);

    QPlainTextEdit *t = new QPlainTextEdit(memoText,dialog);
    t->setReadOnly(true);
    label->setBuddy(t);

    QFont font=t->font();
#ifdef UNIX
    font.setFamily("Monospace");
#else
    font.setFamily("Lucida Console");
#endif
    font.setItalic(false);
    t->setFont(font);

    QPushButton *closeButton = new QPushButton(QIcon(":images/ok.svg"),tr("Close"), dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(closeButton);

    mainLayout->addWidget(label);
    mainLayout->addWidget(t);
    //mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    connect(closeButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    dialog->setLayout(mainLayout);

    dialog->exec();

    settings.setValue("dbfeditor/memoedsize", dialog->size());

    delete dialog;

}

void QDbfEditor::readDbt4File(int i)
{
    /*
    dBASE IV

        _______________________
     0 | Number of next        |  ^
     1 | available block       |  |
     2 | for appending data    | Header
     3 | (binary)              |  |
       |-----------------------|  |
     4 | ( Reserved )          |  |
       | Size of blocks      *1|  |
       |                       |  |
     7 |                       |  |
       |-----------------------|  |
     8 | DBF file name         |  |
       | without extention     |  |
       :                       :  |
    15 |                       |  |
       |-----------------------|  |
    16 | Reserved   (00h)      |  |
       |-----------------------|  |
    17 | ( Reserved )          |  |
    18 |                       |  |
    19 |                       |  |
       |-----------------------|  |
    20 | Block length in bytes |  |
    21 |                     *4|  |
       |-----------------------|  |
    22 | ( Reserved )          |  |
       |                       |  |
       | (i.e. garbage)        |  |
       :                       :  |
       :                       :  |
    511|                       |  |
       |=======================| _v_____
      1|                       |  ^                 Used block
       |                       |  ^           __  |=======================|
       |                       |  |          /   0| ( Reserved )          |
       :                       :  |         /    1|                       |
       :                       :  |        /     2|  FFh FFh 08h 00h      |
       |                       |  |       /      3|                       |
    511|                       |  |      /        |-----------------------|
       |=======================| _|_____/        4| Length of memo field  |
      1|                       |  |              5|                       |
       :                       :  |              6|                       |
       :                       :  |              7|                       |
       |                       |  |               |-----------------------|
    511|                       | _|_____         8| Memo data           *2|
       |=======================|  |     \         :                       :
       |                       |  |      \       N|                       |
       |                       |  |       \_____  |=======================|
       |                       |  |
       |                       | 512 Bytes
       |                       | text blocks
       :                       :  |
       :                       :  |                 Unused block
       :                       :  |           __  |=======================|
       :                       :  |          /   0| Pointer to next free  |
       :                       :  |         /    1| block                 |
       :                       :  |        /     2|                       |
       |                       |  |       /      3|                       |
    511|                       |  |      /        |-----------------------|
       |=======================| _|_____/        4| Pointer to next used  |
      1|                       |  |              5| block                 |
       :                       :  |              6|                       |
       :                       :  |              7|                       |
       |                       |  |               |-----------------------|
    511|                       | _|_____         8| ( Reserved )          |
       |=======================|  |     \         :                       :
      1|                       |  |      \       N|                       |
       |                       |  |       \_____  |=======================|
       |                       |  |
       :                       :  |
       |                       |  |
       |-----------------------| _|_____
       | Field terminator (1Ah)|  |  ^
       |-----------------------|  |  |Terminating field
       | Field terminator (1Ah)|  |  |within the block *3
       |-----------------------| _|__v__
       : ( Unused )            :  |
    511|                       :  |
       |=======================| _v_____
       |                       |  ^
       |                       |  |
       |                       | 512 Bytes
       |                       | text blocks
       :                       :  |
       :                       :  |
       |                       |  |
       |                       | _v_____
       |=======================|

       *1. Size of blocks in memo file (SET BLOCKSIZE). Default is 512 bytes (FoxBase, dBASE IV ??) .
       *2. End of text mark is 0Dh 0Ah and line breaks are 8Dh 0Ah
       *3. Field terminator Is reported to use only one field terminator (1Ah) - (FoxPro, Fox??).
       *4. dBASE III files are marked as lenght = 1.
    */

    QByteArray memoData;
    QString dbtFileName = dbfFileName;
    unsigned char a,b;
    //quint32 tipMemo;
    quint32 lengthMemo;
    //quint32 memoBlockLength;
    quint16 lengthInBlocks;

    int k = dbtFileName.length();
    dbtFileName.truncate(k-3);
    dbtFileName += "dbt";

    QFile file;

    file.setFileName(dbtFileName);
    if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("DBT open error"));
            return;
        }

    file.seek(0);
    memoData = file.read(512);

    a = memoData.at(21);
    b = memoData.at(20);

    lengthInBlocks = a + (b << 8);

    //file.seek(i*512*lengthInBlocks);
    file.seek(i*512);
    memoData = file.read(8);

    a = memoData.at(4);
    lengthMemo = a;

    //file.seek(i*512*lengthInBlocks+8);
    file.seek(i*512+8);
    memoData = file.read(lengthMemo-8);

    QString memoText = QString(memoData);

    QDbfDialog *dialog = new QDbfDialog(tr("Memo data"), this);
    QSettings settings;

    dialog->resize(settings.value("dbfeditor/memoedsize", QSize(880,560)).toSize());
    dialog->setWindowIcon(QIcon(":images/edit.svg"));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QString labelText;
    QLabel *label = new QLabel(tr("The text from the memo file"), dialog);

    QPlainTextEdit *t = new QPlainTextEdit(memoText,dialog);
    t->setReadOnly(true);
    label->setBuddy(t);

    QFont font=t->font();
#ifdef UNIX
    font.setFamily("Monospace");
#else
    font.setFamily("Lucida Console");
#endif
    font.setItalic(false);
    t->setFont(font);

    QPushButton *closeButton = new QPushButton(QIcon(":images/ok.svg"),tr("Close"), dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(closeButton);

    mainLayout->addWidget(label);
    mainLayout->addWidget(t);
    //mainLayout->addStretch(1);
    mainLayout->addLayout(buttonLayout);

    connect(closeButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    dialog->setLayout(mainLayout);

    dialog->exec();

    settings.setValue("dbfeditor/memoedsize", dialog->size());

    delete dialog;

}

void QDbfEditor::helpDbf()
{
    QDbfDialog *dialog = new QDbfDialog(tr("qtDbf documentation"), this);
    QSettings settings;

    dialog->resize(settings.value("dbfeditor/helpsize", QSize(860,540)).toSize());
    dialog->setWindowIcon(QIcon(":images/help.svg"));

    QString dbfLocal = settings.value("dbflocal", "en").toString();

    QVBoxLayout *mainLayout = new QVBoxLayout;

//    QString helpText;

    QString dbfDirPath;
/**/
#if (defined Q_OS_UNIX) || (defined Q_OS_OS2)
    if (QFile::exists("/usr/local/share/qtdbf/help"))
    {
        dbfDirPath = "/usr/local/share/qtdbf/help";
    }
    else
    {
        if (QFile::exists("/usr/share/qtdbf/help"))
        {
            dbfDirPath = "/usr/share/qtdbf/help";
        }
        else
        {
            dbfDirPath = qApp->applicationDirPath();
        }
    }
#else
    dbfDirPath = qApp->applicationDirPath();
#endif
    dbfDirPath += "/qtdbf_";
    dbfDirPath += dbfLocal;
    dbfDirPath += ".html";
    QFile f(dbfDirPath);
    QTextEdit *t = new QTextEdit(this);
    t->setReadOnly(true);
    if (f.open(QIODevice::ReadOnly))
    {
        QByteArray data = f.readAll();
        QTextCodec *codec = Qt::codecForHtml(data);
        QString str = codec->toUnicode(data);
        t->setHtml(str);
    }
    else
    {
        t->setText(tr("Help file missing").append("\n").append(f.errorString()));
    }

    QPushButton *aboutButton = new QPushButton(QIcon(":images/qtdbf.svg"),tr("About"), dialog);
    QPushButton *aboutQtButton = new QPushButton(QIcon(":images/qt.png"),tr("About Qt"), dialog);
    QPushButton *closeButton = new QPushButton(QIcon(":images/ok.svg"),tr("Close"), dialog);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(aboutButton);
    buttonLayout->addWidget(aboutQtButton);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(closeButton);

    mainLayout->addWidget(t);
    mainLayout->addLayout(buttonLayout);

    connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()));
    connect(aboutQtButton, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
    connect(closeButton, SIGNAL(clicked()), dialog, SLOT(accept()));

    //qApp->processEvents(QEventLoop::ExcludeUserInputEvents);

    dialog->setLayout(mainLayout);

    dialog->exec();

    settings.setValue("dbfeditor/helpsize", dialog->size());

    delete dialog;

}

void QDbfEditor::configApp()
{
    QDetaliiTabDialog *tabDialog = new QDetaliiTabDialog(strTableName);
    tabDialog->exec();
    delete tabDialog;
}

void QDbfEditor::about()
{
   QString explic;

   explic = tr("<b align='center'>qtDbf</b> <p>- an open source, multiplatform DBF viewer and editor written in Qt and using SQLite.</p>");

   QMessageBox::about(this,"qtDbf 0.9.10", explic);
}

void QDbfEditor::sortDbf(const QModelIndex& index)
{
    int current = view->currentIndex().row();
    int c = index.column();
    QString query;

    order = fieldsCollection.at(c-1)->fieldName;

    query = "SELECT * FROM ";
    query += tableName;
    if (where != "") query += ' WHERE ' + where;
    if (order != "") query += " ORDER BY " + order;


    model->setQuery(query, QSqlDatabase::database("dbfEditor"));
    if (model->lastError().isValid())
        {
            QMessageBox::critical(this, tr("Error"), model->lastError().text());
            return;
        }

    refresh(current);

}

void QDbfEditor::calculator()
{
    QCalculatorDialog *d = new QCalculatorDialog(tr("Calculator"), this);
    d->exec();
    delete d;
}

void QDbfEditor::setToolButtonIconSize(int i)
{
    QSize size = QSize(i,i);
    editButton->setIconSize(size);
    openButton->setIconSize(size);
    insertButton->setIconSize(size);
    deleteButton->setIconSize(size);
    saveButton->setIconSize(size);
    configButton->setIconSize(size);
    fillButton->setIconSize(size);
    calcButton->setIconSize(size);
    helpButton->setIconSize(size);
    quitButton->setIconSize(size);
    filterButton->setIconSize(size);
}

QDbfEditor::~QDbfEditor()
{
}
