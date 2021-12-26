#!/bin/bash

source make_verf 3

make_base 2>&1 | tee log-install 

if [ "$1" == "x" ]; then
    make_extn  2>&1 | tee -a log-install 
fi

( cd $CCCDIR/usr/bin/$CCCUNAME && mklink.exe )
