#!/bin/bash

if ! [ -d ../html ]; then
    ln -s $CCCDIR/doc/html ../html 2>/dev/null
fi



cp -pf *.png ../html
 