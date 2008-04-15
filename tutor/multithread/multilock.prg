
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

//Demonstrálja, hogy Windoson a mutexlock rekurzív.
//Linuxon ez a program deadlockot okoz.

static mutex:=thread_mutex_init()

#define MUTEX_LOCK    ? "lock", thread_self(), thread_mutex_lock(mutex)
#define MUTEX_TRYLOCK ? "trylock", thread_self(), thread_mutex_trylock(mutex)
#define MUTEX_UNLOCK  ? "unlock", thread_self(), thread_mutex_unlock(mutex)

function main()
local th1,th2
    MUTEX_LOCK
    MUTEX_LOCK //Linuxon ez deadlock

    MUTEX_UNLOCK
    th1:=thread_create({||try()}) //ez még nem tud lockolni
    sleep(100)

    MUTEX_UNLOCK
    th2:=thread_create({||try()}) //ez már tud lockolni
    sleep(100)

    thread_join(th1)
    thread_join(th2)
    ?

function try()
    MUTEX_TRYLOCK

