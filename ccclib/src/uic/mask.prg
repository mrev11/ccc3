
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
#define MSK_COLOR    13
#define MSK_SIZE     13

static color:={}
static mask:={}

*************************************************************************
static function mskPush(msk)
    aadd(mask,msk)

static function mskPop(msk)
    asize(mask,len(mask)-1)

function mskActive()
    return atail(mask)

*************************************************************************
function mskColorSay() //push
local spec
    if( !empty(mask) )
        spec:=mask::atail[MSK_COLOR]
    end
    aadd(color,setcolor(spec))


function mskColorGet() //push
    aadd(color,setcolor(ccc_colortheme("MSKCOLOR_GET")))


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
    msk[ MSK_COLOR  ]:=NIL

    return msk


*************************************************************************
function mskSay(msk,r,c,s)
    aadd(msk[MSK_SAYLIST],{r,c,s,setcolor()})


*************************************************************************
function mskGet(msk,r,c,var,name)
local get:=getNew(msk[MSK_TOP]+r,msk[MSK_LEFT]+c,{|x|if(x==NIL,var,var:=x)},name)
    get:picture:=replicate("X",len(get:varget))
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
function mskTextArea(msk,t,l,b,r,var,name)
local area:=textareaNew(msk[MSK_TOP]+t,msk[MSK_LEFT]+l,msk[MSK_TOP]+b,msk[MSK_LEFT]+r,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],area)
    return area


*************************************************************************
function mskTextLabel(msk,t,l,var,name)
local label:=textlabelNew(msk[MSK_TOP]+t,msk[MSK_LEFT]+l,{|x|if(x==NIL,var,var:=x)},name)
    aadd(msk[MSK_GETLIST],label)
    return label


*************************************************************************
function mskShow(msk)

local t:=msk[ MSK_TOP    ]
local l:=msk[ MSK_LEFT   ]
local b:=msk[ MSK_BOTTOM ]
local r:=msk[ MSK_RIGHT  ]
local slist:=msk[MSK_SAYLIST],n
local mskcolor:=msk[MSK_COLOR]

    if( msk[MSK_SCREEN]==NIL )
        msk[ MSK_CURSOR ]:=setcursor(1)
        msk[ MSK_CRSPOS ]:={row(),col()}
        msk[ MSK_SCREEN ]:=savescreen(t,l,b,r)

        if( mskcolor!=NIL )
            for n:=1 to len(msk[MSK_GETLIST])
                if( msk[MSK_GETLIST][n]::getclassid==textlabelClass() )
                    msk[MSK_GETLIST][n]:colorspec:=mskcolor
                end
            next
        end

        @ t,l clear to b,r
        for n:=1 to len(slist)
            @ t+slist[n][1],l+slist[n][2] say slist[n][3]  color mskcolor|slist[n][4]
        next
    end

    return msk


*************************************************************************
function mskLoop(msk)
local level
    for level:=len(mask) to 0 step -1
        msk[MSK_COLOR]:=ccc_colortheme("MSKCOLOR_SAY"+level::str::alltrim)
        if( msk[MSK_COLOR]!=NIL )
            exit
        end
    next
    if( msk[MSK_COLOR]==NIL  )
        msk[MSK_COLOR]:=ccc_colortheme("MSKCOLOR_SAY")
    end
    dispbegin()
    mskPush(msk)
    mskShow(msk)
    eval(msk[MSK_BLOAD],msk[MSK_GETLIST])
    dispend()
    readexit(.f.)
    while(.t.)
        eval(msk[MSK_BREAD],msk[MSK_GETLIST])
        if( lastkey()==27 .or. eval(msk[MSK_BSTORE],msk[MSK_GETLIST]) )
            exit
        end
    end
    mskHide(msk)
    mskPop()
    return msk


*************************************************************************
function mskHide(msk)
    if( msk[MSK_SCREEN]!=NIL )
        setcursor(msk[MSK_CURSOR])
        setpos(msk[MSK_CRSPOS][1],msk[MSK_CRSPOS][2])
        restscreen(msk[MSK_TOP],msk[MSK_LEFT],msk[MSK_BOTTOM],msk[MSK_RIGHT],msk[MSK_SCREEN])
        msk[MSK_SCREEN]:=NIL
    end
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
function mskMove(msk,key)

local x:=msk[MSK_LEFT]
local y:=msk[MSK_TOP]
local b:=msk[MSK_BOTTOM]
local r:=msk[MSK_RIGHT]
local getlist:=msk[MSK_GETLIST]
local row:=row()
local col:=col()

    if( key==K_SH_UP .and. y>0 )
        mskReplace(msk,x,y-1)
        row--
    elseif( key==K_SH_DOWN .and. b<maxrow())
        mskReplace(msk,x,y+1)
        row++
    elseif( key==K_SH_LEFT .and. x>0 )
        mskReplace(msk,x-1,y)
        col--
    elseif( key==K_SH_RIGHT .and. r<maxcol() )
        mskReplace(msk,x+1,y)
        col++
    end
    aeval(getlist,{|g|g:display})
    setpos(row,col)


*************************************************************************
function mskTop(msk)
    return msk[MSK_TOP]

function mskLeft(msk)
    return msk[MSK_LEFT]

function mskBottom(msk)
    return msk[MSK_BOTTOM]

function mskRight(msk)
    return msk[MSK_RIGHT]

function mskWidth(msk)
    return msk[MSK_RIGHT]-msk[MSK_LEFT]+1

function mskHeight(msk)
    return msk[MSK_BOTTOM]-msk[MSK_TOP]+1



*************************************************************************
function mskAdjustPosition(msk,x,y)

local top:=msk[1]
local lef:=msk[2]
local bot:=msk[3]
local rig:=msk[4]

    if(  bot>maxrow() .or. rig>maxcol() )
        settermsize(1+max(bot,maxrow()),1+max(rig,maxcol()))
    end

    if( y==NIL .and. (maxrow()-(bot-top))>=6 )
        if( top<3  )
            // ha y nincs megadva
            // es a maszk kicsi a terminalhoz kepest
            // es a maszk a terminal szelen van
            // akkor beljebb tolja
            y:=40
        end
        if( maxrow()-bot<3  )
            y:=60
        end
    end
    if( x==NIL .and. (maxcol()-(rig-lef))>=6  )
        if( lef<3 )
            x:=40
        end
        if( maxcol()-rig<3 )
            x:=60
        end
    end

    if( !x==NIL .or. y!=NIL )
        if( y==NIL )
            y:=top // top
        else
            y::=max(0)
            y::=min(100)
            y:=int((maxrow()-(bot-top))*y/100)
        end
        if( x==NIL )
            x:=lef // left
        else
            x::=max(0)
            x::=min(100)
            x:=int((maxcol()-(rig-lef))*x/100)
        end
        mskReplace(msk,x,y)
    end
    return msk


*************************************************************************
