
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

#include "regex.ch"

using regex  regcomp regexec regfree


function main()

local pattern:=a"ho(Y+(X+))ho"
local flags//:=REGEX_EXTENDED//+REGEX_NOSUB

local text:=a"xxxxxhoYYYXXhoxxxxxxxx"
local offs//:=1 //innen kezdi a keresést, default=1
local match:=4  //ennyi pozíciót ad, default=1
local rx,pos,n

    rx:=regcomp(pattern,flags)
    pos:=regexec(rx,text,offs,match)
    regfree(rx)

    ? pattern
    ? text
    ? pos
    
    //a kapott pozíciók {startidx,length} alakúak,
    //startidx offs-tól függetlenül a teljes text-re vonatkozik,
    //1-től indul, substr-nak, stuff-nak közvetlenül átadható

    if( pos==NIL )
        //nincs illeszkedés
        
    elseif( empty(pos) )
        //ha REGEX_NOSUB be van állítva,
        //akkor nem ad semmilyen pozíciót,
        //ilyenkor pos=={}

    elseif( match==NIL .or. match==1 )    
        //csak a teljes kifejezés pozícióját adja
        ? substr(text,pos[1],pos[2])

    else
        //a () részkifejezések pozícióját is adja
        for n:=1 to len(pos)
            ? n, pos[n], substr(text,pos[n][1],pos[n][2])
        next
    end
    ?
