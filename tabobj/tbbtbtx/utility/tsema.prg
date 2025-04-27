
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
#include "table.ch"

******************************************************************************
function main(cmd)


    tranSemaOn(SEMA_MANUAL,0,.t.)
    tranSemaOn(SEMA_XOPEN ,0,.t.)
    tranSemaOn(SEMA_RLOCK ,0,.t.)

    ? "transaction semaphor locked"

    if( empty(cmd) )
        ?? ", hit any key ..."
        inkey(0)
    else
        run(cmd)
    end

    tranSemaOff(SEMA_MANUAL)
    tranSemaOff(SEMA_XOPEN)
    tranSemaOff(SEMA_RLOCK)

    ? "transaction semaphor unlocked"
    ?


******************************************************************************
