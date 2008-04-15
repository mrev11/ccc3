@echo off
call clean.bat
javac jterminal.java 2>log-jterminal
call mkjar.bat
type log-jterminal
