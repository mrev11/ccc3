@echo off
del error 2>nul
:Windowson nem tudja magat felulirni,
:ezert ideiglenesen idehozunk egy peldanyt

set EXE=%CCCDIR%\usr\bin\%CCCUNAME%
copy %EXE%\build.exe . >nul
call bapp_w32_ "BUILD_EXE=%EXE%"
del build.exe
