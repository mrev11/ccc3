
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
function jtgetenv(name)

local rsp,dom,node,i,n,v

    jtsocket():send("<jtgetenv>"+name+"</jtgetenv>")
    
    //válasz:
    //  <jtenv>
    //    <name>n</name>
    //    <value>v</value>
    //  </jtenv>

    while( (rsp:=jtsocket():recv)!=NIL )

        dom:=xmlparser2New():parsestring(rsp)  
        node:=dom//:content[1]

        if( node:type=="jtenv" )
            for i:=1 to len( node:content )
                if( node:content[i]:type=="name" )
                    n:=node:content[i]:gettext 
                end
                if( node:content[i]:type=="value" )
                    v:=node:content[i]:gettext 
                end
            next
            return if(n==name,v,NIL)
        else
            jtsocket():enqueue(rsp)
        end
    end



*****************************************************************************
function jtsetenv(name,value)
local x:=""
    x+="<jtsetenv>"
    x+="<name>"+name+"</name>" 
    if( value!=NIL )
        x+="<value>"+cdataif(value)+"</value>" 
    end
    x+="</jtsetenv>"
    jtsocket():send(x)
    return NIL
 

*****************************************************************************
 
 