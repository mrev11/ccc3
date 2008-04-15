
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

#include "table.ch"


************************************************************************
function ujrekord(brw,tab)
    tabAppend(tab)
    modosit(brw,tab)
    return NIL


************************************************************************
function modosit(dbfbrw,tab)
    if( !tabEof(tab) )
        brwKillFocus(dbfbrw)
        tabModRecord(tab)
        brwSetFocus(dbfbrw)
        dbfbrw:refreshAll()
    end
    return NIL


************************************************************************
function lockol(dbfbrw,tab)
    if( tabRlock(tab,busyRecord()) )
        alert(@"Record locked "+alltrim(str(tabPosition(tab))),{@"Unlock"})
        tabUnlock(tab)
    end
    return NIL
 

************************************************************************
function xopen(brw,tab)
local save:=tabSave(tab)
    if( tabOpen(tab,OPEN_EXCLUSIVE,busyFile()) )
        alert(@"File locked",{@"Unlock"})
    end
    tabOpen(tab)
    tabRestore(tab,save)
    return NIL


************************************************************************
function pakkol(brw,tab)
local save:=tabSave(tab)
    if( 2<=alert(@"Pack database?",{@"Cancel",@"Pack"}) .and.;
        tabOpen(tab,OPEN_EXCLUSIVE,busyFile()) )
        tabPack(tab)
    end
    tabOpen(tab)
    tabRestore(tab,save)
    brw:gotop()
    return NIL
 

************************************************************************
function zapol(brw,tab)
local save:=tabSave(tab)
    if( 2<=alert(@"Zap database?",{@"Cancel",@"Zap"}) .and.;
        tabOpen(tab,OPEN_EXCLUSIVE,busyFile()) )
        tabZap(tab)
    end
    tabOpen(tab)
    tabRestore(tab,save)
    brw:gotop()
    return NIL
 

************************************************************************
function torol(brw,tab)
    if( !tabEof(tab) .and.;
        2<=alert(@"Delete record?",{@"Cancel",@"Delete"}) .and.;
        tabRLock(tab,busyRecord()) )

        tabDelete(tab)
        brw:refreshAll()
    end
    return NIL


************************************************************************
function tabModRecord(tab)
    tabEditRecord(tab,"EMTS")
    return NIL


************************************************************************
