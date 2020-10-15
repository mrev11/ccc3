
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
