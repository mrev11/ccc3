
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

#include "savex.ch"
#include "statvar.ch"


******************************************************************************    
function sortNev(brw)
local arr:=brwArray(brw)
    asort(arr,,,{|x,y|x[IDX_FILE]<y[IDX_FILE]})
    brw:refreshAll()
    return NIL


******************************************************************************    
function sortBaseName(brw)
local arr:=brwArray(brw)
    asort(arr,,,{|x,y|fnameext(x[IDX_FILE])>fnameext(y[IDX_FILE])})
    brw:refreshAll()
    return NIL


******************************************************************************    
function sortIdo(brw)
local arr:=brwArray(brw)
    if( "S"$s_compmode )
        asort(arr,,,{|x,y|x[IDX_SAVE]>y[IDX_SAVE]})
    else
        asort(arr,,,{|x,y|x[IDX_WORK]>y[IDX_WORK]})
    end
    brw:refreshAll()
    return NIL


******************************************************************************    
function sortMeret(brw)
local arr:=brwArray(brw)
    asort(arr,,,{|x,y|x[IDX_SIZE]>y[IDX_SIZE]})
    brw:refreshAll()
    return NIL


******************************************************************************    
