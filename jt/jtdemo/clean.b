#!/bin/bash
find . -type d | while read NAME; do
  rm -f $NAME/*.bak $NAME/*.lib $NAME/*.obj $NAME/*.exe  # $NAME/*.dlg $NAME/*.pnl $NAME/out* 
done
