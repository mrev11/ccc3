@echo off
call %cccdir%\usr\bin\%cccuname%\__common
call %cccdir%\usr\bin\%cccuname%\__%cccbin% c

set BUILD_LIB=ccc3_btbtx,ccc3,ccc3_ui_
 
build %1 %2 %3 %4 %5 %6 %7 %8 %9

 
