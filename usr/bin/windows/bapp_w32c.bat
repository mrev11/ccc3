@echo off
call %cccdir%\usr\bin\%cccuname%\__common
set BUILD_LIB=ccc%CCCVER%,ccc%CCCVER%_uic
build %1 %2 %3 %4 %5 %6 %7 %8 %9


