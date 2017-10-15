@echo off

call t--host.bat


sslforw-term.exe  %host%:40002  terminal.exe

