
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


#ifdef _CCC2_

#include "charconv.ch"

static function xupper(s) 
    return _charconv(s,CHARTAB_LOWER2UPPER)

static function xlower(s) 
    return _charconv(s,CHARTAB_UPPER2LOWER) 

#define UPPER(x) xupper(x)
#define LOWER(x) xlower(x) 

#endif



function _zedit_chcase(this,flag)

local clp, n 
 
    if( this:markflg )
        this:cut(.f.) 
        clp:=this:clipboard 
        
        for n:=1 to len(clp)
            clp[n]:=if(flag,UPPER(clp[n]),LOWER(clp[n]))
        next
        
        this:clipboard:=clp
        this:paste
    end 
 
    return NIL 

