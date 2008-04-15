
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

//folyamatosan listázza egy szövegfilé növekményét

#include "fileio.ch"

function main(fspec)

local buf:=a" "
local fd:=fopen(fspec)

    if( fd<0 )
        ? "file not found:", fspec
        quit
    end
    fseek(fd,0,FS_END)
    while( .t. )
        while( 1!=fread(fd,@buf,1) )
            sleep(500)
        end
        ?? buf
    end
    