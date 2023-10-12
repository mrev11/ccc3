
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

//TARTALOM  : tabla pack/zap
//STATUS    : kozos
//
//function tabPack(table)   adatfile packolasa
//function tabZap(table)    adatfile zapolasa

#include "error.ch"
#include "tabobj.ch"


#ifdef NOTDEFINED

//Az itteni pack arra epul, hogy tabUpgrade minden rekordot mezonkent 
//atir egy uj, ideiglenes filebe, mikozben kihagyja a torolt rekordokat. 
//Az algoritmus lassu, mert nem hasznalja a platformfuggo optimalizalasi 
//lehetosegeket (viszont egyseges).

******************************************************************************
function tabPack(table)

local result
local save:=tabSave(table)

    tranNotAllowedInTransaction(table,"pack")
 
    tabCommit(table)

    if( tabIsOpen(table)!=OPEN_EXCLUSIVE )
        taberrOperation("tabPack")
        taberrDescription(@"exclusive open required")
        tabError(table) 
    end
    
    if( tabSlock(table)>0 )
        tabClose(table)
        result:=tabUpgrade(table)
        tabOpen(table,OPEN_EXCLUSIVE)
        tabRestore(table,save)
        tabGotop(table)
        tabSunlock(table)
    end
    return result==.t.

#endif


******************************************************************************
function tabPack(table)

local result
local save:=tabSave(table)
local logged

    tranNotAllowedInTransaction(table,"pack")
 
    tabCommit(table)

    if( tabIsOpen(table)!=OPEN_EXCLUSIVE )
        taberrOperation("tabPack")
        taberrDescription(@"exclusive open required")
        tabError(table) 
    end
    
    if( tabSlock(table)>0 )
        logged:=table[TAB_LOGGED]
        table[TAB_LOGGED]:=.f.
        tabClose(table)
        result:=tabCopybt(table)
        tabOpen(table,OPEN_EXCLUSIVE)
        tabRestore(table,save)
        tabGotop(table)
        table[TAB_LOGGED]:=logged
        tabWriteChangeLogPack(table)         
        tabSunlock(table)
    end
    return result==.t.
 

******************************************************************************
function tabZap(table)  //fajl kiuritese

local result
local save:=tabSave(table)
local logged

local cryptflg
local cryptflg1
local db,pgno


    tranNotAllowedInTransaction(table,"zap")
 
    if( tabIsOpen(table)!=OPEN_EXCLUSIVE )
        taberrOperation("tabZap")
        taberrDescription(@"exclusive open required")
        tabError(table)
    end
    
    if( tabSlock(table)>0 )
        logged:=table[TAB_LOGGED]
        table[TAB_LOGGED]:=.f.
        cryptflg:=_db_cryptflg(table[TAB_BTREE])    // titkositva van-e az eredeti
        tabClose(table)
        result:=tabDelTable(table) 

        tabCreate(table)
        tabOpen(table,OPEN_EXCLUSIVE)
        cryptflg1:=_db_cryptflg(table[TAB_BTREE])   // titkositva van-e az uj
        if( cryptflg!=cryptflg1 )
            db:=table[TAB_BTREE]
            pgno:=1
            while( _db_pgrewrite(db,pgno,cryptflg) )
                pgno++
            end
            _db_cryptflg(db,cryptflg)
        end

        tabRestore(table,save)
        tabGotop(table)
        table[TAB_LOGGED]:=logged
        tabWriteChangeLogZap(table)         
        tabSunlock(table)
    end
    return result


******************************************************************************
