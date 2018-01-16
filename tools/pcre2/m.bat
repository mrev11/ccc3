@echo off
call bapp_w32_ @parfile.bld

copy obj%CCCBIN%\*.lib  %CCCDIR%\usr\lib\%CCCBIN%
copy *.ch  %CCCDIR%\usr\include



:: ha dll helyett static konyvtarakkal akarunk linkelni
:: akkor a cpp forrasokban megadjuk: #define PCRE2_STATIC
