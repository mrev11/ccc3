
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

#include "pageman.ch"


*************************************************************************************************
class page(object)
    attrib  buffer
    attrib  dirty


    method  pgid
    method  trid

    method  content

    method  initialize
    method  clone


*************************************************************************************************
static function page.initialize(this)
    this:buffer:=pagebuffer(PAGESIZE)
    this:dirty:=.f.
    return this


*************************************************************************************************
static function page.clone(this)
local page:=objectNew(pageClass()) //inicializálatalan 
    page:buffer:=this:buffer[..]
    page:dirty:=this:dirty
    return page
   

*************************************************************************************************
static function page.pgid(this,id)
    if(id!=NIL)
        xvputchar(this:buffer,PGOFFS_PAGEID,PGFIELD_WIDTH,id)
    else
        id:=xvgetchar(this:buffer,PGOFFS_PAGEID,PGFIELD_WIDTH)
    end
    return id


*************************************************************************************************
static function page.trid(this,id)
    if(id!=NIL)
        xvputchar(this:buffer,PGOFFS_TRANID,PGFIELD_WIDTH,id)
    else
        id:=xvgetchar(this:buffer,PGOFFS_TRANID,PGFIELD_WIDTH)
    end
    return id


*************************************************************************************************
static function page.content(this,x)
    if( x!=NIL  )
        x::=str2bin
        xvputchar(this:buffer,PGOFFS_BEGDATA,PAGESIZE-PGOFFS_BEGDATA,x)
        this:dirty:=.t.
    else
        x:=xvgetchar(this:buffer,PGOFFS_BEGDATA,PAGESIZE-PGOFFS_BEGDATA)::alltrim
    end
    return x


*************************************************************************************************
