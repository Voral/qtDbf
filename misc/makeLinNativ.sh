#!/bin/sh
cd ..
qmake
make clean
make 
strip bin/qtdbf
cd misc
