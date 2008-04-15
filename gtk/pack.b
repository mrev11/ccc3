#!/bin/bash
#set -x

NAME=cccgtk

cat >content.savex <<EOF
-lx$NAME*.zip
-x.obj.exe.bak.so.lib.a.savex.bt.btx.
-lxout*
-lxlog
-lxpid
-lxexe
-r.ppo.html.dvi.code_generated.proba.utilsave.enums.
-r.objlin.objfre.objsol.objmsc.objmng.objbor.
-r.semaphor.tmp.backup.tmp.
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

