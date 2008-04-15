#!/bin/bash
find . -type d | while read NAME; do
    rm -f $NAME/*.class $NAME/*.bak  $NAME/*.log
done

