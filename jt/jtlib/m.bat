@echo off
call bapp_w320  @parfile.bld
copy  obj%CCCBIN%\*.lib %CCCDIR%\usr\lib\%CCCBIN%
 