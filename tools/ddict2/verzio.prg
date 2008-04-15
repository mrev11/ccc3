
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

#include "table.ch"
#include "_ddict.ch"

**************************************************************************
function verzioDelete() //töröl egy nem legújabb verziót

local tab:=DDICT_TABLE, ver:=DDICT_VERSION

    if( structLatest("") )
        alert("The latest version must be deleted by records!")
    else
        DDICT:seek({tab,ver})
        while( !DDICT:eof .and. DDICT_TABLE==tab .and. DDICT_VERSION==ver )
            DDICT:rlock
            DDICT:delete
        end
        DDICT:unlock
    end
    return NIL


**************************************************************************
function verzioMake() //új verziót készít eggyel nagyobb sorszámmal

local tab:=DDICT_TABLE
local ver:=DDICT_VERSION
local verzio:={}, n

    if( structLatest("Only the latest version can be multiplied!") )
        
        DDICT:seek(DDICT_TABLE)
        while( !DDICT:eof .and. DDICT_TABLE==tab .and. DDICT_VERSION==ver )
            aadd(verzio,recordget())
            DDICT:skip
        end
        //kikaptuk az utolsó verziót
        
        for n:=1 to len(verzio)
            verzio[n][2]:=ver-1
            recordput(verzio[n])
        end
    end
    return NIL
    

**************************************************************************
static function recordget()
local rec:={},n
    for n:=1 to DDICT:fcount
        aadd(rec,DDICT:evalcolumn(n))
    next
    return rec

**************************************************************************
static function recordput(arr)
local n
    DDICT:append
    for n:=1 to DDICT:fcount
        DDICT:evalcolumn(n,arr[n])
    next
    DDICT:unlock
    return NIL

**************************************************************************
