
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


function url_encode(x)

local lowa:=asc("a"), lowz:=asc("z")
local capa:=asc("A"), capz:=asc("Z")
local num0:=asc("0"), num9:=asc("9")

local y:="",c,n
    x::=str2bin
    for n:=1 to len(x)
        c:=asc(x[n])
        if( lowa<=c<=lowz .or. capa<=c<=capz .or. num0<=c<=num9 )
            y+=chr(c)
        else
            y+="%"+upper(bin2hex(x[n]))
        end
    next
    return y


function url_decode(y)
local x:=a"",n:=1
    while( n<=len(y) )
        if( y[n]=="%" )
            x+=y::substr(n+1,2)::hex2l::bin
            n+=3
        else
            x+=y[n]::str2bin
            n+=1
        end
    next
    return bin2str(x)
         