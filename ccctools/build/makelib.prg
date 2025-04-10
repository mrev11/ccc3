
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


#define LOWER(x) (x)

****************************************************************************
function makelib(libnam,object)  //lib-et az objectekből

local target:=buildenv_obj()+dirsep()+libnam+".lib",ttarget 
local depend,tdepend,update:=.f.
local torun:=buildenv_bat()+dirsep()+"obj2lib"+s_batext()
local objdir:=LOWER(buildenv_obj()), n 
local libdir:=buildenv_libdir()
local objlist
local trginst

    if( !file(torun) )
        ? "["+torun+"]", @"does not exist"
        ?
        errorlevel(1)
        quit 
    end
    
    torun+=" "+libnam
 
    ttarget:=ftime(target) 
    if( ttarget==NIL )
        ttarget:=""
    end

    if( s_debug() )
        ? target, "["+ttarget+"]"
    end
    
    for n:=1 to len(object)
    
        depend:=object[n]
        depend:=objdir+dirsep()+depend+".obj"
        update:=verifdep(ttarget,depend).or.update
    next

    if( s_debug() )
        ? 
    end
    
    if( update )
    
        #ifdef _UNIX_
            for n:=1 to len(object)
                torun+=" "+object[n]
            next

        #else

            //Windows hiba: csak rövid parancsok kezelésére képes.

            objlist:=""
            for n:=1 to len(object)
                objlist+=object[n]+".obj"+endofline()
            next
            memowrit(objdir+dirsep()+"objects-"+libnam,objlist)
        #endif

        run1 (torun)

        if( !empty(libdir) )
            trginst:=libdir+dirsep()+libnam+".lib"
            ferase( trginst )
            filecopy(target,trginst+".tmp")
            filemove(trginst+".tmp",trginst)
        end
    end

 
****************************************************************************
