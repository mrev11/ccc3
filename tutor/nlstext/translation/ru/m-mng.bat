@echo off
:MinGW kell hozzá
set NAME=nlstext
set LANG=ru

tran2cpp.exe %NAME%.%LANG%.tran  %NAME%.%LANG%.cpp
call bapp_w32_
c++ -o %NAME%.%LANG%.dll obj%CCCBIN%\%NAME%.%LANG%.obj -shared
strip %NAME%.%LANG%.dll

:a PATH-ba kell tenni
move  %NAME%.%LANG%.dll ..
