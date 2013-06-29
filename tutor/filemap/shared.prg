
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

function main()

local fd
local map1,map2
local t

    fd:=fcreate("shared")
    chsize(fd,64)
    map1:=filemap.open(fd,"rw")
    fclose(fd)

    fd:=fopen("shared")
    map2:=filemap.open(fd,"r")
    fclose(fd)
    
    while(.t.)

        sleep(100)

        t:=time()::str2bin
        xvputbin(map1,7,len(t),t)  //0 based
        filemap.sync(map1)
        
        ? map2[8..15] //1 based
    end
