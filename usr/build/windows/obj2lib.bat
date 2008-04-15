@echo off
echo OBJ2LIB.BAT %1 

:Vagy a paraméterként vagy az objects-ben 
:kapott filéket kell rsplib-be kiírni.
:Build vagy egyik vagy másik módon működik,
:az egyiknek üresnek kell lennie.
:Azért van ez a kettősség, hogy átmenetileg 
:a régi build is működjön az új bat-okkal.

pushd %BUILD_OBJ%

set TARGET=%1.lib
set LSTFIL=%1.lst
set RSPLIB=rsplib
set OBJECTS=objects

del %TARGET% 2>nul
del %RSPLIB% 2>nul
del error 2>nul

:mng --------------------------------------------------------------------------
if not "%cccbin%"=="mng" goto msc

echo q %TARGET% >%RSPLIB%

if exist %OBJECTS% goto endobj_mn
shift
:begobj_mn
if [%1]==[] goto endobj_mn
  echo %1.obj >>%RSPLIB%
  shift
  goto begobj_mn
:endobj_mn

type %OBJECTS% >>%RSPLIB% 2>nul

ccomp ar @%RSPLIB% 2>outlib
goto iferror


:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto bor

echo -OUT:%TARGET% >%RSPLIB%

if exist %OBJECTS% goto endobj_ms
shift
:begobj_ms
if [%1]==[] goto endobj_ms
  echo %1.obj >>%RSPLIB%
  shift
  goto begobj_ms
:endobj_ms

type %OBJECTS% >>%RSPLIB% 2>nul

lib @%RSPLIB% >outlib
goto iferror


:bor --------------------------------------------------------------------------
if not "%cccbin%"=="bor" goto cccbin_not_set

echo %TARGET% /C /P256 ^& >%RSPLIB% 

if exist %OBJECTS% goto endobj_br
shift
:begobj_br
if [%1]==[] goto endobj_br
  echo +%1 ^& >>%RSPLIB%
  shift
  goto begobj_br
:endobj_br

type %OBJECTS% >>%RSPLIB% 2>nul
echo ,%LSTFIL% >>%RSPLIB% 
 
tlib @%RSPLIB%
goto iferror


:cccbin_not_set ---------------------------------------------------------------
echo cccbin environment variable not set >error
goto stop
 
 
:iferror ----------------------------------------------------------------------
if errorlevel 1 copy outlib error >nul

:stop
popd
@echo -------------------------------------------------------------------------
