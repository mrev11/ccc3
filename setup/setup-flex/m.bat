@echo off

set FLEX=%CCCDIR%\usr\bin\%CCCUNAME%\flex.exe

if exist %FLEX% goto inst

:mng --------------------------------------------------------------------------
if not "%cccbin%"=="mng" goto mng1
gcc  -I .  *.c  -o %FLEX%
:mng1

:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto msc1
cl -Fe%FLEX%  -I . *.c   /link bufferoverflowu.lib
:msc1


if exist %FLEX% goto ok
    echo flex failed to compile
    goto stop

:ok
    echo flex succesfully compiled

:inst
    copy flexlexer.h  %CCCDIR%\usr\include 1>NUL

:stop

