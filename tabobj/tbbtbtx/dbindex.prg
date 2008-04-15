
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

#include "fileio.ch"
#include "tabobj.ch"

******************************************************************************
//Public interface

//function tabControlIndex(table,ord)     //vezérlő index kiválasztása/lekérdezése
//function tabSuppIndex(table,index)      //ideiglenes indexet ad table-hoz
//function tabDropIndex(table)            //ideiglenes index törlése
//function tabKeyCompose(table,order)     //kulcs az aktuális rekordból
//function tabKeyLength(table,order)      //kulcshossz az aktuális indexből 
 

******************************************************************************
function tabControlIndex(table,ord) //vezérlő index kiválasztása/lekérdezése
local old:=table[TAB_ORDER]
    if( ord!=NIL .and. (ord:=tabGetIndex(table,ord))!=NIL .and. ord!=old )
        tabCommit(table)
        table[TAB_ORDER]:=ord
        tabGoto(table,tabPosition(table))
    end
    return old

 
******************************************************************************
function tabSuppIndex(table,index) //ideiglenes indexet ad table-hoz
local lkcnt:=tabSLock(table)
local res:=lkcnt>0 .and. _SuppIndex(table,index)
    tabSUnLock(table)
    return res

static function _SuppIndex(table,index) //ideiglenes indexet ad table-hoz

local state, ord, ordname, db, key 
local msg, total, n

    tranNotAllowedInTransaction(table,"suppindex",.t.)
 
    tabCommit(table)

    if( tabIsOpen(table)<OPEN_EXCLUSIVE )
        taberrOperation("tabSuppIndex")
        taberrDescription(@"exclusive open requiered")
        tabError(table)
    end
    
    if( (ord:=tabScanIndex(table,index))==NIL )

        //ha korábban is volt ilyen index,
        //akkor csak be kell állítani,
        //olyankor ide nem jön

        state:=tabSave(table)
        tabControlIndex(table,0)
        tabFilter(table,0)
        tabDeleteFieldTable(table)
 
        tabAddIndex(table,index)  //oszlop blockot módosít!
        index[IND_TYPE]:=.t.  //ideiglenes indexet jelölő flag
        ord:=len(table[TAB_INDEX])

      #ifdef UNSORTED_KEYS

        //A kulcsok rendezetlen sorrenben való rakosgatásánál 
        //sokkal hatékonyabb, ha először rendezzük a kulcsokat. 
        //Nagy filéknél (tíz millió rekord felett) óriási a különbség.
        //Ezért az #else (build_bt_index) ágat kell befordítani.
        
        db:=table[TAB_BTREE]
        _db_creord(db,ordname:="<#>") //ideiglenes név

        n:=0
        total:="/"+alltrim(str(tabLastRec(table)))
        //msg:=message(msg,@"Create index:"+str(n)+total)

        tabGotop(table)
        while( !tabEof(table) )

            key:=tabKeyCompose(table,ord) 
            _db_setord(db,ordname) 
            _db_put(db,key)
            
            if( ++n%1103==0 )
                msg:=message(msg,@"Create index:"+str(n)+total)
            end
            tabSkip(table)
        end

        //Ha idáig nem jut el, akkor az új index <#> néven
        //marad benne a filében, azt az open észre fogja venni,
        //és törli a félbemaradt indexet.

        _db_renord(db,ordname,index[IND_NAME]) //végleges név
        _db_addresource(db,arr2bin(tabIndex(table)),1) //frissít

        if( msg!=NIL )
            msg:=message(msg)
        end

      #else
        build_bt_index(table,ord,.t.) //optimized
      #endif
        
        tabSetFieldTable(table)
        tabRestore(table,state)
    end

    tabControlIndex(table,ord) 
    return index


******************************************************************************
function tabDropIndex(table)  //ideiglenes indexek törlése
local lkcnt:=tabSLock(table)
local res:=lkcnt>0 .and. _DropIndex(table)
    tabSUnLock(table)
    return res

static function _DropIndex(table)  //ideiglenes indexek törlése

local index,aindex:=tabIndex(table)
local col,acolumn:=tabColumn(table)
local n,state
local filno,status

    tranNotAllowedInTransaction(table,"dropindex",.t.)

    tabCommit(table)

    if( tabIsOpen(table)<OPEN_EXCLUSIVE )
        taberrOperation("tabDropIndex")
        taberrDescription(@"exclusive open requiered")
        tabError(table)
    end

    tabControlIndex(table,0)
    state:=tabSave(table)
    tabDeleteFieldTable(table)
    
    //először minden indexet törlünk,
    //utána az állandókat visszarakjuk
    
    for n:=1 to len(acolumn)
        col:=acolumn[n]
        col[COL_KEYFLAG]:=.f.
    next
    
    table[TAB_INDEX]:={}

    for n:=1 to len(aindex) 
        index:=aindex[n]

        if( !index[IND_TYPE] )
            tabAddIndex(table,index)
        else
            //az egész indexet szabadlistába tesszük
            _db_delord(table[TAB_BTREE],index[IND_NAME])
        end
    next
    
    _db_addresource(table[TAB_BTREE],arr2bin(tabIndex(table)),1) //frissít
    
    tabRestore(table,state)
    tabSetFieldTable(table)
    return index


******************************************************************************
function tabKeyCompose(table,order) //kulcs az aktuális rekordból

local aindex:=tabIndex(table)
local idxcol:=if(order>0,aindex[order][IND_COL],{})
local col,type,width,dec,n
local segval,key:=x""
 
    for n:=1 to len(idxcol)

        col    := tabGetColumn(table,idxcol[n])
        type   := col[COL_TYPE]
        width  := col[COL_WIDTH]
        dec    := col[COL_DEC]
        segval := eval(col[COL_BLOCK])
        

        if( type=="C" )
            key+=str2bin(segval)

        elseif( type=="X" )
            key+=segval //nem kell transzformálni

        elseif( type=="N" )
            key+=_db_numseg(segval,width,dec) 

        elseif( type=="D" )
            key+=str2bin(dtos(segval)) //nem kell transzformálni
 
        elseif( type=="L" )
            key+=str2bin(if(segval,"T","F"))
        end
    next

    key+=_db_wrbig32(tabPosition(table))+table[TAB_RECPOS]
    return key


******************************************************************************
function tabKeyLength(table,order) //kulcshossz az aktuális indexből

local aindex:=tabIndex(table)
local idxcol:=if(order>0,aindex[order][IND_COL],{})
local keylen:=10
local col,width,n
 
    for n:=1 to len(idxcol)
        col    := tabGetColumn(table,idxcol[n])
        width  := col[COL_WIDTH]
        keylen += width
    next

    return keylen
 
******************************************************************************
