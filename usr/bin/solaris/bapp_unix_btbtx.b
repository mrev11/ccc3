#!/bin/bash
. $CCCDIR/usr/bin/solaris/__unix.b
export BUILD_LIB=ccc3_btbtx,ccc3,ccc3_ui_

build.exe "$@"
 