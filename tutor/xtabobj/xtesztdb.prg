
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

#include "directry.ch"

#include "table.ch"
#include "_tesztdb.ch"

function main()
local dir:=directory("*.*"), n

    TESZTDB:open
    
    for n:=1 to len(dir)
        TESZTDB:append
        TESZTDB_NAME:=dir[n][F_NAME]
        TESZTDB_SIZE:=dir[n][F_SIZE]
        TESZTDB_DATE:=dir[n][F_DATE]
        TESZTDB_TIME:=dir[n][F_TIME]
        TESZTDB_ATTR:=dir[n][F_ATTR]
    next
    
    TESZTDB:close
    
    return NIL
    
    