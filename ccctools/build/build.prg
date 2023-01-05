
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


#define VERSION "1.6.2"

#define LOWER(x) (x)

static maxthread:=4
static pool


****************************************************************************
function main()

local opt:=aclone(argv()),n

#define OPTION(x)  x==left(opt[n],2) 
#define VALUE()    substr(opt[n],3)

    if( !file(buildenv_bat()+dirsep()+"multithread_support") )
        maxthread:=1
    elseif( 1<=val(buildenv_thr())  )
        maxthread:=val(buildenv_thr())
    end

    if( !s_quiet() )
        ?? @"CCC Program Builder "+VERSION+" Copyright (C) ComFirm Bt."
        ?? " (Thr"+alltrim(str(maxthread))+")"
        ?
    end


    for n:=1 to len(opt)
        opt[n]:=procpar(opt[n])
        
        if( OPTION("-l") )
            s_libnam(VALUE())
            s_shared(.f.)
 

        elseif( OPTION("-s") )
            s_libnam(VALUE())
            s_shared(.t.)
 

        elseif( OPTION("-d") )
            if( s_srcdir()==NIL )
                s_srcdir(VALUE())
            else
                s_srcdir(s_srcdir()+","+VALUE())
            end


        elseif( OPTION("-i") )
            if( s_incdir()==NIL )
                s_incdir(VALUE())
            else
                s_incdir(s_incdir()+","+VALUE())
            end


        elseif( OPTION("-p") )
            if( s_libdir()==NIL )
                s_libdir(VALUE())
            else
                s_libdir(s_libdir()+","+VALUE())
            end
 

        elseif( OPTION("-b") )
            if( s_libfil()==NIL )
                s_libfil(VALUE())
            else
                s_libfil(s_libfil()+","+VALUE())
            end


        elseif( OPTION("-x") .or.  OPTION("-m") )
            if( s_main()==NIL )
                s_main(VALUE())
            else
                s_main(s_main()+","+VALUE())
            end

        elseif( OPTION("-o") )
            omitted_hash()[VALUE()::strtran("\","/")]:=.t.

        elseif( OPTION("-h") )
            usage()
            quit

        elseif( OPTION("-q") )
            s_quiet(.t.)

        elseif( OPTION("-v") )
            s_version(.t.)

        elseif( "--debug"==opt[n] )
            s_debug(.t.)

        elseif( "--dry"==opt[n] )
            s_debug(.t.)
            s_dry(.t.)

        elseif( "@"==left(opt[n],1) )
            readpar(substr(opt[n],2),opt,n)

        elseif( "="$opt[n] )
            putenv(opt[n])
 
        else
            ? @"Invalid switch: ", opt[n]
            usage()
            errorlevel(1)
            quit
        end
    next
    
    //compatibility
    if( "on"$LOWER(buildenv_dbg()) )
        s_debug(.t.)
    end
    if( "debug"$LOWER(buildenv_dbg()) )
        s_debug(.t.)
    end
    if( "dry"$LOWER(buildenv_dbg()) )
        s_debug(.t.)
        s_dry(.t.)
    end
    
    if( s_version() )
        quit
    end
    
    rules_from_build_bat()
    extension_types()

    srcroot()
    params()

    if( s_debug() )
        maxthread:=1
        buildenv_thr("1")
        list_buildenv()
    end

    pool:=threadpoolNew(maxthread)
    
    build()
    
    ?


****************************************************************************
static function usage()
    ? @"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"
    ?
    return NIL



****************************************************************************
static function build()
    
local dir:={}     //forrásdirektorik listája
local obj:={}     //elsődleges források (prg,cpp,c,asm)
local lib:={}     //main-t nem tartalmazó objectek 
local mmd:={}     //main-t tartalmazó objectek (csak prg-ből)
local todo:={}    //mit kell csinálni

local d1,f,o,n,i,txt,dep


    if( s_main()!=NIL )
        mmd:=xsplit(LOWER(s_main()),",;")
    end


    if( s_srcdir()!=NIL  )
        dir:=xsplit(s_srcdir(),",;") //a felsorolt directorykból
    else
        dir:={"."} //csak az aktuális directoryból
    end

    for n:=1 to len(dir)
        
        ?? "",dir[n]

        d1:=directory(dir[n]+dirsep()+"*.*","H") 
 
        for i:=1 to len(d1)
            
            f:=LOWER(d1[i][1])
            
            if( fext(f)+"."$s_primary()  )
                if( omitted_hash()[strtran(dir[n]+dirsep()+f,"\","/")]!=NIL )
                    //kihagy
                else
                    aadd(obj,dir[n]+dirsep()+f)
                end
            end
            //vigyazat: tdc$primary and tdc$resource!
            if( fext(f)+"."$s_resource() )
                resource_hash()[f]:=dir[n]+dirsep()+f
            end
        next
    next
    ?

    //megvannak az elsődleges források (prg,cpp,c,asm)
    //(elsődleges forrás az, amiből object készíthető)

    for n:=1 to len(obj)
    
        f:=obj[n]
        o:=fname(f)
        txt:=memoread(f)

        if( 0!=ascan(mmd,{|m|m==LOWER(o)}) )
            //már benn van
        elseif( fext(f)==".prg" .and. "function main("$txt )
            if( s_main()==NIL )
                aadd(mmd,o)
            end
        else
            aadd(lib,o)
        end
 
        dep:={o+".obj",f} 
        for i:=2 to len(dep)
            if( i==2 )
                //txt: már beolvasta
            elseif(i>1024)
                ? "recursive dependencies:",dep
                ?
                quit
            else
                txt:=memoread(dep[i])
            end
            search_include(txt,dep,dir,todo) //hosszabíthatja dep-et
        end
        
        aadd(todo,dep)
    next
    
    normalize(todo)
    
    asort(todo,,,{|x,y|psort(x,y)})
    //most megvan, hogy mit kell csinálni


    if( s_debug() )
        ? "main:", mmd
        ? "lib :", lib
        ?
        for n:=1 to len(todo)
            ? todo[n]
        next
        ?
    end
    
    ferase("error")
    for n:=1 to len(todo)
        if( !fext(todo[n][1])==".obj" )
            pool:addjob( {{|i|makeobj(todo[i])},n}  )
        end
    next
    pool:wait

    for n:=1 to len(todo)
        if( fext(todo[n][1])==".obj" )
            pool:addjob( {{|i|makeobj(todo[i])},n}  )
        end
    next
    pool:wait

    //itt már megvan az összes object
    
    if( s_libnam()!=NIL )
        makelib(s_libnam(),lib)
        
        if( s_shared()==.t. .and. dirsep()=="/" )
            makeso(s_libnam(),lib)
        end
        
        for n:=1 to len(mmd)
            pool:addjob( {{|m,l|makeexe1(m,l)}, mmd[n], s_libnam()} )
        next
    else
        for n:=1 to len(mmd)
            pool:addjob( {{|m,l|makeexe(m,l)}, mmd[n], lib} )
        next
    end
    pool:wait


****************************************************************************

