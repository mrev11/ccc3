
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

//Ezzel lehet próbálgatni a létrehozható threadek számát.
//2.6-os Linuxon és Windowson símán lehet csinálni 4096 threadet.
//2.4-es kernelen kevés threadet (kb 100) lehetett csinálni.

function main()
local threads:={}, th, n:=0
    while( NIL!=(th:=thread_create({|| qout(thread_self()) })) .and. ++n<=4096 )
        aadd(threads,th)
    end
    for n:=1 to len(threads)
        ? n, thread_join(threads[n])
    end
        