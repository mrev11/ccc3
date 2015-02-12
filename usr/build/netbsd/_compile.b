#!/bin/bash
#C++ forditas
#set -x

TARGET=$BUILD_OBJ/$1.obj
CMPOPT=$BUILD_OBJ/compopt-$1
OUTCPP=outcpp-$1
ERROR=error--$OUTCPP

#rm -f error
rm -f $ERROR
rm -f $CMPOPT 
mkdir -p $BUILD_OBJ

if ! test -f $CCCDIR/usr/options/$CCCBIN/gccver.opt; then
   gccver.b >$CCCDIR/usr/options/$CCCBIN/gccver.opt 
fi

cat $CCCDIR/usr/options/$CCCBIN/gccver.opt >$CMPOPT
cat $CCCDIR/usr/options/$CCCBIN/$BUILD_OPT >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
if test -f "$BUILD_CFG"; then
    cat $BUILD_CFG >>$CMPOPT 
fi
 
if c++ `cat $CMPOPT` -o $TARGET -c $2/$1.cpp 2>$OUTCPP; then

    if [ [$BUILD_CPP] != [] ]; then
        mkdir -p $BUILD_CPP;
        cp -pf $2/$1.cpp $BUILD_CPP;
    fi;

else
    touch error
    cp $OUTCPP $ERROR
    rm -f $TARGET
fi

cat $OUTCPP
rm -f $OUTCPP
