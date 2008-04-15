#!/bin/bash

export TEMP=~/.temp
export GREP='grep -i -H -n'
export FIND='export CCC_TERMINAL=dummy;\
             savex.exe . -f -i.prg.cpp.ch.h.tex. -r.ppo. -lrobj*'
export CCC_XSIZE=90x25
 
zgrep.exe "$1" "$2" 

