
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

// Hasonló, mint test-a, csak a selectek lockolnak.
// Most minden program úgy viselkedik, mint a DB2 test-a-ban,
// ami igazolja, hogy DB2 MVCC helyett csak lockol.

// DB2      Ok
// SQLite3  nincs "for update", azaz nincs lock, mert egy felhasználós
// MySQL    Ok
// Oracle   Ok
// Postgres Ok



#define WAIT   ? "press any key"; inkey(0)


#include "sql.ch"

****************************************************************************************
function main(db,isolev)

local con:=connect(db,isolev)
local tab:=isol.tableEntityNew(con)

local con1:=connect(db,isolev)
local tab1:=isol.tableEntityNew(con1)


    ? "látja?"
    query(tab)
 
    concurrent(tab1)

    WAIT

    ? "nem látja?"
    query(tab)

    con:sqlcommit
    
    WAIT
    
    ? "na látja!"
    query(tab)

    con:sqlcommit
    con:sqldisconnect    
    
    WAIT
    
    ?

****************************************************************************************
function query(tab)
local rowset,row
    rowset:=tab:select_name("a",LOCK_WAIT)
    while( NIL!=(row:=rowset:next) )
        ? row:key, row:name, row:number
    end

****************************************************************************************
function concurrent(tab)

local row

    row:=tab:find({"1"})
  //row:=tab:find({"1"},LOCK_WAIT)
    row:delete

    row:=tab:find({"2"})
    row:name:="aa"
    row:update

    row:=tab:find({"3"})
    row:number:=11
    row:update

    row:=tab:find({"5"})
    row:name:="a"
    row:number:=12
    row:update
    
    row:=tab:instance
    row:key:="8"
    row:name:="a"
    row:number:=10
    row:insert

    tab:connection:sqlcommit
    tab:connection:sqldisconnect    

****************************************************************************************
