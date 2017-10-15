@echo off

call t--host.bat

set SSLFORW_CAPATH=pem/clncert
:set SSLFORW_CAFILE=pem/clncert/localhost-cert.pem

set SSLFORW_PKEYFILE=pem/clnpkey/demo.pem
set SSLFORW_CERTFILE=pem/clnpkey/demo.pem


sslforw-term.exe  %host%:40003  terminal.exe

