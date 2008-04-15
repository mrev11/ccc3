#!/bin/bash

export STARTDIR=`pwd`

sudo rm -f websrv.log

sudo ./script/websrv-stop.b  
sudo ./script/websrv-start.b  @parfile.web &

if test -f websrv.log; then
    less websrv.log
fi
 