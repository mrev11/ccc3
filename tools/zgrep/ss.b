#!/bin/bash

export TEMP=~/.temp
export GREP='grep -i -H -n'
export FIND='savex.exe . -f -i.prg.cpp.ch.h.tex.lem.lex. -r.ppo. -lrobj*'
export CCC_XSIZE=90x25
 
zgrep.exe "$1" "$2" 

