#!/bin/bash
. $CCCDIR/usr/bin/solaris/__unix.b
export BUILD_LIB=ccc${CCCVER}_btbtx,ccc${CCCVER},ccc${CCCVER}_ui_

build.exe "$@"
