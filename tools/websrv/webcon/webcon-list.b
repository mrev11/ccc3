#!/bin/bash

show()
{
    ps -A | grep webcon.exe | while read PID; do
        echo $PID
    done
}

show | less