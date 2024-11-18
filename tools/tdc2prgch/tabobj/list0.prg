
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

#include "table.ch"
#include "_cassa.ch"

******************************************************************************************
function main()
local n:=0
    set dosconv fileshare

    while( ++n<10 )
        test()
        ?
    end
    
    ? "OK"
    ?


******************************************************************************************
static function test()

    CASSA:open
    CASSA:control:="penztaros"
    CASSA:gotop

    while( !CASSA:eof )
        ? CASSA:position, CASSA_SOREGYEB, CASSA_PENZTAROS
        CASSA:skip
    end

    CASSA:close
    
******************************************************************************************

