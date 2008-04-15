
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

#include "fileio.ch"
#include "stat.ch"
 
******************************************************************************
function filecopy(fsource,ftarget) // CA-Tools  

local st1, fd1, fd2
local buf, nr, nw
local nbyte:=0 

    st1:=stat(fsource)
    fd1:=fopen(fsource,FO_READ)  
    if( fd1<0 )
        return 0
    end
    
    ferase(ftarget)
    fd2:=fcreate(ftarget) 
    if( fd2<0 )
        fclose(fd1)
        return 0
    end
    
    buf:=replicate(x"00",4096)
    nr:=fread(fd1,@buf,len(buf))
    while( nr>0 )
        nbyte+=(nw:=fwrite(fd2,buf,nr)) 
        if( nw!=nr )
            exit
        end
        nr:=fread(fd1,@buf,len(buf))
    end
   
    fclose(fd1)
    fclose(fd2)
    
    if( st1!=NIL )
        utime(ftarget,st1[STAT_ATIME],st1[STAT_MTIME])
        chmod(ftarget,st1[STAT_MODE])
        chown(ftarget,st1[STAT_UID],st1[STAT_GID])
    end
 
    return nbyte

******************************************************************************
