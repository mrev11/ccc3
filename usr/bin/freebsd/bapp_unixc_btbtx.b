#!/bin/bash
. $CCCDIR/usr/bin/freebsd/__unix.b
export BUILD_LIB=ccc3_btbtx,ccc3_btbtxui,ccc3,ccc3_uic

build.exe "$@"
 