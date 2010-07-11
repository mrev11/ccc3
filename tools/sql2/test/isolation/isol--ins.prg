
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

function main()

local con:=connect()  
local tab:=isol.tableEntityNew(con)
local row
local err

    begin
        tab:create
    recover err <sqlerror>
        //err:list
    end
    
    row:=tab:instance

    row:key:="1"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="2"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="3"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="4"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="5"
    row:name:="b"
    row:number:=1
    row:insert

    row:key:="6"
    row:name:="c"
    row:number:=1
    row:insert

    row:key:="7"
    row:name:="d"
    row:number:=1
    row:insert
    
    con:sqlcommit
    con:sqldisconnect    
    
    