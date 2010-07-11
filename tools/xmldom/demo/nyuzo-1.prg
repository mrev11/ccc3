
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

****************************************************************************
function main(build)
local p,dom,n:=0

    thread_create({||dogc()})

    p:=xmlparserNew()

    //p:file:="example.xml"
    p:file:="z.xml"
    
    if(build==NIL)
        p:info:buildflag:=.f.
    end
    
    ? "buildflag", p:info:buildflag

    p:nodebeginblock:={|prs,ni|nodebegin(prs,ni)}
    //p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    p:contentblock:={|prs,node|content(prs,node)}

    while(.t.)
        dom:=p:parse 
        if( ++n%100==0 )
            ?? "."
        end
    end


****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo

    if( ni:type=="include" )
        prs:info:buildflag:=.t.     //hogy működjön az include
    end

****************************************************************************
function content(prs,node)
local p,dom

    if( node:type=="include" )
        p:=prs:copy
        p:file:=node:getattrib("file")
        
        //részfa bekapcsolás
        dom:=p:parse
        node:type:=dom:type
        node:content:=dom:content
        node:attrib:=dom:attrib
    end
    
    return .t.


****************************************************************************
function dogc()
    ? thread_self()
    while(.t.)
        sleep(10)
        gc()
    end

****************************************************************************
