
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

//TARTALOM  : browse függvények
//STATUS    : közös, ifdef
//
//
//function tabBrowse(table,t,l,b,r,def) //menüző browse
//function tabSBrowse(table)            //teszt browse (seek után hasznos)
//function tabTBrowse(table)            //teszt browse az összes table objectre


#include "tabobj.ch"

******************************************************************************
static function skipBrowse(table,stp) //skip browse-okhoz

local n
    if(table[TAB_MODIF] .and. stp!=0)
        // TAB_MODIF vizsgálata nem hagyható ki,
        // mert a belső használatú tabGetNext(),
        // tabGetPrev() a gyorsaság érdekében már
        // nem végez commit-ot.
        tabCommit(table)
    end
    if( stp>0 )
        if( (n:=tabGetNext(table,stp))<stp )
            tabGoBottom(table)
        end
        return n 
    elseif( stp<0 )
        if( (n:=-tabGetPrev(table,-stp))>stp )
            tabGoTop(table)
        end
        return n
    end   
    return 0


******************************************************************************
function tabBrowse(table,top,left,bottom,right,def) //menüző browse

local browse:=brwCreate(top,left,bottom,right)
local n, col

    browse:skipBlock:={|n|skipBrowse(table,n)}
    browse:goTopBlock:={||tabGoTop(table)}
    browse:goBottomBlock:={||tabGoBottom(table)}
    browse:PercentBlock:={|p|tabPercent(table,p)}

    if(def==.t.)
        for n:=1 to len(table[TAB_COLUMN])
            col:=table[TAB_COLUMN][n]
            brwColumn(browse,col[COL_NAME],col[COL_BLOCK],col[COL_PICT])
        next
    end
    return browse
   

******************************************************************************
function tabSBrowse(table) //teszt browse (seek után hasznos)

local browse, posColumn
local crs:=setcursor(0)
local state:=tabSave(table)
local ord:=table[TAB_ORDER]
local index:=if(ord>0,table[TAB_INDEX][ord][IND_NAME],"NATURAL")
local ctrl:=@"Controlling index: "+padr(index,8)
local position:=@"  Position:"+str(tabPosition(table),5)
local found:=@"  Found:"+if(tabFound(table),"T","F")

    browse:=tabBrowse(table,0,0,maxrow(),maxcol(),.t.)
   
    posColumn:=TBColumnNew("",{||str(tabPosition(table),5)})
    browse:insColumn(1,posColumn)
    browse:freeze:=1
    
    brwCaption(browse, @"Table: "+tabAlias(table))
    brwMenuName(browse, @"Database file: "+tabPathName(table) )
    brwMenu(browse,"",ctrl+position+found,{||.t.})
    brwShow(browse)
    brwLoop(browse)
    brwHide(browse)
    tabRestore(table,state)
    setcursor(crs)
    return NIL


******************************************************************************
function tabTBrowse(table) //teszt browse az összes table objectre

local objectlist:=tabObjectList()
local browse
local crs:=setcursor(0)
local n,tab:={},alias,ord,index,mode,locks
local sbrwBlock:={|t|t:=objectList[brwArrayPos(browse)],;
                     if(tabIsopen(t)>0,tabSBrowse(t),NIL),.t.}

    for n:=1 to len(objectList)
        table:=objectList[n]
        alias:=tabAlias(table)
        ord:=tabControlIndex(table)
        index:=if(ord>0,table[TAB_INDEX][ord][IND_NAME],"")
        mode:={@"Closed",@"Readonly",@"Shared",@"Exclusive"}[table[TAB_OPEN]+1]
        locks:=len(tabLocklist(table))
        aadd(tab,{alias,mode,index,locks})
    next

    if( len(tab)>0 )

        browse:=brwCreate(8,10,maxrow()-2,maxcol()-10)
        brwArray(browse,tab)
        brwColumn(browse,@"TableName ",brwABlock(browse,1),10)
        brwColumn(browse,@"OpenMode  ",brwABlock(browse,2),10)
        brwColumn(browse,@"ControlInd",brwABlock(browse,3),10)
        brwColumn(browse,@"LockNumber",brwABlock(browse,4),10)
   
        brwMenuName(browse,@"[TableObjects of Application]")
        brwMenu(browse,@"Browse",@"Browse current database table",sbrwBlock,"B")
        brwShow(browse)
        brwLoop(browse)
        brwHide(browse)
    else
        alert(@"tabTBrowse: no table object")
    end
        
    setcursor(crs)
    return NIL


******************************************************************************
