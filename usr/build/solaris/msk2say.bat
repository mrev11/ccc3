#!/bin/bash
#set -x
echo MSK2SAY.BAT $1 $2 
if test -e $2/$1.sor; then
   msk2say.exe -r $2/$1.sor $2/$1 $2/$1.say
else
   msk2say.exe              $2/$1 $2/$1.say
fi

echo ----------------------------------------------------------------
