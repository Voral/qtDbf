#!/bin/sh

APP=qtdbf.app

echo Compiling
cd ../../
qmake -spec macx-g++ qtdbf.pro
if [ $? -ne 0 ];then
    exit;
fi
make clean
make
if [ $? -ne 0 ];then
    exit;
fi

lupdate -verbose qtdbf.pro
lrelease qtdbf.pro

cd misc/macos

echo Copying Qt frameworks
macdeployqt ${APP} -no-plugins

echo Refining application bundle
cp Info.plist ${APP}/Contents
cp ../../src/images/qtdbf.icns ${APP}/Contents/Resources
mkdir -p ${APP}/Contents/MacOS/lang
cp ../../src/lang/*.qm ${APP}/Contents/MacOS/lang/
mkdir -p ${APP}/Contents/MacOS/help
cp ../../src/help/*.html ${APP}/Contents/MacOS/help/

echo Strip
strip ${APP}/Contents/MacOS/qtdbf


echo "Done"
