
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

//1999.02.16
//az eredetileg táblaobjektumokhoz készült kód
//átalakítva dbaseiiiClass osztályhoz
//member függvényként (editrecord) is hívható

#include "inkey.ch"
#include "dbstruct.ch"

#define MODR_FIELD   1
#define MODR_NAME    2
#define MODR_TYPE    3
#define MODR_VALUE   4
#define MODR_PICT    5

static widthData:=10
static widthName:=10
static widthWind:=60


************************************************************************
function dbEditRecord(db,opt,fld)

// opt - "EMST"  Exit,Modify,Store,Type
// fld - {{"FIELD","Megnevezés","PICTURE"},{...},{...},...}

local margin:=int((maxcol()-widthWind)/2)
local col:=db:dbstruct,value:={},n,m,c,v,dcol
local brw:=brwCreate(3,margin,maxrow()-1,maxcol()-margin)

    brw:flushright:=.f. //számok balra igazítva  
 
    if( opt==NIL )
        opt:="EMST"
    end
    
    if( fld!=NIL )
        for m:=1 to len(fld)
            if( 0<(n:=ascan(col,{|c|alltrim(c[DBS_NAME])==fld[m][1]})) )
                aadd(value,v:={})
                aadd(v,n)
                aadd(v,fld[m][2])
                aadd(v,tipus(col[n]))
                aadd(v,eval(db:fldblk[n]))

                if( len(fld[m])>=3 )
                    aadd(v,fld[m][3])
                else
                    aadd(v,defpict(col[n]))
                end
                
                widthName:=max(widthName,len(fld[m][2]))
            end
        next
    else
        for n:=1 to len(col)
            aadd(value,v:={})
            aadd(v,n)
            aadd(v,col[n][DBS_NAME])
            aadd(v,tipus(col[n]))
            aadd(v,eval(db:fldblk[n]))
            aadd(v,defpict(col[n]))

            widthName:=max(widthName,len(col[n][DBS_NAME]))
        next
    end

    widthData:=widthWind-5-(widthName+3)-if("T"$opt,10,0)-if("S"$opt,4,0)

    brwArray(brw,value)

    brwColumn(brw,"Name",brwABlock(brw,MODR_NAME),widthName)

    if( "T"$opt )
        brwColumn(brw,"Type",brwABlock(brw,MODR_TYPE),7)
    end

    brwColumn(brw,"Data",{||formaz(brw)},widthData)
    dcol:=brw:colcount //editálható oszlop száma
 
    if( "S"$opt )
        brwColumn(brw,"",{||status(brw,db)},1)
    end

    brwMenuName(brw,"["+rightName(db:fspec,30)+"]")
    if( "E"$opt )
        brwMenu(brw,"Quit","Quit without saving",{||.f.},"Q")
    end
    if( "M"$opt )
        brwMenu(brw,"Modify","Modify field data",{||edit(brw,dcol),.t.},"M")
    end
    if( "S"$opt )
        brwMenu(brw,"Save","Save modification to database",{||beir(brw,db),.f.},"S")
    end
    if( opt=="" )
        brwMenu(brw,"","",{||.f.})
    end

    brwSetFocus(brw)
    brwShow(brw)
    brwLoop(brw)
    brwHide(brw)
    return NIL


************************************************************************
static function tipus(col)
    return col[DBS_TYPE]+str(col[DBS_LEN],3)+"."+str(col[DBS_DEC],1)


************************************************************************
static function formaz(brw)
local pos:=brwArrayPos(brw)
local col:=brwArray(brw)[pos]
local value:=col[MODR_VALUE]
local pict:=col[MODR_PICT]

    if( brw:flushright .and. valtype(value)=="N" )
        value:=padl(transform(value,pict),widthData)
    else
        value:=transform(value,pict) 
    end    
 
    return value
 

************************************************************************
static function status(brw,db)
local pos:=brwArrayPos(brw)
local col:=brwArray(brw)[pos]
local value:=col[MODR_VALUE]
local field:=col[MODR_FIELD]
    return if(eval(db:fldblk[field])==value,"","*")


************************************************************************
static function beir(brw,db)
local arr:=brwArray(brw), n
local value,field
    for n:=1 to len(arr)
        field:=brwArray(brw)[n][MODR_FIELD]
        value:=brwArray(brw)[n][MODR_VALUE]
        eval(db:fldblk[field],value) //readonly
    next
    return NIL

//Ez nincs kidolgozva:
//egyrészt a dbaseiii osztály readonly,
//másrészt ki van véve a recordlock,
//ezért a függvény a jelenlegi formájában hatástalan.

************************************************************************
static function edit(brw,dcol) 

local arr:=brwArray(brw)
local column,pos,pict,key
local saveb,savep
 
    brw:colPos:=dcol
    brw:refreshCurrent()

    while(.t.)

        keyboard("")
        brw:refreshcurrent()
        brw:forcestable()
   
        pos:=brwArrayPos(brw)
        pict:=arr[pos][MODR_PICT]

        if( replicate("X",widthData+1)$pict )
            pict:=strtran(pict,"@R","@S"+alltrim(str(widthData)))
        end
       
        column:=brw:getcolumn(dcol) 
            
        saveb:=column:block
        savep:=column:picture

        column:block:={|x|if(x==NIL,arr[pos][MODR_VALUE],arr[pos][MODR_VALUE]:=x)} 
        column:picture:=pict

        key:=brwEditCell(brw,dcol)

        column:block:=saveb
        column:picture:=savep
 
        if( key==K_ESC )
            exit
        elseif( key==K_UP )
            brw:up()
        elseif( key==K_DOWN )
            brw:down()
        elseif( key==K_ENTER )
            exit
        end
    end
  
    brw:refreshcurrent()
    return key


************************************************************************
static function rightName(name,length)
    return if(len(name)<=length,name,"..."+right(name,length-3))


************************************************************************
static function defpict(col)

local type:=col[DBS_TYPE]
local width:=col[DBS_LEN]
local dec:=col[DBS_DEC]
local pict

    if( type=="C" )
        pict:="@R "+replicate("X",width)

    elseif( type=="D" )
        pict:="D"

    elseif( type=="L" )
        pict:="@! L"

    elseif( type=="N" )
        pict:=replicate("9",width)
        if( dec>0 )
            pict+="."+replicate("9",dec)
            pict:=right(pict,width)
            pict:="@R "+pict
        end
    end
    
    return pict


************************************************************************

