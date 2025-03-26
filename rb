#!/bin/bash

# REBUILD
#
# Hasznalat:
# Egy terminalban a jelen directoryba cd-zunk,
# es ott vegrehajtjuk a parancsot: 
#
#   ./rb
#
# Az rb script elvegzi a CCC kezdeti forditasat.
# A forditashoz elozoleg telepiteni kell a fuggosegeket: C++ fordito, konyvtarak.
# A kesobbi munkahoz (a mostani forditason kivul) be kell allitani a CCC kornyezetet.
# A fuggosegekre es a kornyezet beallitasara vonatkozoan lasd: $CCCDIR/usr/setenv.

### CCC env ############

. cccver
export CCCDIR=$(pwd)
export CCC_OREFSIZE=200000

UNAME=$(uname -a)
if [[ "$UNAME" == *Linux* ]];then
    if [[ "$UNAME" == *Android* ]]; then
        CCCUNAME=termux
    elif [[ "$UNAME" == *armv7l* ]]; then
        CCCUNAME=raspi
    else
        CCCUNAME=linux
    fi
elif [[ "$UNAME" == *FreeBSD* ]];then
    CCCUNAME=freebsd
elif [[ "$UNAME" == *NetBSD* ]];then
    CCCUNAME=netbsd
elif [[ "$UNAME" == *SunOS* ]];then
    CCCUNAME=solaris
else
    echo unknown OS: $UNAME
    read
fi
export CCCUNAME

CVERSION=$(c++ -v 2>&1 | grep \ version)
if [[ $CVERSION =~ gcc ]]; then
    CCCBIN=gcc
elif [[ $CVERSION =~ clang ]]; then
    CCCBIN=clang
else
    echo unknown C compiler: $CVERSION
    read
fi
export CCCBIN


### BUILD env ##########

export BUILD_THR=4
export BUILD_OBJ=object
export BUILD_EXE=.
export BUILD_CACHE=~/.cache/build
mkdir -p $BUILD_CACHE
export BUILD_ROOT=$(pwd -P)

### PATH ###############

export PATH=.:$CCCDIR/usr/bin:$PATH
export LD_LIBRARY_PATH=$CCCDIR/usr/lib:$LD_LIBRARY_PATH


### COMPILE ############

git clean -fXd  >/dev/null

if [ "$1" == -nc ]; then
    # do not use object cache
    export BUILD_USECACHE=no
fi

time m x

########################
