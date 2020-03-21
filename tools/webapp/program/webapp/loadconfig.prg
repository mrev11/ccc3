
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

namespace webapp

***************************************************************************************
function loadconfig(fspec)

local config,n
local line,pos,opt,val
local hash:=simplehashNew()

    config:=memoread(fspec)::split(chr(10))

    for n:=1 to len(config)
        line:=config[n]::alltrim

        if( empty(line) )
            loop
        end

        if( left(line,1)=="#" )
            loop
        end
        
        pos:=at("=",line)
        if( pos==0 )
            loop
        end

        opt:=line[1..pos-1]
        val:=line[pos+1..]
        
        hash[opt]:=substenv(val)
    next
    
    return hash


***************************************************************************************
static function substenv(val)
local pos1,pos2
    while( 0<(pos1:=at("$(",val)) )
        pos2:=at(")",val,pos1+3)
        val::=stuff(pos1, pos2-pos1+1, getenv( val[pos1+2..pos2-1] ))
    end
    return val


***************************************************************************************
