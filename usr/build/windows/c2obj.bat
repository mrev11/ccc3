@echo off 
echo C2OBJ.BAT %1 %2 

:C forditas (c-->obj)

set TARGET=%BUILD_OBJ%\%1.obj
set CMPOPT=%BUILD_OBJ%\compopt-%1
set OUTC=outc-%1
set ERROR=error--%OUTC%

del %ERROR% 2>nul
del %CMPOPT% 2>nul
md %BUILD_OBJ% 2>nul

type %CCCDIR%\usr\options\%CCCBIN%\%BUILD_OPT% >>%CMPOPT%
set ECHOOUT=%CMPOPT%
set ECHOPRE=-I
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_INC%

if "%BUILD_CFG%"=="" goto cfg
type %BUILD_CFG% >>%CMPOPT% 
:cfg
 
:mng --------------------------------------------------------------------------
if not "%CCCBIN%"=="mng" goto msc

ccomp gcc @%CMPOPT% -o %TARGET% -c %2\%1.c 2>>%OUTC%
goto iferror 
 

:msc --------------------------------------------------------------------------
if not "%CCCBIN%"=="msc" goto cccbin_not_set

echo -Fo%TARGET% >>%CMPOPT%  
cl %2\%1.c @%CMPOPT% >%OUTC%
goto iferror

 
:cccbin_not_set --------------------------------------------------------------- 
echo cccbin environment variable not set >error
goto stop

 
:iferror ----------------------------------------------------------------------
if not  errorlevel 1 goto stop
    touch error
    del  %TARGET%
    copy %OUTC% %ERROR% >nul
    type %OUTC%

:stop

del %OUTC%


@echo -------------------------------------------------------------------------

 