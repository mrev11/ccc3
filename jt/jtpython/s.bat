@echo off

: 1) egyszerű listener ssl nélkül
:jtlisten 127.0.0.1:46000  python test-alert.py
 
: 2) egyszerű listener ssl forwardinggal (kell hozzá a server.pem filé)
:jtlisten 46000 sslforward.exe python test-alert.py -jtdebug

 
:3) önálló program indítás 
python test-alert.py -jtauto


:4) sokszori indítás jtstart-tal
:start /b jtstart python test-alert.py
 

 

