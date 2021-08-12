
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

#include "setcurs.ch"
#include "inkey.ch"
#include "table.ch"

#define MODR_FIELD   1
#define MODR_NAME    2
#define MODR_TYPE    3
#define MODR_VALUE   4
#define MODR_PICT    5
#define MODR_MEMO    6
 
static widthData:=10
static widthName:=10
static widthWind:=60

#define MEMOLENGTH   1024
 
************************************************************************
function tabEditRecord(tab,opt,fld)
 
// opt - "EMST"  Exit,Modify,Store,Type
// fld - {{"FIELD","Megnevezes","PICTURE"},{...},{...},...}

local margin:=int((maxcol()-widthWind)/2)
local col:=tabColumn(tab),value:={},n,m,c,v,dcol
local brw:=brwCreate(3,margin,maxrow()-1,maxcol()-margin)

    brw:flushright:=.f. //szamok balra igazitva

    if( opt==NIL )
        opt:="EMST"
    end
    
    if( fld!=NIL )
        for m:=1 to len(fld)
            if( 0<(n:=ascan(col,{|c|alltrim(c[COL_NAME])==fld[m][1]})) )
                aadd(value,v:={})
                aadd(v,n)
                aadd(v,fld[m][2])
                aadd(v,tipus(col[n]))
                aadd(v,tabEvalColumn(tab,n))

                if( len(fld[m])>=3 )
                    aadd(v,fld[m][3])
                elseif( tabMemoField(tab,col[n]) )
                    aadd(v,"@R "+replicate("X",MEMOLENGTH))
                else
                    //aadd(v,col[n][COL_PICT])
                    //ha hosszu, akkor teljes hossz (2011.09.19)

                    if( replicate("X",32)$col[n][COL_PICT] )
                        aadd(v,"@R "+replicate("X",col[n][COL_WIDTH]))
                    else
                        aadd(v,col[n][COL_PICT])
                    end


                end

                aadd(v,tabMemoField(tab,col[n]))
                
                widthName:=max(widthName,len(fld[m][2]))
            end
        next
    else
        for n:=1 to len(col)
            aadd(value,v:={})
            aadd(v,n)
            aadd(v,col[n][COL_NAME])
            aadd(v,tipus(col[n]))
            aadd(v,tabEvalColumn(tab,n))

            if( tabMemoField(tab,col[n]) )
                aadd(v,"@R "+replicate("X",MEMOLENGTH))
            else
                //aadd(v,col[n][COL_PICT])
                //ha hosszu, akkor teljes hossz (2011.09.19)

                if( replicate("X",32)$col[n][COL_PICT] )
                    aadd(v,"@R "+replicate("X",col[n][COL_WIDTH]))
                else
                    aadd(v,col[n][COL_PICT])
                end

            end

            aadd(v,tabMemoField(tab,col[n]))
 
            widthName:=max(widthName,len(col[n][COL_NAME]))
        next
    end

    widthData:=widthWind-5-(widthName+3)-if("T"$opt,10,0)-if("S"$opt,4,0)

    brwArray(brw,value)

    brwColumn(brw,@"Name",brwABlock(brw,MODR_NAME),widthName)

    if( "T"$opt )
        brwColumn(brw,@"Type",brwABlock(brw,MODR_TYPE),7)
    end

    brwColumn(brw,@"Data",{||formaz(brw)},widthData)
    dcol:=brw:colcount //editalhato oszlop szama

    if( "S"$opt )
        brwColumn(brw,"",{||status(brw,tab)},1)
    end

    brwMenuName(brw,"["+rightName(tabPathname(tab),30)+"]")
    if( "E"$opt )
        brwMenu(brw,@"Quit",@"Quit without saving",{||.f.},"Q")
    end
    if( "M"$opt )
        brwMenu(brw,@"Modify",@"Modify field data",{||edit(brw,dcol),.t.},"M")
    end
    if( "S"$opt )
        brwMenu(brw,@"Save",@"Save modified record to database",{||beir(brw,tab),.f.},"S")
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
    return col[COL_TYPE]+str(col[COL_WIDTH],3)+"."+str(col[COL_DEC],1)


