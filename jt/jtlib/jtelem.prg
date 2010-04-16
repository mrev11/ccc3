
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
//jtelem
****************************************************************************
class jtelem(object)  new:  //nem kell jtelemNew

    method initialize
        
    //------------------------------------- 
    //Belső használatra 
    //------------------------------------- 
 
    //Összekapcsolják a kontrollt és a dialogboxot.

    method setdialogid      {|this,x|this:dialogid:=x}
    attrib dialogid

    //Beágyazott kontrollok

    attrib itemlist

    //Belső használatú metódusok az xml kommunikációhoz        

    method send             {|this,x|jtsocket():send(x)}
    method xmlout
    method xmlname          {|this|this:classname}
    method xmladd           {||""}
    method xmlput           {|this,x|this:text:=x:gettext}
    method xmlget           {|this|this:text}

    //Ehhez hasonlítva állapítja meg a változást a changed metódus.

    method savestate        {||NIL}
    attrib laststate

    //Kell-e küldeni a kontroll értéket a reaction üzenetben?

    method changed          {||.f.}
 
    //-------------------------------------
    //Alkalmazási programoknak
    //------------------------------------- 
 
    //Kiolvassák/beállítják a kontrollok tartalmát,
    //konvertálják a típusokat az adott kontroll fajtája szerint.

    method varget       {|this|this:text}
    method varput       {|this,x|this:text:=x}
 
    //Az alábbiak a kontrollok általános attribútumai:

    attrib top
    attrib left
    attrib bottom
    attrib right
    attrib halign
    attrib valign
    attrib alignx
    attrib aligny
    attrib htextpos
    attrib vtextpos
    attrib name         //kontroll azonosító

    attrib text
    attrib tooltip
    attrib icon         //terminál oldali jpeg/gif filéspec 
    attrib image        //átküldött jpeg/gif image
    attrib border       //defaulttól eltérő keret
 
    attrib valid        //akciót kell generálni
    attrib escape       //nem kell ellenőrizni a kontrollt
    attrib enabled      //t/f
    attrib focusable    //adható-e fókusz a kontrollra
    attrib mnemonic     //egy betű
    attrib accelerator  //egy string, pl. "control shift X"
 
    //Ha egy kontrollnak van akcióblokkja,
    //akkor azt a getmessage automatikusan végrehajtja,
    //ha a kontrollból akció érkezik.

    attrib actionblock

    //Az alábbiak nemcsak átírják a megfelelő attribútumot,
    //hanem rögtön xml üzenetet is küldenek a terminálra,
    //csak akkor kell őket használni, amikor a már létező
    //dialogboxban akarunk változásokat eszközölni:

    method changetext
    method changetooltip
    method changeicon
    method changeimage
    method changeenabled
    method changefocusable
    method changeitem
    method setfocus


****************************************************************************
static function jtelem.initialize(this,t,l,b,r) 
static counter:=0

    this:(object)initialize

    this:dialogid    :=""

    this:top         :=t
    this:left        :=l
    this:bottom      :=b
    this:right       :=r
    this:halign      :=NIL
    this:valign      :=NIL
    this:alignx      :=NIL
    this:aligny      :=NIL
    this:name        :="_ctrl_"+alltrim(str(++counter))
 
    this:text        :=""
    this:tooltip     :=NIL
    this:icon        :=NIL
    this:image       :=NIL
    this:border      :=NIL
 
    this:valid       :=.f.
    this:escape      :=.f.
    this:enabled     :=.t.
    this:focusable   :=.t.
    this:itemlist    :=NIL
    this:actionblock :=NIL
  
    return this
 
