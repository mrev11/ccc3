
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


#ifdef _DBFNTX_
#define COPYDBF
#define OPTIMIZED
#endif

#ifdef _DBFCTX_
#define COPYDBF
#define OPTIMIZED
#endif

#ifdef _DATIDX_
#define COPYDAT
#define OPTIMIZED
#endif

#ifdef _BTBTX_
#define COPYBT
#define OPTIMIZED
#endif
 

#ifndef OPTIMIZED

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


#ifdef COPYBT
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
 
#endif
 

#ifdef COPYDBF   
******************************************************************************
function tabPack(table)

local result
local save:=tabSave(table)
local tmp:=tabPath(table)+TMPCHR+tabFile(table)
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

        copydbf(lower(tabPathName(table)),lower(tmp+tabDataExt())) //pack dbf
        if( tabMemoCount(table)>0 )
            copy file (lower(tabMemoName(table))) to (lower(tmp+tabMemoExt())) //memo
        end

        if( !tabBackup(table) )
            taberrOperation("tabPack")
            taberrDescription(@"failed saving old file")
            tabError(table) 
        end

        if( !tabDelTable(table) )
            taberrOperation("tabPack")
            taberrDescription(@"failed deleting old file")
            tabError(table) 
        end

        frename(lower(tmp+tabDataExt()),lower(tabPathName(table)))
        if( tabMemoCount(table)>0 )
            frename(lower(tmp+tabMemoExt()),lower(tabMemoName(table)))
        end

        tabOpen(table,OPEN_EXCLUSIVE)  //ujraindexel
        tabRestore(table,save)
        tabGotop(table)
        table[TAB_LOGGED]:=logged
        tabWriteChangeLogPack(table)         
        tabSunlock(table)
    end
    return result==.t.

#endif


#ifdef COPYDAT
******************************************************************************
function tabPack(table)

local result
local save:=tabSave(table)
local tmp:=tabPath(table)+TMPCHR+tabFile(table)
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
 
        tabCopydat(table,TMPCHR+tabFile(table)) //pack dat
        tabClose(table)

        if( tabMemoCount(table)>0 )
            copy file (lower(tabMemoName(table))) to (lower(tmp+tabMemoExt())) //memo
        end

        if( !tabBackup(table) )
            taberrOperation("tabPack")
            taberrDescription(@"failed saving old file")
            tabError(table) 
        end

        if( !tabDelTable(table) )
            taberrOperation("tabPack")
            taberrDescription(@"failed deleting old file")
            tabError(table) 
        end

        frename(lower(tmp+tabDataExt()),lower(tabPathName(table)))
        if( tabMemoCount(table)>0 )
            frename(lower(tmp+tabMemoExt()),lower(tabMemoName(table)))
        end

        tabOpen(table,OPEN_EXCLUSIVE)  //ujraindexel
        tabRestore(table,save)
        tabGotop(table)
        table[TAB_LOGGED]:=logged
        tabWriteChangeLogPack(table)         
        tabSunlock(table)
    end
    return result==.t.

#endif


******************************************************************************
function tabZap(table)  //fajl kiuritese

local result
local save:=tabSave(table)
local logged

    tranNotAllowedInTransaction(table,"zap")
 
    if( tabIsOpen(table)!=OPEN_EXCLUSIVE )
        taberrOperation("tabZap")
        taberrDescription(@"exclusive open required")
        tabError(table)
    end
    
    if( tabSlock(table)>0 )
        logged:=table[TAB_LOGGED]
        table[TAB_LOGGED]:=.f.
        tabClose(table)
        result:=tabDelTable(table) 
        tabCreate(table)
        tabOpen(table,OPEN_EXCLUSIVE)
        tabRestore(table,save)
        tabGotop(table)
        table[TAB_LOGGED]:=logged
        tabWriteChangeLogZap(table)         
        tabSunlock(table)
    end
    return result


******************************************************************************
