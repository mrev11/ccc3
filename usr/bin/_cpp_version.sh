#!/bin/bash

unset COMPILER_NAME

VER=$(c++ -v 2>&1 | grep \ version)
for tag in $VER; do
    if [[ $tag =~ (clang|gcc) ]]; then
        COMPILER_NAME=$tag
    elif [[ $tag =~ [0-9]*\.[0-9]*\.[0-9]* ]]; then
        COMPILER_VERSION=$tag
    fi
done

if [ -z $COMPILER_NAME ] ;then
    echo ERROR: unknown c++ compiler
    c++ -v
    read
    exit 1
fi

CPPVER=$CCCDIR/usr/options/${CCCUNAME}/${CCCBIN}/cppver


if ! test -f $CPPVER.exp; then
    echo  CPP_COMPILER=${COMPILER_NAME}     >> $CPPVER.exp
    echo  CPP_VERSION=${COMPILER_VERSION}   >> $CPPVER.exp
fi
. $CPPVER.exp

if [[ $COMPILER_NAME != $CPP_COMPILER ]]; then
    echo ERROR: incompatible object types: $COMPILER_NAME  '<->' $CPP_COMPILER
    read
    exit 1
fi


if ! test -f $CPPVER.opt; then
    echo -D_${COMPILER_NAME^^}_                  > $CPPVER.opt
    echo -DCPP_COMPILER=${COMPILER_NAME}        >> $CPPVER.opt
    echo -DCPP_VERSION=${COMPILER_VERSION}      >> $CPPVER.opt
    if ! [ "$TERMUX_VERSION" == "" ]; then
        echo -D_TERMUX_                         >> $CPPVER.opt
    fi
fi

export CPP_COMPILER
export CPP_VERSION

