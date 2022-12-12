
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

// A program sok threadet hoz letre.
// A threadek atlagosan 1 masodpercig elnek,
// az egyszerre eletben levo threadek szama<=MAXTHREAD.
// Vegul megvarjuk az osszes thread kilepeset.

#include "inkey.ch"

#define MAXTHREAD  16

static mutex:=thread_mutex_init()
static cond:=thread_cond_init()

static level:=0
static count:=0

*******************************************************************************
function main()
local th

    while( inkey(0.05)!=K_ESC  )

        th:=thread_create({|x,r|t(x,r)},count,rand())
        thread_detach(th)
        
        //A threadeket vagy el kell engedni (detach)
        //vagy meg kell varni  (join), maskulonben
        //elfogynak a letrehozhato threadek (Linuxon kb. 90).

        thread_mutex_lock(mutex)

        //A level valtozot a threadek modositgatjak,
        //ezert csak mutex vedelem alatt biztonsagos a kiolvasasa.

        ? padl(l2hex(th),8), count, level
        ++level
        ++count
        while( level>MAXTHREAD )
            thread_cond_wait(cond,mutex)
        end
        thread_mutex_unlock(mutex)
    end

    thread_mutex_lock(mutex)
    while( level>0 )
        thread_cond_wait(cond,mutex)
        //? "quit",level
    end
    thread_mutex_unlock(mutex)
    ?

    return NIL


*******************************************************************************
static function t(x,r)
    sleep(r*2000)  //atlagosan 1 masodpercet var
    thread_mutex_lock(mutex)
    --level
    ? "quit",x,r
    thread_cond_signal(cond)
    thread_mutex_unlock(mutex)
    return NIL


*******************************************************************************

