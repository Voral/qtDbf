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

    QSettings settings("voral", "qtDbf");
    QString dbfLocal = settings.value("dbflocal", QLocale::system().name().left(2)).toString();

    QCoreApplication::setOrganizationName("voral"); // was Hevele-Hegyi-Istvan
    QCoreApplication::setOrganizationDomain("va-soft.ru"); // was hevele.juniorcom.ro
    QCoreApplication::setApplicationName("qtDbf");

    QTranslator translator;
    if (dbfLocal.compare("en"))
    {
        QString dbfDirPath="";

#ifdef Q_OS_UNIX
        if (QFile::exists("/usr/local/share/qtdbf/"))
        {
            dbfDirPath = "/usr/local/share/qtdbf/";
        }
        else
        {
            if (QFile::exists("/usr/share/qtdbf/"))
            {
                dbfDirPath = "/usr/share/qtdbf/";
            }
            else
            {
                dbfDirPath = app.applicationDirPath();
            }
        }
#else
        dbfDirPath = app.applicationDirPath();
#endif
        dbfDirPath += "/lang/qtdbf_";
        dbfDirPath += dbfLocal;
        dbfDirPath += ".qm";

        QFileInfo f(dbfDirPath);
        if (f.exists())
        {
            translator.load(dbfDirPath);
            app.installTranslator(&translator);
        }
    }
    QFont dbfFont("Verdana", 10, QFont::Normal);

    QApplication::setFont(dbfFont);
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "dbfEditor");
        db.setDatabaseName(":memory:");
        db.open();
        if (db.lastError().isValid())
           {
            QMessageBox::critical(0, QObject::tr("Error"), db.lastError().text());
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

