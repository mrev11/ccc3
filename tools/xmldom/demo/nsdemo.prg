
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

****************************************************************************************
function main()

local xml:=<<XML>>

<?xml xmlns="default" xmlns:pf="other"?>

<pf:proba pf:a1="aaa111" pf:a2="aaa222">
    <szerencse b="bbb" xmlns:pf="OTHER1" xmlns:ns="some-uri" >
        <pf:hopp>HOPP1</pf:hopp>
        <pf:hopp xmlns:pf="OTHER2">HOPP2</pf:hopp>
        <ns:hopp>HOPP3</ns:hopp>
    </szerencse>
</pf:proba>  

<<XML>>



local p,dom

    p:=xmlparser2New()
    // p:liststruct

    p:attribblock       ({|*|attribblock(*)})
    p:contentblock      ({|*|contentblock(*)})
    p:nodebeginblock    ({|*|nodebeginblock(*)})
    p:nodeendblock      ({|*|nodeendblock(*)})
    p:textnodeblock     ({|*|textnodeblock(*)})

    dom:=p:parse(xml)

    ?
    ?
    p:qmxml:xmloutind
    dom:xmloutind
    ?


****************************************************************************************
function attribblock(parser,attrname,attrvalue)
    ? pinfo("Atr",*), attrname+"="+attrvalue, parser:info:nsmap[nsprefix(attrname)]


// megjegyzes:
// az attributumnevek is lehetnek minositve -> lehet nsprefixuk es nevteruk
// az attributumok nevtere a parser:info:nsmap-bol kaphato meg

                                                                
****************************************************************************************
function contentblock(parser,node)                                        
    ? pinfo("Con",*), "namespace =",parser:info:namespace
    return .t.                                                  

****************************************************************************************
function nodebeginblock(parser,nodeinfo)                                      
    ? pinfo("Beg",*), "namespace =",parser:info:namespace

****************************************************************************************
function nodeendblock(parser,nodeinfo)                                        
    ? pinfo("End",*), "namespace =",parser:info:namespace

****************************************************************************************
function textnodeblock(parser,text) 
    ? pinfo("Txt",*), text

****************************************************************************************
function pinfo(blktype,parser,*)
local x:=""

    x+=parser:infodepth::str::alltrim::padr(2)
    x+=parser:info:fullpath::padr(32)
    x+=blktype::padr(5)
    x+="type="+parser:info:type::padr(16)
    x+="nsmap="+parser:info:nsmap:toarr::any2str::padr(64)
    
    return x    


****************************************************************************************
static function nsprefix(name)
local pos:=at(":",name)
    if( pos>0 )
        return left(name,pos-1)
    end
    return ""


****************************************************************************************
        