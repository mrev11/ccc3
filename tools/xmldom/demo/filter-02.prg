
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
  úgy indul, hogy nem készít node-okat
  x4 típusú node-oknál bekapcsolja a node építést
  de nem kéri az x6 node-okat (újra kikapcsol)

<<REMARK>>

****************************************************************************
function main()

local p,n

    ? remark

    p:=xmlparserNew()

    p:file:="x.xml"

    p:info:buildflag:=.f.   //kikapcsolt node építéssel indul
    p:cargo:={}             //user data

    p:nodebeginblock:={|prs,ni|nodebegin(prs,ni)}
    p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    
    p:parse 
    
    for n:=1 to len(p:cargo)
        ?
        p:cargo[n]:xmlout
    next

    ?

****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo
    
    if( ni:fullpath=="/x1/x2/x3/x4" )
        prs:info:buildflag:=.t.     //jön az érdekes rész

    elseif( ni:fullpath=="/x1/x2/x3/x4/x5/x6"  )
        prs:info:buildflag:=.f.     //ez nem kell
    end

    ? ">>>", ni
    

****************************************************************************
function nodeend(prs,ni,node)  //parser, nodeinfo, node/NIL

    ? "<<<", ni, node

    if( ni:fullpath=="/x1/x2/x3/x4" )
        aadd(prs:cargo,node)    //gyűjt
    end


****************************************************************************
