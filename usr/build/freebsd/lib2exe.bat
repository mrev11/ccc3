#!/bin/bash
echo LIB2EXE.BAT $1 $BUILD_EXE

EXENAM=$1
LIBNAM=$2
TARGET=$BUILD_EXE/$EXENAM.exe 
RSPLNK=$BUILD_OBJ/rsplink
rm $TARGET 2>/dev/null
rm $RSPLNK 2>/dev/null
rm error 2>/dev/null

echo -o $TARGET >$RSPLNK
for i in $BUILD_LPT; do echo -L$i >>$RSPLNK; done

echo -Wl,--start-group >>$RSPLNK
echo $BUILD_OBJ/$EXENAM.obj >>$RSPLNK 
echo $BUILD_OBJ/$LIBNAM.lib >>$RSPLNK  
for i in $BUILD_LIB; do echo $i >>$RSPLNK; done
echo -Wl,--end-group >>$RSPLNK
 
#cat $CCCDIR/usr/options/$CCCBIN/link.opt | envsubst >>$RSPLNK
cat $CCCDIR/usr/options/$CCCBIN/link.opt  >>$RSPLNK
echo -R$CCCDIR/usr/lib/$CCCBIN  >>$RSPLNK

if ! c++ `cat $RSPLNK` 2>outlnk;  then
    cp outlnk error;
    rm $TARGET 2>/dev/null;
fi

echo ----------------------------------------------------------------

 