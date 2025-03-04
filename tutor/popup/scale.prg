
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

#define PRINT(x)    ? #x, x


function scale()
local scale,n


    scale:=" "    
    for n:=1 to 20
        scale+=str(10*n,10)
    next
    @ 0,0 say scale color "w+/n"

    scale:="0123456789"::replicate(20)::left(maxcol()+1)    
    @ 1,0 say scale color "w+/n"

    for n:=2 to maxrow()
        @ n,0 say str(n,2)+" "+replicate( chr(asc("A")+(n%26)),maxcol()-3)
    next

