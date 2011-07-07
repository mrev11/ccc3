
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

#include "box.ch"
#include "inkey.ch"

#define RECT          t,l,b,r
#define TOP_LINE      0,0,0,maxcol()
#define BOTTOM_LINE   maxrow(),0,maxrow(),maxcol()


*******************************************************************************
function DrawBox(nTop, nLeft, nBottom, nRight, cFrame)
local cScreen:=savescreen(nTop, nLeft, nBottom, nRight)
    @ nTop, nLeft clear to nBottom, nRight 
    @ nTop, nLeft, nBottom, nRight box cFrame
    return cScreen


*******************************************************************************
function ChoiceBox(top,left,bottom,right,menu,sel,fun,ini,winrow)
local posr:=row(), posc:=col()
local screen:=DrawBox(top,left,bottom,right,B_SINGLE)
local choice:=achoice(top+1,left+1,bottom-1,right-1,menu,,,ini)
    restscreen(top,left,bottom,right,screen)
    setpos(posr,posc)
    return choice


*******************************************************************************
function BotMessage(get,text,color) // változó tartalmú message alul
local curs:=setcursor(0)
local posr:=row(), posc:=col()

    if( get==NIL )
        get:=GetNew(maxrow(),0,;
                {|x|if(x!=NIL, padc(text:=x,maxcol()), padc(text,maxcol()) )};
                ,,,color)
        get:cargo:=savescreen(BOTTOM_LINE)
        get:display()

    elseif(text!=NIL)
        get:varPut(text)
        get:display()

    else
        restscreen(BOTTOM_LINE, get:cargo)
    end
    setpos(posr,posc)
    setcursor(curs)
    return get


*******************************************************************************
function topMessage(get,text) // változó tartalmú message felül
local curs:=setcursor(0)
local posr:=row(), posc:=col()

    if( get==NIL )
        get:=GetNew(0,0,;
                {|x|if(x!=NIL, padc(text:=x,maxcol()), padc(text,maxcol()) )};
                ,,,logcolor(setcolor(),2) )
        get:cargo:=savescreen(TOP_LINE)
        get:display()

    elseif(text!=NIL)
        get:varPut(text)
        get:display()

    else
        restscreen(TOP_LINE, get:cargo)
    end
    setpos(posr,posc)
    setcursor(curs)
    return get


*******************************************************************************
function Message(get, text, color) // változó tartalmú message középen
local curs:=setcursor(0)
local posr:=row(), posc:=col()
local savecolor
//local t:=12,l:=10,b:=16,r:=70
local mr:=int(maxrow()/2), mc:=int(maxcol())
local t:=mr-2,l:=10,b:=mr+2,r:=mc-10


    if( get==NIL )
        savecolor:=setcolor(color)
        get:=GetNew( (t+b)/2, l+2,;
                {|x|if(x!=NIL, padc(text:=x,r-l-4), padc(if(text==NIL,"",text),r-l-4) )};
                ,,,setcolor(color))
        get:cargo:=DrawBox(RECT, B_DOUBLE)
        get:display()
        setcolor(savecolor)

    elseif(text!=NIL)
        get:varPut(text)
        get:display()

    else
        restscreen(RECT, get:cargo)
    end
    setpos(posr,posc)
    setcursor(curs)
    return get


*******************************************************************************
function DispBox(t,l,b,r,frame,color) 

local top,bot,ver,n
local useframe:=B_SINGLE
local savecolor:=setcolor(color)

    if( valtype(frame)=="N" )
        if( frame==2 )
            useframe:=B_DOUBLE
        end

    elseif( valtype(frame)=="C" )

        if( len(frame)==1 )
            useframe:=replicate(frame,len(useframe))

        elseif( len(frame)==len(useframe) )
            useframe:=frame
        end
    end

    top:=substr(useframe,1,1)+replicate(substr(useframe,2,1),r-l-1)+substr(useframe,3,1)
    bot:=substr(useframe,7,1)+replicate(substr(useframe,6,1),r-l-1)+substr(useframe,5,1)
    ver:=replicate(substr(useframe,8,1),b-t-1)
    
    devpos(t,l);devout(top)
    devpos(t+1,l);devoutvertical(ver)
    devpos(t+1,r);devoutvertical(ver)
    devpos(b,l);devout(bot)

    setcolor(savecolor) 
    return NIL

*******************************************************************************
