
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
  többszörös include + részfa kiválasztás 
  
  induláskor info:buildflag:=.f.
  
  beállítjuk: rootflag:=.f., hogy ne kelljen bajlódni a #ROOT node-okkal
  enélkül is lehet, de akkor bonyolultabb a részfa becsatolás
  
  az include node-oknál be kell állítani buildflag:=.t.-t
  máskülönben az include node nem készül el => nem fut a contentblock
  az include buildflag-je nem öröklődik az inkludált részfára
  mert közben az elemző eggyel visszalép
  tehát az include node parentjének a buildflag-je öröklődik

  az inkludált részfa becsatolásánál vigyázni kell a NIL-re


<<REMARK>>


****************************************************************************
function main()

local p,dom,n

    ? remark

    p:=xmlparserNew()

    p:file:="z.xml"
    p:infosize:=20
    p:cargo:={}
    p:rootflag:=.f.         //vagy xmlparser2
    p:info:buildflag:=.f.
  

    p:nodebeginblock:={|prs,ni|nodebegin(prs,ni)}
    p:nodeendblock:={|prs,ni,node|nodeend(prs,ni,node)}
    p:contentblock:={|prs,node|content(prs,node)}
    
    dom:=p:parse
    ?

    for n:=1 to len(p:cargo)
        printnode(p:cargo[n])

        p:cargo[n]:xmlout 
        ?
    end
    ?

****************************************************************************
function nodebegin(prs,ni) //parser, nodeinfo

    if( ni:type=="include" )        //fel kell építeni
        prs:info:buildflag:=.t.     //hogy működjön az include
                                    //az include node-nak nincs gyereke
                                    //azért buildflag-et semmi nem örökli

    elseif( ni:type=="y3" )
        prs:info:buildflag:=.t.     //érdekes rész
    end

    ? ">>>", ni:fullpath, ni:buildflag
   

****************************************************************************
function nodeend(prs,ni,node)  //parser, nodeinfo, node/NIL
    ? "<<<", ni:fullpath, ni:buildflag

    if( ni:type=="y3" )
        aadd(prs:cargo,node)        //érdekes rész gyűjtve
    end


****************************************************************************
function content(prs,node)
local p,dom

    if( node:type=="include" )
        p:=prs:copy
        p:file:=node:getattrib("file")

        dom:=p:parse 

        if( dom==NIL )
            // vigyázni kell a NIL-re                     
            // a buildflag kapcsolgatása miatt lehet NIL  
            // a contentblock nem hívódik meg nem felépített node-okra
            // de az eredeti include node fel volt építve
            return .f.
        else
            // részfa becsatolás
            // dom típusa z1 (most nincs #ROOT)                       
            node:type:=dom:type
            node:content:=dom:content
            node:attrib:=dom:attrib
            return .t.
        end
    end
    
    return .t.

****************************************************************************

