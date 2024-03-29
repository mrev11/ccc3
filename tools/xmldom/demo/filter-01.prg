
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
    x4 tipusu node-oknal bekapcsolja a node epitest
    a cargo-ban kigyujti az x4 node-okat

<<REMARK>>


****************************************************************************
function main()

local p,n

    ? remark

    p:=xmlparser2New()
    p:file:="x.xml"
    p:info:buildflag:=.f.   //kikapcsolja a node építést
    p:cargo:={}             //tetszőleges adat

    p:nodebeginblock:={|prs,ni|nodebegin(prs,ni)}
    p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    
    p:parse 
    
    for n:=1 to len(p:cargo)
        p:cargo[n]:xmloutind
        ?
    next

    ?

****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo

    if( ni:type=="x4" )
        prs:info:buildflag:=.t. //jön az érdekes rész
    end

    

****************************************************************************
function nodeend(prs,ni,node)   //parser, nodeinfo, node/NIL

    if( ni:type=="x4" /*.and. node!=NIL*/ )
        aadd(prs:cargo,node)    //gyűjti az x4-eket
    end


****************************************************************************
