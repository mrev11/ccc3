
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

//table definition script (tds) -> prg

//Beolvas egy tds (tableentity definition script) filét,
//abból felépít egy DOM-ot, majd kódot generál. A dom2prg 
//kódgenerátor ugyanaz, mint a ted2prg programban.

******************************************************************************
function main(fspec)

    if( NIL==fspec )
        usage()
    end

    //MSYS2 compatibility
    fspec::=strtran("/",dirsep())
    fspec::=strtran("\",dirsep())
    
    if( !file(fspec) )
        usage(fspec, "not found")
    end

    tdsutil.dom2prg(tdsutil.tds2dom(fspec),fspec)


******************************************************************************
static function usage(x1,x2,x3,x4)
local x:={x1,x2,x3,x4,NIL},n:=0

    if( x[1]==NIL )
        ? "Usage:","tds2prg","<fspec>"
    else
        ?
        while( x[++n]!=NIL  )
            ?? x[n],""
        next
    end
    ?
    errorlevel(1)
    quit


******************************************************************************
