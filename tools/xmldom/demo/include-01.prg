
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
    <include file="fspec"/> alaku include, az eredmeny dom-ot egybeepiti
  
    az inkludalt fajlok kulonbozo kodolasuak
        x.xml UTF-8
        y.xml ISO-859-2
        z.xml UTF-8
    belso kodolas Unicode (bemenettol fuggetlenul)
    xmlout eredmenye UTF-8 (bemenettol fuggetlenul)

    Mukodes:
    a contentblock helyettesiti az include node-ot  
    az include fajl elemzesbol kapott node-dal
      
    Megjegyzes:
    a parser:copy-val vigyazni kell
    ha a blokkokban refes valtozok is vannak

<<REMARK>>


****************************************************************************
function main()

local p,dom,rflag

    ? remark

    p:=xmlparser2New()
    p:file:="z.xml"
    p:contentblock:={|*|content(*)}
    dom:=p:parse
    ?

    dom:xmloutind()
    ?

****************************************************************************
function content(parser,node)
local p,dom

    if( node:type=="include" )
        p:=parser:copy
        p:file:=node:getattrib("file")

        dom:=p:parse

        //részfa bekapcsolás
        node:type:=dom:type
        node:content:=dom:content
        node:attrib:=dom:attrib
    end
    
    return .t.


****************************************************************************
