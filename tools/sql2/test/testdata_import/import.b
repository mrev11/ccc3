#!/bin/bash

DATADIR=../testdata

# Mindkét esetben (Oracle/Postgres)
# a táblákat a "konto" sémába importáljuk.
# A program a sémát nem hozza létre magától,
# hanem azt előzőleg létre kell hozni.
# A két adatbáziskezelőben a schema nem teljesen
# ugyanazt jelenti. Az Oracleben a séma egyúttal
# usert is jelent, azaz egy sémát csak egy userrel
# együtt lehet létrehozni (ha jól értem).
# Postgresben a séma egyszerűen egy névtér
# (de akkor miért nem lehet többszintű?).

# Oracle esetén az ORACLE_CONNECT környezeti változót
# használják a programok a bejelentkezéshez, pl.
# "export ORACLE_CONNECT=konto@test/konto" hatására 
# a "konto" nevű felhasználó 
# a "test" adatbázisba (SID)
# a "konto" jelszóval
# fog bejelentkezni.
# A connect string mostani formája megegyzik az sqlplus
# és más utilityk által használt formával, pl. ez a parancs:
# "sqlplus konto@test/konto" azonnal belép az adatbázisba.

# Postgres esetén a Unix user fog bejelentkezni a saját 
# lokális adatbázisába, aminek neve megegyezik a user nevével. 
# Ez a default, nem kell hozzá jelszó.  Ha ez nem megfelelő, 
# akkor használható a POSTGRES_CONNECT környezeti változó, 
# amit úgy kell  beállítani, ahogy a PQconnectdb a paraméterében
# megköveteli.


# -d dbdriver
# Ez opció választja ki az adatbázis meghajtót (oracle/postgres).
#
# -e entityname
# E néven található meg az entity a btimport-ba linkelt könyvtárban.
#
# -f filename
# Az input tábla file specifikációja.

export SQLDEBUG=on

rm log*

btimport.exe -d $DBDRIVER  -e testdata.a  -f $DATADIR/a.bt
btimport.exe -d $DBDRIVER  -e testdata.b  -f $DATADIR/b.bt
btimport.exe -d $DBDRIVER  -e testdata.c  -f $DATADIR/c.bt
