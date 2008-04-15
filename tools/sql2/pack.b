#!/bin/bash
#set -x

NAME=sql2

cat >content.savex <<EOF
-lx$NAME*.zip
-r.ppo.html.dvi.semaphor.tmp.
-lrobj*
-lrexe*
-x.bak.obj.exe.ppo.savex.
-lxout*
-lxlog*
EOF


setperm set
$CCCDIR/ccctools/pack/copyright.exe

WDIR=$(basename $(pwd))
pushd ..
export CCC_TERMINAL=dummy
savex -s$WDIR  @$WDIR/content.savex  -f | zip -uy $WDIR/$NAME  -@
popd

$CCCDIR/ccctools/pack/datename.exe $NAME.zip
rm content.savex

