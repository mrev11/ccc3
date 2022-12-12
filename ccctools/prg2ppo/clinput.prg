
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

//ez lényegében egy stack

static clid_input:=inputRegister()

****************************************************************************
function inputClass() 
    return clid_input

****************************************************************************
static function inputRegister() 
local clid:=classRegister("input",objectClass())//osztálynév,parentID
    classMethod(clid,"initialize",{|this,s,t| inputIni(   this,s,t )})
    classMethod(clid,"next"      ,{|this,n  | inputNext(  this,n   )})
    classMethod(clid,"get"       ,{|this    | inputGet(   this     )})
    classMethod(clid,"unget"     ,{|this,t,s| inputUnget( this,t,s )})
    classMethod(clid,"len"       ,{|this    | inputLen(   this     )})
    classMethod(clid,"cont"      ,{|this    | inputCont(  this     )})
    classMethod(clid,"index"     ,{|this,i  | inputIndex( this,i   )})
    classMethod(clid,"clear"     ,{|this    | inputClear( this     )})
    classAttrib(clid,"buffer")   //token stack
    classAttrib(clid,"bufidx")   //első szabad hely pozíciója
    return clid


****************************************************************************
function inputNew(size,toklist) 
local clid:=inputClass()
    return objectNew(clid):initialize(size,toklist)


****************************************************************************
static function inputIni(this,size,toklist) 


    //minden adattagot inicializálni kell!
    
    this:buffer  := array(size)
    this:bufidx  := size
    
    if( toklist!=NIL )
        this:unget(toklist)
    end
    
    return this


**************************************************************************** 
static function inputNext(this,n)

local x

    if( n==NIL )
        x:=this:bufidx+1
    else
        x:=this:bufidx+n
    end

    if( 1<=x .and. x<=len(this:buffer) )
        return this:buffer[x]
    end
    return NIL


**************************************************************************** 
static function inputGet(this)
local x:=this:bufidx+1
    if( 1<=x .and. x<=len(this:buffer) )
        this:bufidx++
        return this:buffer[x]
    end
    return NIL
 
 
**************************************************************************** 
static function inputUnget(this,t,lent)

local n,typt:=valtype(t),arrflg

    if( typt=="A" )
        if( lent==NIL )
            lent:=len(t)
        end
        arrflg:=.t.
    else
        lent:=1
        arrflg:=.f.
    end
    

    if( this:bufidx<lent )
        ? this:bufidx, lent
        ? this:buffer
        ? t
        ? @"Input Stack Overflow"
        quit
    end
    
    if( arrflg )
        for n:=lent to 1 step -1
            this:buffer[this:bufidx]:=t[n]
            this:bufidx--
        next
    else
        this:buffer[this:bufidx]:=t
        this:bufidx--
    end
    
    return t


**************************************************************************** 
static function inputLen(this)
    return len(this:buffer)-this:bufidx


**************************************************************************** 
static function inputCont(this)
local a:=array(this:len),n
    for n:=1 to this:len
        a[n]:=this:next(n)
    next
    return a 


**************************************************************************** 
static function inputIndex(this,i)
    return this:bufidx+i  //a next(i) elem indexe bufferban
 

**************************************************************************** 
static function inputClear(this)
    this:bufidx:=len(this:buffer)
    return NIL
 
**************************************************************************** 
 
 
