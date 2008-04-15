#!/bin/bash

ps -A   | grep websrv-start.b | awk '{print $1}' | while read PID; do
    kill $PID
done

ps -A   | grep websrv.exe     | awk '{print $1}' | while read PID; do
    kill $PID
done

ps -A   | grep websrv.exe     | awk '{print $1}' | while read PID; do
    kill -KILL $PID
done
