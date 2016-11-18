@echo off
set CCCTERM_SIZE=80x30

:set CCCTERM_GTKFONTSPEC=Courier New 14
set CCCTERM_GTKFONTSPEC=Monospace 15
set CCCTERM_CONNECT=%CCCDIR%\usr\bin\%CCCUNAME%\terminal-gtk.exe
:set CCCTERM_CONNECT=%CCCDIR%\usr\bin\%CCCUNAME%\terminal.exe

terminal-gtk.exe
:terminal.exe
