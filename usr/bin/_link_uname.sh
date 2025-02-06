#!/bin/bash
#set -x

if  [ -d $CCCUNAME ]; then
    :
elif [ -n "$MSYS64" ]; then
    cmd //c mklink //j $CCCUNAME .
else
    ln -s . $CCCUNAME
fi
