@echo off
call bapp_w32_ -lccc3_glade @gtk-win.bld  @parfile.bld 
copy obj%CCCBIN%\*.lib %CCCDIR%\usr\lib\%CCCBIN%
