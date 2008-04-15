
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

// Be kell járni egy DOM-ot,
// és ki kell belőle szedni egy rakás paramétert.
// Erre szolgál a tdsutil.domparse osztály, 
// a bejárás az initialize metódusban történik.

namespace tdsutil


******************************************************************************
class domparse(object)

    attrib version
    attrib ename
    attrib tablst
    attrib collst
    attrib indlst
    attrib sellst
    attrib tabjoin
    attrib primkey
    
    method initialize 

******************************************************************************
static function domparse.initialize(this,dom)

local version
local ename
local tablst:={}
local collst:={}
local indlst:={}
local sellst:={}
local tabjoin
local primkey

local entity,n
local tag
local err

    entity:=dom:content[1] 
    
    if( !entity:type=="entity" )
        err:=tdserrorNew("tdsutil.domparse")
        err:description:="not a valid entity definition DOM"
        err:args:={entity:type}
        break(err)
    end
    
    version:=entity:getattrib("version")
    
    for n:=1 to len(entity:content)

        tag:=entity:content[n] 

        if( tag:type=="name" )
            ename:=lower(tag:gettext)

        //elseif( tag:type=="version" )
        //    version:=tag:gettext

        elseif( tag:type=="tablist" )
            tablst:=split(lower(rmbl(tag:gettext)))
 
        elseif( tag:type=="column" )
            aadd(collst,coldef(tag))   //definíció collst-ben

        elseif( tag:type=="colref" )
            aadd(collst,colref(tag))   //referencia collst-ben

        elseif( tag:type=="index" )
            aadd(indlst,inddef(tag))

        elseif( tag:type=="join" )
            tabjoin:=rmlf(tag:gettext)

        elseif( tag:type=="select" )
            aadd(sellst,seldef(tag))
 
        elseif( tag:type=="primarykey" )
            primkey:=split(lower(rmbl(tag:gettext)))

        else
            err:=tdserrorNew("tdsutil.domparse")
            err:description:="unknown tag in entity"
            err:args:={tag:type}
            break(err)
        end
    next

    this:version:=version
    this:ename:=ename
    this:tablst:=tablst
    this:collst:=collst
    this:indlst:=indlst
    this:sellst:=sellst
    this:tabjoin:=tabjoin
    this:primkey:=primkey

    return this

******************************************************************************
static function colref(tag1)

local n,tag
local name,expr
local err

    for n:=1 to len(tag1:content)
        tag:=tag1:content[n] 

        if( tag:type=="name" )
            name:=lower(tag:gettext)

        elseif( tag:type=="expr" )
            expr:=tag:gettext
        
        elseif( tag:type=="type" )        //elfogadja, de kihagyja
        elseif( tag:type=="default" )     //elfogadja, de kihagyja
        elseif( tag:type=="notnull" )     //elfogadja, de kihagyja
        elseif( tag:type=="null" )        //elfogadja, de kihagyja
        elseif( tag:type=="label" )       //elfogadja, de kihagyja
        elseif( tag:type=="tooltip" )     //elfogadja, de kihagyja
        elseif( tag:type=="picture" )     //elfogadja, de kihagyja
 
        else
            err:=tdserrorNew("tdsutil.domparse")
            err:description:="unknown tag in column"
            err:args:={tag:type}
            break(err)
        end
    next

    if( name==NIL )
         err:=tdserrorNew("tdsutil.domparse")
         err:description:="column without name"
         //err:args:={}
         break(err)
    end
    
    return tdsutil.columnrefNew(name,expr)


******************************************************************************
static function coldef(tag1)

