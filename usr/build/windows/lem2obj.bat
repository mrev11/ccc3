@echo off
echo LEM2OBJ.BAT %1 %2 

set OUTLEM=outlemon-%1
set ERROR=error--outlemon-%1

del %ERROR% 2>nul
del %OUTLEM% 2>nul
md ppo 2>nul

:Lemon forditas
lemon.exe -q %2\%1.lem 1>%OUTLEM%
if not errorlevel 1 goto lemon_ok
    touch error
    del %2\%1.c 2>nul
    move %OUTLEM% %ERROR% >nul 
    type %ERROR%
    goto stop
:lemon_ok

:C++ forditas (cpp-->obj)
move %2\%1.c ppo\%1.cpp >nul
call %BUILD_BAT%\_compile %1 ppo

:stop
del %OUTLEM% 2>nul
@echo -------------------------------------------------------------------------

