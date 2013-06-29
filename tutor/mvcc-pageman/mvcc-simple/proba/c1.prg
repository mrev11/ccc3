
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


***********************************************************************************************
static function getkey(key)
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
local key
local page

    con:=dbconnectionNew("dbproba")
    

    while( getkey()!=K_ESC  )
        
        //most olvas egyet

        page:=con:read(a"0000000000000004")  //D-s page

        ? page:content

        //amit olvasott, módosítja

        if( page:content[1]==a"Z" ) //nagy Z
            page:content:="A"::replicate(10)
        elseif( page:content[1]==a"z" ) //kis z
            page:content:="a"::replicate(10)
        else
            page:content:=(page:content::asc()+1)::chr::replicate(10)
        end

        //majd megpróbálja kiírni

        begin
            sleep(1000) //többiek szivatása
            con:commit
            ?? " ->", page:content
            //siker

        recover err <dbserialerror>
            con:rollback
            ?? " ->", err:description
            getkey(32)
            //ismétel
        end

        //tranzakcióhatár
    end

    ?

***********************************************************************************************
