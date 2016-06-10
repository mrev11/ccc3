@echo off
del error 2>nul
call bapp_w32_ 
:Windowson nem tudja magat felulirni
copy build.exe %CCCDIR%\usr\bin\windows
del build.exe