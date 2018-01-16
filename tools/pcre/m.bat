@echo off 
call bapp_w32_.bat   @parfile.bld


copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
copy *.ch  %CCCDIR%\usr\include
