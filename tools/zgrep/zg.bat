@echo off
:pelda zg hasznalatara

grep -H -n main *.prg  >outpre
zg.exe outpre  main
del outpre


