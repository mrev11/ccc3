@echo off
:Windowson nem tudja magát felülírni,
:ezért ideiglenesen idehozunk egy példányt

set EXE=%CCCDIR%\usr\bin\%CCCUNAME%
copy %EXE%\build.exe . >nul
call bapp_w32_ "BUILD_EXE=%EXE%"
del build.exe
