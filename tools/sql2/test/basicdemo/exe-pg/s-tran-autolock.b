#!/bin/bash
export CCCTERM_SIZE=72x16
#export SQLDEBUG=on
konkur-auto.exe  1000 >log-auto-1  &
konkur-auto.exe 10000 >log-auto-2  &

