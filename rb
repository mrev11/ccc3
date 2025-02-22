#!/bin/bash
# rebuild

gc

# clear cache
# rm -f ~/.cache/build/*

export BUILD_ROOT=$(pwd -P)

if [ "$1" == -nc ]; then
    # do not use cache
    export BUILD_CACHE=DO_NOT_USE_CACHE
fi


time m x

