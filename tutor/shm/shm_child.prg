
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

#include "shm.ch"

***************************************************************************************
function main(shmid)

local buf,t

    signalblock({|s|sighandler(s)})

    shmid::=val

    ? "CHILD ",shmid 
    buf:=ipc.shmat(shmid)

    ? len(buf)

    while(.t.)
        t:=time()::str2bin
        xvputbin(buf,0,len(t),t)
        sleep(2000)
    end

    ipc.shmdt(buf) // detach
    ipc.shmctl(shmid,IPC_RMID) // remove


***************************************************************************************
static function sighandler(signum)
    ? "CHILD"
    varstack()
    ?
    quit
        

***************************************************************************************
