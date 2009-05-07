#!/bin/bash
echo CPP2OBJ.BAT $1 $2 

#C++ fordítás (cpp-->obj)
$BUILD_BAT/_compile.b $1 $2

if ! test -f error; then
    cat outcpp
fi

echo ----------------------------------------------------------------