local col
local n,tag
local name,expr,type,notnull,default
local label,tooltip,picture
local err

    for n:=1 to len(tag1:content)
        tag:=tag1:content[n] 

        if( tag:type=="name" )
            name:=lower(tag:gettext)

        elseif( tag:type=="expr" )
            expr:=tag:gettext

        elseif( tag:type=="type" )
            type:=upper(tag:gettext)

        elseif( tag:type=="label" )
            label:=tag:gettext

        elseif( tag:type=="tooltip" )
            tooltip:=tag:gettext

        elseif( tag:type=="picture" )
            picture:=tag:gettext

        elseif( tag:type=="notnull" )
            notnull:=.t.

        elseif( tag:type=="null" )
            notnull:=.f.

        elseif( tag:type=="default" )
            default:=tag:gettext

        else
            err:=tdserrorNew("tdsutil.domparse")
            err:description:="unknown tag in column"
            err:args:={tag:type}
            break(err)
        end
    next

    if( name==NIL )
        err:=tdserrorNew("tdsutil.domparse")
        err:description:="column without name"
        break(err)
    end
    if( type==NIL )
        err:=tdserrorNew("tdsutil.domparse")
        err:description:="column without type"
        err:args:={name}
        break(err)
    end

    col:=tdsutil.columndefNew(name,expr,type)

    if(label!=NIL);   col:label:=label;     end
    if(tooltip!=NIL); col:tooltip:=tooltip; end
    if(picture!=NIL); col:picture:=picture; end
    if(notnull!=NIL); col:notnull:=notnull; end
    if(default!=NIL); col:default:=default; end
    
    return col


******************************************************************************
static function inddef(tag1)

local n,tag
local name,seglist,unique
local err

    for n:=1 to len(tag1:content)
        tag:=tag1:content[n] 

        if( tag:type=="name" )
            name:=lower(tag:gettext)

        elseif( tag:type=="seglist" )
            seglist:=split(lower(rmbl(tag:gettext)))

        elseif( tag:type=="unique" )
            unique:=.t.
 
        else
            err:=tdserrorNew("tdsutil.domparse")
            err:description:="unknown tag in index"
            err:args:={tag:type}
            break(err)
        end
    next

    if( name==NIL )
        err:=tdserrorNew("tdsutil.domparse")
        err:description:="index without name"
        break(err)
    end
    if( seglist==NIL )
        err:=tdserrorNew("tdsutil.domparse")
        err:description:="index without segments"
        err:args:={name}
        break(err)
    end
    
    return tdsutil.indexdefNew(name,seglist,unique)


******************************************************************************
static function seldef(tag1)

local n,tag
local name,where,order//,distinct
local err

    for n:=1 to len(tag1:content)
        tag:=tag1:content[n] 

        if( tag:type=="name" )
            name:=lower(tag:gettext)
 
        elseif( tag:type=="where" )
            where:=strtran(rmlf(tag:gettext),"&lt;","<") 

        elseif( tag:type=="order" )
            order:=split(lower(rmlf(tag:gettext)))

        //elseif( tag:type=="distinct" )
        //    distinct:=split(lower(rmlf(tag:gettext)))
 
        else
            err:=tdserrorNew("tdsutil.domparse")
            err:description:="unknown tag in select"
            err:args:={tag:type}
            break(err)
        end
    next

    if( name==NIL )
        err:=tdserrorNew("tdsutil.domparse")
        err:description:="select without name"
        break(err)
    end

    return {name,where,order/*,distinct*/}

 
******************************************************************************
static function rmlf(x) //remove linefeed
    x:=strtran(x,chr(13),"")
    while( (" "+chr(10))$x  )
        x:=strtran(x," "+chr(10),chr(10))
    end
    while( (chr(10)+" ")$x  )
        x:=strtran(x,chr(10)+" ",chr(10))
    end
    return strtran(x,chr(10)," ")


******************************************************************************
static function rmbl(x) //remove blank
    x:=strtran(x," ","")
    x:=strtran(x,chr(9),"")
    x:=strtran(x,chr(10),"")
    x:=strtran(x,chr(13),"")
    return x


******************************************************************************
function  veriftype(c)
local err

    if( ctype(c:type)  )
    elseif( ntype(c:type) )
    elseif( c:type=="D" )
    elseif( c:type=="L" )
    elseif( c:type=="M" )
    else
        err:=tdserrorNew("tdsutil.domparse")
        err:description:="invalid column type"
        err:args:={c:name,c:type}
        break(err)
    end

static function ctype(t)
local width:=xval(substr(t,2))
    return  left(t,1)=="C" .and. 0<width .and. width<=0xffff

static function ntype(t)
local width:=0,decml:=0,pos
    if( (pos:=at(".",t))>0 .or. (pos:=at(",",t))>0  )
        width:=xval(substr(t,2,pos-2))
        decml:=xval(substr(t,pos+1))
    else
        width:=xval(substr(t,2))
    end
    return left(t,1)=="N" .and. 0<=decml .and. decml<=width .and. width<64

static function xval(x)
local v:=val(x)
    return if(alltrim(str(v,6,0))==x,v,-1)


******************************************************************************


