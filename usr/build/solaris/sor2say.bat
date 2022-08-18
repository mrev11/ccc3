#!/bin/bash
#set -x
echo SOR2SAY.BAT $1 $2 
msk2say.exe -r $2/$1.sor $2/$1 $2/$1.say

echo ----------------------------------------------------------------
