#!/bin/bash
#set -x

NAME=jt

cat >content.savex <<EOF
-lx$NAME*.zip
-x.class.exe.bak.jar.zip.xml.cer.bt.btx.dlg.pnl.log.savex.
-lxout*
-r.ppo.html.dvi.javademo.ssl.javalog.semaphor.tmp.backup.tmp.archiv.nopack.
-lrobj*
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

