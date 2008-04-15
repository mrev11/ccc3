#!/bin/bash
#set -x
for w in $(gcc -v 2>&1); do
    if [ "$PREV" = "version" ]; then
        echo "-DGCC_VERSION=$w"
        echo "-DGCC_VERSION_MAJOR=$(echo $w | cut -d . -f 1)"
        echo "-DGCC_VERSION_MINOR=$(echo $w | cut -d . -f 2)"
        echo "-DGCC_VERSION_PATCH=$(echo $w | cut -d . -f 3)"
    fi
    PREV=$w
done
