
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

*****************************************************************************
function main()
local thr,thw,sp

    ? sp:=socketpair()

    thr:=thread_create({||read(sp[1])})
    thw:=thread_create({||write(sp[2])})

    thread_join(thw); ? "OK-W" 
    thread_join(thr); ? "OK-R"  
    
    ?
    sleep(1000)
 
    return NIL

*****************************************************************************
static function write(s)
local x:=memoread("socketpair.prg"),n
    for n:=1 to len(x) 
        swrite(s,substr(x,n,1),1)
        sleep(1)
    next
    sclose(s)
    return NIL

*****************************************************************************
static function read(s)
local x
    while( NIL!=(x:=sread(s,1)) )
        ?? upper(x)
    end
    sclose(s)
    return NIL

*****************************************************************************
