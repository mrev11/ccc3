#!/bin/bash
export OREF_SIZE=8000000

export DIFF=diff
export LIST="*=list.exe:bt=tview"
export EDIT="*=z.exe %f:bt=tstru %f"

export CCCTERM_INHERIT=yes


savex.exe "$@"  '@savex.par' &
 