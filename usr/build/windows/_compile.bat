@echo off
:C++ forditas

set TARGET=%BUILD_OBJ%\%1.obj
set CMPOPT=%BUILD_OBJ%\compopt-%1
set OUTCPP=outcpp-%1
set ERROR=error--%OUTCPP%

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

:type %CMPOPT%
 

:mng ------------------------------------------------------------
if not "%cccbin%"=="mng" goto msc

ccomp c++ @%CMPOPT% -o %TARGET% %2\%1.cpp 2>>%OUTCPP%
goto iferror 
 

:msc ------------------------------------------------------------
if not "%cccbin%"=="msc" goto cccbin_not_set

echo -Fo%TARGET% >>%CMPOPT%  
cl %2\%1.cpp @%CMPOPT% >%OUTCPP%
goto iferror 
 
 
:cccbin_not_set ------------------------------------------------- 
echo cccbin environment variable not set >error
goto stop


:iferror --------------------------------------------------------
if errorlevel 1 goto error 

    if [%BUILD_CPP%]==[] goto stop
    md %BUILD_CPP% 2>nul
    copy %2\%1.cpp %BUILD_CPP% >nul
    goto stop

:error
    touch error
    del   %TARGET%  2>nul
    copy  %OUTCPP% %ERROR% >nul
    type  %OUTCPP%

:stop

del %OUTCPP%


 