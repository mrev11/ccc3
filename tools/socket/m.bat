@echo off
call bapp_w320  -d. -lccc%CCCVER%_socket
copy obj%cccbin%\*.lib  %cccdir%\usr\lib\%cccbin%

pushd ssl
    call m.bat
popd 
