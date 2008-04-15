@echo off 
echo C2OBJ.BAT %1 %2 

:C fordítás (c-->obj)

set TARGET=%BUILD_OBJ%\%1.obj
set CMPOPT=%BUILD_OBJ%\compopt
md %BUILD_OBJ% 2>nul
del error 2>nul
del %CMPOPT% 2>nul
type %cccdir%\usr\options\%cccbin%\%BUILD_OPT% >>%CMPOPT%

set ECHOOUT=%CMPOPT%
set ECHOPRE=-I
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_INC%

if "%BUILD_CFG%"=="" goto cfg
type %BUILD_CFG% >>%CMPOPT% 
:cfg
 
:mng --------------------------------------------------------------------------
if not "%cccbin%"=="mng" goto msc

echo %1 >>outc
ccomp gcc @%CMPOPT% -o %TARGET% -c %2\%1.c 2>>outc
goto iferror 
 

:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto wat

echo -Fo%TARGET% >>%CMPOPT%  
cl %2\%1.c @%CMPOPT% >outc
goto iferror



:wat --------------------------------------------------------------------------
if not "%cccbin%"=="wat" goto bor

echo -Fo=%TARGET% >>%CMPOPT%  
wcc386 %2\%1.c @%CMPOPT% >outc
goto iferror



:bor --------------------------------------------------------------------------
if not "%cccbin%"=="bor" goto gcc

bcc32 -c -o%TARGET% @%CMPOPT% %2\%1.c >outc
goto iferror
 


:gcc --------------------------------------------------------------------------
if not "%cccbin%"=="gcc" goto cccbin_not_set
goto iferror
 

 
:cccbin_not_set --------------------------------------------------------------- 
echo cccbin environment variable not set >error
goto stop

 
:iferror ----------------------------------------------------------------------
if errorlevel 1 copy  outc error  >nul
if exist error goto stop

if [%BUILD_CPP%]==[] goto stop
md %BUILD_CPP% 2>nul
copy %2\%1.c %BUILD_CPP% 
 
:stop
@echo -------------------------------------------------------------------------

 