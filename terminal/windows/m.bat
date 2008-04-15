@echo off
call bapp_w320g @parfile.bld


:copy terminal.exe %CCCDIR%\usr\bin\%CCCUNAME%
:copy *.v2i %CCCDIR%\usr\bin\%CCCUNAME%
