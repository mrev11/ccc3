@echo off
mkdir exe-sqlite3 2>nul
copy  start-scripts\*.bat exe-sqlite3 2>nul

bapp_w32c  @parfile-l.bld
