@echo off

:: KAPJA
set CCCVER=%1
set CCCSUB=%2

:: ide installaltuk az MSYS2 rendszert
set MSYS=C:\msys64

:: MSYS2 alrendszer 
:: (MINGW64, UCRT64, CLANG64 kozul valamelyik) 
set MSYSTEM=CLANG64

:: ide klonoztuk a CCC-t 
:: (peldaul az msys2 home-unkba: %MSYS%\home\%USERNAME%\ccc%CCCVER%%CCCSUB%)
:: (vagy peldaul a ccchome-ba: %USERPROFILE\ccchome\ccc%CCCVER%%CCCSUB%)
set CCCDIR=%USERPROFILE%\ccchome\ccc%CCCVER%%CCCSUB%


:: memoria objektum referenciak max szama 
:: (oriasi programoknal akar sokmillio is lehet)
set OREF_SIZE=50000


set CCCBIN=mng
set CCCUNAME=windows

:: msys-util path
set PATH=%MSYS%\bin;%PATH%
set PATH=%MSYS%\usr\bin;%PATH%

:: compiler path
set PATH=%MSYS%\%MSYSTEM%\bin;%PATH%
set INCLUDE=%MSYS%\%MSYSTEM%\include;%INCLUDE%
set LIB=%MSYS%\%MSYSTEM%\lib;%LIB%

:: ccc path
set PATH=%CCCDIR%\usr\bin\%CCCUNAME%;%PATH%

:: other path
set PATH=%USERPROFILE%\bin;%PATH%
set PATH=%CCCHOME%\bin;%PATH%

:: terminal
set CCCTERM_SIZE=90x32
set CCCTERM_ICONFILE=%CCCDIR%\usr\bin\%CCCUNAME%\terminal.xpm
set CCCTERM_FONTFACE=DejaVu Sans Mono
set CCCTERM_FONTSIZE=12
set CCCTERM_GTKFONTSPEC=Monospace 12

:: valasztani kell egy terminalt
set CCCTERM_CONNECT=term://console.exe          && set CCCTERM_INHERIT=yes
::set CCCTERM_CONNECT=term://terminal.exe         && set CCCTERM_INHERIT=no
::set CCCTERM_CONNECT=term://terminal-gtk3.exe    && set CCCTERM_INHERIT=no
::set CCCTERM_CONNECT=connect://i3x:55013         && set CCCTERM_INHERIT=no

set ZCOLOR_TEXT=w/n,w+/n+
set ZCOLOR_MASK=n/rg,w+/n+
set ZHOME=%CCCHOME%\z
set ZEOL=LF

cd %CCCHOME%
title %CCCDIR%
route print -4
set | grep CCC

start /b

