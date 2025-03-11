
// reszleges shm implementacio

namespace ipc

#include "shm.ch"
#include "fileio.ch"


******************************************************************************************
function shmget(private,size,access)
local shmid
local tempdir:=getenv("TEMP")
local tmp:=tempfile(tempdir+dirsep(),"tmp")
local qbl:=quitblock()
local err
    quitblock({|*|ferase(tmp),eval(qbl,*)})
    shmid:=fopen(tmp,FO_CREATE+FO_READWRITE)
    if( shmid<0 )
        err:=ioerrorNew()
        err:operation:="ipc.shmget"
        err:description:="cannot create temporary file"
        err:filename:=tmp
        break(err)
    end
    chsize(shmid,size)
    return shmid
    

******************************************************************************************
function shmat(shmid)
    return filemap.open(shmid,"rw")


******************************************************************************************
function shmdt(buffer)
    filemap.close(buffer)


******************************************************************************************
function shmctl(shmid,ctl)
    if( ctl==IPC_RMID )
        fclose(shmid)
    end

******************************************************************************************
