@echo off

set OREF_SIZE=2000000
set DIFF=diff

set CCCTERM_SIZE=100x40

set TERMDIR=%CCCDIR%\terminal-nt-alt
set CCCTERM_KEYDEF=%TERMDIR%\terminal\keydef-vm.v2i
set CCC_TERMINAL_START=%TERMDIR%\terminal\terminal.exe


:savex.exe . %1 %2 %3 %4 %5 %6 
start /b savex.exe . %1 %2 %3 %4 %5 %6 


:set CCC_TERMINAL_START=
:start savex . %1 %2 %3 %4 %5 %6 

