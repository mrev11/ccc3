@echo off
echo LIB2EXE.BAT %1 %BUILD_EXE% 

set EXENAM=%1
set TARGET=%BUILD_EXE%\%1.exe 
set RSPLNK=%BUILD_OBJ%\rsplink
del %TARGET% 2>nul
del %RSPLNK% 2>nul
del error 2>nul

:mng --------------------------------------------------------------------------
if not "%cccbin%"=="mng" goto msc
 
echo -o %TARGET% >%RSPLNK%

set ECHOOUT=%RSPLNK% 
set ECHOPRE=-L
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_LPT%

echo -Wl,--start-group >>%RSPLNK%

echo %BUILD_OBJ%\%1.obj >>%RSPLNK%
echo %BUILD_OBJ%\%2.lib >>%RSPLNK%
 
set ECHOOUT=%RSPLNK% 
set ECHOPRE=
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_LIB%

echo -Wl,--end-group >>%RSPLNK%
 
type %CCCDIR%\usr\options\%CCCBIN%\link.opt >>%RSPLNK%


ccomp c++ @%RSPLNK% 2>outlnk
goto iferror
 
 
:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto bor
 
echo -nologo >>%RSPLNK%
echo -subsystem:%BUILD_SYS% >>%RSPLNK%
echo -out:%TARGET% >>%RSPLNK%

echo %BUILD_OBJ%\%1.obj >>%RSPLNK%
echo %BUILD_OBJ%\%2.lib >>%RSPLNK%

set ECHOOUT=%RSPLNK%
set ECHOPRE=-libpath:
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_LPT%

set ECHOOUT=%RSPLNK%
set ECHOPRE=
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_LIB%
 
type %cccdir%\usr\options\msc\link.opt >>%RSPLNK%

link @%RSPLNK% >outlnk
goto iferror


:bor --------------------------------------------------------------------------
if not "%cccbin%"=="bor" goto cccbin_not_set

set CONCAT=-c -L
set CONCATPRE=
set CONCATPOST=;
call %BUILD_BAT%\_concat %BUILD_LPT%
set CONCAT=%CONCAT% %BUILD_SYS% +
echo %CONCAT% >%RSPLNK%

echo %BUILD_OBJ%\%1.obj >>%RSPLNK% 
 
echo %TARGET% >>%RSPLNK%

echo nul >>%RSPLNK%
 
echo %BUILD_OBJ%\%2.lib + >>%RSPLNK%
set ECHOOUT=%RSPLNK%
set ECHOPRE=
set ECHOPOST= +
call %BUILD_BAT%\_echo %BUILD_LIB%
 
type %cccdir%\usr\options\bor\link.opt >>%RSPLNK% 
 

ilink32 @%RSPLNK%. >outlnk    
goto iferror
 

:cccbin_not_set ---------------------------------------------------------------
echo cccbin environment variable not set >error
goto stop


:iferror ----------------------------------------------------------------------
if errorlevel 1 copy outlnk error >nul
del %BUILD_EXE%\%EXENAM%.tds 2>nul
if exist error del %TARGET% 2>nul


:stop
@echo -------------------------------------------------------------------------

 