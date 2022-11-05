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

export XMLRPC_TIMEOUT=300

$SERVERDIR/rpcsession.exe                       2>>err-rpcsession     &
$SERVERDIR/rpcsession.exe                       2>>err-rpcsession     &
$SERVERDIR/rpctest.exe                          2>>err-rpctest        & 
 
$SERVERDIR/rpcwrapper.exe --reuseaddr \
    -k  localhost.pem \
    -l  $RPCHOST:$PORTPLAIN:plain \
    -l  $RPCHOST:$PORTSSL:ssl



# Megjegyzesek:

# A wrapper a $PORTPLAIN es $PORTSSL portokon figyel.
# Az XMLRPC_WRAPPER valtozo beallitasatol fuggoen a szerverek 
# (egymas kozott) plain vagy ssl socketen kommunikalnak.
# Az is lehetseges, hogy a kulonbozo szervereknek 
# kulonfelekeppen adjuk meg az XMLRPC_WRAPPER valtozot,
# ez esetben a wrapper a plain es titkos vonalon kommunikalo
# reszvevok kozott automatikusan fordit.

# A demoban kliensek is barmelyik portra kapcsolodhatnak,
# es ettol fuggoen a wrapper<-->kliens forgalom plain vagy 
# titkositott lesz, a wrapper automatikusan ki/betitkosit.

# Ertelmes konfiguracio lehet pl., hogy a wrapper egy belso
# interfeszen plain porton figyeljen, mig egy kulso interfeszen
# SSL-t alkalmazzon.

# A jelen demoban sehol nincs hitelesites.
# Ha hitelesitesre van szukseg, akkor minden reszvevonek
# letre kell hoznia egy sslctx objektumot, amiben megadja
# a sajat maga igazolasara szolgalo kulcsot, es az elfogadott
# partnerek bizonyitvanyat.
#
# A wrappernek a --keyfile, --cafile, --capath opciokban 
# lehet ezeket megadni.
#
# A tobbi program a warpperhez kapcsolodas elott az 
# xmlrpc_sslcontext(ctx) hivassal beallithat egy statikus
# sslctx objektumot.
