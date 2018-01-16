@echo off
call bapp_w320 -lccc%CCCVER%_crypto
copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
 
 