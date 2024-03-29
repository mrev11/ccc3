#!/bin/bash
#C++ forditas
#set -x

TARGET=$BUILD_OBJ/$1.obj
CMPOPT=$BUILD_OBJ/compopt-$1
OUTCPP=outcpp-$1
ERROR=error--$OUTCPP

rm -f $TARGET
rm -f $CMPOPT
rm -f $OUTCPP
rm -f $ERROR
mkdir -p $BUILD_OBJ

cat $CCCDIR/usr/options/$CCCBIN/cppver.opt >$CMPOPT
cat $CCCDIR/usr/options/$CCCBIN/$BUILD_OPT >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
if test -f "$BUILD_CFG"; then
    cat $BUILD_CFG >>$CMPOPT
fi

if c++ $(cat $CMPOPT | tr -d '\r') -o $TARGET -c $2/$1.cpp 2>$OUTCPP; then

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

