#!/bin/bash 

echo PGE2WRO.BAT $1 $2 
if   test -e $2/$1.sor; then
   pge2wro.exe -r $2/$1.sor $2/$1
else
   pge2wro.exe              $2/$1
fi

echo ---------------------------------------------------------------- 