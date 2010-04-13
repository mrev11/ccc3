#!/bin/bash

if [ $CCCBIN == "net" ]; then 
    export BUILD_BAT=$CCCDIR/usr/build/netbsd
    export BUILD_OPT=compile.opt 
    export BUILD_INC=$CCCDIR/usr/include
    export BUILD_LPT=$CCCDIR/usr/lib/$CCCBIN
    export BUILD_LPT=$BUILD_LPT:/usr/lib:/usr/local/lib:/usr/X11/lib:/usr/pkg/lib
    export BUILD_OBJ=obj$CCCBIN
    export BUILD_EXE=.
    export BUILD_DBG=off
    export BUILD_SYS=NETBSD
else
    echo CCCBIN environment variable not set!
    exit 1
fi


 