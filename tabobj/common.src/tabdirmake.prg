
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


*************************************************************************
function tabDirMake(tab)
local path:=tabPath(tab)
    if( empty(path) )
        return 0
    end
    return dirdirmake(path)


*************************************************************************
static function dirdirmake(path)

// dirdirmake("proba\szerencse")
// dirdirmake("proba\szerencse\")
// dirdirmake("c:\proba\szerencse\")
// dirdirmake("c:proba\szerencse\")

local code:=0,sep:=1,dir

    path:=strtran(path,"/",dirsep())
    path:=strtran(path,"\",dirsep())
    
    if( right(path,1)!=dirsep() )
        path+=dirsep()
    end
 
    while( code==0 .and. 0<sep<len(path) )
        sep:=at(dirsep(),path,sep+1)
        dir:=left(path,sep-1)
        
        if( len(dir)==2 .and. isalpha(dir[1]) .and. dir[2]==":" )
            // DOS drive
        elseif( !direxist(dir) )
            code:=dirmake(dir)
        end
    end

    return code


*************************************************************************


