#!/bin/bash
# rebuild

gc

# clear cache
# rm -f ~/.cache/build/*

if [ "$1" == -nc ]; then
    # do not use cache
    export BUILD_CACHE=DO_NOT_USE_CACHE
fi


time m x

