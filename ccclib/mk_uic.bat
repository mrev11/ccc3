@echo off
del error 2>nul

if [%cccbin%]==[msc] set BUILD_PRE=-dMSVC
if [%cccbin%]==[mng] set BUILD_PRE=-dMINGW
 
set BUILD_OBJ=obj%cccbin%_uic
 
build @uic.bldwin

md %cccdir%\usr\lib\%cccbin% 2>nul
copy %BUILD_OBJ%\*.lib %cccdir%\usr\lib\%cccbin%
 