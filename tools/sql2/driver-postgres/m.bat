@echo off
call bapp_w32_  -lccc%CCCVER%_sql2_postgres

copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
copy sql.ch %CCCDIR%\usr\include

