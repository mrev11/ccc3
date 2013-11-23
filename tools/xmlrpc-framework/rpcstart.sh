#!/bin/bash
#set -x

rm log-*  2>/dev/null 
rm err-*  2>/dev/null 
 
export CCC_TABLIB=btbtx

RPCHOST=localhost
PORTPLAIN=45000
PORTSSL=45001

SERVERDIR=`pwd`/server
 
export XMLRPC_WRAPPER=$RPCHOST,$PORTPLAIN,PLAIN
#export XMLRPC_WRAPPER=$RPCHOST,$PORTSSL,SSL

export XMLRPC_TIMEOUT=20

$SERVERDIR/rpcsession.exe                       2>>err-rpcsession     &
$SERVERDIR/rpcsession.exe                       2>>err-rpcsession     &
$SERVERDIR/rpctest.exe                          2>>err-rpctest        & 
 
$SERVERDIR/rpcwrapper.exe --reuseaddr \
    -k  localhost.pem \
    -l  $RPCHOST:$PORTPLAIN:plain \
    -l  $RPCHOST:$PORTSSL:ssl



# Megjegyzések:

# A wrapper a $PORTPLAIN és $PORTSSL portokon figyel.
# Az XMLRPC_WRAPPER változó beállításától függően a szerverek 
# (egymás között) plain vagy ssl socketen kommunikálnak.
# Az is lehetséges, hogy a különböző szervereknek 
# különféleképpen adjuk meg az XMLRPC_WRAPPER változót,
# ez esetben a wrapper a plain és titkos vonalon kommunikáló
# részvevők között automatikusan fordít.

# A demóban kliensek is bármelyik portra kapcsolódhatnak,
# és ettől függően a wrapper<-->kliens forgalom plain vagy 
# titkosított lesz, a wrapper automatikusan ki/betitkosít.

# Értelmes konfiguráció lehet pl., hogy a wrapper egy belső
# interfészen plain porton figyeljen, míg egy külső interfészen
# SSL-t alkalmazzon.

# A jelen demóban sehol nincs hitelesítés.
# Ha hitelesítésre van szükség, akkor minden részvevőnek
# létre kell hoznia egy sslctx objektumot, amiben megadja
# a saját maga igazolására szolgáló kulcsot, és az elfogadott
# partnerek bizonyítványát.
#
# A wrappernek a --keyfile, --cafile, --capath opciókban 
# lehet ezeket megadni.
#
# A többi program a warpperhez kapcsolódás előtt az 
# xmlrpc_sslcontext(ctx) hívással beállíthat egy statikus
# sslctx objektumot.
