
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
//jtcombo
****************************************************************************
class jtcombo(jtelem) 

    method  initialize

    method  xmladd
    method  xmlput          {|this,x|this:selectedindex:=val(x:gettext)}
    method  xmlget          {|this|alltrim(str(this:selectedindex))}

    method  changed         {|this|this:laststate!=this:selectedindex}
    method  savestate       {|this|this:laststate:=this:selectedindex}
    method  varput          {|this,x|this:selectedindex:=x}
    method  varget          {|this|this:selectedindex}
 
    method  additem         {|this,item|aadd(this:choicelist,item),item}
    method  insertitem
    method  deleteitem
    method  select          {|this,x|this:selectedindex:=x}
    method  getitem         {|this,x|this:choicelist[x]}
    method  selecteditem
    method  selectitem
    attrib  choicelist
    attrib  selectedindex

    //Az alábbiak nemcsak átírják a megfelelő attribútumot,
    //hanem rögtön xml üzenetet is küldenek a terminálra,
    //csak akkor kell őket használni, amikor a már létező
    //dialogboxban akarunk változásokat eszközölni:
 
    method  changelist
    method  changedelete    {|this,x|jtcombo.changelist(this,x,"del")}
    method  changeappend    {|this,x|jtcombo.changelist(this,x,"app")}
    method  changeinsert    {|this,x,i|jtcombo.changelist(this,x,"ins",i)}


****************************************************************************
static function jtcombo.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:choicelist:={}
    this:selectedindex:=1
    return this

****************************************************************************
static function jtcombo.selecteditem(this)
local sx:=this:selectedindex 
local lx:=len(this:choicelist)
local sitem
    if( 0<sx .and. sx<=lx )
        sitem:=this:choicelist[sx]
    end
    return sitem  //kiválasztott item/NIL


****************************************************************************
static function jtcombo.selectitem(this,txt)
    this:select( ascan(this:choicelist,txt) )
    return this:selectedindex 

****************************************************************************
static function jtcombo.insertitem(this,item,idx)
    this:additem //növeli a hosszat
    ains(this:choicelist,idx) //beszúr egy NIL-t
    this:choicelist[idx]:=item
    return this:choicelist
 

****************************************************************************
static function jtcombo.deleteitem(this,idx)
    adel(this:choicelist,idx)
    asize(this:choicelist,len(this:choicelist)-1)
    return this:choicelist

 
****************************************************************************
static function jtcombo.xmladd(this)
local n, x:=EOL
    for n:=1 to len(this:choicelist)
        x+="<item>"+cdataif(this:choicelist[n])+"</item>"+EOL
    end
    x+="<selectedindex>"+alltrim(str(this:selectedindex))+"</selectedindex>"+EOL
    return x

****************************************************************************
static function jtcombo.changelist(this,v,mode,i)

// jtcombo:changelist()           elküldi (az egész) choicelistet
// jtcombo:changelist(v)          kicseréli choicelistet, és küldi 
// jtcombo:changelist(v,"app")    bővíti choicelistet, és küldi a bővítést
// jtcombo:changelist(v,"ins",i)  beszúr i-nél, és küldi a bővítést
// jtcombo:changelist(v,"del",i)  törli v/i-t, és küldi a törölt indexet
 
local x, n, e

    //először végrehajtjuk lokálisan

    if( mode==NIL )
        if( v==NIL )
            v:=this:choicelist       //újraküldi choicelistet
        else
            this:choicelist:=v       //kicseréli és küldi choicelistet 
        end
 
    elseif( mode=="app" )
        if( !valtype(v)=="A" )
            v:={v}
        end
        for n:=1 to len(v)
            this:additem(v[n])     //bővíti choicelistet, küldi a bővítést
        next

    elseif( mode=="ins" )
        this:insertitem(v,i)       //beszúr, és küldi a bővítést

    elseif( mode=="del" )
    
        if( valtype(v)=="N" )
            i:=v
        elseif( valtype(v)=="C" ) 
            i:=ascan(this:choicelist,{|x|x==v})
        else
            //eredeti i paraméter
        end

        if( i<1 .or. len(this:choicelist)<1  )
            return NIL
        end
        this:deleteitem(i)         //törli i-t, és küldi a törölt indexet
 
    else
        e:=errorNew()
        e:operation:="jcombo.changelist"
        e:description:="invalid mode"
        e:args:={mode}
        break(e)
    end
    
    //azután elküldjük a terminálnak

    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changelist>"
    
    if( mode==NIL )
        x+="<removeall/>"+EOL
        for n:=1 to len(v)
            x+="<app>"+cdataif(v[n])+"</app>"+EOL
        next

    elseif( mode=="app" )
        for n:=1 to len(v)
            x+="<app>"+cdataif(v[n])+"</app>"+EOL
        next

    elseif( mode=="ins" )
        x+="<ins>"
        x+="<at>"+alltrim(str(i-1))+"</at>"+v 
        x+="</ins>"

    elseif( mode=="del" )
        x+="<del>"+alltrim(str(i-1))+"</del>"
    end

    x+="</changelist>"
    x+="</jtmessage>"
    this:send(x)
 
    return NIL


****************************************************************************
 

 