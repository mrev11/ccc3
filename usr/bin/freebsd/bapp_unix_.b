#!/bin/bash
. $CCCDIR/usr/bin/freebsd/__unix.b
export BUILD_LIB=ccc${CCCVER},ccc${CCCVER}_ui_
build.exe "$@"

