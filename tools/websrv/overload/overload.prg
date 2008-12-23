
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
#include "signal.ch"

static count:=0
static level:=0
static mutex:=thread_mutex_init()
static cond:=thread_cond_init()
static maxthr:=16
static delaft:=.t.
static begtim:=seconds()


*****************************************************************************
function main(url,thr,rep) //URL, maxthread count, repeat count

local full:=.f.

    if(thr!=NIL)
        maxthr:=val(thr)
    end

    if(rep=="1")
        delaft:=.f.
    end
    
    thread_create_detach({||wgkill(20)})

    while( !inkey(0.2)==K_CTRL_Q )
        thread_mutex_lock(mutex)
        if( level<maxthr )
            ? ++count,++level, seconds()-begtim

            if(level>=maxthr)
                full:=.t.
            end
            
            if(full.and.level<2)
                quit
            end
            
            
            thread_create_detach({||wget(url)})
            //vagy el kell engedni (thread_detach)
            //vagy meg kell várni (thread_join)
        end
        thread_mutex_unlock(mutex)
        
        if( rep!=NIL .and. val(rep)<=count )
            exit
        end
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

    if( delaft )
        aadd(arg,"--delete-after")
    end

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
static function wgkill(maxtime:=60)

//lelövi azokat a wget processzeket,
//amik maxtime másodpercnél öregebbek

local prev:=simplehashNew(32)
local wget,now,pid,btm,n

    while(.t.)

        wget:=wglist()
        now:=seconds()

        for n:=1 to len(wget:hasharray)
            if( wget:hasharray[n]!=NIL )

                pid:=wget:hasharray[n][1]   //most élő wget-ek
                btm:=prev[pid]              //indulási idő (vagy NIL)

                if( btm!=NIL )
                    wget[pid]:=btm
                    if( now-btm>maxtime )
                        signal_send(val(pid),SIG_TERM)
                        ? "KILLED", pid
                    end
                end
            end
        next
        prev:=wget

        sleep(1000)
    end

*****************************************************************************
static function wglist()

local wg:=simplehashNew(32)
local fd,rl,buf

    run( "ps -A | grep wget >wg" )

    fd:=fopen("wg")
    rl:=readlineNew(fd)
    while( NIL!=(buf:=rl:readline) )
        wg[buf::val::str::alltrim]:=seconds()
    end
    fclose(fd)
    return wg

*****************************************************************************
