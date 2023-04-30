@echo off 

::set CCCTERM_CONNECT=term://cterm.exe            && set CCCTERM_INHERIT=yes
set CCCTERM_CONNECT=term://console.exe          && set CCCTERM_INHERIT=yes
::set CCCTERM_CONNECT=term://terminal.exe         && set CCCTERM_INHERIT=no
::set CCCTERM_CONNECT=term://terminal-gtk3.exe    && set CCCTERM_INHERIT=no
::set CCCTERM_CONNECT=connect://i3x:55013         && set CCCTERM_INHERIT=no


%1
