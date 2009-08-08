
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

#include "directry.ch"
#include "jtelem.ch"
 
****************************************************************************
function jtmakedir( name ) 
local x,rsp,dom,node

    x:="<jtfileutil><makedir>"
    x+="<name>"+name+"</name>"
    x+="</makedir></jtfileutil>"
 
    jtsocket():send(x)

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="makedir" )
            return node:gettext=="true"
        else
            jtsocket():enqueue(rsp)
        end
    end

    return .f.


****************************************************************************
function jtmakedirs( name ) 
local x,rsp,dom,node

    x:="<jtfileutil><makedirs>"
    x+="<name>"+name+"</name>"
    x+="</makedirs></jtfileutil>"
 
    jtsocket():send(x)

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="makedirs" )
            return node:gettext=="true"
        else
            jtsocket():enqueue(rsp)
        end
    end

    return .f.
 

****************************************************************************
function jtdelete( name )  
local x,rsp,dom,node

    x:="<jtfileutil><delete>"
    x+="<name>"+name+"</name>"
    x+="</delete></jtfileutil>"
 
    jtsocket():send(x)

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="delete" )
            return node:gettext=="true"
        else
            jtsocket():enqueue(rsp)
        end
    end

    return .f.


****************************************************************************
function jtexists( name )  
local x,rsp,dom,node

    x:="<jtfileutil><exists>"
    x+="<name>"+name+"</name>"
    x+="</exists></jtfileutil>"
 
    jtsocket():send(x)

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="exists" )
            return node:gettext=="true"
        else
            jtsocket():enqueue(rsp)
        end
    end

    return .f.


****************************************************************************
function jtisfile( name )  
local x,rsp,dom,node

    x:="<jtfileutil><isfile>"
    x+="<name>"+name+"</name>"
    x+="</isfile></jtfileutil>"
 
    jtsocket():send(x)

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="isfile" )
            return node:gettext=="true"
        else
            jtsocket():enqueue(rsp)
        end
    end

    return .f.


****************************************************************************
function jtisdirectory( name )  
local x,rsp,dom,node

    x:="<jtfileutil><isdirectory>"
    x+="<name>"+name+"</name>"
    x+="</isdirectory></jtfileutil>"
 
    jtsocket():send(x)

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="isdirectory" )
            return node:gettext=="true"
        else
            jtsocket():enqueue(rsp)
        end
    end

    return .f.
 
 
****************************************************************************
function jtrename( oldname, newname )
local x,rsp,dom,node

    x:="<jtfileutil><rename>"
    x+="<oldname>"+oldname+"</oldname>"
    x+="<newname>"+newname+"</newname>"
    x+="</rename></jtfileutil>"
 
    jtsocket():send(x)

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="rename" )
            return node:gettext=="true"
        else
            jtsocket():enqueue(rsp)
        end
    end

    return .f.

 
****************************************************************************
