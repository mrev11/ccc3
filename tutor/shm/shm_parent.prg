
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
#include "spawn.ch"

***************************************************************************************
function main()

local shmid,pid,buf

    shmid:=ipc.shmget(IPC_PRIVATE,20,IPC_CREAT+0b110100100) // IPC_CREAT+0644

    ? "PARENT", shmid
    buf:=ipc.shmat(shmid)

    pid:=spawn(SPAWN_NOWAIT,"shm_child.exe",str(shmid))

    while( inkey()==0 )
        sleep(1000)
        ? buf
    end

    ? "PARENT"
    varstack()
    ?

    ipc.shmdt(buf) // detach
    ipc.shmctl(shmid,IPC_RMID) // remove
    
    sleep(2000)
    
    run( "kill"+str(pid)  )
    

***************************************************************************************
