
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

//TARTALOM  : egyszerű szemafor protokol
//STATUS    : közös utility


#include "fileio.ch"

// egyszerű szemafor protokoll
//
// hnd:=sema_open(sname,mode)
// sema_close(hnd)
//
// mode értéke lehet FO_EXCLUSIVE (default), vagy FO_SHARED
//
// ezek közönséges file open/close műveletek,
// a filék a semaphor-ban jönnek létre (automatikusan),
// hiba: az exclusive szemafor lockok nem ágyazhatók egymásba
//
// a protokol nyilván platformfüggetlen, 
// a fő nehézség, hogy meg kell állapodni a szemafor nevekben,

// a tábla objketumok szemaforozása a tabslock-ban megírt
// külön függvényekkel történik, ezek megmaradtak általános
// használatra


#define SEMDIR     "semaphor.tmp"
#define SEMFIL(x)  lower(SEMDIR+dirsep()+x)


****************************************************************************
function sema_open(sname,mode)

    if( !file(SEMFIL(sname)) )
        dirmake(SEMDIR)
        fclose(fcreate(SEMFIL(sname)))
    end
    
    if( mode==NIL )
        mode:=FO_EXCLUSIVE
    end
    
    return fopen(SEMFIL(sname),mode)


****************************************************************************
function sema_close(hnd)
    return fclose(hnd)


****************************************************************************
