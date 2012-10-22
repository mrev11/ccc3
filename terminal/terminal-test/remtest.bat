@echo off
start xstart.exe xstart.par
sleep 1


set CCCTERM_REDIR_CONSOLE=y
set CCCTERM_REDIR_PRINTER=y
set CCCTERM_REDIR_ALTERNATE=y


start     /d remio terminal.exe localhost 44965
start /b  /d remio terminal.exe localhost 44966

:hol keletkeznek a kimenetek?
:  ha remio-ban  -> akkor atvitte
:  ha helyben    -> akkor nem vitte at

