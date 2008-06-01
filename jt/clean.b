#!/bin/bash

find . -type d \
       -name ppo -o \
       -name objlin -o \
       -name objsol -o \
       -name objfre | xargs rm -rf

find . -type f \
       -name outerr -o \
       -name outcpp -o \
       -name outlnk -o \
       -name outpre -o \
       -name outlemon -o \
       -name outflex -o \
       -name error | xargs rm -f


find . -type d | while read NAME; do
  rm -f $NAME/*.class $NAME/*.jar $NAME/*.bak $NAME/*.lib $NAME/*.so $NAME/*.obj $NAME/*.exe $NAME/out* $NAME/log-*
done
