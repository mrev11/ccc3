#!/bin/bash
export OREF_SIZE=8000000

export DIFF=diff
export LIST="*=list.exe:bt=tview"
export EDIT="*=z.exe %f:bt=tstru %f"
export PLAY='diff-report %f %s %w'

export CCCTERM_INHERIT=yes



#Pelda: 
#az osszes valtozas reportja a PLAY pluginnal
#inditas utan a K_ALT_P-t (shortcut) kell utni
#savex.exe -s$CCC2DIR/tools/savex -r:objlin:ppo: -i.prg.ch.ver. -md | tee report



savex.exe "$@"

 