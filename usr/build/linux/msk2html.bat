#!/bin/bash
#set -x
echo MSK2HTML.BAT $@

if [ "$2" == "" ]; then
    msk2html.exe $1
else
    msk2html.exe $2/$1
fi


echo ----------------------------------------------------------------
