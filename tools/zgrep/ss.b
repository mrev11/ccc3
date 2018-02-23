#!/bin/bash

#FIGYELEM, ezekre kell ugyelni:
#
#1) Az ncterm-es programok nem futhatnak hatterben.
#
#2) Az ncterm-es child programok csak orokolt terminallal mukodnek jol.
#   Maskepp ket terminal fut egyszerre, es osszekeverednek az uzenetek.
#
#3) Amikor a child a parentjetol orokolt terminalban fut,
#   akkor a parentnek mindenkepp meg kell varnia a child kilepeset, 
#   maskepp osszekeverednek az uzenetek (es barmi lehet, pl. coredump).
#   Ezt ncterm-es es X-es programoknal is be kell tartani.


export OREF_SIZE=200000
export CCCTERM_SIZE=120x40

export TEMP=~/.temp
export GREP='grep --text -i -H -n'
export FIND='savex.exe . -y -f -i.js.less.bat.prg.cpp.c.ch.h.lex.lem.java.tds.IMP.EXP. -r.ppo. -lrobj* -lr*.nopack'


if echo "$CCCTERM_CONNECT" | grep "ncterm.exe" >/dev/null; then
    export CCCTERM_INHERIT=yes
    zgrep.exe "$1" "$2"         #must not run in background

elif echo "$CCCTERM_CONNECT" | grep "SOCKET:" >/dev/null; then
    zgrep.exe "$1" "$2"         #must not run in background

else    
    export CCCTERM_INHERIT=no   #choice: separate window
    #export CCCTERM_INHERIT=yes  #choice: inherited window
    zgrep.exe "$1" "$2" &       #may run in bacground
fi    
