@echo off

set LEMON=%CCCDIR%\usr\bin\%CCCUNAME%\lemon.exe

:if exist %LEMON% goto inst

:mng --------------------------------------------------------------------------
if not "%cccbin%"=="mng" goto mng1
gcc  lemon.c  -o %LEMON%
:mng1

:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto msc1
cl -Fe%LEMON% lemon.c /link bufferoverflowu.lib
:msc1

:bor --------------------------------------------------------------------------
if not "%cccbin%"=="bor" goto bor1
bcc32 -e%LEMON% -w-pro -w-sus -w-rvl lemon.c
:bor1


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

