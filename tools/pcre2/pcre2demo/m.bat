@echo off 
call bapp_w320.bat   -xpcre2demo -bpcre2-8.dll

:: dll helyett static konyvtarakkal is lehet linkelni
:: ehhez a c forrasokban megadjuk: #define PCRE2_STATIC

