
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

******************************************************************************
function truename(fspec)
local drive,colon,path,i

    path:=fspec
    path:=strtran(path,"/",dirsep())
    path:=strtran(path,"\",dirsep())
    
    colon:=at(":",path)
    if( colon==0 )
        drive:=diskname()
        if( !empty(drive) )
            drive+=":"
        end
    else
        drive:=left(path,colon)
        path:=substr(path,colon+1)
    end
    
    if( !left(path,1)==dirsep() )
        path:=curdir(drive)+dirsep()+path
    else
        path:=substr(path,2)
    end
    
    path:=split(path,dirsep())

    i:=1
    while( i<=len(path) .and. path[i]!=NIL )
        if( path[i]=="." )
            adel(path,i)
        else
            i++
        end
    next
    asize(path,i-1)

    i:=1
    while( i<=len(path) .and. path[i]!=NIL )
        if( path[i]==".." )
            if( i>1 )
                i--
                adel(path,i)
            end
            adel(path,i)
        else
            i++
        end
    next
    asize(path,i-1)
    
    fspec:=drive
    for i:=1 to len(path)
        fspec+=dirsep()+path[i]
    next
    if( fspec==drive )
        fspec+=dirsep()
    end
    
    return fspec

******************************************************************************
