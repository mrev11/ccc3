@echo off 

set OPT=
set OPT=%OPT% -c
set OPT=%OPT% -O0
set OPT=%OPT% -DMINGW 
set OPT=%OPT% -D_CCC_ 
set OPT=%OPT% -D_CCC3_ 
set OPT=%OPT% -DWIN32 
set OPT=%OPT% -DWINDOWS 
set OPT=%OPT% -DMULTITHREAD 
set OPT=%OPT% -funsigned-char 
set OPT=%OPT% -mms-bitfields 
set OPT=%OPT% -I . 
set OPT=%OPT% -I %CCCDIR%\usr\include
set OPT=%OPT% -I %CCCDIR%\ccclib\src\include
set OPT=%OPT% -Wno-incompatible-ms-struct



if exist %1 goto cc-one
:cc-all
    echo SETUP: %cd%\*.cpp
    c++ %OPT% *.cpp
    goto stop

:cc-one
    echo SETUP: %1
    c++ %OPT% %1
    goto stop
    
:stop

    