
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
function params() //paraméterek a fordítónak/linkernek

local txt,set,lst,n

    //Ez a program összegyűjti az include és library paramétereket, 
    //és elhelyezi egy-egy környezeti változóban úgy (blank elválasztó),
    //hogy később batch filéből shiftekkel könnyen fel lehessen dolgozni.
    //A használt környezeti változók:
    //
    // BUILD_INC : include directoryk listája
    // BUILD_LPT : library directoryk listája
    // BUILD_LIB : library filé listája

    //include directories
    
    txt:=""
    txt+=if(s_srcdir()==NIL,".",s_srcdir())+";"
    txt+=if(s_incdir()==NIL,"",s_incdir())+";"
    txt+=buildenv_inc()+";"
    txt+=getenv("include")+";"
    txt:=strtran(txt,","," ")  //","->" "
    txt:=strtran(txt,";"," ")  //";"->" "
    #ifdef _UNIX_
    txt:=strtran(txt,":"," ")  //":"->" "
    #endif
    buildenv_inc(txt)
    //memowrit(buildenv_obj()+dirsep()+"buildi",txt)
 
 
    //library directories 

    txt:=""
    txt+=if(s_libdir()==NIL,"",s_libdir())+";"
    txt+=buildenv_lpt()+";"
    txt+=getenv("lib")+";"
    txt:=strtran(txt,","," ")  //","->" "
    txt:=strtran(txt,";"," ")  //";"->" "
    #ifdef _UNIX_
    txt:=strtran(txt,":"," ")  //":"->" "
    #endif
    buildenv_lpt(txt)
    //memowrit(buildenv_obj()+dirsep()+"buildp",txt)


    //library files

    txt:=""
    txt+=if(s_libfil()==NIL,"",s_libfil())+";"
    txt+=buildenv_lib()+";"
    txt:=strtran(txt,","," ")  //","->" "
    txt:=strtran(txt,";"," ")  //";"->" "
    buildenv_lib(txt)
    s_libspec(search_library())
    buildenv_lib(s_libspec())
    s_libspec(split(s_libspec()," "))
    
    return NIL


****************************************************************************
