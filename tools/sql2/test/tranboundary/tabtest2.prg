
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

//listázza az egész táblát

#include "sql.ch"

function main(db)   //db: P,M,O,D,L.
local con,tab,rowset,row

    set date format 'yyyy-mm-dd'

    if( db$'M')
        con:=sql2.mysql.sqlconnectionNew() 
    elseif( db$'P')
        con:=sql2.postgres.sqlconnectionNew() 
    elseif( db$'D')
        con:=sql2.db2.sqlconnectionNew() 
    elseif( db$'O')
        con:=sql2.oracle.sqlconnectionNew() 
    elseif( db$'L')
        con:=sql2.sqlite3.sqlconnectionNew() 
    end
    ? con:version

    tab:=proba.tableEntityNew(con)
    rowset:=tab:select_ord //összes sor
    while( NIL!=(row:=rowset:next) )
        ? row:szamlaszam, ;
          row:devnem, ;
          row:nev, ;
          row:egyenleg::str(10,2), ;
          row:sorszam, ;
          row:tulmenflag, ;
          row:konyvkelt, ;
          row:megjegyzes
          //exit  //ha csak az első fetch-ig mérünk
    end
    rowset:close

    con:sqldisconnect
