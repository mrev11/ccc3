@echo off

set FLEX=%CCCDIR%\usr\bin\%CCCUNAME%\flex.exe

if exist %FLEX% goto inst

set CFLAGS=
set CFLAGS=-Wno-deprecated-non-prototype %CFLAGS%
set CFLAGS=-Wno-unknown-warning-option %CFLAGS%


cc %CFLAGS%  -I .  *.c  -o %FLEX%

if exist %FLEX% goto ok
    echo flex failed to compile
    goto stop

:ok
    echo flex succesfully compiled

:inst
    copy flexlexer.h  %CCCDIR%\usr\include 1>NUL

:stop

