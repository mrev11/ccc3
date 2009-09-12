#!/bin/bash
export CCCTERM_SIZE=72x16
#export SQLDEBUG=on
konkur-lock.exe  1000 &
konkur-lock.exe 10000 &

