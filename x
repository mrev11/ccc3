#!/bin/bash

find . | while read file; do
    #echo $file
    if [[ ${file##*.} == savex ]]; then
        mv ${file}  ${file%.*}.dsync
    fi
done