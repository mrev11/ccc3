#!/bin/bash
find . -type d | while read NAME; do
  rm -f $NAME/*.class $NAME/*.jar $NAME/*.bak $NAME/*.lib $NAME/*.so $NAME/*.obj $NAME/*.exe $NAME/out*
done
