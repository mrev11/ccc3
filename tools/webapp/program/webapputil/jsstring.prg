
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

namespace webapp

***************************************************************************************
function jsstring(x)

    x::=strtran("\","\\")
    x::=strtran(chr(9),"\t")
    x::=strtran(chr(10),"\n")
    x::=strtran(chr(13),"\r")

    if( !'"'$x )
        x:='"'+x+'"'
    elseif( !"'"$x )
        x:="'"+x+"'"
    else
        x:='"'+x::strtran('"','\"')+'"'
    end
    
    return x

***************************************************************************************
function htmlstring(x)
    x::=strtran("&","&amp;")
    x::=strtran("<","&lt;")
    return x

***************************************************************************************
