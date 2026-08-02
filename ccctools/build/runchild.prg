
#include "spawn.ch"


****************************************************************************
function runchild(cmd,pid)

static mutex_fd:=thread_mutex_init()

local p1,p2
local fd0,fd1,fd2
local pr,pw
 
    if( valtype(cmd)=="C" )
        //darabolás
        while("  "$cmd)
            cmd:=strtran(cmd,"  "," ")
        end
        cmd:=split(cmd," ")
    end

    thread_mutex_lock(mutex_fd)

        p1:=pipe() // p1[1] <---< p1[2] 
        p2:=pipe() // p2[2] >---> p2[1] 
    
        pr:=fdup(p1[1],.f.,.t.) //parent oldal (nem öröklődik, eredeti lezáródik)
        pw:=fdup(p2[2],.f.,.t.) //parent oldal (nem öröklődik, eredeti lezáródik)
     
        fd0:=fdup(0,.f.); fdup(p2[1],0,.t.)  // stdin : ment, átirányít, lezár
        fd1:=fdup(1,.f.); fdup(p1[2],1,.t.)  // stdout: ment, átirányít, lezár 
        fd2:=fdup(2,.f.); fdup(1,2)          // stderr: ment, átirányít
     
        pid:=spawn(SPAWN_NOWAIT+SPAWN_PATH,cmd) 
    
        fdup(fd0,0,.t.)  // stdin : visszaállít
        fdup(fd1,1,.t.)  // stdout: visszaállít 
        fdup(fd2,2,.t.)  // stderr: visszaállít 
   
    thread_mutex_unlock(mutex_fd)

    return {pr,pw}


****************************************************************************
