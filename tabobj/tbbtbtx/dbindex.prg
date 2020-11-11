
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

//function tabControlIndex(table,ord)     //vezerlo index kivalasztasa/lekerdezese
//function tabSuppIndex(table,index)      //ideiglenes indexet ad table-hoz
//function tabDropIndex(table)            //ideiglenes index torlese
//function tabKeyCompose(table,order)     //kulcs az aktualis rekordbol
//function tabKeyLength(table,order)      //kulcshossz az aktualis indexbol 
 

******************************************************************************
function tabControlIndex(table,ord) //vezerlo index kivalasztasa/lekerdezese
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
        taberrDescription(@"exclusive open required")
        tabError(table)
    end
    
    if( (ord:=tabScanIndex(table,index))==NIL )

        //ha korabban is volt ilyen index,
        //akkor csak be kell allitani,
        //olyankor ide nem jon

        state:=tabSave(table)
        tabControlIndex(table,0)
        tabFilter(table,0)
        tabDeleteFieldTable(table)
 
        tabAddIndex(table,index)  //oszlop blockot modosit!
        index[IND_TYPE]:=.t.  //ideiglenes indexet jelolo flag
        ord:=len(table[TAB_INDEX])

      #ifdef UNSORTED_KEYS

        //A kulcsok rendezetlen sorrenben valo rakosgatasanal 
        //sokkal hatekonyabb, ha eloszor rendezzuk a kulcsokat. 
        //Nagy fileknel (tiz millio rekord felett) oriasi a kulonbseg.
        //Ezert az #else (build_bt_index) agat kell beforditani.
        
        db:=table[TAB_BTREE]
        _db_creord(db,ordname:="<#>") //ideiglenes nev

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

        //Ha idaig nem jut el, akkor az uj index <#> neven
        //marad benne a fileben, azt az open eszre fogja venni,
        //es torli a felbemaradt indexet.

        _db_renord(db,ordname,index[IND_NAME]) //vegleges nev
        _db_addresource(db,arr2bin(tabIndex(table)),1) //frissit

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
function tabDropIndex(table)  //ideiglenes indexek torlese
local lkcnt:=tabSLock(table)
local res:=lkcnt>0 .and. _DropIndex(table)
    tabSUnLock(table)
    return res

static function _DropIndex(table)  //ideiglenes indexek torlese

local index,aindex:=tabIndex(table)
local col,acolumn:=tabColumn(table)
local n,state
local filno,status

    tranNotAllowedInTransaction(table,"dropindex",.t.)

    tabCommit(table)

    if( tabIsOpen(table)<OPEN_EXCLUSIVE )
        taberrOperation("tabDropIndex")
        taberrDescription(@"exclusive open required")
        tabError(table)
    end

    tabControlIndex(table,0)
    state:=tabSave(table)
    tabDeleteFieldTable(table)
    
    //eloszor minden indexet torlunk,
    //utana az allandokat visszarakjuk
    
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
            //az egesz indexet szabadlistaba tesszuk
            _db_delord(table[TAB_BTREE],index[IND_NAME])
        end
    next
    
    _db_addresource(table[TAB_BTREE],arr2bin(tabIndex(table)),1) //frissit
    
    tabRestore(table,state)
    tabSetFieldTable(table)
    return index


******************************************************************************
function tabKeyCompose(table,order) //kulcs az aktualis rekordbol

local aindex:=tabIndex(table)
local idxcol:=if(order>0,aindex[order][IND_COL],{})
local col,type,offs,width,dec,n
local segval,key:=x""

    for n:=1 to len(idxcol)

        col    := tabGetColumn(table,idxcol[n])
        type   := col[COL_TYPE]
        offs   := col[COL_OFFS]
        width  := col[COL_WIDTH]
        dec    := col[COL_DEC]

        //2013.09.26 atirva, sajnos ez kivetel:
        //Az olvasas az oszlopblokk megkerulesevel,
        //kozvetlenul a rekordbufferbol tortenik.
        //hogy elkeruljuk az odavissza tipuskonverziot.
        segval := xvgetchar(table[TAB_RECBUF],offs,width)

        if( type=="N" )
            segval:=_db_numseg(val(segval),width,dec)
        end
        key+=segval
    next

    key+=_db_wrbig32(tabPosition(table))+table[TAB_RECPOS]
    return key


******************************************************************************
function tabKeyLength(table,order) //kulcshossz az aktualis indexbol

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
