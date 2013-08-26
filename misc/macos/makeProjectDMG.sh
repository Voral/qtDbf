#!/bin/sh
cp ../../src/images/qtdbf_big.png ./
./makeDMG.sh -V -b qtdbf_big.png -i ../../src/images/qtdbf.icns -s "800:500" -c 535:345:253:345 "qtdbf.app"

cd ..
rm ./qtdbf.png