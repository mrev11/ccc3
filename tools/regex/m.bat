@echo off
call bapp_w32_  -lccc3_regex -bpcreposix
copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
copy *.ch  %CCCDIR%\usr\include
