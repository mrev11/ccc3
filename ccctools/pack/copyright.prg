
#include "directry.ch"

static copyright:=<<TEXT>>
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
<<TEXT>>

static s_skip:=":.:..:objlin:objfre:objsol:objmng:objbor:objmsc:setup:ppo:"
static s_srcf:=".cpp.h.prg.ch.lem.lex.java."


*****************************************************************************
function main()
    set dosconv off
    doproc(".")
    ?

*****************************************************************************
static function doproc(dspec)
local name,n,d,d1:={}

    d:=directory(dspec+dirsep()+fullmask(),"DH")
    
    for n:=1 to len(d)
        name:=alltrim(d[n][F_NAME])

        if( "D"$d[n][F_ATTR] )
            if( "L"$d[n][F_ATTR] .or. ":"+name+":"$s_skip )
                //kihagy
            else
                aadd(d1,name)
            end
        elseif( fext(name)$s_srcf )
            proc(dspec+dirsep()+name)
        end
    next
   
    d:=NIL
    
    for n:=1 to len(d1)
        doproc(dspec+dirsep()+d1[n])
    next

*****************************************************************************
static function proc(fspec)

local x:=memoread(fspec)
local ftime:=getfiletime(fspec)
local pos1,pos2,pos3

    x:=strtran(x,chr(13),"")

    if( copyright $ x )
        return NIL
    elseif( at("#define",x)==1 ) //a Lemon generál ilyeneket
        return NIL
    end
    
    ? fspec
    
    pos1:=at("/*",x)
    pos2:=at("CCC - The Clipper to C++ Compiler",x)
    pos3:=at("*/",x)
    
    if( pos1<pos2 .and. pos2<pos3 )
        x:=left(x,pos1-1)+substr(x,pos3+2)
        ?? " x"
    end

    memowrit(fspec,copyright+chr(10)+xtrim(x))
    setfiletime(fspec,ftime[1],ftime[2],ftime[3]+1) //plusz 1 sec

*****************************************************************************
static function fext(fspec) // fspec --> .ext.
local pos:=rat(".",fspec)
    return if(pos==0,"..",substr(fspec,pos)+".")

*****************************************************************************
static function xtrim(x)
local wspace:=chr(9)+chr(10)+chr(13)+chr(32)
local c,pos:=1
    while( !empty(c:=substr(x,pos,1)) .and. c$wspace )
        pos++
    end
    return substr(x,pos)

*****************************************************************************
