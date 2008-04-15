
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

//TARTALOM  : save/restore/filter függvények
//STATUS    : közös, ifdef
//
//function tabSave(table)           //elmenti:{control,filter,position}
//function tabRestore(table,state)  //beállítja:{control,filter,position}
//function tabFilter(table,filter)  //filter beállítása/lekérdezése

#include "tabobj.ch"

******************************************************************************
function tabSave(table) //elmenti:{control,filter,position}
    return {tabControlIndex(table),tabFilter(table),tabPosition(table)}


******************************************************************************
function tabRestore(table,state)  //beállítja:{control,filter,position}
    tabControlIndex(table,state[1])
    tabFilter(table,state[2]) 
    tabGoto(table,state[3])
    return state

******************************************************************************
function tabFilter(table,filter) //filter beállítása/lekérdezése
local old:=table[TAB_FILTER]

    if( filter==NIL )

    elseif( empty(filter) )
        table[TAB_FILTER]:=NIL

    elseif( valtype(filter)=="B" )
        table[TAB_FILTER]:=filter
    end
    return if(old==NIL,0,old)

******************************************************************************
