#!/bin/sh

cp ../qtDbf/src/images/qtdbf.svg qtdbf/usr/share/pixmaps/qtdbf.svg
cp ../src/other/qtdbf.desktop qtdbf/usr/share/applications/qtdbf.desktop
cp ../qtDbf/src/help/*.html qtdbf/usr/share/doc/qtdbf/help/
cp ../qtDbf/src/help/*.png qtdbf/usr/share/doc/qtdbf/help/
cp ../qtDbf/bin/lang/*.qm qtdbf/usr/share/qtdbf/lang/
cp ../qtDbf/bin/qtdbf qtdbf/usr/bin/
cp control qtdbf/DEBIAN

