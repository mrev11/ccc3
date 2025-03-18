
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

//TARTALOM  : egyszeru szemafor protokol
//STATUS    : kozos utility


#include "fileio.ch"

// egyszeru szemafor protokoll
//
// hnd:=sema_open(sname,mode)
// sema_close(hnd)
//
// mode erteke lehet FO_EXCLUSIVE (default), vagy FO_SHARED
//
// ezek kozonseges file open/close muveletek,
// a filek a semaphor-ban jonnek letre (automatikusan),
// hiba: az exclusive szemafor lockok nem agyazhatok egymasba
//
// a protokol nyilvan platformfuggetlen, 
// a fo nehezseg, hogy meg kell allapodni a szemafor nevekben,

// a tabla objketumok szemaforozasa a tabslock-ban megirt
// kulon fuggvenyekkel tortenik, ezek megmaradtak altalanos
// hasznalatra


#define SEMDIR     "semaphor.tmp"
#define SEMFIL(x)  (SEMDIR+dirsep()+x)


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
