#!/bin/bash
echo LEM2OBJ.BAT $1 $2
OUTLEMON=outlemon-$1
ERROR=error--outlemon-$1

#rm -f error
rm -f $ERROR
mkdir -p ppo


#Lemon forditas

if ! lemon.exe -q $2/$1.lem 1>$OUTLEMON 2>&1; then
    touch error
    mv $OUTLEMON $ERROR
    rm -f $2/$1.c
    cat $ERROR
else
    #cat $OUTLEMON
    rm -f $OUTLEMON
    mv  $2/$1.c  ppo/$1.cpp
    #C++ forditas (cpp-->obj)
    $BUILD_BAT/_compile.b $1 ppo
fi

echo ----------------------------------------------------------------
