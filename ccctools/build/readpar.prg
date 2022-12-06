
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
function readpar(parfil,opt,optx)
local par:=memoread(parfil),n,p,i

    if(empty(par))
        //2006.09.26
        //Először a megadott directoryban keres,
        //ha ott nincs, akkor megnézi a build directoryban.
        par:=memoread(buildenv_bat()+dirsep()+parfil)
    end

    if(s_debug())
        if( empty(par) )
            ?? "Build parfile empty:", parfil;?
        else
            ?? "Build parfile:", parfil;?
        end
    end

    par:=strtran(par,chr(13),"")
    par:=split(par,chr(10)) //sorokra bontva

    for n:=1 to len(par)
        p:=par[n]
        if( "#"$p )
            p:=left(p,at("#",p)-1) 
        end

        p:=split(p," ") //szavakra bontva
        for i:=1 to len(p)
            if( !empty(p[i]) )
                aadd(opt,NIL)
                ains(opt,++optx)
                opt[optx]:=p[i]
            end
        next
    next
    return NIL


****************************************************************************
