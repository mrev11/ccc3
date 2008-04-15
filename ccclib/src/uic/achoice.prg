
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

#include "inkey.ch"
#include "setcurs.ch"

*************************************************************************
function achoice(top,left,bottom,right,item,res1,res2,inich)

local crs:=setcursor(SC_NONE)
local choice:=inich
local toppos:=1
local leni:=len(item)
local height:=min(leni,bottom-top+1)
local key

    if( height<1 ) //1998.12.06
        setcursor(crs)
        return choice:=0
    end

    bottom:=top+height-1
    
    if( valtype(choice)!="N" )
        choice:=1
    elseif( choice<1 )
        choice:=1
    elseif( choice>leni )
        choice:=leni
    end

    if( toppos<choice-height+1 )
        toppos:=choice-height+1
    end
    chdraw(top,left,bottom,right,item,toppos,choice)
    
    while(.t.)
    
        key:=inkey(0)
        
        if( key==K_ESC  )
            choice:=0
            exit

        elseif( key==K_LEFT )
            choice:=0
            exit

        elseif( key==K_RIGHT )
            choice:=0
            exit
        
        elseif( key==K_ENTER )
            exit

        elseif( key==K_HOME )
            choice:=1
            toppos:=1
            chdraw(top,left,bottom,right,item,toppos,choice)

        elseif( key==K_END )
            choice:=leni
            toppos:=leni-height+1
            chdraw(top,left,bottom,right,item,toppos,choice)

        elseif( key==K_UP )
            if( choice>1 )
                choice--
                if( toppos>choice )
                    toppos:=choice
                end
                chdraw(top,left,bottom,right,item,toppos,choice)
            end

        elseif( key==K_PGUP )
            choice:=max(1,choice-height)
            if( toppos>choice )
                toppos:=choice
            end
            chdraw(top,left,bottom,right,item,toppos,choice)

        elseif( key==K_DOWN )
            if( choice<leni )
                choice++
                if( toppos<choice-height+1 )
                    toppos:=choice-height+1
                end
                chdraw(top,left,bottom,right,item,toppos,choice)
            end

        elseif( key==K_PGDN )
            choice:=min(leni,choice+height)
            if( toppos<choice-height+1 )
                toppos:=choice-height+1
            end
            chdraw(top,left,bottom,right,item,toppos,choice)
        end
    end
   
    setcursor(crs)
    return choice

*************************************************************************
static function chdraw(top,left,bottom,right,item,toppos,choice)

local color:=setcolor()
local stColor:=LogColor(color,1)
local hiColor:=LogColor(color,2)
local r,w:=right-left+1
local pos:=toppos
local screen:=a""
local outstr

    for r:=top to bottom
        outstr:=padr(item[pos],w)
        screen+=devoutbuffer(outstr,if(pos==choice,hiColor,stColor))
        pos++
    next
    
    restscreen(top,left,bottom,right,screen)
    setpos(top+choice-toppos,right+1)
    //achoice a kurzort a kiemelt sor után kell hagyja!
    return NIL


*************************************************************************
