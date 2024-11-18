
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

******************************************************************************************
function main()

local t1,t2,n:=0

    set dosconv fileshare
    
    t1:=tabobj.cassaNew(); t1:open
    t2:=tabobj.cassaNew(); t2:open

    while( ++n<=10 )
        t1:append
        t1:soregyeb:=n
        t1:penztaros:=crypto_rand_bytes(4)::crypto_bin2hex
        t1:szamlaszam:=crypto_rand_bytes(8)::crypto_bin2hex
        t1:unlock

        if((n%1000)==0)
            ?? "."
        end
    end

    t1:control:="soregyeb"; t1:gotop
    t2:control:="penztaros"; t2:gotop

    while( !t1:eof .or. !t2:eof )
         ?  t1:position, t1:soregyeb
        ??  t2:position, t2:penztaros

        t1:skip
        t2:skip
    end

    t1:close
    t2:close
    
    ? "OK"
    ?


******************************************************************************************
