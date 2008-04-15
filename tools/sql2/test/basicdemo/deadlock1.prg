
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

//deadlock demó: lockolja e1-t, e2-t.

#include "sql.ch"

function main()

local con
local tbl,rset
local e0,e1,e2

    set date format "yyyy-mm-dd"
    set printer to log-deadlock-1
    set printer on

    con:=sqlConnect()  
 
    tbl:=testdata.a.tableEntityNew(con)
    
    rset:=tbl:select
    e1:=rset:next
    e2:=rset:next
    rset:close
    
    con:sqlcommit()
    
    e0:=e1:find(LOCK_WAIT)
    alert("E1 LOCKED")
    e0:=e2:find(LOCK_WAIT)
    alert("E1-E2 LOCKED")

    con:sqldisconnect

    return NIL
 
    