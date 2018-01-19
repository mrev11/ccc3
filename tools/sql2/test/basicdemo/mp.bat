@echo off
mkdir exe-pg 2>nul
copy  start-scripts\*.bat exe-pg 2>nul

bapp_w32c  @parfile-p.bld
