#!/bin/sh
qmake32 -spec linux-g++-32 
make clean
make
strip bin/qtdbf
