#!/bin/bash
#set -x

source make_verf 3
make_base 2>&1 | tee log-install
if [ "$1" == "x" ]; then
    make_extn  2>&1 | tee -a log-install
fi


if ! [ "$CCCUNAME" == msys2 ]; then
    ( cd $CCCDIR/usr/bin && mklink.exe >/dev/null )
fi

