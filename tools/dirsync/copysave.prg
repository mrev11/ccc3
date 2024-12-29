
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

#include "dirsync.ch"
#include "statvar.ch"


******************************************************************************    
function copyFreshen(brw)
local arr:=brwArray(brw), n
local msg, fname

    msg:=message(msg,"Freshen")

    for n:=1 to len(arr)
        if( arr[n][IDX_WORK] < arr[n][IDX_SAVE] )
            fname:=arr[n][IDX_FILE]
            msg:=message(msg,s_save+fname+" --> "+s_work+fname)
            xfilecopy(s_save+fname,s_work+fname)
        end
    next
    message(msg)
    return .f.

******************************************************************************    
function copySave(brw)
local arr:=brwArray(brw), n
local msg, fname

    msg:=message(msg,"Save")

    for n:=1 to len(arr)
        if( arr[n][IDX_WORK] > arr[n][IDX_SAVE] )
            fname:=arr[n][IDX_FILE]
            msg:=message(msg,s_save+fname+" <-- "+s_work+fname)
            xfilecopy(s_work+fname,s_save+fname)
        end
    next
    message(msg)
    return .f.



******************************************************************************    
