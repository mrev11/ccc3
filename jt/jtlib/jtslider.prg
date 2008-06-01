
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
//jtslider
****************************************************************************
class jtslider(jtelem) 

    method  initialize

    method  xmladd
    method  xmlput      {|this,x|this:value:=val(x:gettext)}
    method  xmlget      {|this|alltrim(str(this:value))}

    method  changed     {|this|!this:laststate==this:value}
    method  savestate   {|this|this:laststate:=this:value}
    method  varput      {|this,x|this:value:=x}
    method  varget      {|this|this:value}
 
    attrib  value

    attrib  orientation //h/v (kisbetű)
    attrib  inverted    //.f.
    attrib  min         //0
    attrib  max         //100
    attrib  majortick   //10
    attrib  minortick   //1
    attrib  painttick   //.f.
    attrib  paintlabel  //.f.
    attrib  labeltable  
 
    //Az alábbiak nemcsak átírják a megfelelő attribútumot,
    //hanem rögtön xml üzenetet is küldenek a terminálra,
    //csak akkor kell őket használni, amikor a már létező
    //dialogboxban akarunk változásokat eszközölni:
 
    method  changevalue

****************************************************************************
static function jtslider.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:orientation:="h"
    this:inverted:=.f.
    this:value:=50
    this:min:=0
    this:max:=100
    this:majortick:=10
    this:minortick:=1
    this:painttick:=.f.
    this:paintlabel:=.f.
    return this

****************************************************************************
static function jtslider.xmladd(this)
local x:="",val,lab,n

    x+="<orientation>"+this:orientation+"</orientation>"
    x+="<inverted>"+if(this:inverted,"true","false")+"</inverted>"
    x+="<value>"+alltrim(str(this:value))+"</value>"
    x+="<min>"+alltrim(str(this:min))+"</min>"
    x+="<max>"+alltrim(str(this:max))+"</max>"
    x+="<minortick>"+alltrim(str(this:minortick))+"</minortick>"
    x+="<majortick>"+alltrim(str(this:majortick))+"</majortick>"
    x+="<painttick>"+if(this:painttick,"true","false")+"</painttick>"
    x+="<paintlabel>"+if(this:paintlabel,"true","false")+"</paintlabel>"

    if( this:labeltable!=NIL )
        for n:=1 to len(this:labeltable)
            //<val1>value</val1><lab1>label</lab1>
            val:="val"+alltrim(str(n))
            lab:="lab"+alltrim(str(n))
            x+="<"+val+">"+alltrim(str(this:labeltable[n][1]))+"</"+val+">"
            x+="<"+lab+">"+this:labeltable[n][2]+"</"+lab+">"
        next
    end

    return x

****************************************************************************
static function jtslider.changevalue(this,v)
local x
    if( v!=NIL )
        this:value:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changevalue>"
    x+=this:xmlget
    x+="</changevalue>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

****************************************************************************
