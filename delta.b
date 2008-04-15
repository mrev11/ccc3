#!/bin/bash
SINCE=20061201
setperm set
$CCCDIR/ccctools/pack/copyright.exe
sx -s. @delta.savex -d$SINCE  | zip -uy delta.zip -@ 
$CCCDIR/ccctools/pack/datename.exe delta.zip
