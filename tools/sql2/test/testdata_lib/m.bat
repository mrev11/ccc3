@echo off

:set GENSCRIPT=bt2tds.exe
set GENSCRIPT=echo

%GENSCRIPT% ..\testdata\a.bt  -n testdata.a  -t konto.a  -p id
%GENSCRIPT% ..\testdata\b.bt  -n testdata.b  -t konto.b  -p id
%GENSCRIPT% ..\testdata\c.bt  -n testdata.c  -t konto.c  -p name

mkentitylib.exe --prgdir code_generated  testdata


bapp_w32_ -ltestdata_lib -dcode_generated
