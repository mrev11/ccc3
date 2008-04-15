#!/bin/bash

find . -type d | while read NAME; do

    rm -f   $NAME/*.obj  \
            $NAME/*.lib  \
            $NAME/*.exe  \
            $NAME/*.so   \
            $NAME/*.bak  \
            $NAME/log-*  \
            $NAME/err-*  \
            $NAME/ppo/*

done
