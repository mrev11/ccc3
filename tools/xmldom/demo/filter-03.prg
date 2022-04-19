
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

static remark:=<<REMARK>>
    ugy indul, hogy nem keszit node-okat
    megkeresi az A="8" attributummal rendelkezo x5 node-ot
    es kigyujti azt a cargoba

<<REMARK>>


****************************************************************************
function main()

local p,n

    ? remark

    p:=xmlparser2New()
    p:file:="x.xml"
    p:info:buildflag:=.f.   //kikapcsolt node építéssel indul
    p:cargo:={}             //user data

    p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    p:attribblock:={|prs,an,av|attrib(prs,an,av)}
    
    p:parse 
    
    for n:=1 to len(p:cargo)
        p:cargo[n]:xmloutind
        ?
    next
    ?


****************************************************************************
function nodeend(prs,ni,node)  //parser, nodeinfo, node/NIL
local n

    for n:=1 to len(prs:cargo)
        if( prs:cargo[n]==ni )
            prs:cargo[n]:=node          // gyűjt
        end
    next


****************************************************************************
function attrib(prs,an,av)

    //? "Attr:", an+"="+av

    if( an=="A" .and. av::unquote=="8" )
        prs:info:buildflag:=.t.         // node építés bekapcsol
        aadd(prs:cargo,prs:info)        // megjegyzi
    end


****************************************************************************
