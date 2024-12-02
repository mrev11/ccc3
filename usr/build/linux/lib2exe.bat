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

if [ "${CPP_COMPILER}" == "clang"  ]; then
    # LLVM linker: lld
    # GNU linker: ld (default)
    echo -fuse-ld=lld >>$RSPLNK
fi

if [ "${CPP_COMPILER}" == "gcc"  ]; then
    echo -Wl,--no-as-needed >>$RSPLNK
fi

echo -Wl,--start-group >>$RSPLNK
echo $BUILD_OBJ/$EXENAM.obj >>$RSPLNK
echo $BUILD_OBJ/$LIBNAM.lib >>$RSPLNK
for i in $BUILD_LIB; do echo $i >>$RSPLNK; done
if test -f "$BUILD_LIBX"; then
    cat $BUILD_LIBX >>$RSPLNK
fi
echo -Wl,--end-group >>$RSPLNK

if ! [ "$TERMUX_VERSION" == "" ]; then
    echo -landroid-shmem >>$RSPLNK
fi
cat $CCCDIR/usr/options/$CCCBIN/link.opt >>$RSPLNK


if ! c++ $(cat $RSPLNK) 2>$OUTLNK;  then
    touch error
    cat $OUTLNK
    mv  $OUTLNK $ERROR;
    rm -f $TARGET
else
    rm -f $OUTLNK;
    #readelf --string-dump .comment $TARGET
    echo " ["$(git log --pretty=format:"%h %ai" -1 2>/dev/null)"] " >>$TARGET
    echo "$(cccbn.exe 2>/dev/null)" >>$TARGET
fi


echo ----------------------------------------------------------------

