@echo off
call bapp_w320 -lccc%CCCVER%_dbaseiii

copy  obj%CCCBIN%\*.lib %CCCDIR%\usr\lib\%CCCBIN%

 