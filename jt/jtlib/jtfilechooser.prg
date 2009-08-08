
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

#include "jtelem.ch"
 
****************************************************************************
function jtfilechooser(fc)

local ff,mask,dsep,wdir,n

    if( valtype(fc)=="C" )
        mask:=fc

        mask:=strtran(mask,"\","/")
        dsep:=rat("/",mask)
        if( dsep>0 )
            wdir:=left(mask,dsep)
            mask:=substr(mask,dsep+1)
        end

        fc:=jtfilechooserNew()
        fc:workdir:=wdir 
        ff:=jtfilefilterNew() 
        ff:description:=mask
        ff:addpattern(mask)
        ff:regexdir:=jtfilepattern("*")
        fc:addfilter( ff )

    elseif( valtype(fc)=="A" )
        mask:=fc
        fc:=jtfilechooserNew()
        for n:=1 to len(mask)
            ff:=jtfilefilterNew() 
            ff:description:=mask[n]
            ff:addpattern(mask[n])
            ff:regexdir:=jtfilepattern("*")
            fc:addfilter( ff )
        next
    end
    
    return fc:getchoice


****************************************************************************
class jtfilechooser(object) 
    method  initialize
    method  xmlout
    method  addfilter       {|this,ff|aadd(this:filterlist,ff),ff}
    method  getchoice
    attrib  caption
    attrib  text
    attrib  workdir
    attrib  filterlist
    attrib  selectmode      //"F", "D", "FD"
    attrib  multiselect     //.t., .f.

****************************************************************************
static function jtfilechooser.initialize(this) 
    this:(object)initialize
    this:caption:=""
    this:text:=""
    this:workdir:=NIL
    this:filterlist:={}
    this:selectmode:="FD"
    this:multiselect:=.t.
    return this
    

****************************************************************************
static function jtfilechooser.xmlout(this)
local x, n
    x:="<jtfilechooser>"

    if( !empty(this:caption) )
        x+="<caption>"+cdataif(this:caption)+"</caption>" 
    end

    if( !empty(this:text) )
        x+="<text>"+this:text+"</text>" 
    end
 
    if( !empty(this:workdir) )
        x+="<workdir>"+this:workdir+"</workdir>" 
    end

    if( !empty(this:multiselect) )
        x+="<multiselect/>"
    end
 
    if( !empty(this:selectmode) )
        x+="<selectmode>"+this:selectmode+"</selectmode>" 
    end
    
    x+=EOL

    if( !empty(this:filterlist) )
        for n:=1 to len(this:filterlist)
            x+=this:filterlist[n]:xmlout+EOL
        next
    end
    
    x+="</jtfilechooser>"
    return x
 

****************************************************************************
static function jtfilechooser.getchoice(this)
local rsp,dom,node
local choice:={},n 

    jtsocket():send( this:xmlout )

    while( (rsp:=jtsocket():recv)!=NIL )
        dom:=xmlparserNew():parsestring(rsp)  
        node:=dom:content[1]
        if( node:type=="filechooser" )
            for n:=1 to len( node:content )
                aadd(choice,node:content[n]:gettext )
            next
            exit
        else
            jtsocket():enqueue(rsp)
        end
    end

    return choice

****************************************************************************
 