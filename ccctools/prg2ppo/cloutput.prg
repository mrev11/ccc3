
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

//ez lényegében egy egyszerű FIFO sor
//egy array, amibe rakosgatjuk a kimenetet
//akár egyesével, akár array-ben gyűjtve, 
//a buffer mérete szükség esetén automatikusan növekszik,
//végül az egészet tartalmat elkérjük
//aadd optimalizálására használható


#define BUFFER_INCREMENT  32


static clid_output:=outputRegister()
 
****************************************************************************
function outputClass() 
    return clid_output

****************************************************************************
static function outputRegister() 
local clid:=classRegister("output",objectClass())//osztálynév,parentID
    classMethod(clid,"initialize",{|this,s | outputIni(   this,s )})
    classMethod(clid,"add"       ,{|this,t | outputAdd(   this,t )})
    classMethod(clid,"len"       ,{|this   | outputLen(   this   )})
    classMethod(clid,"buf"       ,{|this   | outputBuf(   this   )})
    classMethod(clid,"clear"     ,{|this   | outputClear( this   )})
    classAttrib(clid,"buffer")   
    classAttrib(clid,"bufidx")   
    classAttrib(clid,"bufinc")    
    return clid
    

****************************************************************************
function outputNew(incsize) 
local clid:=outputClass()
    return objectNew(clid):initialize(incsize)


****************************************************************************
static function outputIni(this,size) 


    //minden adattagot inicializálni kell!

    this:bufinc  := if(size!=NIL,size,BUFFER_INCREMENT) 
    this:buffer  := array(this:bufinc)
    this:bufidx  := 1
    
    return this


**************************************************************************** 
static function outputAdd(this,t)

local n,typt:=valtype(t),lent,arrflg

    if( typt=="A" )
        lent:=len(t)
        arrflg:=.t.
    else
        lent:=1
        arrflg:=.f.
    end

    if( this:bufidx+lent>len(this:buffer) )
        asize(this:buffer,this:bufidx+lent+this:bufinc)
    end
    
    if( arrflg )
        for n:=1 to lent
            this:buffer[this:bufidx]:=t[n]
            this:bufidx++
        next
    else
        this:buffer[this:bufidx]:=t
        this:bufidx++
    end
    
    return t


**************************************************************************** 
static function outputLen(this)
    return this:bufidx-1


**************************************************************************** 
static function outputBuf(this)
    return this:buffer


**************************************************************************** 
static function outputClear(this)
    this:buffer:=array(this:bufinc) 
    this:bufidx:=1
    return NIL

 
**************************************************************************** 
 
 
 
