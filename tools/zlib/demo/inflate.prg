
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


******************************************************************************************
function main(fspec)

local fdout:=fopen("out",FO_CREATE+FO_TRUNCATE+FO_WRITE)
local fdin:=fopen(fspec,FO_READ)
local map:=filemap.open(fdin)
local offs:=1,incr:=4096,part,chunk
local strm

    fclose(fdin)

    strm:=zlib.inflateinit2()
    while( offs<=len(map) )
        part:=map::substr(offs,incr)
        chunk:=zlib.inflate(strm,part)
        fwrite(fdout,chunk)
        offs+=incr
    end

    filemap.close(map)
    fclose(fdout)


******************************************************************************************
