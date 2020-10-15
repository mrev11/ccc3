
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
