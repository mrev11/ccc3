#!/bin/bash
echo OBJ2EXE.BAT $1 $BUILD_EXE

EXENAM=$1
TARGET=$BUILD_EXE/$EXENAM.exe 
RSPLNK=$BUILD_OBJ/rsplink
rm $TARGET 2>/dev/null
rm $RSPLNK 2>/dev/null
rm error 2>/dev/null

echo -o $TARGET >$RSPLNK

for i in $BUILD_LPT; do echo -L$i >>$RSPLNK; done
 
echo -Wl,--start-group >>$RSPLNK
for i in "$@"; do echo $BUILD_OBJ/$i.obj >>$RSPLNK; done
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

 