#!/bin/bash

find . -type d | while read NAME; do
    rm -f $NAME/*.exe $NAME/*.so $NAME/*.lib  $NAME/*.a
done

