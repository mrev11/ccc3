@echo off

:: windows batch 
if "%MSYSTEM%" == "MSYS" (
    echo "script cannot run in MSYS2"
    exit 1
)

if not "%CCCVER%" == "%1" (
    echo "CCCVER (=%CCCVER%) environment variable not properly set"
    exit 1
)

touch cccdir
if not exist %CCCDIR%\cccdir (
    del cccdir
    echo "script must start from CCCDIR as working directory"
    exit 1
) else (
    del cccdir
)

if not exist .\usr\bin\%CCCUNAME%\__common.bat (
    echo "CCCDIR\usr\bin\CCCUNAME\__common.bat found"
    echo "CCCUNAME (=%CCCUNAME%) environment variable not properly set"
    exit 1
)

if not exist .\usr\options\%CCCBIN%\compile.opt (
    echo "CCCDIR\usr\options\CCCBIN\compile.opt not found"
    echo "CCCBIN (=%CCCBIN%) environment variable not properly set"
    exit 1
)

cppver.bat
