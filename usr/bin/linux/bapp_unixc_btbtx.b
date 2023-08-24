#!/bin/bash
. $CCCDIR/usr/bin/linux/__unix.b
export BUILD_LIB=ccc${CCCVER}_btbtx,ccc${CCCVER}_btbtxui,ccc${CCCVER},ccc${CCCVER}_uic

build.exe "$@"
