#!/bin/bash
echo
ps -A  | grep websrv.exe | while read PID; do
    echo $PID
done
