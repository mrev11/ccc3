
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


#command ?  [ <list,...> ] => print( <list> )

static mutx:=thread_mutex_init()
static cond:=thread_cond_init()

static level:=10

******************************************************************************************
function main()

local t1:=thread_create({|x,l|fun(x,l)},"A",8)
local t2:=thread_create({|x,l|fun(x,l)},"B",5)
local t3:=thread_create({|x,l|fun(x,l)},"C",2)

    while( level>0 )
        sleep(100)
        ? "INKEY"    
        inkey(0)

        mutx::thread_mutex_lock
        --level
        cond::thread_cond_signal
        mutx::thread_mutex_unlock
    end

    thread_join(t1)
    thread_join(t2)
    thread_join(t3)

    ? "HOPP"
    ?

******************************************************************************************
static function fun(x,lwm)

    mutx::thread_mutex_lock
    while( level>lwm )
        ? "    WAIT-"+x,level
        cond::thread_cond_wait(mutx)
    end
    mutx::thread_mutex_unlock
    sleep(50)
    ? "       HOPP-"+x


******************************************************************************************
static function print(*)  // ne keveredjenek a kiirasok
static print:=thread_mutex_init()  
    print::thread_mutex_lock 
    qout(*)
    print::thread_mutex_unlock 


******************************************************************************************

#ifdef NOTDEFINED

    Itt az a fontos, hogy a thread_cond_signal jelet
    mindegyik szal megkapja, noha a POSIX szabvany csak
    annyit mond, hogy legalabb egy szal kap jelet.
    A program Linuxon, OmniOS-en, Windowson mukodik.

#endif




