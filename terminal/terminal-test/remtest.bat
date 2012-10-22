@echo off

start xstart.exe xstart.par
sleep 1

:hol keletkeznek a kimenetek?
:  ha remio-ban  -> akkor atvitte
:  ha helyben    -> akkor nem vitte at


set CCCTERM_REDIR_CONSOLE=y
set CCCTERM_REDIR_PRINTER=y
set CCCTERM_REDIR_ALTERNATE=y
set CCCTERM_REDIR_EXTRA=n

set CCCTERM_CAPTURE_PRN=remio-printer.bak
set CCCTERM_CAPTURE_LPT1=remio-printer.bak

start     /d remio terminal.exe localhost 44965
start /b  /d remio terminal.exe localhost 44966

