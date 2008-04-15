
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

    for n:=1 to len(opt)
        if( opt[n]=="-x" )
            quit //csak ellenőrzi, hogy megvan-e a program
        else
            fspec:=opt[n]
        end
    next

    ftxt:=memoread(fspec,.t.) //binary
    ftxt1:=strtran(ftxt,x"0d0a",x"0a")
    //ftxt1:=strtran(ftxt,x"0d",x"")

    if( !ftxt==ftxt1 )
      #ifdef UNIX 
        fmode:=stat_st_mode(fspec)
      #endif
        memowrit(fspec,ftxt1)
      #ifdef UNIX 
        chmod(fspec,fmode)
      #endif
    end

    return NIL

