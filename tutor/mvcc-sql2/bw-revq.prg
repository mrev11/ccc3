
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
function main(arg)

local con
local q,szla,nev

    set date format "yyyy-mm-dd"
    
    con:=connect()

    //Ellenpróba REPEATABLE READ módban (csak Postgres)
    //egy tranzakcióra (sorrend fontos)
    // con:sqlexec("rollback")
    // con:sqlexec("begin transaction")
    // con:sqlexec("set transaction isolation level repeatable read")
    

    //Ellenpróba REPEATABLE READ módban (csak Postgres)
    //egész session-re (sorrend fontos)
    // con:sqlexec("rollback")
    // con:sqlexec("set session characteristics as transaction isolation level repeatable read")
    // con:sqlexec("begin transaction")
    

    if( arg=="B" .or. arg=="W" )

        q:=con:sqlqueryNew("select szamla, megnevezes from konto.proba")
        while( q:next )
            ? szla:=q:getchar(1), nev:=q:getchar(2)

            if( arg=="B" )
                if( "WHITE"$nev )
                    ??  "->", nev:="BLACK"
                    con:sqlexec("update konto.proba set megnevezes=:2 where szamla=:1",{szla,nev})
                else
                    //nem változtat
                end
            end
        
            if( arg=="W" )
                if( "BLACK"$nev )
                    ??  "->", nev:="WHITE"
                    con:sqlexec("update konto.proba set megnevezes=:2 where szamla=:1",{szla,nev})
                else
                    //nem változtat
                end
            end

            sleep(100)
        end
        q:close

        ? "------------------------------"
    end
    
    
    if( arg=="W" )
        sleep(500)
    end

    //a repeatable read ellenőrzése

    q:=con:sqlqueryNew("select szamla, megnevezes from konto.proba")
    while( q:next )
        ? q:getchar(1), q:getchar(2)
    end
    q:close

    con:sqlcommit
    ?


***********************************************************************************************


#ifdef NOTDEFINED //Postgres megjegyzés

  9.1 előtti helyzet:

  read uncommitted  -> read committed
  read committed    -> read committed
  repeatable read   -> repeatable read
  serializable      -> repeatable read

  vagyis négy helyett valójában csak két különbőző szint volt.

  9.1-től kezdve:

  read uncommitted  -> read committed
  read committed    -> read committed
  repeatable read   -> repeatable read
  serializable      -> serializable (true)

  Tehát a régi értelemben vett síma MVCC serializable működéshez 
  9.1-től kezdve a REPEATABLE READ szintet kell(ene) beállítani.

#endif
