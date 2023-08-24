#!/bin/bash
echo C2OBJ.BAT $1 $2

TARGET=$BUILD_OBJ/$1.obj
CMPOPT=$BUILD_OBJ/compopt-$1
OUTC=outc-$1
ERROR=error--outc-$1

#rm -f error
rm -f $ERROR
rm -f $CMPOPT
mkdir -p $BUILD_OBJ


cat $CCCDIR/usr/options/$CCCBIN/cppver.opt >$CMPOPT
cat $CCCDIR/usr/options/$CCCBIN/$BUILD_OPT >>$CMPOPT
for i in $BUILD_INC; do echo -I$i >>$CMPOPT; done
if test -f "$BUILD_CFG"; then
    cat $BUILD_CFG >>$CMPOPT
fi

#C forditas (c-->obj)
if ! cc `cat $CMPOPT` -o $TARGET  -c $2/$1.c  2>$OUTC; then
    touch error
    cp $OUTC $ERROR
    rm -f $TARGET
fi

cat $OUTC
rm -f $OUTC

echo ----------------------------------------------------------------


