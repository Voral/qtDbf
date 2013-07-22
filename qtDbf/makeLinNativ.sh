#!/bin/sh
qmake
make clean
make 
strip bin/qtdbf
