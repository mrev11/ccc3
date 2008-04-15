
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
function jtdirectory( mask, attr ) 

//utánozza Clipper directory()-t 
//
// jtdirectory("*.java")          java filék
// jtdirectory("*.bat|*.java")    bat vagy java filék 
// jtdirectory("getutil/*.java")  java filék a getutil directoryból
// jtdirectory("*.bat","D")       bat filék plusz directoryk 
// jtdirectory(,"D")              csak directoryk  

local dl,workdir,dsep
   
    if(mask==NIL)
        mask:=""
    end
    if(attr==NIL)
        attr:=""
    end
 
    mask:=strtran(mask,"\","/")
    dsep:=rat("/",mask)
    if( dsep>0 )
        workdir:=left(mask,dsep)
        mask:=substr(mask,dsep+1)
    end
    
    dl:=jtdirlistNew()
    dl:workdir:=workdir
    dl:filter:addpattern(mask)
    dl:filter:regexdir:=if("D"$attr,jtfilepattern("*"),NIL)
    
    return dl:getdirlist

****************************************************************************
function jtdirlist( workdir, fmask, dmask )

//egy másik utility függvény a dirlist objektumhoz
//
//workdir : ezt a directoryt listázza (empty==curdir)
//fmask   : illeszkedő filék maszkja, vagy egy jtfilefilter
//dmask   : illeszkedő directoryk maszkja, ha üres, nem ad directorykat

local dl, n

    if( dmask==NIL )
        dmask:=""
    end
 
    dl:=jtdirlistNew()
    dl:workdir:=workdir

    if( valtype(fmask)=="C" )
        //fmask: filémaszk
        //dmask: directory maszk

        dl:filter:addpattern(fmask)
        dl:filter:regexdir:=jtfilepattern(dmask)
  
    elseif( valtype(fmask)=="A" )
        //fmask: filémaszk lista
        //dmask: directory maszk

        for n:=1 to len(fmask)
            dl:filter:addpattern(fmask[n])
        next
        dl:filter:regexdir:=jtfilepattern(dmask)

    elseif( valtype(fmask)=="O" )
        //fmask: jtfilefilter objektum
        //dmask: nem használjuk

        dl:filter:=fmask
    end

    return dl:getdirlist


****************************************************************************
class jtdirlist(object) 
    method  initialize
    method  xmlout
    method  getdirlist
    attrib  workdir
    attrib  filter

****************************************************************************
static function jtdirlist.initialize(this) 
    this:(object)initialize()
    this:workdir:=NIL
    this:filter:=jtfilefilterNew()
    return this
    

****************************************************************************
static function jtdirlist.xmlout(this)
local x, n
    x:="<jtdirlist>"

    if( !empty(this:workdir) )
        x+="<workdir>"+this:workdir+"</workdir>" 
    end
    
    if( !empty(this:filter) )
        x+=this:filter:xmlout
    end
    
    x+="</jtdirlist>"
    return x
 

****************************************************************************
static function jtdirlist.getdirlist(this)

local rsp,dom,node
local dlist:={}, n
 
    jtsocket():send( this:xmlout )

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="dirlist" )
            for n:=1 to len( node:content )
                if( node:content[n]:type=="file" )
                    aadd(dlist, getitem(node:content[n]) )
                end
            next
            exit
        end
    end
    
    return dlist


****************************************************************************
static function getitem( fnode )
local item:={NIL,NIL,NIL,NIL,""}
local child, type, n
    for n:=1 to len( fnode:content )
        child:=fnode:content[n] 
        type:=child:type
        if( type=="name" )
            item[F_NAME]:=child:gettext
        elseif( type=="size" )
            item[F_SIZE]:=val(child:gettext)
        elseif( type=="date" )
            item[F_DATE]:=stod(child:gettext)
        elseif( type=="time" )
            item[F_TIME]:=child:gettext
        elseif( type=="attr" )
            item[F_ATTR]:=child:gettext
        end
    next
    return item

****************************************************************************
 