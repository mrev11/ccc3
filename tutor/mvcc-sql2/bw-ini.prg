
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

#include "inkey.ch"
#include "sql.ch"

***********************************************************************************************
static function connect()
local con
local dbchoice:=memoread("DBCHOICE")::alltrim[1]

    if( dbchoice=="O" )
        con:=sql2.oracle.sqlconnectionNew()
        con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //session

    elseif( dbchoice=="P" )
        con:=sql2.postgres.sqlconnectionNew()
        con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //session

    elseif( dbchoice=="L" )
        con:=sql2.sqlite3.sqlconnectionNew()  // "db1:db1=konto"
        con:sqlIsolationLevel(ISOL_SERIALIZABLE,.t.)  //hatástalan
    end
    
    ? con:version

    return con


***********************************************************************************************
function main()

local con,tab,row,n

    set date format "yyyy-mm-dd"
    
    con:=connect()
    
    
    tab:=proba.tableEntityNew(con)
    
    begin
        tab:create
    end
    tab:zap
    
    for n:=0 to 9
        row:=tab:instance
        row:szamlaszam :=replicate(chr(asc("0")+n),24)
        row:devnem     :="HUF"
        row:nev        :=if( n%3==0,"BLACK","WHITE")
        row:insert
    next

    con:sqlcommit


***********************************************************************************************
