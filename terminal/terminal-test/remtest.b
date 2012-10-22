#!/bin/bash


xterm -e  "xstart.exe xstart.par" &
sleep 1

#hol keletkeznek a kimenetek?
#  remio-ban -> akkor atvitte
#  helyben   -> akkor nem vitte at


export CCCTERM_REDIR_CONSOLE=y
export CCCTERM_REDIR_PRINTER=y
export CCCTERM_REDIR_ALTERNATE=y
export CCCTERM_REDIR_EXTRA=n

export CCCTERM_CAPTURE_PRN=remio-printer.bak
export CCCTERM_CAPTURE_LPT1=remio-printer.bak

#cd remio && terminal.exe localhost 44965  &
cd remio && terminal.exe localhost 44966  

