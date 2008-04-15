#!/bin/bash

ps -A  | grep rpc | grep '.exe' | awk '{print $1}' | while read PID; do
    echo $PID
    kill $PID
done
