#!/bin/bash
#C++ fordítás
#set -x

TARGET=$BUILD_OBJ/$1.obj
CMPOPT=$BUILD_OBJ/compopt
rm error 2>/dev/null
mkdir $BUILD_OBJ 2>/dev/null
rm $CMPOPT 2>/dev/null

if ! test -f $CCCDIR/usr/options/$CCCBIN/gccver.opt; then
   gccver.b >$CCCDIR/usr/options/$CCCBIN/gccver.opt 
fi

cat $CCCDIR/usr/options/$CCCBIN/gccver.opt >$CMPOPT
cat $CCCDIR/usr/options/$CCCBIN/$BUILD_OPT >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
if test -f "$BUILD_CFG"; then
    cat $BUILD_CFG >>$CMPOPT 
fi
 
if c++ `cat $CMPOPT` -o $TARGET -c $2/$1.cpp 2>outcpp; then

    if [ [$BUILD_CPP] != [] ]; then
        mkdir $BUILD_CPP 2>/dev/null;
        cp -pf $2/$1.cpp $BUILD_CPP;
    fi;

    cat outcpp

else
    cp outcpp error;
fi

