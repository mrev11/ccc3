
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
