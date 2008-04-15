#!/bin/bash
echo LEX2OBJ.BAT $1 $2 

rm error 2>/dev/null
mkdir ppo 2>/dev/null

removecr.exe $2/$1.lex
 
#LEX fordítás
if ! flex.exe $BUILD_LEX -oppo/$1.cpp $2/$1.lex 2>outflex; then
    cp outflex error;
else
    #C++ fordítás (cpp-->obj)
    $BUILD_BAT/_compile.b $1 ppo
fi

echo ----------------------------------------------------------------

