@echo off

: 1) egyszerű listener ssl nélkül
:jtlisten 127.0.0.1:46000  empty.exe
 
: 2) egyszerű listener ssl forwardinggal (kell hozzá a server.pem filé)
jtlisten 46000 sslforward.exe empty.exe -jtdebug

 
:3) önálló program indítás 
:set JTERMINAL=start /b java -jar d:\jt1\jterminal\jterminal.jar localhost JTPORT
:start /b empty.exe -jtauto


:4) önálló program indítás
:start /b empty.exe -jtdebug -jtsocket :46000
:start /b java -jar d:\jt1\jterminal\jterminal.jar localhost 46000
 

:5) sokszori indítás jtstart-tal
:set JTERMINAL=start /b java -jar d:\jt1\jterminal\jterminal.jar localhost JTPORT
:start /b jtstart empty.exe
 

 

