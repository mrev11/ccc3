
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

#include "directry.ch"

*****************************************************************************
function main(fspec)

local fspec1,dir,strfrom,strto

    set dosconv off

    dir:=directory(fspec,"H")
    if( len(dir)!=1 )
        ? fspec, @"not found"
        ?
        quit
    end

    strfrom:=fext(fspec)
    strto:="-"+dtos(dir[1][F_DATE])
    fspec1:=strtran(fspec,strfrom,strto)+strfrom
    frename(fspec,fspec1)
    
    return NIL


*****************************************************************************
function fext(name) // .ext
local extpos:=rat(".",name)
local bslpos:=rat(dirsep(),name)
    if( extpos>bslpos )
        return alltrim(substr(name,extpos))
    end
    return "."


*****************************************************************************
