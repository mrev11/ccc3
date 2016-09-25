
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

static objdir

*****************************************************************************
function main(rootdir)

    set dosconv off

    objdir:=getenv("CCCBIN")

    if( empty(objdir) )
        ? "CCCBIN not set" 
        ?  
        quit
    end
    objdir:="obj"+objdir

    delobj("")
    ?
    return NIL
    

*****************************************************************************
function delobj(dir)    

local d:=directory(dir+fullmask(),"DH")
local d1:={}, n
local dname,t,i

    for n:=1 to len(d)
    
        dname:=alltrim(d[n][F_NAME])
        #ifdef WINDOWS
            dname:=lower(dname)
        #endif

        if( "D"$d[n][F_ATTR] .and.; 
            !"L"$d[n][F_ATTR] .and. !"."==dname .and. !".."==dname  )
            
            if( 1==at(objdir,dname) )
                //ennek a belsejét le kell törölni

                t:=directory(dir+dname+dirsep()+fullmask(),"H")
                for i:=1 to len(t)
                    ? dir+dname+dirsep()+t[i][F_NAME]
                    ferase( dir+dname+dirsep()+t[i][F_NAME] )
                next
            else
                //ebbe be kell menni és rekurzívan folytatni
                //egyelőre csak megjegyezzük a nevét
                aadd(d1,dname)
            end
        end
    next
    
    d:=NIL //átadjuk a szemétgyűjtésnek

    for n:=1 to len(d1)
        delobj(dir+d1[n]+dirsep())
    next

    return NIL


*****************************************************************************

    