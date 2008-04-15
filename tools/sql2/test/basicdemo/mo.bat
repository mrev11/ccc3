@echo off

mkdir exe-ora 2>nul

copy start-scripts\*.bat  exe-ora 2>nul

pushd tds 
    mkentitylib.exe
popd    

bapp_w32c  @parfile-o.bld

