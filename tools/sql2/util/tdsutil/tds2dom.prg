
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

namespace tdsutil 
 

******************************************************************************
function tds2dom(fspec)

local s,n,entry

local entity:=xmlnodeNew("entity")
local name:=xmlnodeNew("name")
local tablist:=xmlnodeNew("tablist")
local join //egyelőre NIL //:=xmlnodeNew("join")
local primkey:=xmlnodeNew("primarykey")
local collist:={} //column node-ok
local idxlist:={} //index node-ok
local sellist:={} //select node-ok
local types:=tdsutil.hashtableNew() 
local x,t
local err

    s:=tdsutil.splittds(memoread(fspec))

    for n:=1 to len(s)
        entry:=s[n]
  
        if( left(entry,5)=="name:"  )
            addtext(name,substr(entry,6))

        elseif( left(entry,8)=="version:"  )
            entity:addattrib(xmlattribNew("version",alltrim(substr(entry,9))))

        elseif( left(entry,6)=="table:" )
            addtext(tablist,if(empty(tablist:gettext),"",",")+alltrim(substr(entry,7)))

        elseif( left(entry,5)=="join:"  )
            join:=xmlnodeNew("join")
            addtext(join,substr(entry,6))

        elseif( left(entry,8)=="primkey:" )
            addtext(primkey,alltrim(substr(entry,9)))

        elseif( left(entry,7)=="column:"  )
            aadd(collist,parse_col(entry,types))

        elseif( left(entry,7)=="colref:"  )
            aadd(collist,parse_cref(entry))

        elseif( left(entry,6)=="index:" )
            aadd(idxlist,parse_idx(entry))

        elseif( left(entry,7)=="select:" )
            aadd(sellist,parse_sel(entry))

        elseif( left(entry,5)=="type:" )
            types:add(parse_typ(entry))

        elseif( left(entry,8)=="include:" )
            parse_inc(entry,types,fspec)

        elseif( left(entry,8)=="comment:" )
            //kihagy

        else
            err:=tdserrorNew("tds2dom")
            err:description:="invalid tds entry"
            err:args:={entry}
            break(err)
        end
    next

    //összeszerelés
    
    entity:addcontent(name)
    entity:addcontent(tablist)

    if( join!=NIL )
        entity:addcontent(join)
    end

    for n:=1 to len(collist)
        entity:addcontent(collist[n])
    next
    
    entity:addcontent(primkey)

    for n:=1 to len(idxlist)
        entity:addcontent(idxlist[n])
    next

    for n:=1 to len(sellist)
        entity:addcontent(sellist[n])
    next

    return entity

******************************************************************************
static function parse_col(entry,types)

local col:=xmlnodeNew("column")
local name:=xmlnodeNew("name")
local type:=xmlnodeNew("type")
local typdef,realtype
local n,expr,notnull,default,label,picture,tooltip,collate
local err

    entry:=alltrim(substr(entry,8))  //"column:" levágva
    entry:=tdsutil.splitpar(entry)

    addtext(name,entry[1])

    realtype:=upper(entry[2])
    if( NIL!=(typdef:=types:get(realtype)) )  
        realtype:=typdef[2]
    end
    addtext(type,realtype)
    
    for n:=3 to len(entry)
        if( left(entry[n],2)=="x=" )
            expr:=xmlnodeNew("expr")
            addtext(expr,substr(entry[n],3))
        elseif( left(entry[n],2)=="l=" )
            label:=xmlnodeNew("label")
            addtext(label,substr(entry[n],3))
        elseif( left(entry[n],2)=="t=" )
            tooltip:=xmlnodeNew("tooltip")
            addtext(tooltip,substr(entry[n],3))
        elseif( left(entry[n],2)=="p=" )
            picture:=xmlnodeNew("picture")
            addtext(picture,substr(entry[n],3))
        elseif( left(entry[n],2)=="d=" )
            default:=xmlnodeNew("default")
            addtext(default,substr(entry[n],3))
        elseif( left(entry[n],2)=="c=" )
            collate:=xmlnodeNew("collate")
            addtext(collate,substr(entry[n],3))
        elseif( left(entry[n],2)=="nn" )
            notnull:=xmlnodeNew("notnull")
        else
            err:=tdserrorNew("tds2dom")
            err:description:="invalid column option"
            err:args:={entry[n]}
            //? entry
            break(err)
        end
    next

    //összeszerelés

    col:addcontent(name)
    col:addcontent(type)
    if(expr!=NIL)
        col:addcontent(expr)
    end
    if(notnull!=NIL)
        col:addcontent(notnull)
    end
    if(default!=NIL)
        col:addcontent(default)
    end
    if(picture!=NIL)
        col:addcontent(picture)
    end
    if(label!=NIL)
        col:addcontent(label)
    end
    if(tooltip!=NIL)
        col:addcontent(tooltip)
    end
    if(collate!=NIL)
        col:addcontent(collate)
    end
    return col


