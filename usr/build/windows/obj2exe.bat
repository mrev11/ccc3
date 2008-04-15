@echo off
echo OBJ2EXE.BAT %1 %BUILD_EXE%

:Vagy a paraméterként vagy az objects-ben 
:kapott filéket kell rsplink-be kiírni.
:Build vagy egyik vagy másik módon működik,
:az egyiknek üresnek kell lennie.
:Azért van ez a kettősség, hogy átmenetileg 
:a régi build is működjön az új bat-okkal.

set EXENAM=%1
set TARGET=%BUILD_EXE%\%1.exe 
set RSPLNK=%BUILD_OBJ%\rsplink
set OBJECTS=%BUILD_OBJ%\objects

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

ccomp c++ @%RSPLNK% 2>outlnk
goto iferror
 

:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto bor
 
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

link @%RSPLNK% >outlnk
goto iferror


:bor --------------------------------------------------------------------------
if not "%cccbin%"=="bor" goto cccbin_not_set

set CONCAT=-c -L
set CONCATPRE=
set CONCATPOST=;
call %BUILD_BAT%\_concat %BUILD_LPT%
echo %CONCAT% %BUILD_SYS% + >%RSPLNK%


if exist %OBJECTS% goto endobj_brx
set CONCAT=
:begobj_br
if [%1]==[] goto endobj_br
  set CONCAT=%CONCAT% %BUILD_OBJ%\%1
  shift
  goto begobj_br
:endobj_br
echo %CONCAT% >>%RSPLNK%
:endobj_brx

type %OBJECTS% >>%RSPLNK% 2>nul

echo %TARGET% >>%RSPLNK%
echo nul >>%RSPLNK%
 
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

 