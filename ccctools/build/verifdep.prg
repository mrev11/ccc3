
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


****************************************************************************
function verifdep(ttarget,depend)

local update:=.f.
local tdepend:=ftime(depend)

    if( tdepend==NIL )
        if( s_dry() )
            tdepend:=""
        else
            ? depend, @"does not exist"
            ?
            errorlevel(1)
            quit
        end

    elseif( ttarget<tdepend )
        update:=.t.
    end

    if( s_debug() )
        ? "  ",depend, "["+tdepend+"]", if(ttarget<tdepend,"UPDATE","")
    end
    
    return update


****************************************************************************
