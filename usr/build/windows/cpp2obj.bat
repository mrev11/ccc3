@echo off 
echo CPP2OBJ.BAT %1 %2 

del error 2>nul

:C++ fordítás (cpp-->obj)
call %BUILD_BAT%\_compile %1 %2

:stop
@echo -------------------------------------------------------------------------
