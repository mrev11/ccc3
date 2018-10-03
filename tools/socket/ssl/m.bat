@echo off
call bapp_w320  -d. -dwindows  -lccc%CCCVER%_sslsocket

copy obj%cccbin%\*.lib  %cccdir%\usr\lib\%cccbin%
