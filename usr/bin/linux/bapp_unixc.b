#!/bin/bash
. $CCCDIR/usr/bin/linux/__unix.b
export BUILD_LIB=ccc${CCCVER},ccc${CCCVER}_uic
build.exe "$@"

