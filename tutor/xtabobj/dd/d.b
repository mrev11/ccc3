#!/bin/bash
ddict2 .. xddict >log

#bapp_unix0.b -lxddict

if test -s log; then
    list log &
fi
