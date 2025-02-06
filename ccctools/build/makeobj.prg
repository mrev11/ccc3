
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
function makeobj(deplist)  //object előállítása (egyenként)

local target:=deplist[1] 
local depend:=deplist[2]  
local objdir:=buildenv_obj() 
local ttarget,tdepend
local update:=.f.,torun
local n,p1,p2,p3

    if( fext(target)==".obj" )
        target:=objdir+dirsep()+fname(target)+fext(target)
    end

    ttarget:=ftime(target) 
    if( ttarget==NIL )
        ttarget:=""
    end

    if( s_debug() )
        ? target, "["+ttarget+"]"
    end
 
    for n:=2 to len(deplist)
        depend:=deplist[n] 
        update:=verifdep(ttarget,depend).or.update
    next

    if( s_debug() )
        ? 
    end
    
    if( update )
        
        torun:=buildenv_bat()+dirsep()
        torun+=strtran(fext(deplist[2])+"2"+fext(deplist[1]),".","")
        torun+=s_batext()

        if( !file(torun) )
            ? "["+torun+"]", @"does not exist"
            ?
            errorlevel(1)
            quit 
        end

        p1:=fname(deplist[1])
        p2:=fpath0(deplist[2]); p2:=if(empty(p2),".",p2)
        p3:=deplist[2]
        for n:=3 to len(deplist)
            p3+=" "+deplist[n]
        next
    
        run1(torun+" "+p1+" "+p2+" '"+p3+"'" )  // p3 egyben
    end

 
****************************************************************************

