@echo off
echo OBJ2LIB.BAT %1 

:Vagy a parameterkent vagy az objects-ben 
:kapott fileket kell rsplib-be kiirni.
:Build vagy egyik vagy masik modon mukodik,
:az egyiknek uresnek kell lennie.
:Azert van ez a kettosseg, hogy atmenetileg 
:a regi build is mukodjon az uj bat-okkal.

pushd %BUILD_OBJ%

set LIBNAM=%1
set TARGET=%1.lib
set LSTFIL=%1.lst
set RSPLIB=rsplib-%1
set OUTLIB=outlib-%1
set ERROR=error--outlib-%1

set OBJECTS=objects-%1
if exist %OBJECTS% goto objects_ok
set OBJECTS=objects
:objects_ok

del %TARGET% 2>nul
del %LSTFIL% 2>nul
del %RSPLIB% 2>nul
del %ERROR% 2>nul

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

ccomp ar @%RSPLIB% 2>%OUTLIB%
goto iferror


:msc --------------------------------------------------------------------------
if not "%cccbin%"=="msc" goto cccbin_not_set

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

lib @%RSPLIB% >%OUTLIB%
goto iferror


:cccbin_not_set ---------------------------------------------------------------
echo cccbin environment variable not set >error
goto stop
 
 
:iferror ----------------------------------------------------------------------
if not errorlevel 1 goto stop

    touch error
    del   %TARGET% 2>nul
    copy  %OUTLIB% %ERROR% >nul
    type  %OUTLIB%

:stop

del  %OUTLIB% 2>nul
del  %OBJECTS% 2>nul
del  objects 2>nul

popd
@echo -------------------------------------------------------------------------
