@echo off
call bapp_w32_  -lccc3_sql2_postgres

copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
copy sql.ch %CCCDIR%\usr\include

