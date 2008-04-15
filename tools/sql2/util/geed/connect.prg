
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

function connect()

local con, n, arg:=argv()

    set date format "yyyy-mm-dd"
    
    for n:=1 to len(arg)
        if( arg[n]$"Oo" )
            con:=sql2.oracle.sqlconnectionNew()  
            return con
        elseif( arg[n]$"Pp" )
            con:=sql2.postgres.sqlconnectionNew()  
            return con
        end
    next

    return  con:=sql2.postgres.sqlconnectionNew()  