******************************************************************************
static function parse_cref(entry)

local col:=xmlnodeNew("colref")
local name:=xmlnodeNew("name")
local n,expr
local err

    entry:=alltrim(substr(entry,8))  //"colref:" levágva
    entry:=tdsutil.splitpar(entry)

    addtext(name,entry[1])

    for n:=2 to len(entry)
        if( left(entry[n],2)=="x=" )
            expr:=xmlnodeNew("expr")
            addtext(expr,substr(entry[n],3))
        else
            err:=tdserrorNew("tds2dom")
            err:description:="invalid colref option"
            err:args:={entry[n]}
            break(err)
        end
    next

    //összeszerelés

    col:addcontent(name)
    if(expr!=NIL)
        col:addcontent(expr)
    end
    return col


******************************************************************************
static function parse_idx(entry)

local index:=xmlnodeNew("index")
local name:=xmlnodeNew("name")
local seglist:=xmlnodeNew("seglist")
local unique //:=xmlnodeNew("unique")
local pos1,pos2

    entry:=alltrim(substr(entry,7))  //"index:" levágva

    pos1:=at("(",entry)
    pos2:=at(")",entry)

    addtext(name,left(entry,pos1-1))
    addtext(seglist,substr(entry,pos1+1,pos2-pos1-1))
    if( "unique"$substr(entry,pos2+1) )
        unique:=xmlnodeNew("unique")
    end
    
    //összeszerelés

    index:addcontent(name)
    index:addcontent(seglist)
    if( unique!=NIL )
        index:addcontent(unique)
    end
    
    return index


******************************************************************************
static function parse_sel(entry)

local sel:=xmlnodeNew("select")
local name:=xmlnodeNew("name")
local where //:=xmlnodeNew("where")
local order //:=xmlnodeNew("order")
local poswhr,posgrp,poshav,posord,posdst,txt

    entry:=alltrim(substr(entry,8))  //"select:" levágva
    
    poswhr:=tdsutil.atsymbol("where",entry)
    posgrp:=tdsutil.atsymbol("group",entry)
    poshav:=tdsutil.atsymbol("having",entry)
    posord:=tdsutil.atsymbol("order",entry)
    posdst:=tdsutil.atsymbol("distinct",entry)

    addtext(name,subtext(entry,1,{poswhr,posgrp,poshav,posord,posdst}))

    txt:=""
    if( posdst>0 )
        txt+="distinct"
    end
    if( poswhr>0 )
        txt+=" "+subtext(entry,poswhr,{posord,posdst})
    elseif( posgrp>0 )
        txt+=" "+subtext(entry,posgrp,{posord,posdst})
    elseif( poshav>0 )
        txt+=" "+subtext(entry,poshav,{posord,posdst})
    end
    if( !empty(txt) )
        where:=xmlnodeNew("where")
        addtext(where,txt)
    end
   
    if( posord>0 )  
        txt:=subtext(entry,posord,{posdst})
        txt:=alltrim(substr(txt,6)) //order levágva
        if( left(txt,3)=="by " )
            txt:=alltrim(substr(txt,4)) //by levágva
        elseif( left(txt,1)=="(")
            txt:=substr(txt,2,len(txt)-2) // (...) levágva
        end
        order:=xmlnodeNew("order")
        addtext(order,txt)
    end

    //összeszerelés

    sel:addcontent(name)

    if(where!=NIL)
        sel:addcontent(where)
    end
    
    if(order!=NIL)
        sel:addcontent(order)
    end

    return sel

