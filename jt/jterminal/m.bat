@echo off

if not exist jterminal.jar (
    javac -version 

    javac jterminal.java 2>log-jterminal
    call mkjar.bat
    type log-jterminal
)

copy jterminal.jar %CCCDIR%\usr\bin\%CCCUNAME%
