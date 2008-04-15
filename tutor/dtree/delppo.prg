
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
function main(rootdir)

    set dosconv on

    if( rootdir==NIL )
        rootdir:=""
    elseif( !right(rootdir,1)$"\" )
        rootdir+="\"
    end
    delppo(rootdir)
    return NIL
    

*****************************************************************************
function delppo(dir)    

local d:=directory(dir+"*.*","D")
local d1:={}, n
local t, i

    for n:=1 to len(d)

        if( "D"$d[n][F_ATTR] .and.;
            !"L"$d[n][F_ATTR] .and.;
            !"."==d[n][F_NAME] .and.!".."==d[n][F_NAME]  )

            if( "ppo"==lower(d[n][F_NAME]) )
                //ennek a belsejét le kell törölni
                t:=directory(dir+"ppo\*.*")
                for i:=1 to len(t)
                    ? dir+"PPO\"+t[i][F_NAME]
                    ferase( dir+"PPO\"+t[i][F_NAME] )
                next
            else
                //ebbe be kell menni és rekurzívan folytatni
                //egyelőre csak megjegyezzük a nevét
                aadd(d1,d[n][F_NAME])
            end
        end
    next
    
    d:=NIL //átadjuk a szemétgyűjtésnek

    for n:=1 to len(d1)
        delppo(dir+d1[n]+"\")
    next

    return NIL


*****************************************************************************

    