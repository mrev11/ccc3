
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

//demonstrálja,
//hogy a szálak egyidőben futnak
//hogy a szálak közös static változókkal, de külön local stackkel rendelkeznek
//a localstack függvény használatát

static s1:="s1"
static s2:="s2"
static s3:="s3"

static mutex:=thread_mutex_init()

*********************************************************************************
function main()

local a:="a",b:="b",c:="c"
local blk:={|*|other_thread(*)}
local th

    s1 //hivatkozás nélkül nem jön létre
    s2
    s3
    
    rand(seconds())
    
    th:=thread_create(blk,1,2,3)
    //th:=eval(blk,1,2,3)

    work("MAIN")

    if(th!=NIL)
        thread_join(th)
    end
    

*********************************************************************************
function other_thread(*)
local hopp:="HOPP"
    work("THREAD")
    
*********************************************************************************
function work(text)
local n
    for n:=1 to 100
        sleep(rand())
        thread_mutex_lock(mutex)
        ? text,n
        thread_mutex_unlock(mutex)
    next

    thread_mutex_lock(mutex)
    varstack()
    ? localstack(1), localstack(2), localstack(3), localstack(4), localstack(5)
    ?
    thread_mutex_unlock(mutex)


*********************************************************************************
    