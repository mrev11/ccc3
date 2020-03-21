
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

#define FILEMAP

************************************************************************************
function main(fspec:="a.csv")

local text,fd
local reader
local record,i

    set printer to log-demo
    set printer on

#ifdef FILEMAP
    fd:=fopen(fspec)
    text:=filemap.open(fd)
    fclose(fd)
#else
    text:=memoread(fspec)
#endif

    reader:=csvreaderNew(text,";")

    while( !empty( record:=reader:nextrecord ) )

        ? '----------------------------'
        for i:=1 to len(record)
            ? space(2*(i-1)),a'['+record[i]+a']'
        next
    end  
    ? '----------------------------'

    reader:free

#ifdef FILEMAP
    filemap.close(text)
#endif

    ?

************************************************************************************
