
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

*****************************************************************************
function xtoc(x) // CA Tools
local t:=valtype(x),c,e
    if( t=="N" )
        c:=ftoc(x)
    elseif( t=="X" )
        c:=bin2str(x)
    elseif( t=="C" )
        c:=x
    elseif( t=="D" )
        c:=dtos(x)
    elseif( t=="L" )
        c:=if(x,"T","F")
    elseif( t=="P" )
        c:=l2hex(x)
    else
        e:=errorNew()
        e:operation:="xtoc"
        e:description:=@"argument error"
        e:args:={x}
        break(e)
    end
    return c
    

*****************************************************************************
function ctof(cFloatingPointNumber) // CA Tools
    return bin2f(cFloatingPointNumber)


*****************************************************************************
function ftoc(nFloatingPointNumber) // CA Tools
    return f2bin(nFloatingPointNumber)
 

*****************************************************************************

