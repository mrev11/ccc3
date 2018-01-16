@echo off
call bapp_w32_  @parfile.bld   -bpcre2-8.dll  -bpcre2-16.dll

:: figyelem
:: Windowson  a 16 bites libet kell linkelni, mert sizof(wchar_t)==16
:: Linuxon    a 32 bites libet kell linkelni, mert sizof(wchar_t)==32
