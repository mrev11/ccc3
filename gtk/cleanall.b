#!/bin/bash

find . -type d | while read NAME; do
    rm -f $NAME/*.obj  $NAME/*.exe $NAME/*.lib  $NAME/*.so $NAME/*.a
done

