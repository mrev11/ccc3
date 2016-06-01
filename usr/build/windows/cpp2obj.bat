@echo off 
echo CPP2OBJ.BAT %1 %2 

:C++ forditas (cpp-->obj)
call %BUILD_BAT%\_compile %1 %2

@echo -------------------------------------------------------------------------