************************************************************************
static function formaz(brw)
local pos:=brwArrayPos(brw)
local col:=brwArray(brw)[pos]
local value:=col[MODR_VALUE]
local pict:=col[MODR_PICT]
local flushright:=.f.

    #ifndef _cl_
    flushright:=brw:flushright  
    #endif

    if( flushright .and. valtype(value)=="N" )
        value:=padl(transform(value,pict),widthData)
    else
        value:=transform(value,pict) 
    end    
    return value


************************************************************************
static function status(brw,tab)
local pos:=brwArrayPos(brw)
local col:=brwArray(brw)[pos]
local value:=col[MODR_VALUE]
local field:=col[MODR_FIELD]
    return if(tabEvalColumn(tab,field)==value,"","*")

************************************************************************
static function beir(brw,tab)
local arr:=brwArray(brw), n
local value,field
    if( tabRLock(tab,busyRecord()) )
        for n:=1 to len(arr)
            field:=brwArray(brw)[n][MODR_FIELD]
            value:=brwArray(brw)[n][MODR_VALUE]
            tabEvalColumn(tab,field,value)
        next
        tabUnlock(tab)
    end
    return NIL


************************************************************************
static function edit(brw,dcol) 

local arr:=brwArray(brw)
local column,pos,pict,key
local saveb,savep
local memoflg,memotxt,scrn,curs

    brw:colPos:=dcol
    brw:refreshCurrent()

    while(.t.)

        keyboard("")
        brw:refreshcurrent()
        brw:forcestable()
   
        pos:=brwArrayPos(brw)
        pict:=arr[pos][MODR_PICT]
        memoflg:=arr[pos][MODR_MEMO]
 
        if( replicate("X",widthData+1)$pict )
            pict:=strtran(pict,"@R","@S"+alltrim(str(widthData)))
        end
         
        column:=brw:getcolumn(dcol) 
            
        saveb:=column:block
        savep:=column:picture

        column:block:={|x|setget(arr,pos,pict,x)} 
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
            if( memoflg )
                scrn:=savescreen(brw:ntop,brw:nleft,brw:nbottom,brw:nright) 
                curs:=setcursor(SC_NORMAL)
                memotxt:=bin2str(rtrim(arr[pos][MODR_VALUE]))
                memotxt:=memoedit(memotxt,brw:ntop,brw:nleft,brw:nbottom,brw:nright)
                if(lastkey()!=K_ESC)
                    if( "X"$arr[pos][MODR_TYPE] )
                        memotxt::=str2bin
                    end
                    memotxt::=rtrim
                    while( memotxt::len>0 .and. memotxt::right(1)::asc<32 )
                        memotxt::=substr(1,len(memotxt)-1)
                        memotxt::=rtrim
                    end
                    arr[pos][MODR_VALUE]:=memotxt
                end
                restscreen(brw:ntop,brw:nleft,brw:nbottom,brw:nright,scrn) 
                setcursor(curs)
            end
            exit
        end
    end
  
    brw:refreshcurrent()
    return key

************************************************************************
static function setget(arr,pos,pict,x)
//A getek stringeket (C) editalnak, binary (X) adatokat nem!
//Ezert, amikor egy memo vagy binary mezo bekerul a getbe editalasra,
//akkor automatikusan stringre konvertalodik (itt info veszhet el).
//Amikor az editalt stringet kivesszuk, vissza kell konvertalni binaryra.

    if( x==NIL )
        x:=arr[pos][MODR_VALUE]
    else
        if( valtype(arr[pos][MODR_VALUE])=="X" )
            x:=str2bin(x) //visszakonvertal
        end
        arr[pos][MODR_VALUE]:=if(len(pict)>MEMOLENGTH,rtrim(x),x)
    end
    return x

************************************************************************
static function rightName(name,length)
    return if(len(name)<=length,name,"..."+right(name,length-3))


************************************************************************
