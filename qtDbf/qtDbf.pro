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

TARGET = qtdbf
TEMPLATE = app
DESTDIR = bin

CONFIG += qt \
    warn_on
unix:DEFINES += UNIX
HEADERS += src/structures.h \
    src/dbfeditor.h \
    src/mainwindow.h \
    src/widgets.h \
    src/qtcalculator.h \
    src/globals.h \
    src/customsqlmodel.h \
    src/dbfconfig.h
SOURCES += src/dbfeditor.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/widgets.cpp \
    src/qtcalculator.cpp \
    src/customsqlmodel.cpp \
    src/dbfconfig.cpp \
    src/saveconfig.cpp
RESOURCES += qtDbf.qrc
QT += sql \
    svg
OBJECTS_DIR += ./.obj
MOC_DIR += ./.moc
RCC_DIR += ./.rcc

win32:RC_FILE = qtDbf.rc

TRANSLATIONS = lang/qtDbf_en.ts \
    lang/qtDbf_hu.ts \
    lang/qtDbf_ru.ts \
    lang/qtDbf_ro.ts

updateqm.input = TRANSLATIONS
updateqm.output = *.qm
updateqm.commands = lrelease qtDbf.pro && $(MOVE) lang/*.qm ${DESTDIR}/lang/
updateqm.CONFIG += no_link target_predeps

QMAKE_EXTRA_COMPILERS += updateqm

# install
unix {
    target.path = /usr/bin
    translations.files = lang/*.qm
    translations.path = /usr/share/qtdbf/lang
    help.files = help/*
    help.path = /usr/share/doc/qtdbf/help
}
win32 {
    target.path = "c:/Program Files/qtDbf"
    translations.path = "c:/Program Files/qtDbf/lang"
    translations.files = *.qm
    help.path = "c:/Program Files/qtDbf/help"
    help.files = help/*.*
}
INSTALLS += target \
    translations \
    help
