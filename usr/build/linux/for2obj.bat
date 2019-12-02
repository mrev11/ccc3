#!/bin/bash
#Fortran forditas (for-->obj)

echo FOR2OBJ.BAT $1 $2 

#set -x

TARGET=$BUILD_OBJ/$1.obj
CMPOPT=$BUILD_OBJ/compopt-$1
OUTFOR=outfor-$1
ERROR=error--$OUTFOR

#rm -f error
rm -f $ERROR
rm -f $CMPOPT 
mkdir -p $BUILD_OBJ

# cat $CCCDIR/usr/options/$CCCBIN/$BUILD_OPT >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
if test -f "$BUILD_CFG"; then
    cat $BUILD_CFG >>$CMPOPT 
fi
 
if ! c++ `cat $CMPOPT` -o $TARGET -c $2/$1.for 2>$OUTFOR; then
    touch error
    cp $OUTFOR $ERROR
    rm -f $TARGET
fi

cat $OUTFOR
rm -f $OUTFOR

echo ----------------------------------------------------------------
