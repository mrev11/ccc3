@echo off

del *.o
del *.lib
del %gnudir%\lib\pcreposix.lib
del %gnudir%\include\pcreposix.h
del %mscdir%\lib\pcreposix.lib
del %mscdir%\include\pcreposix.h

gcc dftables.c -o dftables.exe
dftables pcre_chartables.c
del *.o

gcc -c pcre_*.c
gcc -c *.cpp
ar q pcreposix.lib *.o

copy pcreposix.lib  %gnudir%\lib\pcreposix.lib
copy pcreposix.h    %gnudir%\include\pcreposix.h

copy pcreposix.lib  %mscdir%\lib\pcreposix.lib
copy pcreposix.h    %mscdir%\include\pcreposix.h
