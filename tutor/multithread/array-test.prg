
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

#define THREADS     6
#define REPEAT     16
#define ITER      100

static mutex:=thread_mutex_init()
static counter:=array(THREADS)

*****************************************************************************
function main()

local th:=array(THREADS),n   

    thread_create({||garbage()})

    afill(counter,0)
    
    ?

    for n:=1 to len(th)
        th[n]:=thread_create({|x|proba(x)},n)
    next
    
    for n:=1 to len(th)
        thread_join(th[n])
        ?? "joined",n
        ?
    next


*****************************************************************************
static function garbage()
    while(.t.)
        gc()
        sleep(10)
    end

*****************************************************************************
static function proba(x)
local cnt:=0,a,n

    while( cnt<ITER*REPEAT )
    
        if( ++cnt%ITER==0 )
            thread_mutex_lock(mutex)
            counter[x]++
            for n:=1 to len(counter)
                ?? counter[n]
            next
            ?
            thread_mutex_unlock(mutex)
        end
        
        directory("/opt/ccc2/ccclib/src","H")

        a:={}
        for n:=1 to 100
            aadd(a,errorNew())
        next

        sleep( rand()*100 )
    end


*****************************************************************************

    