@echo off


start xstart.exe -l log-xstart xstart.par
sleep 1

::hol keletkeznek a kimenetek?
::  ha remio-ban  -> akkor atvitte
::  ha helyben    -> akkor nem vitte at


set CCCTERM_REDIR_CONSOLE=n
set CCCTERM_REDIR_PRINTER=y
set CCCTERM_REDIR_ALTERNATE=y
set CCCTERM_REDIR_EXTRA=n
set CCCTERM_REDIR_USEUID=n

::set CCCTERM_CAPTURE_PRN=log-remio-prn
::set CCCTERM_CAPTURE_LPT1=log-remio-lpt1
set CCCTERM_CAPTURE_LPT1=pipe:ccclpr

::start     /d remio terminal-gtk3.exe localhost 44965
start /b  /d remio terminal-gtk3.exe localhost 44966

