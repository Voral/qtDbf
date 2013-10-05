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
macx{
    DESTDIR = misc/macos
}
CONFIG += debug_and_release
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
    src/dbfconfig.h \
    src/dialogfilter.h \
    src/dialogagregat.h
SOURCES += src/dbfeditor.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/widgets.cpp \
    src/qtcalculator.cpp \
    src/customsqlmodel.cpp \
    src/dbfconfig.cpp \
    src/saveconfig.cpp \
    src/dialogfilter.cpp \
    src/dialogagregat.cpp
RESOURCES += src/qtDbf.qrc
QT += sql
OBJECTS_DIR += ./.obj
MOC_DIR += ./.moc
RCC_DIR += ./.rcc

win32:RC_FILE = src/qtDbf.rc
os2:RC_FILE = src/qtDbf_os2.rc

TRANSLATIONS = src/lang/qtdbf_hu.ts \
    src/lang/qtdbf_ru.ts \
    src/lang/qtdbf_ro.ts \
    src/lang/qtdbf_uk.ts

defineReplace(outname) {
  $(MKDIR) $${DESTDIR}/lang
  return($$1)
}

updateqm.name = Lang files compiler
updateqm.input = TRANSLATIONS
updateqm.output = $${DESTDIR}/lang/${QMAKE_FILE_BASE}.qm
macx{
    updateqm.commands = lrelease -silent ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
}
!macx{
    updateqm.commands = $$[QT_INSTALL_PREFIX]/bin/lrelease -silent ${QMAKE_FILE_IN} -qm ${QMAKE_FILE_OUT}
}
updateqm.output_function = outname

updateqm.CONFIG += no_link target_predeps
QMAKE_EXTRA_COMPILERS += updateqm

# install
INSTALLS += target

unix {
    INSTALLS += help \
       translations \
       icon \
       icon128 \
       icon16 \
       icon32 \
       icon48 \
       icon64 \
       desktop
    isEmpty(PREFIX)
    {
      PREFIX=/usr
    }
    target.path = $$PREFIX/bin

    translations.files = bin/lang/*.qm
    translations.path = $$PREFIX/share/qtdbf/lang
    translations.CONFIG += no_check_exist

    help.files = src/help/*.html
    help.path = $$PREFIX/share/qtdbf/help

    icon.files = src/images/qtdbf.svg
    icon.path = $$PREFIX/share/icons/hicolor/scalable/apps

    icon128.files = src/images/qtdbf.png
    icon128.path = $$PREFIX/share/icons/hicolor/128x128/apps

    icon16.files = src/images/16/qtdbf.png
    icon16.path = $$PREFIX/share/icons/hicolor/16x16/apps

    icon32.files = src/images/32/qtdbf.png
    icon32.path = $$PREFIX/share/icons/hicolor/32x32/apps

    icon48.files = src/images/48/qtdbf.png
    icon48.path = $$PREFIX/share/icons/hicolor/48x48/apps

    icon64.files = src/images/64/qtdbf.png
    icon64.path = $$PREFIX/share/icons/hicolor/64x64/apps

    desktop.files = misc/qtdbf.desktop
    desktop.path = $$PREFIX/share/applications
}
win32 {
    isEmpty(PREFIX)
    {
       PREFIX=c:\\Program Files\\qtDbf
    }
    target.path = $$quote(\"$$PREFIX\")
    target.depends += copy_help copy_lang
    copy_lang.target = copy_lang
    copy_lang.commands = xcopy /I /Y \"$$DESTDIR\\lang\\*.qm\" \"$$PREFIX\\lang\\\"
    copy_help.target = copy_help
    copy_help.commands = xcopy /I /Y \"$$DESTDIR\\help\\*.html\" \"$$PREFIX\\help\\\"
    QMAKE_EXTRA_TARGETS += copy_lang copy_help
}
os2 {
    INSTALLS += help \
       translations
    isEmpty(PREFIX)
    {
      PREFIX=/usr
    }
    target.path = $$PREFIX/bin

    translations.files = bin/lang/*.qm
    translations.path = $$PREFIX/share/qtdbf/lang
    translations.CONFIG += no_check_exist

    help.files = src/help/*.html
    help.path = $$PREFIX/share/qtdbf/help
    help.CONFIG += no_check_exist
}
