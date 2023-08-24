@echo off
call %cccdir%\usr\bin\%cccuname%\__common
call %cccdir%\usr\bin\%cccuname%\__%cccbin% c

set BUILD_LIB=ccc%CCCVER%,ccc%CCCVER%_ui_

build %1 %2 %3 %4 %5 %6 %7 %8 %9


