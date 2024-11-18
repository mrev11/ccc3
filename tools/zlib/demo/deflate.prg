
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

// hogyan lehet egyben es darabonkent tomoriteni?

******************************************************************************************
function main(fspec)
local x:=memoread(fspec,.t.)
    deflate_whole(x)
    deflate_chunk(x)
    ?

******************************************************************************************
static function deflate_whole(x)
    memowrit("whole.gz",zlib.deflate(x))


******************************************************************************************
static function deflate_chunk(x)

local offs:=1,incr:=4096
local part,chunk
local strm,z:=a''

    strm:=zlib.deflateinit2()
    while( offs<=len(x) )
        part:=substr(x,offs,incr)
        chunk:=zlib.deflate(strm,part)
        if( len(chunk)>0 )
            z+=chunk
            ?? "!"
        else
            ?? "."
        end
        offs+=incr
    end
    z+=zlib.deflate(strm,a'',.t.) //flush
    memowrit("chunk.gz",z)


******************************************************************************************
