
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

#include "rnm.say"

*****************************************************************************
function main(fspec)
    rnm({|g|load(g,fspec)},{|g|readmodal(g)},{|g|store(g)})
    return NIL
    

*****************************************************************************
static function load(getlist,fs)

local l:=len(g_name_from:varget)
local p:="@RS"+alltrim(str(l))+" "+replicate("X",256) 

    g_name_from:picture:=p
    g_name_to:picture:=p
    g_name_from:varput(fs)
    g_name_to:varput(fs)
    g_name_from:preblock:={||.f.}

    return NIL



*****************************************************************************
static function store(getlist,fs)

local name_from:=alltrim(g_name_from:varget())
local name_to:=alltrim(g_name_to:varget())
local result

    if( name_from==name_to )
    elseif( !empty(getenv("WiNdIr")) )
        if( fileexist(name_to) )
            run( 'del "'+name_to+'"' )
        end
        result:=run( 'ren "'+name_from+'" "'+name_to+'"' )
    else
        result:=run( 'mv  "'+name_from+'" "'+name_to+'"' )
    end
    
    return result==0
 
*****************************************************************************
 
    