@echo on
call bapp_w320  -lccc3_xmldom
copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
 