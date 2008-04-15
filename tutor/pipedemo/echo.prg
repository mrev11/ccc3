
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

function main()

local buf,n:=0,nbyte

    set printer to echo.log
    set printer on
    

    buf:=replicate(x"20",32) 
    nbyte:=fread(0,@buf,32) 
    ? ++n, nbyte, upper(buf)
 
    while( nbyte>0 )
        buf:=replicate(x"20",32) 
        nbyte:=fread(0,@buf,32) 
        ? ++n, nbyte, upper(buf)
    end
    
    ? "Kilép"
 
    return NIL
    