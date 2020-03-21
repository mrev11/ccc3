
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

#include "zsearch.say"


****************************************************************************
function textview.search(this,mode)
local color,offset
    
    color:=setcolor(this:mskcolor) 
    zsearch({|g|load(g,this)},{|g|readmodal(g)},{|g|store(g,this,mode,@offset)})
    setcolor(color)

    if(offset!=NIL)
        this:setpos(offset)
    end
    this:display


****************************************************************************
function textview.searchagain(this,mode)
local offset
    store(,this,mode,@offset)
    if( offset!=NIL )
        this:setpos(offset)
        this:display
    end


****************************************************************************
static function load(getlist,this)

local glen:=alltrim(str(len(g_search:varget())))
local template:="X"
local spict:="@S"+glen+"K "+replicate(template,48)

    g_search:picture:=spict
    g_search:varput(this:searchstring)
    //g_search:postblock:={|g|!empty(g:varget())}


****************************************************************************
static function store(getlist,this,mode:="",offset)

local r:=this:actrow
local c:=this:actcol
local ss, pos

    if( getlist!=NIL )
        this:searchstring:=alltrim(g_search:varget())
    end

    if( empty(this:searchstring) )
        return .t.
    end

    ss:=this:searchstring
    
    if( !"p"$mode ) 
        //forward
        //a searchstring kurzornal levo elofordulasat atugorjuk

        if( c==at(ss,this:line(r),c) )
            c+=len(ss) 
        end
        pos:=rowcol2offset(this,r,c)
        pos:=at(ss::str2bin,this:text,pos)
    else 
        //backward
        pos:=rowcol2offset(this,r,c)
        pos:=rat(ss::str2bin,this:text,pos-1)
    end
    
    if( pos>0 )
        offset:=pos
    end

    return .t.


****************************************************************************
function textview.offset(this)
local r:=this:actrow
local c:=this:actcol
    return rowcol2offset(this,r,c)


****************************************************************************
static function rowcol2offset(this,r,c)
local x

    x:=this:line(r)
    x::=left(c-1)    
    x::=str2bin    
    x::=len  //soron beluli byte offset      

    return this:bolpos(r)+x
    

****************************************************************************
    



