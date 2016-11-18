@echo off
@echo OBJ2EXE.BAT %1 %BUILD_EXE%

:Vagy a parameterkent vagy az objects-ben 
:kapott fileket kell rsplink-be kiirni.
:Build vagy egyik vagy masik modon mukodik,
:az egyiknek uresnek kell lennie.
:Azert van ez a kettosseg, hogy atmenetileg 
:a regi build is mukodjon az uj bat-okkal.

set EXENAM=%1
set TARGET=%BUILD_EXE%\%1.exe 
set RSPLNK=%BUILD_OBJ%\rsplink-%1
set OUTLNK=outlnk-%1
set ERROR=error--outlnk-%1

set OBJECTS=%BUILD_OBJ%\objects-%1
if exist %OBJECTS% goto objects_ok
set OBJECTS=%BUILD_OBJ%\objects
:objects_ok


del %TARGET% 2>nul
del %RSPLNK% 2>nul
del %ERROR% 2>nul

:mng --------------------------------------------------------------------------
if not "%cccbin%"=="mng" goto msc
 
echo -o %TARGET% >%RSPLNK%

set ECHOOUT=%RSPLNK% 
set ECHOPRE=-L
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_LPT%

echo -Wl,--no-as-needed >>%RSPLNK%
echo -Wl,--start-group >>%RSPLNK%

if exist %OBJECTS% goto endobj_mn
:begobj_mn
if [%1]==[] goto endobj_mn
  echo %BUILD_OBJ%\%1.obj >>%RSPLNK%
  shift
  goto begobj_mn
:endobj_mn

type %OBJECTS% >>%RSPLNK% 2>nul

set ECHOOUT=%RSPLNK% 
set ECHOPRE=
set ECHOPOST=
call %BUILD_BAT%\_echo %BUILD_LIB%

echo -Wl,--end-group >>%RSPLNK%
 
type %CCCDIR%\usr\options\%CCCBIN%\link.opt >>%RSPLNK%

ccomp c++ @%RSPLNK% 2>%OUTLNK%
goto iferror
 

:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" cccbin_not_set
 
echo -nologo >%RSPLNK%
echo -subsystem:%BUILD_SYS% >>%RSPLNK%
echo -out:%TARGET% >>%RSPLNK%

if exist %OBJECTS% goto endobj_ms
:begobj_ms
if [%1]==[] goto endobj_ms
  echo %BUILD_OBJ%\%1.obj >>%RSPLNK%
  shift
  goto begobj_ms
:endobj_ms

type %OBJECTS% >>%RSPLNK% 2>nul

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
del  %OBJECTS% 2>nul
del  %BUILD_OBJ%\objects 2>nul

@echo -------------------------------------------------------------------------

 