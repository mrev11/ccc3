#!/bin/bash
. $CCCDIR/usr/bin/_init_build_env.sh
export BUILD_LIB=ccc${CCCVER},ccc${CCCVER}_uic
build.exe "$@"

