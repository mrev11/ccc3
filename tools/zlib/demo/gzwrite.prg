
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

// ir egy gz fajlba (tomorit)

#include "fileio.ch"


function main(fspec)

local map:=memoread(fspec,.t.)
local offs:=1,incr:=128

local fd:=fopen(fspec+".gz",FO_CREATE+FO_TRUNCATE+FO_WRITE)
local gzd:=zlib.gzdopen(fd,"wb6")

    while( offs<=len(map) )
        zlib.gzwrite(gzd,map::substr(offs,incr))
        offs+=incr
    end

    zlib.gzclose(gzd)

    // fd-t nem kell kulon lezarni

