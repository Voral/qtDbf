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
RESOURCES += src/qtDbf.qrc
QT += sql \
    svg
OBJECTS_DIR += ./.obj
MOC_DIR += ./.moc
RCC_DIR += ./.rcc

win32:RC_FILE = src/qtDbf.rc

TRANSLATIONS = src/lang/qtDbf_en.ts \
    src/lang/qtDbf_hu.ts \
    src/lang/qtDbf_ru.ts \
    src/lang/qtDbf_ro.ts

defineReplace(outname) {
  $(MKDIR) $${DESTDIR}/lang
  return($$1)
}

updateqm.name = Lang files compiler
updateqm.input = TRANSLATIONS
updateqm.output = $${DESTDIR}/lang/${QMAKE_FILE_BASE}.qm
updateqm.commands = lrelease -silent ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
updateqm.output_function = outname

updateqm.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += updateqm

# install
INSTALLS += target

unix {
    INSTALLS += help \
       lang \
       icon \
       desktop
    isEmpty(PREFIX)
    {
      PREFIX=/usr
    }
    target.path = $$PREFIX/bin
    lang.files = $$DESTDIR/lang/*.qm
    lang.path = $$PREFIX/share/qtdbf/lang
    help.files = src/help/*.html
    help.path = $$PREFIX/share/doc/qtdbf/help
    icon.files = src/images/qtdbf.svg
    icon.path = $$PREFIX/share/pixmaps
    desktop.files = other/qtdbf.desktop
    desktop.path = $$PREFIX/share/applications
}
win32 {
    isEmpty(PREFIX)
    {
       PREFIX=c:\\Program Files\\qtDbf
    }
    target.path = $$quote(\"$$PREFIX\")
    target.depends += copy_lang copy_help
    copy_lang.target = copy_lang
    copy_lang.commands = xcopy /I /Y \"$$DESTDIR\\lang\\*.qm\" \"$$PREFIX\\lang\\\"
    copy_help.target = copy_help
    copy_help.commands = xcopy /I /Y \"$$DESTDIR\\help\\*.html\" \"$$PREFIX\\help\\\"
    QMAKE_EXTRA_TARGETS += copy_lang copy_help
}
