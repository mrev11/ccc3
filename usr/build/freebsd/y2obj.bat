#!/bin/bash
echo Y2OBJ.BAT $1 $2 

rm error 2>/dev/null
mkdir ppo 2>/dev/null

removecr.exe $2/$1.y 

#YACC fordítás
if bison $BUILD_BSN -l -d -o ppo/$1.cpp  $2/$1.y 2>outbison; then

    #változott a Bison névképzése 

    if test -e ppo/$1.cpp.h; then
       cp ppo/$1.cpp.h  $2/$1.hpp     # 1.28  
    else
       cp ppo/$1.hpp    $2/$1.hpp     # 1.33
    fi

    cat outbison

    #C++ fordítás (cpp-->obj)
    $BUILD_BAT/_compile.b $1 ppo
else
    cp outbison error;
fi

echo ----------------------------------------------------------------

 