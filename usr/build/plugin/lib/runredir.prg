
#include "spawn.ch"


****************************************************************************
function runredir(cmd,fd1,fd2) // stdout->fd1, stderr->fd2

local fd1save
local fd2save
 
    if( valtype(cmd)=="C" )
        //darabolás
        while("  "$cmd)
            cmd:=strtran(cmd,"  "," ")
        end
        cmd:=split(cmd," ")
    end

    fd1save:=fdup(1,.f.)    // ment, fd1save nem oroklodik
    fd2save:=fdup(2,.f.)    // ment, fd2save nem oroklodik

    if( fd2==NIL )
        // 2 nincs atiranyitva
        if( fd1!=NIL )
            // 1 atiranyitva
            fdup(fd1,1,.t.) // stdout: atiranyit, fd1 lezarodik 
        end

    elseif( fd1==NIL )
        // 1 nincs atiranyitva
        if( fd2!=NIL )
            // 2  atiranyitva
            fdup(fd2,2,.t.) // stderr: atiranyit, fd2 lezarodik 
        end

    elseif( fd1!=fd2 )
        // kulon fajoklba iranyitva
        fdup(fd1,1,.t.)     // stdout: atiranyit, fd1 lezarodik 
        fdup(fd2,2,.t.)     // stderr: atiranyit, fd2 lezarodik 

    else//if( fd2==fd1 )
        fdup(fd1,1,.t.)     // stdout: atiranyit, fd1 lezarodik 
        fdup(1,2)           // stderr: ugyanoda
    end
     
    spawn(SPAWN_WAIT+SPAWN_PATH,cmd) 

    fdup(fd1save,1,.t.) // vissza
    fdup(fd2save,2,.t.) // vissza


****************************************************************************

// itt nem kell lockolni
// static mutex_fd:=thread_mutex_init()
//    thread_mutex_lock(mutex_fd)
//    thread_mutex_unlock(mutex_fd)


