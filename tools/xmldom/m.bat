@echo on
call bapp_w320  -lccc%CCCVER%_xmldom
copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
 