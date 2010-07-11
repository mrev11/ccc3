
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

/*
*/

#define WAIT   ? "press any key"; inkey(0)


#include "sql.ch"

#define UPDATE(x)   ?#x+"-update-before"; row##x:update;    ?#x+"-update-after"
#define COMMIT(x)   ?#x+"-commit-before"; con##x:sqlcommit; ?#x+"-commit-after"



****************************************************************************************
function main()

local con1:=connect()  
local tab1:=isol.tableEntityNew(con1)

local con2:=connect()  
local tab2:=isol.tableEntityNew(con2)

local row1,row2

    thread_create({||sleep(3000),qout("deadlock"),quit()})

    query(tab1)
    
    row1:=tab1:find("1")
    row1:name::=(trim()+"1")
    UPDATE(1)


                                    row2:=tab2:find("1")
                                    row2:name::=(trim()+"2")
                                    UPDATE(2) //deadlock
                                    COMMIT(2)

    COMMIT(1)




    query(tab1)

    con1:sqldisconnect    
    con2:sqldisconnect    
    
    WAIT

****************************************************************************************
function query(tab)
local rowset,row
    rowset:=tab:select_ordered
    while( NIL!=(row:=rowset:next) )
        ? row:key, row:name, row:number
    end

****************************************************************************************
