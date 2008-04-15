
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

//TARTALOM  : append record (azonos struktúrájú másik filéből)
//STATUS    : közös
//
//function tabAppendRecord(table,tabfrom,usrblk,flag)


#include "tabobj.ch"


******************************************************************************
function tabAppendRecord(table,tabfrom,usrblk,flag)

local colto:=tabColumn(table)    
local colfr:=tabColumn(tabfrom)    
local nc, n, result

    if( (nc:=len(colto))!=len(colfr) )
        taberrOperation("tabAppendRecord")
        taberrDescription(@"different number of fields")
        tabError(table)
    end

    if( result:=tabAppend(table,usrblk,flag) )
        for n:=1 to nc
            eval(colto[n][COL_BLOCK], eval(colfr[n][COL_BLOCK]) )
        next
    end

    return result


******************************************************************************
