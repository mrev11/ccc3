#!/bin/bash
echo OBJ2SO.BAT $1

LIBNAM=$1.so 
TARGET=$BUILD_OBJ/$LIBNAM
RSPLNK=$BUILD_OBJ/rsplink
rm $TARGET 2>/dev/null
rm $RSPLNK 2>/dev/null
rm error 2>/dev/null

#echo -shared -o $TARGET >$RSPLNK              # GNU ld
echo -G -o $TARGET >$RSPLNK                    # Sun ld
 
shift

for i in $BUILD_LPT; do echo -L$i >>$RSPLNK; done
for i in "$@"; do echo $BUILD_OBJ/$i.obj >>$RSPLNK; done
for i in $BUILD_LIB; do echo $i >>$RSPLNK; done

#echo "-Wl,-soname=$LIBNAM" >>$RSPLNK          # GNU ld 
echo "-Wl,-h$LIBNAM" >>$RSPLNK                 # Sun ld 
 
if ! c++ `cat $RSPLNK` 2>outlnk; then
    cp outlnk error;
    rm $TARGET 2>/dev/null;
fi
 
echo ----------------------------------------------------------------

