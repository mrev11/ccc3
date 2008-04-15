@echo off
mkdir exe-pg 2>nul

copy  start-scripts\*.bat exe-pg 2>nul

pushd tds 
    mkentitylib.exe 
popd

bapp_w32c  @parfile-p.bld
