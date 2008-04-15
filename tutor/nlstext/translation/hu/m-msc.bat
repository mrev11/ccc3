@echo off
:MSC kell hozzá
set NAME=nlstext
set LANG=hu

tran2cpp.exe %NAME%.%LANG%.tran  %NAME%.%LANG%.cpp
call bapp_w32_
link /dll /out:%NAME%.%LANG%.dll /export:hashtable_fill obj%CCCBIN%\%NAME%.%LANG%.obj 

:a PATH-ba kell tenni
move  %NAME%.%LANG%.dll ..
del   %NAME%.%LANG%.exp
del   %NAME%.%LANG%.lib
