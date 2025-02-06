
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
function makeexe(exenam,object) //exe-t az objectekből

local target:=buildenv_exe()+dirsep()+exenam+".exe",ttarget 
local depend,tdepend,update:=.f.
local torun:=buildenv_bat()+dirsep()+"obj2exe"+s_batext()
local objdir:=LOWER(buildenv_obj()), n 
local bindir:=buildenv_bindir()
local objlist, xobj

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
    
    for n:=0 to len(object)
    
        if( n==0 )
            depend:=exenam
        else
            depend:=object[n]
        end
        
        depend:=objdir+dirsep()+depend+".obj"
        update:=verifdep(ttarget,depend).or.update
    next
    
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
        torun+=" "+exenam

        #ifdef _UNIX_
            for n:=1 to len(object)
                torun+=" "+object[n]
            next

        #else

            //Windows hiba: csak rövid parancsok kezelésére képes.
            
            objlist:=""
            for n:=0 to len(object)

                xobj:=objdir+dirsep()
                xobj+=if(n==0,exenam,object[n])
                xobj+=".obj"
                objlist+=xobj+endofline()
            next
            memowrit(objdir+dirsep()+"objects-"+exenam,objlist)
        #endif

        run1 (torun)

        if( !empty(bindir) )
            ferase( bindir+dirsep()+exenam+".exe")
            filecopy(target,bindir+dirsep()+exenam+".exe")
        end
    end


****************************************************************************
