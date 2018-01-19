@echo off
mkdir exe-ora 2>nul
copy start-scripts\*.bat  exe-ora 2>nul

bapp_w32c  @parfile-o.bld

