@echo off
echo LEX2OBJ.BAT %1 %2 

set OUTFLEX=outflex-%1
set ERROR=error--outflex-%1

del %ERROR% 2>nul
md ppo 2>nul


:LEX forditas
flex.exe %BUILD_LEX% -oppo\%1.cpp %2\%1.lex 2>%OUTFLEX%
if not errorlevel 1 goto flex_ok
    touch error
    del ppo\%1.cpp 2>nul
    copy %OUTFLEX% %ERROR% >nul 
    type %OUTFLEX%
    goto stop

:flex_ok

:C++ forditas (cpp-->obj)
call %BUILD_BAT%\_compile %1 ppo

:stop

del %OUTFLEX% 2>nul

@echo -------------------------------------------------------------------------

