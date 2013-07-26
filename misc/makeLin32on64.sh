#!/bin/sh
cd ..
qmake32 -spec linux-g++-32 
make clean
make
strip bin/qtdbf
cd misc
