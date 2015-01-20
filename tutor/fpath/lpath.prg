
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

// megkeres egy filét a LD_LIBRARY_PATH-ban
// vagy csak kiírja a LD_LIBRARY_PATH-t

function main(fname)

local path:=getenv("LD_LIBRARY_PATH")::split(pathsep()),n

    for n:=1 to len(path)
    
        if( empty(path[n]) )
            loop
        end

        if( path[n][1]=='"' )
            path[n]:=path[n][2..len(path[n])-1]
        end

        if( fname==NIL )
            ? path[n]
        else    
            if( path[n]::right(1)!=dirsep() )
                path[n]+=dirsep()
            end
            if( file(path[n]+fname) )
                ? path[n]+fname
            end
        end
    next
    ? 
    
