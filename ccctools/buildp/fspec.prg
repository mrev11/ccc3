
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

****************************************************************************
function fnameext(name)   // name.ext
local bslpos:=rat(dirsep(),name)
    name:=substr(name,bslpos+1)
    return alltrim(name)


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
function fpath0(name) // path
local bslpos:=rat(dirsep(),name)
    if( 0<bslpos )
        return left(name,bslpos-1)
    end
    return ""


****************************************************************************
function fpath(name) // path\
local bslpos:=rat(dirsep(),name)
    if( 0<bslpos )
        return left(name,bslpos)
    end
    return ""

****************************************************************************
function fext(name) // .ext
local extpos:=rat(".",name)
local bslpos:=rat(dirsep(),name)
    if( extpos>bslpos )
        return alltrim(substr(name,extpos))
    end
    return "."


****************************************************************************
function fext0(name) // ext
    return substr(fext(name),2)

 
****************************************************************************
 