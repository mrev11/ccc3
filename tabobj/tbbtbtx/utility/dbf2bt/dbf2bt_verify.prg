
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

#include "table.ch"

****************************************************************************
function main(fspec)

local dbf,tab,n

    //set dosconv fileshare

    dbf:=dbaseiiiNew()
    dbf:open(fspec)

    tab:=tabNew( fspec::fname::upper  )
    tabPath(tab,fpath(fspec))
    for n:=1 to len(dbf:dbstruct)
        tabAddColumn(tab,dbf:dbstruct[n])
    next
    tabCreate(tab)
    tabOpen(tab)
        

    if( dbf:reccnt != tabLastrec(tab) )
        ? "ERROR"
    end
    ? "     ", fspec::padr(32), dbf:reccnt, tabLastrec(tab)


****************************************************************************
function fname(name)   // name
local extpos:=rat(".",name)
local bslpos:=rat(dirsep(),name)
    if( extpos>bslpos )
        name:=substr(name,bslpos+1,extpos-bslpos-1)
    else
        name:=substr(name,bslpos+1)
    end
    return alltrim(name)


****************************************************************************
function fpath(name) // path
local bslpos:=rat(dirsep(),name)
    if( 0<bslpos )
        return left(name,bslpos-1)
    end
    return ""


****************************************************************************

//a dbaseiii konyvtar browse-olasa nem kell

function _clp_brwsetfocus(int)
function _clp_brwarray(int)
function _clp_brwarraypos(int)
function _clp_brwmenu(int)
function _clp_brwcreate(int)
function _clp_maxcol(int)
function _clp_brwshow(int)
function _clp_brwablock(int)
function _clp_brweditcell(int)
function _clp_brwhide(int)
function _clp_maxrow(int)
function _clp_brwloop(int)
function _clp_brwcolumn(int)
function _clp_brwmenuname(int)


