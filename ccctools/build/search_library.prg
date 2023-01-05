
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
function search_library()

//megkeresi a lib-eket libpath-ban,
//így a linker paraméterezése egyszerűbb

local dirlist:=split(buildenv_lpt()," ")
local liblist:=split(buildenv_lib()," ")
local sharing:=LOWER(buildenv_shr())  //"shared" or "static" libraries

local n,i,txt:=""
local f0,f1,f2,f3,pf1,pf2,pf3


    for n:=1 to len(liblist)

        if( empty(f0:=liblist[n]) )
            loop
        end

        if( ".lib"==f0::right(4) .or. ".a"==f0::right(2) .or. ".so"==f0::right(3) )
            f1:=f0
            f2:=f0
            f3:=f0
        else
            f1:=f0+".lib"                           //DOS name
            //f2:=fpath(f0)+"lib"+fname(f0)+".a"    //UNIX name (static lib)
            //f3:=fpath(f0)+"lib"+fname(f0)+".so"   //UNIX name (shared lib)
            f2:=fpath(f0)+"lib"+fnameext(f0)+".a"   //UNIX name (static lib)
            f3:=fpath(f0)+"lib"+fnameext(f0)+".so"  //UNIX name (shared lib)
        end


        for i:=0 to len(dirlist)

            if( i<=0 )
                pf1:=f1
                pf2:=f2
                pf3:=f3
            else
                if( empty(dirlist[i]) )
                    loop
                end

                pf1:=dirlist[i]+dirsep()+f1
                pf2:=dirlist[i]+dirsep()+f2
                pf3:=dirlist[i]+dirsep()+f3
            end

            //? file(pf1),"["+pf1+"]"
            //? file(pf2),"["+pf2+"]"
            //? file(pf3),"["+pf3+"]"

            if( "static"$sharing )

                //a "static" libet preferálja (BUILD_SHR=static)

                if( file(pf1) )
                    txt+=pf1+" "
                    exit
                elseif( file(pf2) )
                    txt+=pf2+" "
                    exit
                elseif( file(pf3) )
                    txt+=pf3+" "
                    exit
                end

            else

                //a "shared" libet preferálja (default)

                if( file(pf3) )
                    txt+=pf3+" "
                    exit
                elseif( file(pf1) )
                    txt+=pf1+" "
                    exit
                elseif( file(pf2) )
                    txt+=pf2+" "
                    exit
                end
            end
        next

        if( i>len(dirlist) )
            if( f0[1..2]=="-l" )
                txt+=f0+" " //eredeti alak
            else
                txt+="-l"+f0+" "
            end
        end
    next

    return txt


****************************************************************************
