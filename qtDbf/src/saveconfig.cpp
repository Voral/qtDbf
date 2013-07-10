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

#include "dbfconfig.h"
#include "mainwindow.h"

extern MainWindow *mainWindow;

void QDetaliiTabDialog::saveConfiguration()
{
    QString fileName
        = QFileDialog::getSaveFileName(this, tr("Save layout"),"./","*.ccf");
    if (fileName.isEmpty())
        return;

    if (fileName.right(4) != ".ccf")
        fileName += ".ccf";

    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QIODevice::Text)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    bool ok = true;

    QTextStream text(&file);
    QSettings settings;
    QVariant settingsValue;

    QStringList settingsKeys = settings.allKeys();

    QList<QString>::iterator j;

    QString settingsType;
    QString stringValue;
    bool okInt;
    int i;

    for (j = settingsKeys.begin(); j != settingsKeys.end(); ++j)
        {
          settingsValue = settings.value(*j);
          settingsType = settingsValue.typeName();
          if (settingsType == "QString")
            {
              stringValue = settingsValue.toString();

              i = stringValue.toInt(&okInt, 10);

              if (okInt)
                  {
                   text << *j << "=@Int(" << settingsValue.toString() << ")" << endl;
                  }
              else
                  {
                    if (stringValue == "true")
                      {
                       text << *j << "=@Bool(" << settingsValue.toString() << ")" << endl;
                      }
                    else if (stringValue == "false")
                      {
                       text << *j << "=@Bool(" << settingsValue.toString() << ")" << endl;
                      }
                    else
                      {
                       text << *j << "=@String(\"" << settingsValue.toString() << "\")" << endl;
                      }
                   }
            }

          if (settingsType == "QSize")
            {
              text << *j << "=@Size(" << settingsValue.toSize().width() << "," << settingsValue.toSize().height() << ")" << endl;
            }

          if (settingsType == "QPoint")
            {
              text << *j << "=@Point(" << settingsValue.toPoint().x() << "," << settingsValue.toPoint().y() << ")" << endl;
            }
        }

    text.flush();

    if (!ok) {
        QString msg = tr("Error writing to %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

void QDetaliiTabDialog::loadConfiguration()
{
    QString fileName
		= QFileDialog::getOpenFileName(this, tr("Load layout"),"./","App Config(*.ccf)");
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QString msg = tr("Failed to open %1\n%2")
                        .arg(fileName)
                        .arg(file.errorString());
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }

    bool ok = true;
    QTextStream in(&file);
    QString line;
    QString variable;
    QString value;
    QStringList sl;
    QFont font;
    QString typeSetting;
    QSettings settings;
    int i, k;

    while (!in.atEnd())
        {
         line = in.readLine();
         //line = line.simplified();
         //line = line.remove(" ");
         sl = line.split("=");
         variable = sl.at(0);
         if (sl.size() == 2)
            {
             value = sl.at(1);
            }
         else if (sl.size() > 2)
            {
             value = "";
             for (i = 1; i < sl.size(); ++i)
                {
                 value += sl.at(i);
                 value += "=";
                }
             k = value.size();
             value.truncate(k-1);
            }

         value = value.mid(1);
         k = value.length();
         value.truncate(k-1);
         sl = value.split("(");
         typeSetting = sl.at(0);
         k = value.indexOf("(");
         value = value.mid(k+1);

         if (typeSetting == "Int")
            {
             settings.setValue(variable, value.toInt());
            }
         else if (typeSetting == "Bool")
            {
             if (value == "true")
                settings.setValue(variable, true);
             else if (value == "false")
                settings.setValue(variable, false);
            }
         else if (typeSetting == "String")
            {
             k = value.length();
             value.truncate(k-1);
             value = value.mid(1);
             settings.setValue(variable, value);
            }
         else if (typeSetting == "Point")
            {
             sl = value.split(",");
             settings.setValue(variable, QPoint(sl.at(0).toInt(), sl.at(1).toInt()));
            }
         else if (typeSetting == "Size")
            {
             sl = value.split(",");
             settings.setValue(variable, QSize(sl.at(0).toInt(), sl.at(1).toInt()));
            }
        }
    settings.sync();

    if (!ok) {
       QString msg = tr("Error reading %1")
                        .arg(fileName);
        QMessageBox::warning(this, tr("Error"), msg);
        return;
    }
}