****************************************************************************
static function jtelem.xmlout(this)
local x,e

    x:="<"+this:xmlname
    x+=ATTRI("top",this:top)
    x+=ATTRI("left",this:left)
    x+=ATTRI("bottom",this:bottom)
    x+=ATTRI("right",this:right)
    x+=ATTR("halign",this:halign)
    x+=ATTR("valign",this:valign)
    x+=ATTR("alignx",this:alignx)
    x+=ATTR("aligny",this:aligny)
    x+=ATTR("htextpos",this:htextpos)
    x+=ATTR("vtextpos",this:vtextpos)
    x+=ATTR("name",this:name)
    x+=">"

    if( !empty(this:tooltip) )
        x+="<tooltip>"+cdataif(this:tooltip)+"</tooltip>"
    end

    if( !empty(this:icon) )
        x+="<icon>"+this:icon+"</icon>"
    end

    if( !empty(this:image) )
        x+="<image>"+bin2str(base64_encode(this:image))+"</image>" 
    end

    if( !empty(this:border) )
        x+="<border>"+this:border+"</border>" 
    end
 
    if( !this:enabled )
        x+="<enabled>"
        x+=if(this:enabled,"true","false")
        x+="</enabled>"
    end

    if( this:escape )
        x+="<escape>"
        x+=if(this:escape,"true","false")
        x+="</escape>"
    end

    if( !this:focusable )
        x+="<focusable>"
        x+=if(this:focusable,"true","false")
        x+="</focusable>"
    end

    if( this:mnemonic!=NIL )
        x+="<mnemonic>"
        x+=this:mnemonic      //pl. "X"
        x+="</mnemonic>"
    end

    if( this:accelerator!=NIL )
        x+="<accelerator>"
        x+=this:accelerator   //pl. "alt X", vagy "control alt X"
        x+="</accelerator>"
    end

    if( this:valid .or. this:actionblock!=NIL  )
        x+="<valid>"
        x+=if(this:valid .or. this:actionblock!=NIL,"true","false")
        x+="</valid>"
        
        if( empty(this:name) )
            e:=errorNew()
            e:operation:="jtelem.xmlout"
            e:description:="valid field without name"
            e:args:={this:xmlname}
            break(e)
            
            //A komponens akciót akar jelenteni,
            //ami nem lehetséges név nélkül,
            //ha itt nem jelentenénk a hibát,
            //akkor később az XML elemzés akadna meg.
        end
    end
    
    x+=this:xmladd //bővítmények

    if( !empty(this:text) )
        x+="<text>"+cdataif(this:text)+"</text>"
    end
 
    x+="</"+this:xmlname+">"
    return x
 
 
****************************************************************************
static function jtelem.changetext(this,v)
local x
    if( v!=NIL )
        this:text:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changetext>"
    x+=cdataif(this:text)
    x+="</changetext>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

****************************************************************************
static function jtelem.changetooltip(this,v)
local x
    if( v!=NIL )
        this:tooltip:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changetooltip>"
    x+=cdataif(this:tooltip)
    x+="</changetooltip>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

****************************************************************************
static function jtelem.changeicon(this,v)
local x
    if( v!=NIL )
        this:icon:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changeicon>"
    x+=cdataif(this:icon)
    x+="</changeicon>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

****************************************************************************
static function jtelem.changeimage(this,v)
local x
    if( v!=NIL )
        this:image:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changeimage>"
    x+=bin2str(base64_encode(this:image))
    x+="</changeimage>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

****************************************************************************
static function jtelem.changeenabled(this,v)
local x
    if( v!=NIL )
        this:enabled:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<enabled>"
    x+=if(this:enabled,"true","false")
    x+="</enabled>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

****************************************************************************
static function jtelem.changefocusable(this,v)
local x
    if( v!=NIL )
        this:focusable:=v
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<focusable>"
    x+=if(this:focusable,"true","false")
    x+="</focusable>"
    x+="</jtmessage>"
    this:send(x)
    return NIL
 
****************************************************************************
static function jtelem.changeitem(this,ctrl)

local e,x,a1,a2,i

    if( ctrl==NIL )
        //2008.01.14

    elseif( !this:classname==ctrl:classname )

        //vakon cseréljük az objektum attribútumait,
        //ami csak egyező struktúrákra engedhető meg
    
        e:=errorNew()
        e:operation("jtelem.changeitem")
        e:description("different class")
        e:args:={ctrl:classname}
        break(e)

    else
        ctrl:setdialogid(this:dialogid) //2010.04.15

        a1:=this:asarray 
        a2:=ctrl:asarray 
        for i:=1 to len(a1)
            a1[i]:=a2[i]
        next
    end
    
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changeitem>"
    x+=this:xmlout
    x+="</changeitem>"
    x+="</jtmessage>"
    this:send(x)

    return NIL

****************************************************************************
static function jtelem.setfocus(this)
local x
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<setfocus/>"
    x+="</jtmessage>"
    this:send(x)
    return NIL

****************************************************************************

