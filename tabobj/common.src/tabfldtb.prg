
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

//TARTALOM  : alias->field kezeles
//STATUS    : kozos, DBFNTX-ben nem kell
//
//function tabSetFieldTable(table)
//function tabDeleteFieldTable(table)

#include "tabobj.ch"

//Ezek a fuggvenyek az alias->field mezohivatkozasok
//CCC-beli kezelesehez kellenek. Clipperben nem kell.

***************************************************************************
function tabSetFieldTable(table)
local aliasname:=tabAlias(table)
local column:=tabColumn(table),n,col

    for n:=1 to len(column)
        col:=column[n]
        _field_insert(aliasname,col[COL_NAME],col[COL_BLOCK])  //C++-ban
        //? "insert", aliasname, col[COL_NAME]
    next
    return NIL

***************************************************************************
function tabDeleteFieldTable(table)
local aliasname:=tabAlias(table)

    _field_delete(aliasname)  //C++-ban
    //? "delete", aliasname
    return NIL

***************************************************************************
