@echo off 
:: minden lefordit
c++ -c -O0 -DMINGW -D_CCC_ -D_CCC3_ -DWIN32 -DWINDOWS -DMULTITHREAD -funsigned-char -mms-bitfields -I . -I %CCCDIR%\usr\include *.cpp
