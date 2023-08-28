@echo off

set LEMON=%CCCDIR%\usr\bin\%CCCUNAME%\lemon.exe

if exist %LEMON% goto inst

set CFLAGS=
set CFLAGS=-Wno-deprecated-non-prototype %CFLAGS%
set CFLAGS=-Wno-unknown-warning-option %CFLAGS%

cc %CFLAGS% lemon.c  -o %LEMON%


if exist %LEMON% goto ok
    echo lemon failed to compile
    goto stop

:ok
    echo lemon succesfully compiled

:inst
    copy lempar.c  %CCCDIR%\usr\bin\%CCCUNAME% 1>NUL
    del *.obj 2>NUL
    del *.tds 2>NUL
:stop

