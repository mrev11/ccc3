
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

#include "recpos.say"


************************************************************************
function modosit(dbfbrw,tab)
    if( !tabEof(tab) )
        brwKillFocus(dbfbrw)
        modrecord(tab)
        brwSetFocus(dbfbrw)
        dbfbrw:refreshAll()
    end


************************************************************************
function ujrekord(brw,tab)
    tabAppend(tab)
    modosit(brw,tab)


************************************************************************
function torol(brw,tab)
    if( !tabEof(tab) .and.;
        2<=alert(@"Delete record?",{@"Cancel",@"Delete"}) .and.;
        tabRLock(tab,busyRecord()) )
        tabDelete(tab)
        brw:refreshAll()
    end


************************************************************************
function goto(dbfbrw,tab)
local recpos
    recpos:=poslist()
    if( !empty(recpos) )
        tabGoto(tab,recpos[1])
    end
    dbfbrw:refreshAll()
 

************************************************************************
function lockcur(dbfbrw,tab)
    if( tabRlock(tab,busyRecord()) )
        dbfbrw:refreshAll()
        prnlklist(tab,{@"Unlock"})
        tabUnlock(tab)
    end
    prnlklist(tab)


************************************************************************
function locktout(dbfbrw,tab,timeout)
    if( tabRlock(tab,timeout) )
        dbfbrw:refreshAll()
        prnlklist(tab,{@"Unlock"})
        tabUnlock(tab)
    end
    prnlklist(tab)


************************************************************************
function lockpos(dbfbrw,tab)
local recpos,n,pos
    recpos:=poslist()
    for n:=1 to len(recpos)
        pos:=recpos[n]
        tabMlock(tab,@pos,busyRecord())
        recpos[n]:=pos
    next
    dbfbrw:refreshAll()
    prnlklist(tab)
 

************************************************************************
function lockmul(dbfbrw,tab)
local recpos,n
    recpos:=poslist()
    tabAlock(tab,recpos,busyRecord())
    dbfbrw:refreshAll()
    prnlklist(tab)


************************************************************************
function unlockpos(dbfbrw,tab)
local recpos,n
    recpos:=poslist()
    for n:=1 to len(recpos)
        tabUnlock(tab,recpos[n],busyRecord())
    next
    prnlklist(tab)


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
 

************************************************************************
function lockfil(brw,tab,timeout)
local save:=tabSave(tab)
    if( timeout==NIL )
        // regi eset
        if( tabOpen(tab,OPEN_EXCLUSIVE,busyFile()) )
            alert(@"File locked",{@"Unlock"})
        end
    else
        // uj eset: timeout
        if( tabOpen(tab,OPEN_EXCLUSIVE,timeout) )
            alert(@"File locked",{@"Unlock"})
        else
            eval(busyFile())
        end
    end
    tabOpen(tab)
    tabRestore(tab,save)


************************************************************************
static function modrecord(tab)
    if( tabIsOpen(tab)>OPEN_READONLY )
        tabEditRecord(tab,"EMTS")
    else
        tabEditRecord(tab,"TM")
    end


************************************************************************
static function poslist()
local poslist:="",recpos,n
    recpos({||},{|g|readmodal(g)},{|getlist|poslist:=g_recpos:varget,.t.})
    recpos:=strtran(poslist," ","")::split
    for n:=1 to len(recpos)
        recpos[n]::=val
    next
    return recpos


************************************************************************
static function prnlklist(tab,alt:={@"Ok"})
local lklist:=tabLocklist(tab)::any2str::strtran(" ","")
    ? "curpos: ",tabPosition(tab), "  locked:", lklist
    alert(@"Locked rekords "+lklist,alt)


************************************************************************
