
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

//Demó thread_join hibájának demonstrálására:
//thread_join-nak mindaddig várnia kellene, amíg a szál (amire vár) be nem
//fejeződik. A demó mutatja, hogy a szál még fut, a main mégis továbbmegy.
//Ez attól függően következik be, hogy a sighandler indít-e új szálat.

//A hiba kernelfüggő:
//2.4.21-es kernelen hibás
//2.6.10-es kernelen jó

#include "signal.ch"

static sig:=.f.
static pid

function main(arg)

    ? "MAIN", getpid(), thread_self()

    sig:=if(arg==NIL,.f.,.t.)
    pid:=getpid()
    
    signalblock({||sighandler()})

    thread_detach( thread_create({||lelo()}) )
    thread_join( thread_create({||var()}) )    //innen hibásan kijön, ha ...
    ? "TOVÁBBMENT"
    sleep(2000)                                //itt var() még printelget
    ?


function sighandler()
local th
    ? "SIG",sig, getpid(), thread_self()
    if( sig )
        th:=thread_create( {||qout("HOPP")})   //... ha itt új szál indul
        thread_detach(th)
    end

    
function lelo() //lelő
    ? "LELO", getpid(), thread_self()
    sleep(1000)
    signal_send(pid,SIG_TERM)
    sleep(4000)
    ? "KILL"
    signal_send(pid,SIG_KILL)
    sleep(1000)


function var() //vár
local cnt:=0
    ? "VAR ", getpid(), thread_self()
    while(.t.) 
        ? "var",++cnt
        sleep(250)
    end



    