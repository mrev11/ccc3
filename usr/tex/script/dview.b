#!/bin/bash

echo active >dview
#kviewshell dvi $1 &>/dev/null
#kdvi $1 &>/dev/null
xdvi -bg lightgrey $1 2>/dev/null
#xdvi -bg lightgrey -s 6 $1
rm dview
