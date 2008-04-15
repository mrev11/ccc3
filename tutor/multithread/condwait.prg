
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

//Ez minden thread függvényt meghív.
//Ellenőrzi a viszonylag egységes 0/errorcode return értékeket.
//Bemutatja a thread_cond_wait/thread_cond_signal használatát.

static mutex:=thread_mutex_init()
static cond:=thread_cond_init()
static mutex1:=thread_mutex_init()

#define MUTEX_LOCK      ? "lock",   thread_mutex_lock(mutex)
#define MUTEX_UNLOCK    ? "unlock", thread_mutex_unlock(mutex)
#define COND_WAIT       ? "wait",   thread_cond_wait(cond,mutex)
#define COND_SIGNAL     ? "signal", thread_cond_signal(cond)
#define MUTEX_TRYLOCK   ? "trylock",thread_mutex_trylock(mutex1)

static var:=.f.

function main()

local blk1:={|x,y,z|xyz(x,y,z)}
local blk2:={||sig()}

local th:=thread_create({||abc()})
local th1:=thread_create(blk1,1,2,3)
local th2:=thread_create(blk2)

    //? "main-tid", thread_self()

    ? "detach", thread_detach(th)
    ? "join1", thread_join(th1)
    ? "join2", thread_join(th2)
    
    ? "destroy", thread_mutex_destroy(mutex)
    ? "destroy", thread_cond_destroy(cond)
    
    ?


******************************************************************************    
function abc()
    MUTEX_TRYLOCK
    thread_exit()

    //mutex1 fogva marad.
    //Linuxon ezt nem lehet lockolni.
    //Windowson lehet lockolni.

******************************************************************************    
function xyz(x,y,z)
    //? "xyz-tid", thread_self()
    ? x,y,z
    
    sleep(1000)
    MUTEX_TRYLOCK //Windowson sikeres, Linuxon sikertelen

    MUTEX_LOCK
    //MUTEX_LOCK  //Linuxon ez deadlock, Windowson továbbmegy
    while( !var )
        COND_WAIT
    end
    MUTEX_UNLOCK

******************************************************************************    
function sig()
    //? "sig-tid", thread_self()

    sleep(3000)
    MUTEX_TRYLOCK
       
    MUTEX_LOCK
    var:=.t.
    COND_SIGNAL
    MUTEX_UNLOCK

******************************************************************************    
