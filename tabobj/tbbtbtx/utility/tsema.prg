
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

******************************************************************************
function main(cmd)

local semafd:=semafd()
local result

    fwaitlock(semafd,1,1)
    result:=fwaitlock(semafd,0,1)
    funlock(semafd,1,1)

    if( result==0 )
        ? "CCC_LOCK_SEMAPHOR locked"
        if( empty(cmd) )
            ?? ", hit any key ..."
            inkey(0)
        else
            run(cmd)
        end
        funlock(semafd,0,1)
        ? "CCC_LOCK_SEMAPHOR unlocked"
    else
        ? "CCC_LOCK_SEMAPHOR failed"
    end
    ?


******************************************************************************
static function semafd()
local sema,fd:=-1
    sema:=getenv("CCC_LOCK_SEMAPHOR")
    if( empty(sema) )
        ? "CCC_LOCK_SEMAPHOR variable is not set"
    elseif( !file(sema) )
        ? "CCC_LOCK_SEMAPHOR file does not exist", sema
    elseif( 0>(fd:=fopen(sema,FO_NOLOCK+FO_READWRITE)) )
        ? "Cannot open CCC_LOCK_SEMAPHOR file", sema
    end
    if( fd<0 )
        ?
        quit
    end
    return fd


******************************************************************************
