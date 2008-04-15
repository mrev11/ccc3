#!/bin/bash
ddict2 . xddict1 >log

#bapp_unix0.b -lxddict

if test -s log; then
    list log &
fi
