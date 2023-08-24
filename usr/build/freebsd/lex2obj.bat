#!/bin/bash
echo LEX2OBJ.BAT $1 $2
OUTFLEX=outflex-$1
ERROR=error--outflex-$1

#rm -f error
rm -f $ERROR
mkdir -p ppo

removecr.exe $2/$1.lex

#LEX forditas

if ! flex.exe $BUILD_LEX -oppo/$1.cpp $2/$1.lex 2>$OUTFLEX; then
    touch error
    mv $OUTFLEX $ERROR
    cat $ERROR

else
    #cat $OUTFLEX
    rm -f $OUTFLEX
    #C++ forditas (cpp-->obj)
    $BUILD_BAT/_compile.b $1 ppo
fi

echo ----------------------------------------------------------------

