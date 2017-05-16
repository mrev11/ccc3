
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

#define MSK_SIZE     10

static color:={}


*************************************************************************
function mskColorSay(spec) //push
    if( empty(spec) )
        spec:=ccc_config("MSKCOLOR_SAY")
    end
    if( empty(spec) )
        spec:=NIL
    end
    aadd(color,setcolor(spec))

function mskColorGet(spec) //push
    if( empty(spec) )
        spec:=ccc_config("MSKCOLOR_GET")
    end
    if( empty(spec) )
        spec:=NIL
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
    msk[ MSK_SCREEN ]:=savescreen(t,l,b,r)
    msk[ MSK_CURSOR ]:=setcursor(1)

    @ t,l clear to b,r
    return msk


*************************************************************************
function mskSay(msk,r,c,s)
    devpos(msk[MSK_TOP]+r,msk[MSK_LEFT]+c)
    devout(s)
    return NIL


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
function mskShow(msk)
    eval(msk[MSK_BLOAD],msk[MSK_GETLIST])
    readexit(.f.)
    return msk


*************************************************************************
function mskLoop(msk)
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
    restscreen(msk[MSK_TOP],msk[MSK_LEFT],msk[MSK_BOTTOM],msk[MSK_RIGHT],msk[MSK_SCREEN])
    return msk


*************************************************************************
