
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


function _zedit_toascii(this)
local clp, n 
    if( this:markflg )
        this:cut(.f.) 
        clp:=this:clipboard 
        
        for n:=1 to len(clp)
            clp[n]::=codeset_letter_latin2_to_ascii
        next
        
        this:clipboard:=clp
        this:paste
    end 
 

function _zedit_tolatin2(this)
local clp, n 
    if( this:markflg )
        this:cut(.f.) 
        clp:=this:clipboard 
        
        for n:=1 to len(clp)
            clp[n]::=codeset_letter_and_box_utf8_to_latin2
        next
        
        this:clipboard:=clp
        this:paste
    end 
 
