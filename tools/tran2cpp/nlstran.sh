#!/bin/bash

LANG=$1
NAME=$2

cd $LANG
tran2cpp.exe nlstext.$LANG.tran  $NAME.$LANG.cpp
bapp_unix_.b -s$NAME.$LANG
rm -R *.$LANG.cpp
cp -pf ${BUILD_OBJ}/*.so   $CCCDIR/usr/lib

