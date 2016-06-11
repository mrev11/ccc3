@echo off

set DRV1=c:
set DRV2=e:

set CCCBIN=msc
set CCCVER=3
set CCCUNAME=windows
set OREF_SIZE=50000

set CCCDIR=%DRV2%\ccc\ccc3-64
set MNGDIR=%DRV2%\mingw64
set MSCDIR=%DRV2%\msc2003
set GTKDIR=%DRV2%\mono
set GNUDIR=%DRV2%\git

:a mingw-vel forditott exe-knek
set PATH=%MNGDIR%\bin;%PATH%

:set PATH=%GTKDIR%\bin;%PATH%
set PATH=%GNUDIR%\bin;%PATH%
set PATH=%CCCDIR%\usr\bin\%CCCUNAME%;%PATH%
set PATH=%DRV1%\bin;%PATH%

if "%CCCBIN%"=="mng" set CMPDIR=%MNGDIR%
if "%CCCBIN%"=="msc" set CMPDIR=%MSCDIR%

:nem kell? set PATH=%CMPDIR%\bin;%PATH%
:nem kell? set PATH=%CMPDIR%\bin\win64;%PATH%
set PATH=%CMPDIR%\Bin\Win64\x86\AMD64;%PATH%

:sorrend fontos
set INCLUDE=%CMPDIR%\Include;%INCLUDE%;
set INCLUDE=%CMPDIR%\Include\crt;%INCLUDE%;
set INCLUDE=%CMPDIR%\Include\crt\sys;%INCLUDE%;

set LIB=%CMPDIR%\Lib\AMD64;%LIB%

set CCCTERM_SIZE=90x40
set CCCTERM_FONTSIZE=18
set CCCTERM_CONNECT=%CCCDIR%\usr\bin\%CCCUNAME%\terminal.exe
set JTERMINAL=%CCCDIR%\usr\bin\%CCCUNAME%\jterminal.jar

set ZCOLOR_0=b/w
set ZCOLOR_2=w/b
set ZHOME=%DRV1%\bin\z


%DRV2%
cd %CCCDIR%

title %CCCDIR%-%CCCBIN%
set | grep CCC | sort
start /b /d %CCCDIR%
