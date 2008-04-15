@echo off
:C++ fordítás

set TARGET=%BUILD_OBJ%\%1.obj
set CMPOPT=%BUILD_OBJ%\compopt
del error 2>nul
md %BUILD_OBJ% 2>nul
del %CMPOPT% 2>nul
type %cccdir%\usr\options\%cccbin%\%BUILD_OPT% >>%CMPOPT%
set ECHOOUT=%CMPOPT%
set ECHOPRE=-I
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_INC%

if "%BUILD_CFG%"=="" goto cfg
type %BUILD_CFG% >>%CMPOPT% 
:cfg

:type %CMPOPT%
 

:mng ------------------------------------------------------------
if not "%cccbin%"=="mng" goto msc

echo %1 >outcpp
ccomp c++ @%CMPOPT% -o %TARGET% %2\%1.cpp 2>>outcpp
goto iferror 
 

:msc ------------------------------------------------------------
if not "%cccbin%"=="msc" goto wat

echo -Fo%TARGET% >>%CMPOPT%  
cl %2\%1.cpp @%CMPOPT% >outcpp
goto iferror 
 
 
:wat ------------------------------------------------------------
if not "%cccbin%"=="wat" goto bor

echo -fo=%TARGET% >>%CMPOPT%  
wpp386 %2\%1.cpp @%CMPOPT% >outcpp 
goto iferror 
 

:bor ------------------------------------------------------------
if not "%cccbin%"=="bor" goto gcc

bcc32 -c -o%TARGET% @%CMPOPT% %2\%1.cpp >outcpp 
goto iferror 
 

:gcc ------------------------------------------------------------
if not "%cccbin%"=="gcc" goto cccbin_not_set
goto iferror 




:cccbin_not_set ------------------------------------------------- 
echo cccbin environment variable not set >error
goto stop


:iferror --------------------------------------------------------
if errorlevel 1 copy  outcpp error >nul
if exist error goto stop

if [%BUILD_CPP%]==[] goto stop
md %BUILD_CPP% 2>nul
copy %2\%1.cpp %BUILD_CPP% 

:stop

 