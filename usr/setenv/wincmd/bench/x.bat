@echo off
:: teszt inditas cmd-ben

echo 1000 >counter

:loop
if not  exist counter  goto stop
    proba.exe
goto loop
:stop
