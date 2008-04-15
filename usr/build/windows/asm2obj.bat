@echo off 
@echo ASM2OBJ.BAT %1 %2 
 
set TARGET=%BUILD_OBJ%\%1.obj
md %BUILD_OBJ% 2>nul
del %TARGET% 2>nul
del error 2>nul

:tasm32 /mx /m2 %2\%1,%TARGET%; >outasm
wasm  %2\%1 -fo=%TARGET% >outasm 

if errorlevel 1 copy outasm error >nul
if exist error goto stop

:stouch %TARGET%
 
:stop
@echo -------------------------------------------------------------------------


 