
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

function memotran(txt,repl)

    if( txt==NIL )
        //semmi

    elseif(  valtype(txt)=="C" )
        if( repl==NIL )
            repl:=";"
        end
        txt::=strtran(chr(13),"")
        txt::=strtran(chr(10),repl)

    elseif( valtype(txt)=="X" )
        if( repl==NIL )
            repl:=a";"
        end
        txt::=strtran(bin(13),a"")
        txt::=strtran(bin(10),repl)

    else
        argerror(*)
    end

    return txt

// !(valtype(txt)$"UXC") eseten argument error-t dob
