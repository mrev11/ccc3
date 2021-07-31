@echo off 
call ../cc.bat
call ../xx.bat build
fpath build.exe
build.exe -v
