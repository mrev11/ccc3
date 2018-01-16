@echo off
call bapp_w32_  -lccc%CCCVER%_regex -bpcreposix
copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
copy *.ch  %CCCDIR%\usr\include
