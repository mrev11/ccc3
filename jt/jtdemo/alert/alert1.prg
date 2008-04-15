
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

******************************************************************************
function main()
local rsp,dom,node
local a:=jtalertNew() 

    a:message:="öt szép szűzlány őrült írót nyúz"
    a:options:={"őő","ŐŐ","űű","ŰŰ"}
    a:caption:="Próba: őŐűŰ"

    ? jtversion()
    jtencoding("UTF-8")

    jtsocket():send(a:xmlout)
    while( (rsp:=jtsocket():recv)!=NIL  )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="alert" )
            return val(node:gettext) 
        end
    end
    return 0 

 
****************************************************************************
