
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
function pack(dir,dirnames,filnames)

local d:=directory(dir+dirsep()+fullmask(),"DHL")
local d1:={},n,x,a

    for n:=1 to len(d)

        x:=d[n][F_NAME]
        a:=d[n][F_ATTR] 
 
        if( x=="." )
            //kihagy

        elseif( x==".." )
            //kihagy

        elseif( "L"$a )
            //kihagy

        elseif( !"D"$a ) //közönséges filé
            if( 0==ascan(filnames,{|p|like(p,lower(x))}) )
                ?? dir+dirsep()+x+endofline()
            end

        else  //közönséges directory
            if( 0==ascan(dirnames,{|p|like(p,lower(x))}) )
                //ebbe be kell menni és rekurzívan folytatni
                //egyelőre csak megjegyezzük a nevét
                aadd(d1,x)
            end
        end
    next
    
    d:=NIL //átadjuk a szemétgyűjtésnek

    for n:=1 to len(d1)
        pack(dir+dirsep()+d1[n],dirnames,filnames)
    next

    return NIL


*****************************************************************************
