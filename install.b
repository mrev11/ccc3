#!/bin/bash
#set -x

export CCCVER=3

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
    echo "CCCDIR/usr/bin/CCCUNAME/__unix.b not found"
    echo "CCCUNAME environment variable not properly set"
    exit 1
fi

if  ! test -f ./usr/options/$CCCBIN/compile.opt; then
    echo "CCCDIR/usr/options/CCCBIN/compile.opt not found"
    echo "CCCBIN environment variable not properly set"
    exit 1
fi

#-------------------
# initial setup
#-------------------

pushd setup/setup-flex  >/dev/null; m; popd >/dev/null
if ! flex.exe -V; then
    echo "flex.exe not installed"
    echo "install flex then run install.b again"
    exit 1
fi    

pushd setup/setup-lemon >/dev/null; m; popd >/dev/null
if ! lemon.exe -x; then
    echo "lemon.exe not installed"
    echo "install lemon then run install.b again"
    exit 1
fi    

pushd setup/setup-unix  >/dev/null; m; popd >/dev/null
if ! build.exe -v; then
    echo "build.exe not installed"
    echo "initial setup failed"
    exit 1
fi    
if ! prg2ppo.exe -v; then
    echo "prg2ppo.exe not installed"
    echo "initial setup failed"
    exit 1
fi    
if ! removecr.exe -x; then
    echo "removecr.exe not installed"
    echo "initial setup failed"
    exit 1
fi    

pushd ccctools/ppo2cpp  >/dev/null; m; popd >/dev/null
if ! ppo2cpp.exe -v; then
    echo "ppo2cpp.exe not installed"
    echo "initial setup failed"
    exit 1
fi    


#-------------------
# ccclib
#-------------------

pushd ccclib; m; popd

#-------------------
# ccctools
#-------------------
 
#pushd ccctools/build; m; popd
pushd ccctools/buildp; m; popd
pushd ccctools/prg2ppo; m; popd
pushd ccctools/removecr; m; popd
pushd ccctools/mklink; m; popd

#-------------------
# terminal
#-------------------
 
pushd terminal/unix; m; popd
#pushd terminal/unix-ncurses; m; popd
pushd terminal/unix-termkey; m; popd
pushd terminal/sslforw; m; popd

if test -f /usr/include/gtk-2.0/gtk/gtk.h; then
    pushd terminal/gtk; m; popd
fi

if test -f /usr/include/gtk-3.0/gtk/gtk.h; then
    pushd terminal/gtk3; m; popd
fi

#-------------------
# msk2say
#-------------------

pushd tools/mask; m; popd

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
pushd tools/regex; m; popd
pushd tools/savex; m; popd
pushd tools/setperm; m; popd
pushd tools/socket; m; popd
pushd tools/tdc2prgch; m; popd
pushd tools/tdccmp; m; popd
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
pushd tutor/fpath; m; popd


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

