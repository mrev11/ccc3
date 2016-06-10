@echo off
:Windowson nem tudja magat felulirni
del error 2>nul

set EXE=%CCCDIR%\usr\bin\%CCCUNAME%
copy %EXE%\ccomp.exe . >nul
call bapp_w32_ "BUILD_EXE=%EXE%"
del ccomp.exe
