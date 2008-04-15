@echo off

if [%cccbin%]==[msc] set BUILD_PRE=-dMSVC
if [%cccbin%]==[bor] set BUILD_PRE=-dBORLAND
if [%cccbin%]==[wat] set BUILD_PRE=-dWATCOM
if [%cccbin%]==[mng] set BUILD_PRE=-dMINGW
 
set BUILD_OBJ=obj%cccbin%
 
build @ccc.bldwin

md %cccdir%\usr\lib\%cccbin% 2>nul
copy %BUILD_OBJ%\*.lib %cccdir%\usr\lib\%cccbin%
 