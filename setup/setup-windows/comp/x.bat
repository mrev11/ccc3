@echo off 
echo link %1
set EXEDIR=%CCCDIR%\usr\bin\%CCCUNAME%
c++ -o %EXEDIR%\%1.exe *.o  ..\lib1\*.o  ..\lib2\*.o ..\lib3\*.o  2>log-link
