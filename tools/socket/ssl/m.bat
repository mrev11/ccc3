@echo off
call bapp_w320  -d. -dwindows  -lccc3_sslsocket

copy obj%cccbin%\*.lib  %cccdir%\usr\lib\%cccbin%
