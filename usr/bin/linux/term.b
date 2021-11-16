#!/bin/bash

# script 
# amivel az ncterm.exe-t kulon ablakban lehet hasznalni
# CCCTERM_CONNECT=${CCCDIR}/usr/bin/${CCCUNAME}/term.b

exec xterm -e ncterm.exe $@
