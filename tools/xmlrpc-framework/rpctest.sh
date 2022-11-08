#!/bin/bash
# kulon elinditja rpctest.exe-t

rm -f  log-*
rm -f  err-*
 
RPCHOST=localhost
PORTPLAIN=45000
PORTSSL=45001

SERVERDIR=`pwd`/server
 
export XMLRPC_WRAPPER=$RPCHOST,$PORTPLAIN,PLAIN
#export XMLRPC_WRAPPER=$RPCHOST,$PORTSSL,SSL

export XMLRPC_TIMEOUT=300

$SERVERDIR/rpctest.exe  2>>err-rpctest  & 



