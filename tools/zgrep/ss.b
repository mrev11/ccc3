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
export CCCTERM_SIZE=100x40
export CCC_XSIZE=$CCCTERM_SIZE


export TEMP=~/.temp
export GREP='grep -i -H -n'
export FIND='export CCC_TERMINAL=dummy;\
             savex.exe . -f -i.bat.prg.cpp.cpp_async.cc.ch.h.tex.lex.lem.java.inc.tds.js. -r.ppo. -lrobj* -lr*.nopack'

if !(echo "$CCCTERM_CONNECT" | grep "SOCKET:" >/dev/null); then
    export CCCTERM_CONNECT="$CCCDIR/usr/bin/$CCCUNAME/terminal-xft.exe" #choice: X
   #export CCCTERM_CONNECT="$CCCDIR/usr/bin/$CCCUNAME/ncterm.exe"       #choice: ncurses
fi


if echo "$CCCTERM_CONNECT" | grep "ncterm.exe" >/dev/null; then
    export CCCTERM_INHERIT=yes
    zgrep.exe "$1" "$2"         #must not run in bacground

elif echo "$CCCTERM_CONNECT" | grep "SOCKET:" >/dev/null; then
    zgrep.exe "$1" "$2"         #must not run in bacground

else    
    export CCCTERM_INHERIT=no   #choice: run childs in separate window
   #export CCCTERM_INHERIT=yes  #choice: run childs in inherited window
    zgrep.exe "$1" "$2" &       #may run in bacground
fi    

