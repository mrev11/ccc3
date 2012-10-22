#!/bin/bash

find . -type d \
       -name ppo -o \
       -name objlin* -o \
       -name objsol* -o \
       -name objfre* | xargs rm -rf

find . -type f \
       -name outerr -o \
       -name outcpp -o \
       -name outlnk -o \
       -name outpre -o \
       -name outlemon -o \
       -name outflex -o \
       -name gccver.opt -o \
       -name compopt -o \
       -name rsplink -o \
       -name error | xargs rm -f

find . -type l | xargs rm -f


find . -type d | while read NAME; do
    rm -f $NAME/*.obj $NAME/*.o $NAME/*.lib  $NAME/*.a
    rm -f $NAME/*.exe $NAME/*.so
    rm -f $NAME/*.class $NAME/*.jar
    rm -f $NAME/*.bak
done

rm xstart.log
