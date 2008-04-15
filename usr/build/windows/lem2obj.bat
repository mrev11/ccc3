@echo off
echo LEM2OBJ.BAT %1 %2 

del error 2>nul
md ppo 2>nul

:Lemon fordítás

lemon.exe -q %2\%1.lem 2>outlemon 

if errorlevel 1 copy outlemon error >nul
if exist error goto stop
    copy %2\%1.c ppo\%1.cpp >nul
    call %BUILD_BAT%\_compile %1 ppo

:stop
del %2\%1.c 2>nul
@echo -------------------------------------------------------------------------


