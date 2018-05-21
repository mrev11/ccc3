@echo off 
echo SETUP: link %1
set EXEDIR=%CCCDIR%\usr\bin\%CCCUNAME%
c++ -o %EXEDIR%\%1.exe *.o  ..\*.o  2>log-link
