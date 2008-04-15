#!/bin/bash

find . -type d | while read NAME; do
    rm -f $NAME/*.obj $NAME/*.o $NAME/*.lib  $NAME/*.a
    rm -f $NAME/*.exe $NAME/*.so
done

