#!/bin/bash

lptadd() #vegere
{
    X=$(echo :$BUILD_LPT: | sed  s^:"$1":^:^)
    X=$X:"$1"
    X=$(echo $X | sed  s^::^:^)
    X=$(echo $X | sed  s^::^:^)
    export BUILD_LPT=$X
}

addlpt() #elejere
{
    X=$(echo :$BUILD_LPT: | sed  s^:"$1":^:^)
    X="$1":$X
    X=$(echo $X | sed  s^::^:^)
    X=$(echo $X | sed  s^::^:^)
    export BUILD_LPT=$X
}


if [ $CCCBIN == "lin" ]; then 
    export BUILD_BAT=$CCCDIR/usr/build/linux
    export BUILD_OPT=compile.opt 
    export BUILD_INC=$CCCDIR/usr/include
    
    lptadd $CCCDIR/usr/lib/$CCCBIN
    if uname -a | grep armv7l >/dev/null; then
        lptadd /usr/lib/arm-linux-gnueabihf
        lptadd /lib/arm-linux-gnueabihf

    elif uname -a | grep x86_64 >/dev/null; then
        #echo 64-bit
        lptadd /usr/lib/x86_64-linux-gnu
        lptadd /lib/x86_64-linux-gnu
        lptadd /usr/lib64
    else
        #echo 32-bit
        lptadd /usr/lib/i386-linux-gnu
        lptadd /lib/i386-linux-gnu
        lptadd /usr/lib32
    fi    
    lptadd $PREFIX/lib #android termux
    lptadd /usr/local/lib
    lptadd /usr/lib
    lptadd /lib

    export BUILD_OBJ=obj$CCCBIN
    export BUILD_EXE=.
    #export BUILD_DBG=off
    export BUILD_SYS=LINUX
else
    echo CCCBIN environment variable not set!
    exit 1
fi

 