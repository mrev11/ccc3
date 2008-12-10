#!/bin/bash
#set -x

#-------------------
# CCCDIR verification
#-------------------

touch cccdir
if [ ! $CCCDIR/cccdir -ef cccdir ]; then
    rm cccdir
    echo "install.b must run from \$CCCDIR as working directory"
    exit 1
else
    rm cccdir
fi

if  ! test -f ./usr/bin/$CCCUNAME/__unix.b; then
    echo "CCCUNAME environment variable not properly set"
    exit 1
fi

if  ! test -f ./usr/options/$CCCBIN/compile.opt; then
    echo "CCCBIN environment variable not properly set"
    exit 1
fi

#-------------------
# initial setup
#-------------------

pushd setup/setup-unix >/dev/null; m; popd >/dev/null
if ! build.exe -v; then
    echo "initial setup failed"
    exit 1
fi    
if ! prg2ppo.exe -v; then
    echo "initial setup failed"
    exit 1
fi    
if ! ppo2cpp.exe -v; then
    echo "initial setup failed"
    exit 1
fi    
if ! removecr.exe -x; then
    echo "initial setup failed"
    exit 1
fi    

pushd setup/setup-flex >/dev/null; m; popd >/dev/null
if ! flex.exe -V; then
    echo "flex not installed"
    echo "install flex then run install.b again"
    exit 1
fi    

pushd setup/setup-lemon >/dev/null; m; popd >/dev/null
if ! lemon.exe -x; then
    echo "lemon not installed"
    echo "install lemon then run install.b again"
    exit 1
fi    

#-------------------
# ccclib
#-------------------

pushd ccclib; m; popd

#-------------------
# ccctools
#-------------------
 
pushd ccctools/build; m; popd
pushd ccctools/ppo2cpp; m; popd
pushd ccctools/prg2ppo; m; popd
pushd ccctools/removecr; m; popd
pushd ccctools/mklink; m; popd

#-------------------
# terminal
#-------------------
 
pushd terminal/unix; m; popd


#-------------------
# tabobj
#-------------------

pushd tabobj/tbbtbtx; m; popd

#-------------------
# tools
#-------------------

pushd tools/crypto; m; popd
pushd tools/dbaseiii; m; popd
pushd tools/dbfview; m; popd
pushd tools/ddict2; m; popd
pushd tools/list; m; popd
pushd tools/mask; m; popd
pushd tools/savex; m; popd
pushd tools/setperm; m; popd
pushd tools/socket; m; popd
pushd tools/tran2cpp; m; popd  #string translation libraries
pushd tools/websrv; m; popd
pushd tools/xmldom; m; popd
pushd tools/xmlrpc; m; popd
pushd tools/xstart; m; popd    #listener
pushd tools/z; m; popd         #unicode text editor
pushd tools/zgrep; m; popd

#-------------------
# other
#-------------------

pushd jt/jtlib; m; popd
pushd tutor/oggedit; m; popd

pushd tutor/dtree; m; popd
pushd tutor/pm/$CCCUNAME; m; popd
pushd tutor/readline; m; popd
pushd tutor/rename; m; popd


#-------------------
# extensions
#-------------------

#pushd jt; mkall.b; popd
#pushd tools/sql2; mkall.b; popd
#pushd gtk; mkall.b; popd

#-------------------
# symlinks
#-------------------

pushd $CCCDIR/usr/bin/$CCCUNAME; mklink.exe; popd

