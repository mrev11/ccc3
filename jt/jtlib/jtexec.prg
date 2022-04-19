
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
function jtexec(cmd)

local rsp,dom,node,err,value

    jtsocket():send("<jtexec>"+cdataif(cmd)+"</jtexec>")
    
    //a válasz:
    //  <exitvalue>value</exitvalue>
    //vagy
    //  <execerror>error</execerror>

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparser2New():parsestring(rsp)  
        node:=dom//:content[1]

        if( node:type=="execerror" )
            err:=apperrorNew()
            err:operation:="jtexec"
            err:description:="execerror"
            err:args:={node:gettext}
            break(err)

        elseif( node:type=="exitvalue" )
            value:=val(node:gettext)
            exit
        else
            jtsocket():enqueue(rsp)
        end
    end
    return value

*****************************************************************************
 
 