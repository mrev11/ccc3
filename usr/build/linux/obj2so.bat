#!/bin/bash
echo OBJ2SO.BAT $1

LIBNAM=$1.so
TARGET=$BUILD_OBJ/$LIBNAM
RSPLNK=$BUILD_OBJ/rsplnk-$1
OUTLNK=outlnk-$1
ERROR=error--outlnk-$1

#rm -f error
rm -f $ERROR
rm -f $TARGET
rm -f $RSPLNK

echo -shared -o $TARGET >$RSPLNK

shift

for i in $BUILD_LPT; do echo -L$i >>$RSPLNK; done
for i in "$@"; do echo $BUILD_OBJ/$i.obj >>$RSPLNK; done
for i in $BUILD_LIB; do echo $i >>$RSPLNK; done
if test -f "$BUILD_LIBX"; then
    cat $BUILD_LIBX >>$RSPLNK
fi

echo "-Wl,-soname=$LIBNAM" >>$RSPLNK

if [ "${CPP_COMPILER}" == "clang"  ]; then
    # LLVM linker: lld
    # GNU linker: ld (default)
    echo -fuse-ld=lld >>$RSPLNK
fi

if ! c++ $(cat $RSPLNK) 2>$OUTLNK; then
    touch error
    cat $OUTLNK
    mv  $OUTLNK $ERROR
    rm -f $TARGET
else
    rm -f $OUTLNK
    #readelf --string-dump .comment $TARGET
fi

echo ----------------------------------------------------------------

