
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

//Nyúzó tesztprogram a webszerverhez.
//Sok szálon (max 16) elindítja a wget-et,
//mindegyik szál tükrözi az url website-ot,
//majd törlik a letöltött filéket, 
//hogy a wgetnek mindig maradjon munkája.

#include "spawn.ch"
#include "inkey.ch"

static count:=0
static level:=0
static mutex:=thread_mutex_init()
static cond:=thread_cond_init()
static maxthr:=16

*****************************************************************************
function main(url,thr)

    if(thr!=NIL)
        maxthr:=val(thr)
    end

    while( !inkey(0.2)==K_CTRL_Q )
        thread_mutex_lock(mutex)
        if( level<maxthr )
            ? ++count,++level
            thread_create_detach({||wget(url)})
            //vagy el kell engedni (thread_detach)
            //vagy meg kell várni (thread_join)
        end
        thread_mutex_unlock(mutex)
    end
    
    //megvárjuk, hogy minden szál befejezze

    thread_mutex_lock(mutex)
    while(level>0)
        ? "quit",level
        thread_cond_wait(cond,mutex)
    end
    thread_mutex_unlock(mutex)
    ?
    
*****************************************************************************
static function wget(url)

local arg:={"wget"}

    aadd(arg,"-m")  //mirror
    aadd(arg,"-q")  //quiet
    aadd(arg,"--delete-after")

    if( "https"$url )
        aadd(arg,"--no-check-certificate")
        aadd(arg,"--private-key=demo-key.pem")
        aadd(arg,"--certificate=demo-cert.pem")
    end

    aadd(arg,url)

    spawn(SPAWN_WAIT+SPAWN_PATH,arg)

    thread_mutex_lock(mutex)
    --level
    thread_cond_signal(cond)
    thread_mutex_unlock(mutex)
    

*****************************************************************************
