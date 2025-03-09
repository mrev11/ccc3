#!/bin/bash
# rebuild

gc
# clear-cache
export BUILD_ROOT=$(pwd -P)

if [ "$1" == -nc ]; then
    # do not use cache
    export BUILD_USECACHE=no
fi

time m x

