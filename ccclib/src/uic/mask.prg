
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

#define MSK_TOP       1
#define MSK_LEFT      2
#define MSK_BOTTOM    3
#define MSK_RIGHT     4
#define MSK_GETLIST   5
#define MSK_BLOAD     6
#define MSK_BREAD     7
#define MSK_BSTORE    8
#define MSK_SCREEN    9
#define MSK_CURSOR   10
#define MSK_CRSPOS   11
#define MSK_SAYLIST  12
#define MSK_SIZE     12

static color:={}


*************************************************************************
function mskColorSay(spec) //push
    if( empty(spec) )
        spec:=ccc_config("MSKCOLOR_SAY")
    end
    if( empty(spec) )
        spec:=NIL
    else
        spec::=strtran(" ","")
    end
    aadd(color,setcolor(spec))

function mskColorGet(spec) //push
    if( empty(spec) )
        spec:=ccc_config("MSKCOLOR_GET")
    end
    if( empty(spec) )
        spec:=NIL
    else
        spec::=strtran(" ","")
    end
    aadd(color,setcolor(spec))

function mskColorRestore()  //pop
    setcolor(color::atail)
    asize(color,max(1,len(color)-1))


*************************************************************************
function mskCreate(t,l,b,r,bl,br,bs)
local msk:=array(MSK_SIZE)

    msk[ MSK_TOP    ]:=t
    msk[ MSK_LEFT   ]:=l
    msk[ MSK_BOTTOM ]:=b
    msk[ MSK_RIGHT  ]:=r
    msk[ MSK_GETLIST]:={}
    msk[ MSK_BLOAD  ]:=bl
    msk[ MSK_BREAD  ]:=br
    msk[ MSK_BSTORE ]:=bs
    msk[ MSK_SCREEN ]:=NIL
    msk[ MSK_CURSOR ]:=NIL
    msk[ MSK_CRSPOS ]:=NIL
    msk[ MSK_SAYLIST]:={}

    return msk


*************************************************************************
function mskSay(msk,r,c,s)
    aadd(msk[MSK_SAYLIST],{r,c,s,setcolor()})


*************************************************************************
function mskGet(msk,r,c,var,name)
local get:=getNew(msk[MSK_TOP]+r,msk[MSK_LEFT]+c,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],get)   
    return get


*************************************************************************
function mskCheck(msk,r,c,var,name)
local get:=checkboxNew(msk[MSK_TOP]+r,msk[MSK_LEFT]+c,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],get)   
    return get
 

*************************************************************************
function mskRadio(msk,r,c,var,name)
local get:=radiobuttonNew(msk[MSK_TOP]+r,msk[MSK_LEFT]+c,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],get)   
    return get


*************************************************************************
function mskList(msk,r,c,var,name)
local get:=listboxNew(msk[MSK_TOP]+r,msk[MSK_LEFT]+c,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],get)   
    return get
 

*************************************************************************
function mskAltButton(msk,r,c,var,name)
local get:=altbuttonNew(msk[MSK_TOP]+r,msk[MSK_LEFT]+c,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],get)   
    return get


*************************************************************************
function mskPushButton(msk,r,c,var,name)
local get:=pushbuttonNew(msk[MSK_TOP]+r,msk[MSK_LEFT]+c,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],get)   
    return get


*************************************************************************
function mskBrowse(msk,t,l,b,r,var,name)
local brw:=getbrwNew(msk[MSK_TOP]+t,msk[MSK_LEFT]+l,msk[MSK_TOP]+b,msk[MSK_LEFT]+r,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],brw)   
    return brw


*************************************************************************
function mskShow(msk)

local t:=msk[ MSK_TOP    ]
local l:=msk[ MSK_LEFT   ]
local b:=msk[ MSK_BOTTOM ]
local r:=msk[ MSK_RIGHT  ]
local slist:=msk[MSK_SAYLIST],n

    msk[ MSK_CURSOR ]:=setcursor(1)
    msk[ MSK_CRSPOS ]:={row(),col()}
    msk[ MSK_SCREEN ]:=savescreen(t,l,b,r)

    @ t,l clear to b,r 
    for n:=1 to len(slist)
        @ t+slist[n][1],l+slist[n][2] say slist[n][3]  color slist[n][4]
    next
    return msk

*************************************************************************
function mskLoop(msk)
    eval(msk[MSK_BLOAD],msk[MSK_GETLIST])
    readexit(.f.)
    while(.t.)
        eval(msk[MSK_BREAD],msk[MSK_GETLIST])
        if( lastkey()==27 .or. eval(msk[MSK_BSTORE],msk[MSK_GETLIST]) )
            exit
        end
    end
    return msk
    

*************************************************************************
function mskHide(msk)
    setcursor(msk[MSK_CURSOR])
    setpos(msk[MSK_CRSPOS][1],msk[MSK_CRSPOS][2])
    restscreen(msk[MSK_TOP],msk[MSK_LEFT],msk[MSK_BOTTOM],msk[MSK_RIGHT],msk[MSK_SCREEN])
    return msk


*************************************************************************
function mskReplace(msk,x,y) //athelyezi a maszkot 

local t:=msk[MSK_TOP]
local l:=msk[MSK_LEFT]
local b:=msk[MSK_BOTTOM]
local r:=msk[MSK_RIGHT]
local glist:=msk[MSK_GETLIST],n
local dx:=x-l
local dy:=y-t
local scr

    if( msk[MSK_SCREEN]!=NIL )
        scr:=savescreen(t,l,b,r)                // ez a kirajzolt maszk
        restscreen(t,l,b,r,msk[MSK_SCREEN])     // visszaallitva az eredeti kepernyo
    end

    msk[MSK_TOP]    := t+=dy
    msk[MSK_LEFT]   := l+=dx
    msk[MSK_BOTTOM] := b+=dy
    msk[MSK_RIGHT]  := r+=dx

    if( msk[MSK_SCREEN]!=NIL )
        msk[MSK_SCREEN]:=savescreen(t,l,b,r)    // mentve a kepernyo az uj helyen
        restscreen(t,l,b,r,scr)                 // kirajzolt maszk az uj helyen
    end
        
    for n:=1 to len(glist)
        glist[n]:col+=dx
        glist[n]:row+=dy   
    next

*************************************************************************
