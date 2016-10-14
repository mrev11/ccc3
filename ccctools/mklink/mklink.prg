
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
function main()
local d,n,exe,lnk
local dirlnk

    d:=directory("*.exe")
    
    asort(d,,,{|x,y|x[1]<y[1]})

    for n:=1 to len(d)

        exe:=d[n][1]
        lnk:=left(exe,len(exe)-4)

        dirlnk:=directory(lnk,"@L")
        if( len(dirlnk)<=0 ) 
            run("ln -s "+exe+" "+lnk)
            dirlnk:=directory(lnk,"@L")
        end

        if( len(dirlnk)!=1 ) 
        elseif( !"L"$dirlnk[1][F_ATTR] ) 
        elseif( len(dirlnk[1])<F_LINK )
        else
            ?? lnk, "->", dirlnk[1][F_LINK];?
        end
    next
    

*****************************************************************************
