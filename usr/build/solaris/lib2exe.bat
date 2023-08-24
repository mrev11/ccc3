#!/bin/bash
echo LIB2EXE.BAT $1 $BUILD_EXE

EXENAM=$1
LIBNAM=$2
TARGET=$BUILD_EXE/$EXENAM.exe
RSPLNK=$BUILD_OBJ/rsplnk-$1
OUTLNK=outlnk-$1
ERROR=error--outlnk-$1

#rm -f error
rm -f $ERROR
rm -f $TARGET
rm -f $RSPLNK

echo -o $TARGET >$RSPLNK
for i in $BUILD_LPT; do echo -L$i >>$RSPLNK; done

#ld 2.22 (precise) egymenetes
#echo -Wl,--no-as-needed >>$RSPLNK

echo -Wl,--start-group >>$RSPLNK
echo $BUILD_OBJ/$EXENAM.obj >>$RSPLNK
echo $BUILD_OBJ/$LIBNAM.lib >>$RSPLNK
for i in $BUILD_LIB; do echo $i >>$RSPLNK; done
echo -Wl,--end-group >>$RSPLNK

cat $CCCDIR/usr/options/$CCCBIN/link.opt >>$RSPLNK
echo -R$CCCDIR/usr/lib/$CCCBIN  >>$RSPLNK


if ! c++ `cat $RSPLNK` 2>$OUTLNK;  then
    touch error
    cat $OUTLNK
    mv  $OUTLNK $ERROR;
    rm -f $TARGET
else
    rm -f $OUTLNK;
fi


echo ----------------------------------------------------------------

