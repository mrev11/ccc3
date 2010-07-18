
if [%cccbin%]==[mng] goto ok
:if [%cccbin%]==[bor] goto ok
if [%cccbin%]==[msc] goto ok
:if [%cccbin%]==[wat] goto ok
 
echo CCCBIN environment variable not set, press CTRL-C
pause

:ok

set BUILD_BAT=%cccdir%\usr\build\%cccuname%
set BUILD_OPT=compile.opt 
set BUILD_INC=%cccdir%\usr\include
set BUILD_LPT=%cccdir%\usr\lib\%cccbin%
set BUILD_OBJ=obj%cccbin%
set BUILD_EXE=.
:set BUILD_DBG=off
 