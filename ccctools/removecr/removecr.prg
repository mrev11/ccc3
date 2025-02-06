
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

function main( fspec )

local opt:=aclone(argv()),n

local ftxt
local ftxt1
local fmode

    set dosconv off

    for n:=1 to len(opt)
        if( opt[n]=="-x" )
            quit //csak ellenorzi, hogy megvan-e a program
        else
            fspec:=opt[n]
        end
    next

    if( fspec==NIL )
        ?? "Usage: removecr <filespec>"
        ?
        quit
    end
    if( !file(fspec) )
        ?? "Usage: removecr <filespec>"
        ?? " (file not found ["+fspec+"])"
        ?
        quit
    end


    ftxt:=memoread(fspec)
    ftxt1:=strtran(ftxt,chr(13),"")

    if( !ftxt==ftxt1 )
      #ifdef UNIX
        fmode:=stat_st_mode(fspec)
      #endif
        memowrit(fspec,ftxt1)
      #ifdef UNIX
        chmod(fspec,fmode)
      #endif
    end


