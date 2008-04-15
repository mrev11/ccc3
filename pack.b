#!/bin/bash
#set -x
rm -f *.zip
setperm set

function pack()
{
    # $1 packagename
    # $2 rootdir

    $CCCDIR/ccctools/pack/pack-ccc3.exe $2 | zip -uy $1 -@  
    $CCCDIR/ccctools/pack/datename.exe $1.zip
}


$CCCDIR/ccctools/pack/copyright.exe

pack ccc3

pack ccc3-setup-unix        setup/setup-unix
pack ccc3-setup-windows     setup/setup-windows
pack ccc3-setup-lemon       setup/setup-lemon
pack ccc3-setup-flex        setup/setup-flex
pack ccc3-sql2              tools/sql2
pack ccc3-gtk               gtk
pack ccc3-jt                jt
