#!/bin/bash
export OREF_SIZE=800000
export LIST=list.exe
export CCCTERM_SIZE=120x32
savex.exe "$@"  '@savex.par' &
 