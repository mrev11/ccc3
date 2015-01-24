
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

local con,tab,rs,row,n

    set date format "yyyy-mm-dd"
    
    con:=connect()

    tab:=proba.tableEntityNew(con)

    if( arg=="B" .or. arg=="W" )

        rs:=tab:select
        while( NIL!=(row:=rs:next) )
            ? row:szamlaszam, row:nev
            
            if( arg=="B" )
                if( "WHITE"$row:nev )
                    ??  "->", row:nev:="BLACK"
                else
                    //nem változtat
                end
            end
        
            if( arg=="W" )
                if( "BLACK"$row:nev )
                    ??  "->", row:nev:="WHITE"
                else
                    //nem változtat
                end
            end
        
            row:update
            sleep(100)
        end

        ? "------------------------------"
    end
    
    
    if( arg=="W" )
        sleep(500)
    end

    //a repeatable read ellenőrzése


    rs:=tab:select
    while( NIL!=(row:=rs:next) )
        ? row:szamlaszam, row:nev
    end

    con:sqlcommit
    ?


***********************************************************************************************
