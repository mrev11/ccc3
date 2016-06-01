@echo off
echo LIB2EXE.BAT %1 %BUILD_EXE% 

set EXENAM=%1
set TARGET=%BUILD_EXE%\%1.exe 
set RSPLNK=%BUILD_OBJ%\rsplink-%1
set OUTLNK=outlnk-%1
set ERROR=error--outlnk-%1

del %TARGET% 2>nul
del %RSPLNK% 2>nul
del %OUTLNK% 2>nul
del %ERROR%  2>nul

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


ccomp c++ @%RSPLNK% 2>%OUTLNK%
goto iferror
 
 
:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto cccbin_not_set 
 
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

link @%RSPLNK% >%OUTLNK%
goto iferror


:cccbin_not_set ---------------------------------------------------------------
echo cccbin environment variable not set >error
goto stop


:iferror ----------------------------------------------------------------------
if not errorlevel 1 goto stop
    touch error
    del  %TARGET% 2>nul
    copy %OUTLNK% %ERROR% >nul
    type %OUTLNK%

:stop

del  %OUTLNK% 2>nul

@echo -------------------------------------------------------------------------

 