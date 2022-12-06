
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
function makeexe1(mmod,libnam) //exe-t a main modulból + lib-ből

local target:=buildenv_exe()+dirsep()+mmod+".exe",ttarget 
local depend,tdepend,update:=.f.
local torun:=buildenv_bat()+dirsep()+"lib2exe"+s_batext()
local objdir:=buildenv_obj(), n 
local bindir:=buildenv_bindir()

    if( !file(torun) )
        ? "["+torun+"]", @"does not exist"
        ?
        errorlevel(1)
        quit 
    end
 
    ttarget:=ftime(target) 
    if( ttarget==NIL )
        ttarget:=""
    end

    if( s_debug() )
        ? target, "["+ttarget+"]"
    end

    
    depend:=mmod
    torun+=" "+depend
    depend:=objdir+dirsep()+depend+".obj"
    update:=verifdep(ttarget,depend).or.update
 
    depend:=libnam
    torun+=" "+depend
    depend:=objdir+dirsep()+depend+".lib"
    update:=verifdep(ttarget,depend).or.update
 
    for n:=1 to len(s_libspec())                         /**/
        if( s_libspec()[n]::right(4)==".lib" )           /**/
            depend:=s_libspec()[n]                       /**/
            update:=verifdep(ttarget,depend).or.update   /**/
        end                                              /**/
    next                                                 /**/

    if( s_debug() )
        ? 
    end
    
    if( update )
        run1 (torun)

        if( !empty(bindir) )
            ferase( bindir+dirsep()+mmod+".exe")
            filecopy(target,bindir+dirsep()+mmod+".exe")
        end
    end


 
****************************************************************************
