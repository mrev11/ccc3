
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

//létrehozza a konto.proba és konto.szerencse táblákat

#ifdef EMLEKEZTETO

A konto schema name jön létre "magától",
hanem azt előzőleg létre kell hozni.

Oracle: 
    A konto user létrehozásával együtt jön létre a schema.
    Az sqlplus-ban végrehajtjuk:

    create tablespace konto logging
    datafile '/opt/oracle/base/oradata/test/konto.dbf'
    size 8M reuse autoextend on next 4M
    maxsize unlimited
    extent management local autoallocate
    segment space management auto;

    create user konto
    identified by konto
    default tablespace konto
    quota 100000M on konto  -- 100G;

    grant connect to konto;

    quit;

Posgres:
    A Postgresben a schema egy névtér (miért nem többszintű?).
    A psql-ben végrehajtjuk: 
    
    create schema konto;

#endif


function main()

local con, tableentity

    set date format "yyyy-mm-dd"
    set printer to log-te-create
    set printer on
 
    con:=sqlconnect()  

    tableentity:=proba.tableEntityNew(con)
    tableentity:drop      //drop table ...
    tableentity:create    //create table ...


    tableentity:=szerencse.tableEntityNew(con)
    tableentity:drop      //drop table ...
    tableentity:create    //create table ...

    con:sqldisconnect
 
    return NIL
 
    