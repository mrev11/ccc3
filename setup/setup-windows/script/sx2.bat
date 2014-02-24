@echo off


set OREF_SIZE=2000000
set DIFF=diff

set CCC_TERMINAL_START=%CCCDIR%\terminal-nt\termclnt\termclnt.exe


:savex.exe . %1 %2 %3 %4 %5 %6
start /b savex.exe . %1 %2 %3 %4 %5 %6

