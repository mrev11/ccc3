#!/bin/bash

export CCCDIR=/opt/ccc3
export CCCUNAME=linux
export CCCBIN=lin
export PATH=$CCCDIR/usr/bin/$CCCUNAME:$PATH
export LD_LIBRARY_PATH=$CCCDIR/usr/lib/$CCCBIN:$LD_LIBRARY_PATH

while true; do
    websrv.exe "$@"
    sleep 5
done
 