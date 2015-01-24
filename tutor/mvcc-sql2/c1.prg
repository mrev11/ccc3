
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
static function getkey(key) //inkey wrapper
static skey:=0
local rkey
    if( key!=NIL )
        skey:=key
    elseif( skey!=NIL )
        sleep(100)
        rkey:=skey
        skey:=NIL
    else
        rkey:=inkey(1)
    end    
    return rkey


***********************************************************************************************
function main()

local con,err
local tab,row,rowset
local key

    set date format "yyyy-mm-dd"
    
    con:=connect()

    tab:=proba.tableEntityNew(con)
    begin
        tab:drop
    end
    tab:create

    row:=tab:instance
    row:szamlaszam :='111111112222222233333333'
    row:devnem     :="HUF"
    row:nev        :="A"::replicate(10)
    row:egyenleg   :=999.99
    row:tulmenflag :=.t.
    row:konyvkelt  :=date()
    row:megjegyzes :=NIL
    row:insert
    con:sqlcommit

    while( getkey()!=K_ESC  )
        
        //most olvas egyet

        rowset:=tab:select
        row:=rowset:next
        rowset:close
        if( row==NIL )
            ? "nincs egy sor sem"
            quit
        end
        ? row:nev::alltrim

        //amit olvasott, módosítja

        if( row:nev[1]=="Z" ) //nagy Z
            row:nev:="A"::replicate(10)
        elseif( row:nev[1]=="z" ) //kis z
            row:nev:="a"::replicate(10)
        else
            row:nev:=(row:nev::asc()+1)::chr::replicate(10)
        end

        //majd megpróbálja kiírni

        begin
            row:update
            sleep(1000) //többiek szivatása
            con:sqlcommit
            ?? " ->", row:nev::alltrim
            //siker

        recover err <sqlerror>
            con:sqlrollback
            ?? " ->", err:description
            getkey(32) //következő key: várakozás nélkül 32
            //ismétel
        end

        //tranzakcióhatár
    end

    ?

***********************************************************************************************
