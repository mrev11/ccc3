@echo off

set DRV1=c:
set DRV2=e:

set CCCBIN=msc
set CCCVER=2
set CCCUNAME=windows
set OREF_SIZE=50000

set CCCDIR=%DRV2%\ccc\ccc2-64
set MNGDIR=%DRV2%\mingw64
set MSCDIR=%DRV2%\msc2003
set GTKDIR=%DRV2%\mono
set GNUDIR=%DRV2%\git

:a mingw-vel forditott exek-nek
set PATH=%MNGDIR%\bin;%PATH%

:set PATH=%GTKDIR%\bin;%PATH%
set PATH=%GNUDIR%\bin;%PATH%
set PATH=%CCCDIR%\usr\bin\%CCCUNAME%;%PATH%
set PATH=%DRV1%\bin;%PATH%

if "%CCCBIN%"=="mng" set CMPDIR=%MNGDIR%
if "%CCCBIN%"=="msc" set CMPDIR=%MSCDIR%

set PATH=%CMPDIR%\Bin\Win64\x86\AMD64;%PATH%

:sorrend fontos
set INCLUDE=%CMPDIR%\Include;%INCLUDE%;
set INCLUDE=%CMPDIR%\Include\crt;%INCLUDE%;
set INCLUDE=%CMPDIR%\Include\crt\sys;%INCLUDE%;

set LIB=%CMPDIR%\Lib\AMD64;%LIB%


: ket terminal van
:
:1) %CCCDIR%/usr/bin/%CCCUNAME%/termclnt.exe
:  ennek nincsenek kornyezeti valtozoi
:  a konzol beallitasaival lehet konfiguralni
:
:2) %CCCDIR%/usr/bin/%CCCUNAME%/terminal.exe
:  CCCTERM_KEYDEF
:  CCCTERM_SIZE
:  CCCTERM_FONT

set CCCTERM_CONNECT=%CCCDIR%/usr/bin/%CCCUNAME%/terminal.exe
set CCCTERM_KEYDEF=%CCCDIR%/usr/bin/%CCCUNAME%/keydef-vm.v2i
set CCCTERM_SIZE=100x40
set CCCTERM_FONT=terminal_10x16





set JTERMINAL=%CCCDIR%\usr\bin\%CCCUNAME%\jterminal.jar

set ZCOLOR_0=b/w
set ZCOLOR_2=w/b
set ZHOME=%DRV1%\bin\z


%DRV2%
cd %CCCDIR%

title %CCCDIR%-%CCCBIN%
set | grep CCC | sort
start /b
