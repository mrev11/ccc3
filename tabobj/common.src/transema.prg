
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
#include "table.ch"


static semaphor:=semafd()

static counter:={0, 0, 0}

static deftime:={5000, 20000, 90000}  // default ertekek (millis)
//               RLOCK XOPEN  MANUAL
//
// SEMA_RLOCK   ha tranEnforced=.t., akkor tranBegin automatikusan bekapcsolja
// SEMA_XOPEN   ha tranEnforced=.t., akkor tabOpen(OPEN_EXCLUSIVE) bekapcsolja
// SEMA_MANUAL  a program barmikor bekapcsolhatja


******************************************************************************************
function tranEnforced(modespec)
static mode:=.f.
local modeprev:=mode
    if( modespec!=NIL )
        mode:=modespec
    end   
    return modeprev    // .t.=bekapcs, .f.=kikapcs


******************************************************************************************
function tranSemaOn(level,timeout,share:=.f.)

// timeout      (millis)
//
// share        .f. = readlock
// share        .t. = writelock
//
// level        1 = tranBegin()
// level        2 = tabOpen(OPEN_EXCLUSIVE)
// level        3 = manual

local offset

    if( counter[level]==0 )
        offset:=(level-1)*2
        fwaitlock(semaphor,offset+1,1,.t.)     // write
        fwaitlock(semaphor,offset+0,1,share)   // read/write
        funlock  (semaphor,offset+1,1)
        
        if( timeout==NIL )
            timeout:=deftime[level]
            trantimer_start(level,timeout)
        elseif( timeout>0 )
            trantimer_start(level,timeout)
        else
            // korlatlan
        end
    end

    return ++counter[level]


******************************************************************************************
function tranSemaOff(level)

    if( counter[level]>0 )
        --counter[level]
        if( counter[level]==0 )
            funlock(semaphor,(level-1)*2,1)
            trantimer_delete(level)
        end
    end

    return counter[level]

******************************************************************************************
static function semafd()
local sema,fd,e 
    sema:=".lock_transema"
    fd:=fopen(sema,FO_CREATE+FO_NOLOCK+FO_READWRITE)
    if( fd<0 )
        e:=fnferrorNew()
        e:operation:="tabLockCount"
        e:description:=@".lock_transema open failed"
        e:filename:=sema
        e:oscode:=ferror()
        break(e)
    end
    return fd // fd vagy NIL


******************************************************************************************

