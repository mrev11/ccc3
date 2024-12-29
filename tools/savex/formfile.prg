
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

#include "dirsync.ch"
#include "statvar.ch"


******************************************************************************    
function formFile(file,maxlen)
    if( len(file)>maxlen )
        file:=left(file,maxlen-13)+"~"+right(file,12)
    end
    return file


******************************************************************************    
function formDir(dir,maxlen)
    if( maxlen==NIL )
        maxlen:=DTSIZE
    end
    if( right(dir,1)==dirsep() )
        dir:=left(dir,len(dir)-1)
    end
    dir:=truename(dir)
    if( len(dir)>maxlen )
        dir:=left(dir,2)+"~"+right(dir,maxlen-3)
    end
    return dir


******************************************************************************    
function formDate(date,time)
    return dtos(date)+" "+if(s_seconds,time,left(time,5))


******************************************************************************    
