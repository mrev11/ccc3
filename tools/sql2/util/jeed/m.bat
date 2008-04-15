@echo off
call bapp_w32_.bat @parfile.bld -bccc3_xmldom
copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%


