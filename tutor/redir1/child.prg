
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

//CHILD:
//stdout-ra echo-zza,
//amit stdin-ból olvas.

*****************************************************************************
function main()

local bs:=32,nb
local buf:=replicate(a" ",bs)

    ? "child-1"
 
    while( 0<(nb:=fread(0,@buf,bs)) )
        ?? left(buf,nb)
        sleep(10)
    end

    ? "child-2"
 
    return NIL


*****************************************************************************
