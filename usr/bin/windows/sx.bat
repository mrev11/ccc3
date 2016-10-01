@echo off
set OREF_SIZE=2000000

set DIFF=diff
set LIST="*=list.exe:bt=tview"
set EDIT="*=z.exe %%f:bt=tstru %%f"

:: %f helyere helyettesitodik a filename
:: ha nincs %f, automatikusan a vegere teszi
:: (a % karaktert vedeni kell -> %%)

set CCCTERM_INHERIT=yes

savex.exe %1 %2 %3 %4 %5 %6 

