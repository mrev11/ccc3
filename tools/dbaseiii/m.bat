@echo off
call bapp_w320 -lccc3_dbaseiii

copy  obj%CCCBIN%\*.lib %CCCDIR%\usr\lib\%CCCBIN%

 