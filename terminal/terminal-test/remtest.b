#!/bin/bash


xterm -e  "xstart.exe -l log-xstart  xstart.par" &
sleep 1

#hol keletkeznek a kimenetek?
#  remio-ban -> akkor atvitte
#  helyben   -> akkor nem vitte at


export CCCTERM_REDIR_CONSOLE=n
export CCCTERM_REDIR_PRINTER=y
export CCCTERM_REDIR_ALTERNATE=y
export CCCTERM_REDIR_EXTRA=n
export CCCTERM_REDIR_USEUID=n

#export CCCTERM_CAPTURE_PRN=log-remio-prn           # PRN fajlba iranyitva
#export CCCTERM_CAPTURE_LPT1=log-remio-lpt1         # LPT1 fajlba iranyitva
export CCCTERM_CAPTURE_LPT1=pipe:ccclpr             # a terminal inditja a scriptet!

#cd remio && terminal-gtk.exe localhost 44965  &
cd remio && terminal-gtk.exe localhost 44966  

