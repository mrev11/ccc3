@echo off
:needs GNU grep
:eg. ftp://agnes.dida.physik.uni-essen.de/home/janjaap/mingw32/binaries/grep-2.1.zip
 
:set TEMP=.
set GREP=grep -i -H -n
set FIND=savex.exe . -f -i.bat.prg.cpp.c.ch.h.tex.java.lex.lem. -r.ppo. -lrobj*

 
zgrep.exe %1 %2

