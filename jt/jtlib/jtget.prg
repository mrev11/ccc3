
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
//jtget
****************************************************************************
class jtget(jtelem) 

    method  initialize

    method  xmladd
    method  xmlput      {|this,x|this:text:=x:gettext}
    method  xmlget      {|this|cdataif(this:text)}

    method  changed     {|this|!this:laststate==this:text}
    method  savestate   {|this|this:laststate:=this:text}
    method  varput
    method  varget
 
    attrib  picture
 
    method  valtype
    method  decimal
    attrib  _valtype_
    attrib  _decimal_
 
    //Az alábbiak nemcsak átírják a megfelelő attribútumot,
    //hanem rögtön xml üzenetet is küldenek a terminálra,
    //csak akkor kell őket használni, amikor a már létező
    //dialogboxban akarunk változásokat eszközölni:
 
    method  changepicture

****************************************************************************
static function jtget.initialize(this,t,l,b,r) 
    this:(jtelem)initialize(t,l,b,r)
    this:picture:=""
    return this

****************************************************************************
static function jtget.xmladd(this)
local x:=""
    if( !empty(this:picture) )
        x+="<picture>"+cdataif(this:picture)+"</picture>"
    end
    return x


****************************************************************************
static function jtget.valtype(this)
local funcstr, p
    if( this:_valtype_==NIL )
        if( this:picture==NIL .or. !left(this:picture,1)=="@" )
            this:_valtype_:="C"
        else
            if( 0<(p:=at(" ",this:picture)) )
                funcstr:=left(this:picture,p)
            else
                funcstr:=this:picture
            end
            
            if( "N"$funcstr )
                this:_valtype_:="N"
            elseif( "D"$funcstr )
                this:_valtype_:="D"
            elseif( "L"$funcstr )
                this:_valtype_:="L"
            else
                this:_valtype_:="C"
            end
        end
    end
    return this:_valtype_


****************************************************************************
static function jtget.decimal(this) //tizedesek száma
local p
    if( this:_decimal_==NIL )
        if( this:valtype=="N" .and. 0<(p:=rat(".",this:picture)) )
            this:_decimal_:=len(this:picture)-p
        else
            this:_decimal_:=0
        end
    end
    return this:_decimal_
 
****************************************************************************
static function jtget.varget(this)
local t:=this:valtype
    if( t=="C" )
        return this:text
    elseif( t=="N" )
        return val(this:text)
    elseif( t=="D" )
        return stod(padr(this:text,8))
    elseif( t=="L" )
        return this:text$"TtYy"
    end
    return NIL

****************************************************************************
static function jtget.varput(this,x)
local t:=this:valtype
    if( t=="C" )
        this:text:=x
    elseif( t=="N" )
        //this:text:=alltrim(str(x))
        //itt a tizedeseket pontosan kell kiírni!
        this:text:=alltrim(str(x,32,this:decimal)) 
    elseif( t=="D" )
        this:text:=dtos(x)
    elseif( t=="L" )
        this:text:=if(x,"T","F")
    end
    return x
 
****************************************************************************
static function jtget.changepicture(this,v)
local x
    if( v!=NIL )
        this:picture:=v
        this:_valtype_:=NIL
    end
    x:='<jtmessage'
    x+=ATTR("pid",alltrim(str(getpid())))
    x+=ATTR("dialogid",this:dialogid)
    x+='>'
    x+="<control>"+this:name+"</control>"
    x+="<changepicture>"
    x+=cdataif(this:picture)
    x+="</changepicture>"
    x+="</jtmessage>"
    this:send(x)
    return NIL


****************************************************************************
 