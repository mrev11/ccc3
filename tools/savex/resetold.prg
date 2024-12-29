
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
function resetold(brw)

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
local fname:=arr[pos][IDX_FILE]

local wfile:=s_work+fname
local sfile:=s_save+fname
local wtime:=arr[pos][IDX_WORK]
local stime:=arr[pos][IDX_SAVE]

    if( empty(wtime) )
        ferase(sfile)

    elseif( empty(stime) )
        ferase(wfile)

    elseif( stime<wtime )
        xfilecopy(sfile,wfile)

    elseif( wtime<stime )
        xfilecopy(wfile,sfile)

    else
        //nincs mit visszaallitani
    end


******************************************************************************    
function copynew(brw)

local arr:=brwArray(brw)
local pos:=brwArrayPos(brw)
local fname:=arr[pos][IDX_FILE]

local wfile:=s_work+fname
local sfile:=s_save+fname
local wtime:=arr[pos][IDX_WORK]
local stime:=arr[pos][IDX_SAVE]

    if( empty(wtime) .or. wtime<stime )
        xfilecopy(sfile,wfile)

    elseif( empty(stime) .or. stime<wtime )
        xfilecopy(wfile,sfile)

    else
        //nincs mit masolni
    end


******************************************************************************    
