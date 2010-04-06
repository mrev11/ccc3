#!/bin/bash

#-------------------
# extensions
#-------------------

pushd jt; mkall.b; popd
pushd tools/sql2; mkall.b; popd
pushd gtk; mkall.b; popd

#-------------------
# symlinks
#-------------------

pushd $CCCDIR/usr/bin/$CCCUNAME; mklink.exe; popd

