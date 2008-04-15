#!/bin/bash
find . -type d | while read NAME; do
    if [ -x $NAME/m ]; then
        pushd $NAME
        ./m
        popd
    fi
done
