@echo off
:Windowson nem tudja magat felulirni

set EXE=%CCCDIR%\usr\bin\%CCCUNAME%
copy %EXE%\ccomp.exe . >nul
call bapp_w32_ "BUILD_EXE=%EXE%"
del ccomp.exe
