#!/bin/bash

find . -type d | while read NAME; do
    rm -f $NAME/*.obj
done

