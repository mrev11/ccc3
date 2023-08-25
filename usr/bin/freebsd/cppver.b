#!/bin/bash

VER=$(c++ -v 2>&1 | grep \ version)
VER=${VER//FreeBSD/}
# echo $VER

IFS=' ' read -r -a ver <<< "$VER"  # split to array
# echo ${ver[0]}  # gcc
# echo ${ver[1]}  # version
# echo ${ver[2]}  # x.y.z

CPPVER=$CCCDIR/usr/options/$CCCBIN/cppver


if ! test -f $CPPVER.exp; then
    echo  CPP_COMPILER=${ver[0]}    >> $CPPVER.exp
    echo  CPP_VERSION=${ver[2]}     >> $CPPVER.exp
    . $CPPVER.exp
else
    OBJECT_TYPE=${ver[0]}$MSYSTEM
    . $CPPVER.exp

    if [[ $OBJECT_TYPE != $CPP_COMPILER$MSYSTEM  ]]; then
        echo ERROR: incompatible object types: $OBJECT_TYPE '<->' $CPP_COMPILER$MSYSTEM
        exit 1
    fi
fi

if ! test -f $CPPVER.opt; then
    echo -D_${ver[0]^^}_             > $CPPVER.opt
    echo -DCPP_COMPILER=${ver[0]}   >> $CPPVER.opt
    echo -DCPP_VERSION=${ver[2]}    >> $CPPVER.opt
fi

export MSYSTEM
export CPP_COMPILER
export CPP_VERSION

