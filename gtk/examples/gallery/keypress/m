#!/bin/bash

mkdir -p obj$CCCBIN
pkg-config --cflags gtk+-2.0  >obj$CCCBIN/gtk-cflags
pkg-config --libs   gtk+-2.0  >obj$CCCBIN/gtk-libs
echo -Wno-deprecated-declarations >>obj$CCCBIN/gtk-cflags

bapp_unix_.b  @parfile.bld  
