#!/bin/bash
ls *.zip | while read ZIP; do
    echo $ZIP
    unzip $ZIP
done
