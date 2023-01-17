
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

//2004.08.23
//A kulso static valtozok inicializalasa szinkronizalt.
//Ezert clid_object kulso definicioja biztositja, hogy tobbszalu
//programokban se inicializalodjon az osztaly tobbszorosen.


static clid_object:=objectRegister()

****************************************************************************
function objectClass() 
    return clid_object

****************************************************************************
static function objectRegister() 
local clid:=classRegister("object",NIL) //osztalynev, {baseid}

    classMethod(clid,"initialize"   ,{|this|objectIni(this)})
    classMethod(clid,"clean"        ,{|this|clean(this)})
    classMethod(clid,"classname"    ,{|this|className(getclassid(this))})
    classMethod(clid,"baseid"       ,{|this|classBaseID(getclassid(this))})
    classMethod(clid,"attrnames"    ,{|this,id|classAttrNames(getclassid(this),id)})
    classMethod(clid,"methnames"    ,{|this,id|classMethNames(getclassid(this),id)})
    classMethod(clid,"length"       ,{|this|classObjectLength(getclassid(this))})
    classMethod(clid,"struct"       ,{|this|classInheritStruct(getclassid(this))})
    classMethod(clid,"asarray"      ,{|this|getobjectasarray(this)})
    classMethod(clid,"attrvals"     ,{|this|attrvals(this)})
    classMethod(clid,"list"         ,{|this|list(this)})
    classMethod(clid,"liststruct"   ,{|this|liststruct(this)})
    classMethod(clid,"ancestors"    ,{|this|ancestors(this)})
    classMethod(clid,"isderivedfrom",{|this,o|isderivedfrom(this,o)})
    classMethod(clid,"evalmethod"   ,{|this,meth,args|evalmethod(this,meth,args)})

    return clid


****************************************************************************
//objectNew() primitiv


****************************************************************************
function objectIni(this)
    return this


****************************************************************************
static function clean(this)
local n
    for n:=1 to len(this)
        this[n]:=NIL
    next
    return this


****************************************************************************
static function attrvals(this) //:attrvals

local names:=this:attrnames
local values:=this:asarray
local acount:=len(names) 
local aNameValue:=array(acount),i

    for i:=1 to acount 
        aNameValue[i]:={names[i],values[i]} 
    next

    return aNameValue


****************************************************************************
static function list(this) //:list
local attrvals:=this:attrvals, i
    for i:=1 to len(attrvals)
        ? i, padr(attrvals[i][1],24),"[",attrvals[i][2],"]"
    next
    return NIL
    

****************************************************************************
static function liststruct(this) //:liststruct
local is:=this:struct,i
    for i:=1 to len(is)
        ? i, padr(is[i][1],24),is[i][2],className(is[i][3])
    next
    return NIL
    

****************************************************************************
static function ancestors(this) //:ancestors

local a:={getclassid(this)}
local n:=0,base,i

    while( ++n<=len(a) )
        base:=classBaseID( a[n] )
        for i:=1 to len(base)
            if( 0==ascan(a,base[i])  )
                aadd(a,base[i])
            end
        next
    end
    a::asort
    for n:=1 to len(a)
        a[n]:=className(a[n])
    next
    return a


****************************************************************************
static function isderivedfrom(this,o)
local cld:=getclassid(this)
local clb:=if(valtype(o)!="N",getclassid(o),o)
    return isderivedfrom1(cld,clb)


static function isderivedfrom1(cld,clb)
local baseid,n
    if( clb==cld )
        return .t.
    else
        baseid:=classBaseID(cld)
        for n:=1 to len(baseid)
            if( isderivedfrom1(baseid[n],clb) )
                return .t.
            end
        next
    end
    return .f.


****************************************************************************
static function evalmethod(this,methname,args)

// nev szerinti metodushivas
// o:evalmethod("methname",{a,b,c}) <-> o:methname(a,b,c)

local ret
local par,n
local blk:=getmethod(getclassid(this),methname) //blokk/index

    if( valtype(blk)=="N" )
        if( len(args)<1 )
            ret:=this:asarray[blk]
        else
            ret:=(this:asarray[blk]:=args[1])
        end
    else
        par:={this}
        for n:=1 to len(args)
            aadd(par,args[n])
        next
        ret:=evalarray(blk,par)
    end
    return ret


****************************************************************************
