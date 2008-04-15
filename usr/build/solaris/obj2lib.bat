#!/bin/bash
echo OBJ2LIB.BAT $1

TARGET=$BUILD_OBJ/$1.lib
SYMDST=$BUILD_OBJ/lib$1.a 
SYMSRC=$1.lib
LSTFIL=$BUILD_OBJ/$1.lst
RSPLIB=$BUILD_OBJ/rsplib
rm $TARGET 2>/dev/null
rm $RSPLIB 2>/dev/null
rm $SYMDST 2>/dev/null
rm error 2>/dev/null

shift
for i in "$@"; do echo $BUILD_OBJ/$i.obj >>$RSPLIB; done 
 
ar q $TARGET `cat $RSPLIB`
ln -s $SYMSRC $SYMDST

echo ----------------------------------------------------------------
