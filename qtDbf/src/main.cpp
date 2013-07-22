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

// TODO: Total refactoring !!!

#include <QtGui>
#include <QtSvg>
#include <QtSql>
#include "mainwindow.h"

MainWindow *mainWindow;

QStringList wordList;

QString charFieldColorString;
QString currencyFieldColorString;
QString numericFieldColorString;
QString dateFieldColorString;
QString timeFieldColorString;
QString doubleFieldColorString;
QString intFieldColorString;
QString logicalFieldColorString;
QString memoFieldColorString;
QString memo4FieldColorString;
QString generalFieldColorString;

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(qtDbf);

    QApplication app(argc, argv);

    QSettings settings("Voral", "qtDbf");
    QString dbfLocal = settings.value("dbflocal", "en").toString();

    QCoreApplication::setOrganizationName("Voral"); // was Hevele-Hegyi-Istvan
    QCoreApplication::setOrganizationDomain("va-soft.ru"); // was hevele.juniorcom.ro
    QCoreApplication::setApplicationName("qtDbf");

    QTranslator translator;
    QString dbfDirPath="";

#ifdef UNIX
    dbfDirPath += "/usr/share/qtdbf/lang/qtDbf_";
    dbfDirPath += dbfLocal;
#endif

    QFileInfo f(dbfDirPath+".qm");
    if (!f.exists())
    {
        dbfDirPath = app.applicationDirPath();
        dbfDirPath += "/lang/qtDbf_";
        dbfDirPath += dbfLocal;
    }
    translator.load(dbfDirPath);
    app.installTranslator(&translator);
    QFont dbfFont("Verdana", 10, QFont::Normal);

    QApplication::setFont(dbfFont);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "dbfEditor");
        db.setDatabaseName(":memory:");
        db.open();
        if (db.lastError().isValid())
           {
            QMessageBox::critical(0, "Eroare", db.lastError().text());
           }
    }

    QString dbfFileName;
    if (app.arguments().count()>1) dbfFileName +=app.arguments().at(1);

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    if (dbfFileName.isEmpty())
        {
            QString currentDirectory;
            QSettings settings;
            currentDirectory= settings.value("dbfeditor/currentdir", "./").toString();

            dbfFileName = QFileDialog::getOpenFileName(0, QObject::tr("Open File"),currentDirectory,"DBF Files(*.dbf)");
            if (dbfFileName.isEmpty())
                {
                    return 1;
                }

            QFileInfo fileInfo(dbfFileName);
            currentDirectory = fileInfo.absolutePath();
            settings.setValue("dbfeditor/currentdir", currentDirectory);
        }

    MainWindow mainWin(dbfFileName);
    mainWin.show();
    return app.exec();
    QSqlDatabase::removeDatabase("dbfEditor");
}

