TEMPLATE = app
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
    lang/qtDbf_ro.ts

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