#ifdef EMLEKEZTETO //distinct 2007.06.19
  Az Oracle csak az egyszerű 'distinct'-et támogatja, 
  azt is csak korlátozásokkal (nem lehet a mezők között blob).
  Az egyszerű distinct pótolható  a 'group by' klózzal, 
  ha a 'group by' után felsoroljuk az egész select listet.
#endif

#ifdef EMLEKEZTETO //a dolgok logikája
  A join meghatározza a táblák összekapcsolását.
  A selectlist meghatározza az eredménytábla oszlopait.
  A where meghatározza az eredménytábla sorait.
  Az order meghatározza az eredménytábla sorainak rendezettségét.
  
  Ezért a distinct klóz logikus helye nem a selectlist,
  hanem a where környékén van. Az SQL utasításgenerátor fogja
  átrakni a distinct-et a selectlist elé. A where név itt kissé
  félrevezető, ui. a sorok filterezéséról van szó.
#endif

#ifdef EMLEKEZTETO //where kiegészítés 2007.06.19
  Korábban vagy volt "where" klóz, vagy egyáltalán nem lehetett 
  filterezni, pl. nem kezdődhetett a filter egy "group by" klózzal.
  A tds elemző a where kulcsszót levágta, az SQL kódgenerátor 
  pedig újra berakta. Most meghagyjuk a filter klózokat úgy, 
  ahogy beírták. 
#endif

#ifdef EMLEKEZTETO //order by 2007.06.19
  Korábban az order-t így kellett beírni a tds-be: order(col1,col2,...)
  Ehelyett jobb a szokásos: order by col1,col2
  Elfogadjuk azért a korábbi szintaktikát is.
  
  Az "order by" kulcsszót a tds elemző levágja,
  az SQL utasítás generátor visszarakja.
#endif

******************************************************************************
static function parse_typ(entry)
local pos,typedef:=array(2)
    entry:=upper(alltrim(substr(entry,6)))  //"type:" levágva
    pos:=at(" ",entry)
    typedef[1]:=left(entry,pos-1)
    typedef[2]:=alltrim(substr(entry,pos+1))
    return typedef


******************************************************************************
static function parse_inc(incl,types,parent)

local fspec,tdspath,n,f,s,entry

    fspec:=alltrim(substr(incl,9))  //"include:" levágva

    tdspath:=getenv("TDSPATH")
    tdspath:=strtran(tdspath,":",";")
    if( parent!=NIL )
        parent:=tdsutil.fpath0(parent)+";"
    else
        parent:=""
    end
    tdspath:=split(".;"+parent+tdspath,";")

    for n:=1 to len(tdspath)
        f:=tdspath[n]+dirsep()+fspec
        if( file(f) )
            exit
        end
    next

    if( !file(f) )
        ? incl
        ? "file not found"
        ?
        errorlevel(1)
        quit
    end

    ?? "    include:",f
    ?

    s:=tdsutil.splittds(memoread(f))

    for n:=1 to len(s)
        entry:=s[n]

        if( left(entry,5)=="type:" )
            types:add(parse_typ(entry))

        elseif( left(entry,8)=="include:" )
            parse_inc(entry,types,f)

        elseif( left(entry,8)=="comment:" )
            //kihagy

        else
            ?? entry
            ? "not allowed here"
            ?
            errorlevel(1)
            quit
        end
    next
    
    return NIL


******************************************************************************
static function addtext(node,text)
local x
    node:addcontent(x:=xmlnodeNew("#TEXT"))
    x:addcontent(alltrim(text))
    return NIL


******************************************************************************
static function subtext(text,pos,apos)
local n,minpos:=len(text)+1
    for n:=1 to len(apos)
        if( apos[n]<=pos )
            //kihagy
        elseif( minpos<apos[n] )
            //volt kisebb
        else
            minpos:=apos[n]
        end
    next
    return alltrim(substr(text,pos,minpos-pos))


******************************************************************************
