
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

#include "page.ch"

*************************************************************************
function readpage(filnam)

local page:=array(TOT_ROW)
local pgestr:=readmask(filnam)
local pgelen:=len(pgestr)
local rowpos,n

    for n:=1 to TOT_ROW
        if( (rowpos:=(n-1)*TOT_COL*4+1)<pgelen )
            page[n]:=substr(pgestr,rowpos,TOT_COL*4)
        else
            page[n]:=emprow()
        end
    next

    return page


*************************************************************************
function emprow() // egy ures sor (szinkoddal)
static empty_row
    if( empty_row==NIL )
        empty_row:=replicate(empchr(),TOT_COL)
    end
    return empty_row


*************************************************************************
function empchr() // egy ures karakter (szinkoddal)
static empty_chr
    if( empty_chr==NIL )
        empty_chr:=screencompose(chr(32),bin(7),bin(0))
    end
    return empty_chr


*************************************************************************
