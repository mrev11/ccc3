@echo off
set IOSTREAM=iostream-new
:set IOSTREAM=iostream-old

set FLEX=%CCCDIR%\usr\bin\%CCCUNAME%\flex.exe

if exist %FLEX% goto inst

:mng --------------------------------------------------------------------------
if not "%cccbin%"=="mng" goto mng1
gcc  -I .  *.c %IOSTREAM%/skel.c  -o %FLEX%
:mng1

:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto msc1
cl -Fe%FLEX%  -I . *.c %IOSTREAM%\skel.c 
:msc1


:bor --------------------------------------------------------------------------
if not "%cccbin%"=="bor" goto bor1
bcc32 -e%FLEX% *.c %IOSTREAM%\skel.c 
:bor1


if exist %FLEX% goto ok
    echo flex failed to compile
    goto stop

:ok
    echo flex succesfully compiled

:inst
    copy %IOSTREAM%\flexlexer.h  %CCCDIR%\usr\include 1>NUL
    del *.obj 2>NUL
    del *.tds 2>NUL
:stop

