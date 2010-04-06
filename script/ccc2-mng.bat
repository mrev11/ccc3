@echo off

set CCCBIN=mng
set CCCVER=2
set CCCUNAME=nt
set CCCDIR=c:\ccc\ccc2

set GNUDIR=c:\MinGW
set MSCDIR=c:\msc2003


set PATH=%CCCDIR%\usr\bin\%CCCUNAME%;%PATH%


if "%CCCBIN%"=="mng" set CMPDIR=%GNUDIR%
if "%CCCBIN%"=="msc" set CMPDIR=%MSCDIR%
set PATH=%CMPDIR%\bin;%PATH%
set INCLUDE=%CMPDIR%\include;%INCLUDE%
set LIB=%CMPDIR%\lib;%LIB%


set CCCTERM_SIZE=80x40
set CCCTERM_FONTSIZE=18
set CCCTERM_CONNECT=%CCCDIR%\usr\bin\%CCCUNAME%\terminal.exe
set JTERMINAL=%CCCDIR%\usr\bin\%CCCUNAME%\jterminal.jar

set ZCOLOR_0=b/w
set ZCOLOR_2=w/b
set ZHOME=c:\.z


cd \
title %CCCDIR%-%CCCBIN%
set | grep CCC
start /b