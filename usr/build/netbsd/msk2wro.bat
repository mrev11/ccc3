#!/bin/bash
echo MSK2WRO.BAT $1 $2 
msk2pge -ur $2/$1 $2/$1.x
if   test -e  $2/$1.sor; then
   pge2wro.exe -r $2/$1.sor $2/$1.x
else
   pge2wro.exe              $2/$1.x
fi

rm -f $2/$1.x

#dos2unix $2/$1.wro
 
echo ----------------------------------------------------------------
