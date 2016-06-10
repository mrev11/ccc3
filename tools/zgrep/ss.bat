@echo off
:needs GNU grep
:eg. ftp://agnes.dida.physik.uni-essen.de/home/janjaap/mingw32/binaries/grep-2.1.zip
 
set GREP=grep -i -H -n
set FIND=savex.exe . -f -i.prg.cpp.ch.h.tex. -r.ppo. -lrobj*
 
zgrep.exe %1 %2

