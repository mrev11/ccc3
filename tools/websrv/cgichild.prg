
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

#include "signal.ch"
#include "spawn.ch"

#include "websrv.ch"


*****************************************************************************
function cgichild(cmd,env,wd,sck)

local p1,p2,pp
local fd0,fd1,fd2
local pr,pw,pid
local savewd:=dirname()

    p1:=pipe() // p1[1] <---< p1[2] 
    p2:=pipe() // p2[2] >---> p2[1] 

    pr:=fdup(p1[1],.f.,.t.) //parent oldal (nem öröklődik, eredeti lezáródik)
    pw:=fdup(p2[2],.f.,.t.) //parent oldal (nem öröklődik, eredeti lezáródik)

    thread_mutex_lock(mutex_spawn())
    dirchange(wd) //a php maga is átvált a script directoryjába
        fd0:=fdup(0,.f.); fdup(p2[1],0,.t.) //stdin: ment, átirányít, lezár
        fd1:=fdup(1,.f.); fdup(p1[2],1,.t.) //stdout: ment, átirányít, lezár 
        if( sck:classname=="socket" )
            sck:inherit(.t.) //a sajátját örökli
            aadd(env,"REMOTE_SOCKET="+alltrim(str(sck:fd))) //bővítmény
        end
        pid:=spawn(SPAWN_NOWAIT,cmd,env) 
        if( sck:classname=="socket" )
            sck:inherit(.f.)
        end
        fdup(fd0,0,.t.) //stdin: visszaállít
        fdup(fd1,1,.t.) //stdout: visszaállít 
    dirchange(savewd) //felesleges
    
    #ifdef _UNIX_
        pp:=pipe()
        pp[1]:=fdup(pp[1],.f.,.t.) //nem öröklődik, eredeti lezáródik
        pp[2]:=fdup(pp[2],.f.,.t.) //nem öröklődik, eredeti lezáródik
        thread_create_detach({||cgishutdown(pid,cgitime()*1000,pp[1])})
    #endif
    thread_mutex_unlock(mutex_spawn())

    //pp[1]-et cgishutdown zárja le
    //pp[2]-et cgipage zárja le, jelzi cgishutdown-nak, hogy kész

    return {pr,pw,if(pp==NIL,NIL,pp[2])}

*****************************************************************************
#ifdef _UNIX_
static function cgishutdown(pid,timeout,pipe)
//local fd
    if( 0==select({pipe},,,timeout) ) //vár, hogy cgipage elkészüljön
        signal_send(pid,SIG_KILL) //esetleg már korábban kilépett
        //fd:=fopen("killed.html",FO_CREATE+FO_WRITE+FO_APPEND)
        //fwrite(fd,"killed"+str(pid)+" "+time()+chr(10))
        //fclose(fd)
    end
    fclose(pipe)
#endif
    
*****************************************************************************
