#!/bin/bash
#set -x

NAME=jtpython

cat >content.savex <<EOF
-lx$NAME*.zip
-x.bak.pyc.savex.cer.
EOF


setperm set
$CCCDIR/ccctools/pack/copyright.exe

WDIR=$(basename $(pwd))
pushd ..
savex -s$WDIR  @$WDIR/content.savex  -f | zip -uy $WDIR/$NAME  -@
popd

$CCCDIR/ccctools/pack/datename.exe $NAME.zip
rm content.savex

