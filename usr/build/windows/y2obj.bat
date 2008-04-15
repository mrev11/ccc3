@echo off 
echo Y2OBJ.BAT %1 %2 

del error 2>nul
md ppo 2>nul


:YACC fordítás
bison %BUILD_BSN% -l -d -o ppo\%1.cpp  %2\%1.y 2>outbison
if errorlevel 1 copy outbison error >nul
if exist error goto stop

if exist ppo\%1.cpp.h  copy ppo\%1.cpp.h %2\%1.hpp >nul
if exist ppo\%1.hpp    copy ppo\%1.hpp   %2\%1.hpp >nul

:C++ fordítás (cpp-->obj)
call %BUILD_BAT%\_compile %1 ppo

:stop
@echo -------------------------------------------------------------------------

 