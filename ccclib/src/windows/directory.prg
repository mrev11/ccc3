
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
 
***************************************************************************
function directory(mask,attr,binopt) //binopt==.t. -> binary filénevek

local dlist:=array(32),dlist_size:=0

local fitem
local adddir:=.f.
local addhid:=.f.
local addsys:=.f.
local addlnk:=.f.

static mutex:=thread_mutex_init()

    if( empty(mask) )
        mask:=a"*"
    else
        mask:=convertfspec2nativeformat(mask)
    end

    if( attr!=NIL )
        attr:=upper(attr)
        adddir:= !"-D"$attr .and. "D"$attr
        addhid:= !"-H"$attr .and. "H"$attr
        addsys:= !"-S"$attr .and. "S"$attr
        addlnk:= !"-L"$attr .and. "L"$attr
    end
 
    thread_mutex_lock(mutex)
    
    fitem:=findfirstx(mask) //binary filénév
    
    while( NIL!=fitem )
    
        attr:=fitem[F_ATTR]
    
        if( "D"$attr .and. !adddir )
            //kihagy
        elseif( "S"$attr .and. !addsys )
            //kihagy
        elseif( "H"$attr .and. !addhid )
            //kihagy
        elseif( "L"$attr .and. !addlnk )
            //kihagy
        else
            //bevesz
            
            if( binopt!=.t. )
                fitem[F_NAME]:=bin2str(fitem[F_NAME])
            end

            if( dlist_size>=len(dlist) )
                asize(dlist,dlist_size+32)
            end
            dlist[++dlist_size]:=fitem
        end
        
        fitem:=findnextx() //binary filénév
    end

    thread_mutex_unlock(mutex)

    return asize(dlist,dlist_size)


***************************************************************************

 