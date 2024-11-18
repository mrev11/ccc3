
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


static pool:=threadpoolNew(5)


******************************************************************************************
function main()

local cnt:=0
local job:={{|*|code(*)}}

    while( 27!=inkey(0) )
        aadd(job,(++cnt)::str::alltrim ) // hosszabbodik a param lista
        pool:addjob(job)
    end
    ? 


******************************************************************************************
static function code(*)
    ? ">>>",name(thread_self()),time(),"params:", {*}
    sleep(5000)       
    ? "<<<",name(thread_self()),time(),"params:", {*}


******************************************************************************************
static function name(tid)
local x:=ascan(pool:threads,tid)
    if( x>0 )
        tid:="ABCDEFGH"[(x-1)%8+1]
    end
    return tid


******************************************************************************************

   