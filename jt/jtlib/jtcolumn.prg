
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
//jtcolumn
****************************************************************************
class jtcolumn(object) 
    method  initialize
    attrib  heading 
    attrib  block  
    attrib  colorblock
    attrib  fontblock
     
    attrib  width
    attrib  picture
    attrib  type
    attrib  editable
    method  xmlout

****************************************************************************
static function jtcolumn.initialize(this,hdr,blk,pic,wid) 

local funcstr,tmplstr,p,x

    // jtcolumnNew(hdr,blk,pic,wid)
    // jtcolumnNew(hdr,blk,wid)
 
    // Koncepció változás:
    // az oszlop a picture-ből (vagy annak hiányából)
    // azonnal meghatározza a típusát (C,N,D,L),
    // és azt tárolja a type attribútumban.

    // Koncepció változás:
    // nem csinálunk minden áron picture-t
    // ui. a memóknak éppen az a jó, 
    // ha csak a wid van megadva, és a get scrolloz.
 
    this:(object)initialize

    this:heading  := if(hdr==NIL,"",hdr)
    this:block    := blk
    this:editable := .f.

    if( valtype(pic)=="C" )
        this:picture  := pic
        this:width    := wid
    elseif( valtype(wid)=="C" )
        this:picture  := wid
        this:width    := pic
    elseif( valtype(pic)=="N" )
        this:width    := pic
        this:picture  := NIL
    elseif( valtype(wid)=="N" )
        this:width    := wid
        this:picture  := NIL
    end
 
    if( empty(this:picture) )
        funcstr:=""
        tmplstr:=""
    elseif( left(this:picture,1)!="@" )
        funcstr:=""
        tmplstr:=this:picture
    elseif( 0==(p:=at(" ",this:picture)) )
        funcstr:=this:picture 
        tmplstr:=""
    else
        funcstr:=left(this:picture,p-1)
        tmplstr:=substr(this:picture,p+1)
    end

    if( "C"$funcstr )
        this:type:="C"
    elseif( "N"$funcstr )
        this:type:="N"
    elseif( "D"$funcstr )
        this:type:="D"
    elseif( "L"$funcstr )
        this:type:="L"
    else
        this:type:="C"
    end
    
    if( empty(this:width) )
        this:width:=min(32,max(len(this:heading),len(tmplstr)))
        if( this:type=="D" )
            this:width:=max(10,this:width)
        end
    end
    
    return this
 

****************************************************************************
static function jtcolumn.xmlout(this)
local x:="<jtcolumn>"
    x+="<name>"+this:heading+"</name>"
    x+="<type>"+this:type+"</type>"

    if( !empty(this:width) )
        x+="<width>"+alltrim(str(this:width))+"</width>"
    end

    if( !empty(this:picture) )
        x+="<picture>"+this:picture+"</picture>"
    end

    if( this:editable )
        //az oszlop editálható, 
        //ha a picture function stringjében 
        //be van állítva az E flag.
        x+="<editable>true</editable>"
    end
    x+="</jtcolumn>"
    return x


****************************************************************************
