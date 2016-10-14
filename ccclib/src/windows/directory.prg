
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

#define PRINT(x) ? #x,x

 
***************************************************************************
function directory(mask,attr,binopt) //binopt==.t. -> binary filenev

local dlist:=array(32),dlist_size:=0

local handle
local fitem
local adddir:=.f. //include directory entries (default: no)
local addhid:=.f. //include hidden entries (default: no)
local addsys:=.f. //include system entries (default: no)
local addlnk:=.t. //include symlink/junction entries (default: yes)
local lnktrg:=.f. //link target in fitem[F_LINK] (default: no)

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
        addlnk:= !"-L"$attr
        lnktrg:= "@L"$attr
    end

    //PRINT(adddir)
    //PRINT(addhid)
    //PRINT(addsys)
    //PRINT(addlnk)
 
    fitem:=__findfirst(@handle,mask,binopt,lnktrg)
    
    while( NIL!=fitem )

        //a __find* megkulonbozteti 
        //a symlinket es a junctiont
        fitem[F_ATTR]::=strtran("J","L")
    
        attr:=fitem[F_ATTR]
    
        if( "D"$attr .and. !adddir )
            //? "kihagy-D"
        elseif( "S"$attr .and. !addsys )
            //? "kihagy-S"
        elseif( "H"$attr .and. !addhid )
            //? "kihagy-H"
        elseif( "L"$attr .and. !addlnk )
            //? "kihagy-L"
        else
            //bevesz

            if( dlist_size>=len(dlist) )
                asize(dlist,dlist_size+32)
            end
            dlist[++dlist_size]:=fitem
        end
        
        fitem:=__findnext(@handle)
    end

    //already closed
    //__findclose(@handle)

    return asize(dlist,dlist_size)


***************************************************************************

 