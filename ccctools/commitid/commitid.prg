
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


// nevenek ellentmondva
// nem hasznalja az ELF headert-t
// -> mukodik Windowson is    


******************************************************************************************
function main(*)
local exe:={*},n

    if(exe::empty)
        exe:=directory("*.exe")
        for n:=1 to len(exe)
            exe[n]:=exe[n][1]
        next
    end

    for n:=1 to len(exe)
        ?? exe[n]::padr(24), commitid(exe[n])
        ?
    next


******************************************************************************************
function commitid(exe)

local fd,map,pos,id:=""

    begin
        fd:=fopen(exe)
        map:=filemap.open(fd)
        pos:=rat(a"COMMITID[",map)
        if( 4096<len(map) .and. len(map)-56<pos )
            id:=map[pos+8..]
        end
    recover
    finally
        if(map!=NIL); filemap.close(map); end
        if(fd>=0); fclose(fd); end
    end

    return bin2str(id)


******************************************************************************************

