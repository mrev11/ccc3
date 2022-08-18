#!/bin/bash

#export CCC_TERMINAL=dummy
 
if [ $CCCBIN == "sol" ]; then 
    export BUILD_BAT=$CCCDIR/usr/build/solaris
    export BUILD_OPT=compile.opt 
    export BUILD_INC=$CCCDIR/usr/include
    export BUILD_LPT=$CCCDIR/usr/lib/$CCCBIN
    export BUILD_LPT=$BUILD_LPT:/usr/lib/64:/usr/X11/lib:/usr/local/lib
    export BUILD_LPT=$BUILD_LPT:/usr/sfw/lib:/opt/sfw/lib
    export BUILD_OBJ=obj$CCCBIN
    export BUILD_EXE=.
    #export BUILD_DBG=off
    export BUILD_SYS=SOLARIS
else
    echo CCCBIN environment variable not set!
    exit 1
fi


 