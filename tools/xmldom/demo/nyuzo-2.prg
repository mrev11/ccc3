
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

    thread_create({||dogc()})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    thread_create({||doparse(build)})
    
    inkey(0)
    ?


****************************************************************************
function doparse()
local p,dom,n:=0

    p:=xmlparser2New()
    p:file:="z.xml"
    p:contentblock:={|*|content(*)}
    
    while(.t.)
        dom:=p:parse 
        if( ++n%100==0 )
            ?? "."
        end
        sleep(10*rand())
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
    while(.t.)
        gc()
        sleep(10)
    end


****************************************************************************
