@echo off
call bapp_w32_ -lccc3_tds @parfile.bld
copy obj%CCCBIN%\ccc3_tds.lib %CCCDIR%\usr\lib\%CCCBIN%
