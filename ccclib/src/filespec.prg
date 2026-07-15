
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

namespace filespec

// basename     : man 1 basename
// path         : az utolso dirsep-ig tarto resz, a vegen dirsep (Windowson ':' is dirsep)
// nameext      : fspec-bol elhagyva a path (esetleg ures)
// name         : nameext-bol elhagyva az extension
// extension    : nameext-bol elhagyva a name ('.' resze az extension-nek)


// ezek teljesulnek
// fspec    == path(fspec)+nameext(fspec)
// nameext  == name(fspec)+extension(fspec)


******************************************************************************************
static function lastsep(fspec)
local sep:=0
    sep::=max(rat("/",fspec))
    sep::=max(rat("\",fspec))
#ifdef WINDOWS
    sep::=max(rat(":",fspec))
#endif
    return sep


******************************************************************************************
function basename(fspec,ext)
local bn,xp
    bn:=fspec::substr(lastsep(fspec)+1)
    if( ext!=NIL )
        xp:=rat(ext,bn)
        if( xp-1+len(ext)==len(bn) )
            bn::=left(xp-1)
        end
    end
    return bn


******************************************************************************************
function path(fspec)
    return fspec::substr(1,lastsep(fspec))


******************************************************************************************
function nameext(fspec)
    return fspec::substr(lastsep(fspec)+1)


******************************************************************************************
function name(fspec)
local sep:=lastsep(fspec)
local dot:=rat(".",fspec)
    return fspec::substr(sep+1,if(dot>sep,dot-sep-1,NIL))


******************************************************************************************
function extension(fspec)
local sep:=lastsep(fspec)
local dot:=rat(".",fspec)
    return if(dot>sep,substr(fspec,dot),"")


******************************************************************************************
function absolute(fspec)
    if( empty(fspec) )
        return .f.
    elseif( fspec[1]$"/\" )
        return .t.
#ifdef WINDOWS
    elseif( isalpha(fspec[1]) .and. (at(":\",fspec)==2 .or. at(":/",fspec)==2) )
        return .t.
#endif
    end
    return .f.


******************************************************************************************
function relative(fspec)
    return !absolute(fspec)


******************************************************************************************
function drive(fspec)
#ifdef WINDOWS
    if( len(fspec)>=2 .and. isalpha(fspec[1]) .and. fspec[2]==":" )
        return fspec[1]
    end
#endif
    return ""


******************************************************************************************

