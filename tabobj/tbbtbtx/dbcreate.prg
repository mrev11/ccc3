
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

#include "tabobj.ch"


******************************************************************************
//Public interface
//
//function tabNew(alias)                //létrehoz egy új table objectet
//function tabDestruct(table)           //megszünteti az objektumot
//function tabObjectList(table)         //a table objectek listája
//function tabCreate(table,userblock)   //a nemlétező dbf-et kreálja

******************************************************************************

static tabobjectList:={}

******************************************************************************
function tabLibName()
    return "DBTABLE"


******************************************************************************
function tabNew(alias) //létrehoz egy új table objectet
local table:=tabNew0(alias)
    aadd(tabobjectList,table)
    return table 

function tabNew0(alias) //létrehoz egy új table objectet (nem teszi listába)
local table:=array(TAB_SIZEOF)

    table[TAB_ALIAS   ] := upper(alltrim(alias))
    table[TAB_FILE    ] := upper(alltrim(alias))
    table[TAB_PATH    ] := ""
    table[TAB_EXT     ] := tabDataExt()
    table[TAB_COLUMN  ] := {}
    table[TAB_INDEX   ] := {}
    table[TAB_ORDER   ] := 0
    table[TAB_FILTER  ] := NIL
    table[TAB_OPEN    ] := OPEN_CLOSED
    table[TAB_RECBUF  ] := NIL
    table[TAB_LOCKLST ] := {}
    table[TAB_LOCKFIL ] := .f.
    table[TAB_POSITION] := 0

    table[TAB_MODIF   ] := .f.
    table[TAB_MODIFKEY] := .f.
    table[TAB_MODIFAPP] := .f.
    table[TAB_EOF     ] := .t.
    table[TAB_FOUND   ] := .f.
    table[TAB_SLOCKCNT] := 0
    table[TAB_SLOCKHND] := -1

    return table 


******************************************************************************
function tabDestruct(table) //megszünteti az objektumot
local n, tlist:={}
    tabClose(table)
    asize(table,0)
    for n:=1 to len(tabobjectList)
        if( !empty(tabobjectList[n]) )
            aadd(tlist,tabobjectList[n])
        end
    next
    tabobjectList:=tlist
    return NIL


******************************************************************************
function tabObjectList(table) //a table objectek listája
   return tabobjectList


******************************************************************************
function tabCreate(table,userblock) //kreálja a nemlétező fájlt
local lkcnt:=tabSLock(table)
local res:=lkcnt>0 .and. create(table,userblock)
    tabSUnlock(table)
    return res

static function create(table,userblock) //kreálja a nemlétező fájlt

local n,rcol,rind,db

    if( !file(lower(tabPathName(table))) ) 

        db:=_db_create( lower(tabPathName(table)), btbtx_pagesize() )  
        
        if( db==NIL  )
            taberrOperation("tabCreate")
            taberrDescription(@"create failed")
            taberrUserBlock(userblock)
            return tabError(table)
        end
        
        rcol:=aclone(tabColumn(table))
        for n:=1 to len(rcol)
            asize(rcol[n],4)
        next

        rind:=aclone(tabIndex(table))
        for n:=1 to len(rind)
            asize(rind[n],3)
        next
        
        _db_addresource(db,arr2bin(rcol),0) //fix:pgno=1,indx=0
        _db_addresource(db,arr2bin(rind),1) //fix:pgno=1,indx=1


        _db_creord(db,"recno")

        for n:=1 to len(tabIndex(table))
            _db_creord(db,tabIndex(table)[n][IND_NAME])
        next

        if( tabMemoCount(table)>0 )
            if( !memoCreate(lower(tabMemoName(table))) )
                taberrOperation("tabCreate")
                taberrDescription(@"failed creating memo file")
                taberrFilename(lower(tabMemoName(table)))
                taberrUserblock(userblock)
                return tabError(table)
            end
        end
 
        //vissza kell zárni
        _db_close(db)

        tabWriteChangeLogCreate(table)         
    end

    return .t.


******************************************************************************

