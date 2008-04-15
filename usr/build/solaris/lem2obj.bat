#!/bin/bash
echo LEM2OBJ.BAT $1 $2 

rm error 2>/dev/null
mkdir ppo 2>/dev/null

#? removecr.exe $2/$1.lem 

#Lemon fordítás

if lemon.exe -q $2/$1.lem 1>outlemon 2>&1; then
    mv  $2/$1.c  ppo/$1.cpp
    #C++ fordítás (cpp-->obj)
    $BUILD_BAT/_compile.b $1 ppo
    cat outlemon
else
    rm  $2/$1.c 2>/dev/null 
    cp outlemon error;
fi

echo ----------------------------------------------------------------


