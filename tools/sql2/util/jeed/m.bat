@echo off
call bapp_w32_.bat @parfile.bld -bcrypto -bssl
copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%


