#!/bin/sh

cp ../src/images/qtdbf.svg package/qtdbf/usr/share/icons/hicolor/scalable/apps/qtdbf.svg
cp ../src/images/qtdbf.png package/qtdbf/usr/share/icons/hicolor/128x128/apps/qtdbf.png
cp ../src/images/16/qtdbf.png package/qtdbf/usr/share/icons/hicolor/16x16/apps/qtdbf.png
cp ../src/images/32/qtdbf.png package/qtdbf/usr/share/icons/hicolor/32x32/apps/qtdbf.png
cp ../src/images/48/qtdbf.png package/qtdbf/usr/share/icons/hicolor/48x48/apps/qtdbf.png
cp ../src/images/64/qtdbf.png package/qtdbf/usr/share/icons/hicolor/64x64/apps/qtdbf.png
cp ../src/images/qtdbf.xpm package/qtdbf/usr/share/pixmaps/qtdbf.xpm
cp ../src/help/*.html package/qtdbf/usr/share/qtdbf/help/

cp qtdbf.desktop package/qtdbf/usr/share/applications/qtdbf.desktop
cp ../bin/lang/*.qm package/qtdbf/usr/share/qtdbf/lang/
cp ../bin/qtdbf package/qtdbf/usr/bin/
cp package/control package/qtdbf/DEBIAN

