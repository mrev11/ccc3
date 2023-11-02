
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
function _zedit_search(this,mode)

local color,pos
    
    if( this:markflg )
        this:searchstring:=this:markedstring
        this:markflg:=.f.    
        this:setpos(this:markrow,this:markcol)
        this:display()
    end

    this:casesensitive:=(mode==NIL.or.!"i"$mode)
    
    color:=setcolor(zcolor_1()) 
    zsearch({|g|load(g,this)},{|g|readmodal(g)},{|g|store(g,this,mode,@pos)})
    setcolor(color)

    if(pos!=NIL)
        this:setpos(pos[1],pos[2])
    end

****************************************************************************
function _zedit_sagain(this,mode)
local pos
    store(,this,mode,@pos)

    if(pos!=NIL)
        this:setpos(pos[1],pos[2])
    end

****************************************************************************
static function load(getlist,this)

local glen:=alltrim(str(len(g_search:varget())))
local template:=if(this:casesensitive,"X","!")
local spict:="@S"+glen+"K "+replicate(template,2048)

    g_search:picture:=spict
    g_search:varput(this:searchstring)
    g_search:postblock:={|g|!empty(g:varget())}


****************************************************************************
static function store(getlist,this,mode,pos)

#define UPPER(x) if(this:casesensitive,x,upper(x))

local r:=this:actrow
local c:=this:actcol
local f, ss, rs

    if( getlist!=NIL )
        this:searchstring:=alltrim(g_search:varget())
    end

    if( empty(this:searchstring) )
        return .t.
    end

    ss:=UPPER(this:searchstring)
    rs:=this:replacestring
    
    if( mode==NIL )
        mode:=""
    end
    
    pos:=NIL
    
    if( !"p"$mode ) 
        //forward
        if( !"b"$mode ) //nem batch 
            //a searchstring kurzornal levo elofordulasat atugorjuk
            //kiveve batch modban ("b"$mode), amikor nem ugorjuk at 
            if( !empty(ss) .and. c==at(ss,UPPER(this:atxt[r]),c) )
                c+=len(ss) 
            end
        end
    
        f:=at(ss,UPPER(this:atxt[r]),c)
        while( f==0 .and. r<len(this:atxt) )
            r++
            f:=at(ss,UPPER(this:atxt[r]),1)
        end

    else 
        //backward
        f:=rat(ss,left(UPPER(this:atxt[r]),c-1))
        while( f==0 .and. r>1 )
            r--
            f:=rat(ss,UPPER(this:atxt[r]))
        end
    end
    
    if( f>0 )
        pos:={r,f}

        //itt nem lehet this:setpos-t hivni,
        //mert meg fenn van a search dialog, es at van allitva a szin,
        //ezert csak jelezzuk a talalt poziciot
    end

    return .t.


****************************************************************************

