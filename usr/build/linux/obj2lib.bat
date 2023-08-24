#!/bin/bash
echo OBJ2LIB.BAT $1

TARGET=$BUILD_OBJ/$1.lib
SYMDST=$BUILD_OBJ/lib$1.a
SYMSRC=$1.lib
LSTFIL=$BUILD_OBJ/$1.lst
RSPLIB=$BUILD_OBJ/rsplib-$1
OUTLIB=outlib-$1
ERROR=error--outlib-$1

#rm -f error
rm -f $ERROR
rm -f $TARGET
rm -f $RSPLIB
rm -f $SYMDST

shift
for i in "$@"; do echo $BUILD_OBJ/$i.obj >>$RSPLIB; done

if ! ar -c -q $TARGET $(cat $RSPLIB)  2>$OUTLIB; then
    touch error
    cat $OUTLIB
    mv  $OUTLIB $ERROR

else
    ln -s $SYMSRC $SYMDST
    rm -f $OUTLIB
fi


echo ----------------------------------------------------------------
