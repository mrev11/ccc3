@echo off
call bapp_w32_  @parfile.bld
copy obj%CCCBIN%\*.lib %CCCDIR%\usr\lib\%CCCBIN%
