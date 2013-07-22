#!/bin/sh
cd src
qmake32 -spec linux-g++-32 
make clean
make

lupdate -verbose protimer.pro
lrelease protimer.pro

cd ..

mkdir -p bin32/lang
cp src/lang/*.qm bin32/lang/

echo Strip
strip bin32/protimer
