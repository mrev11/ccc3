@echo off 
echo LEX2OBJ.BAT %1 %2 

del error 2>nul
md ppo 2>nul


:LEX fordítás
flex.exe %BUILD_LEX% -L -oppo\%1.cpp %2\%1.lex 2>outflex
if errorlevel 1 copy  outflex error >nul
if exist error goto stop


:C++ fordítás (cpp-->obj)
call %BUILD_BAT%\_compile %1 ppo

:stop
@echo -------------------------------------------------------------------------

