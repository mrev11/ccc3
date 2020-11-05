
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

static s_main    //main modulok
static s_libnam  //készítendő lib
static s_shared  //shared library flag
static s_srcdir  //itt keresünk forrásokat
static s_incdir  //átadjuk a fordítónak : srcdir,incdir,BUILD_INC
static s_libdir  //átadjuk a linkernek  : libdir,BUILD_LPT 
static s_libfil  //átadjuk a linkernek  : libfil,BUILD_LIB

static s_quiet   := .f.
static s_version := .f.
 
static s_debug:=.f.
static s_dry:=.f.
static s_primary   //kiszamitja s_rules-bol //:=".y.lem.lex.prg.cpp.c.asm.tds.tdc."
static s_resource  //kiszamitja s_rules-bol //:=".msk.mnt.cls.htm.pge.tdc"

static s_libspec   //lib specifikációk
 
static s_rules:={;
{".msk",".dlg"},;
{".msk",".pnl"},;
{".mnt",".gpi"},;
{".cls",".och"},;
{".msk",".say"},;
{".htm",".ctm"},;
{".msk",".wro"},;
{".pge",".out"},;
{".pge",".wro"},;
{".tdc",".ch" },;
{".asm",".obj"},;
{".c"  ,".obj"},;
{".cpp",".obj"},;
{".tds",".obj"},;
{".prg",".obj"},;
{".y"  ,".obj"},;
{".lem",".obj"},;
{".lex",".obj"},;
{".tdc",".obj"},;
{".obj",".lib"},;
{".obj",".exe"};
}

static resource_hash:=simplehashNew()
static omitted_hash:=simplehashNew()

#define VERSION "1.4.11"
#define LOWER(x) (x)


static mutex_count:=thread_mutex_init()
static cond_count:=thread_cond_init()
static thread_count:=0
static maxthread:=4

****************************************************************************
function main()

local opt:=aclone(argv()),n

#define OPTION(x)  x==left(opt[n],2) 
#define VALUE()    substr(opt[n],3)

    if( !file(getenv("BUILD_BAT")+dirsep()+"multithread_support") )
        maxthread:=1
    elseif( 1<=val(getenv("BUILD_THR"))  )
        maxthread:=val(getenv("BUILD_THR"))
    end

    if( !s_quiet )
        ?? @"CCC Program Builder "+VERSION+" Copyright (C) ComFirm Bt."
        ?? " (Thr"+alltrim(str(maxthread))+")"
        ?
    end


    for n:=1 to len(opt)
        opt[n]:=procpar(opt[n])
        
        if( OPTION("-l") )
            s_libnam:=VALUE()
            s_shared:=.f.
 

        elseif( OPTION("-s") )
            s_libnam:=VALUE()
            s_shared:=.t.
 

        elseif( OPTION("-d") )
            if( s_srcdir==NIL )
                s_srcdir:=VALUE()
            else
                s_srcdir+=","+VALUE()
            end


        elseif( OPTION("-i") )
            if( s_incdir==NIL )
                s_incdir:=VALUE()
            else
                s_incdir+=","+VALUE()
            end


        elseif( OPTION("-p") )
            if( s_libdir==NIL )
                s_libdir:=VALUE()
            else
                s_libdir+=","+VALUE()
            end
 

        elseif( OPTION("-b") )
            if( s_libfil==NIL )
                s_libfil:=VALUE()
            else
                s_libfil+=","+VALUE()
            end


        elseif( OPTION("-x") .or.  OPTION("-m") )
            if( s_main==NIL )
                s_main:=VALUE()
            else
                s_main+=","+VALUE()
            end

        elseif( OPTION("-o") )
            omitted_hash[VALUE()::strtran("\","/")]:=.t.

        elseif( OPTION("-h") )
            usage()
            quit

        elseif( OPTION("-q") )
            s_quiet:=.t.

        elseif( OPTION("-v") )
            s_version:=.t.

        elseif( "--debug"==opt[n] )
            s_debug:=.t.

        elseif( "--dry"==opt[n] )
            s_debug:=.t.
            s_dry:=.t.

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
    if( "on"$LOWER(getenv("BUILD_DBG")) )
        s_debug:=.t.
    end
    if( "debug"$LOWER(getenv("BUILD_DBG")) )
        s_debug:=.t.
    end
    if( "dry"$LOWER(getenv("BUILD_DBG")) )
        s_debug:=.t.
        s_dry:=.t.
    end
    
    if( s_version )
        quit
    end
    
    s_rules_from_build_bat()
    extension_types()

    root()
    params()
    build()
    
    ?

****************************************************************************
static function s_rules_from_build_bat()

//a BUILD_BAT directory tartalmabol
// dinamikusan eloallitja az s_rules tombot

local d,n,rule

    asize(s_rules,0)
    d:=directory(getenv("BUILD_BAT")+dirsep()+"*.bat")
    for n:=1 to len(d)
        rule:=d[n][1]::strtran(".bat","")::split("2")
        if( len(rule)==2 )
            rule[1]:="."+rule[1]
            rule[2]:="."+rule[2]
            aadd(s_rules,rule)
        end
    next
    
    asort(s_rules,,,{|x,y|rulesort(x,y)})
    
    //for n:=1 to len(s_rules)
    //    ? n, s_rules[n]
    //next

static function rulesort(x,y)
local result
    if(result==NIL); result:=cmp(".exe",x,y); end
    if(result==NIL); result:=cmp(".so" ,x,y); end
    if(result==NIL); result:=cmp(".lib",x,y); end
    if(result==NIL); result:=cmp(".obj",x,y); end
    if(result==NIL); result:=x[1]<y[1]; end
    return result
        
static function cmp(ext,x,y)
    if( x[2]==ext )
        return if(y[2]==ext,x[1]<y[1],.f.)
    elseif( y[2]==ext )
        return if(x[2]==ext,x[1]<y[1],.t.)
    end
    return NIL 

****************************************************************************
static function extension_types()
local r1,r2,n

    s_primary:=""
    s_resource:=""

    for n:=1 to len(s_rules)
        r1:=s_rules[n][1]
        r2:=s_rules[n][2]

        //vigyazat: tdc$primary and tdc$resource!
        
        if( r2==".obj" )
            s_primary+=r1
        end
        if( !r2+"."$".obj.lib.exe." )
            s_resource+=r1 //tobbszorozodhet
        end
    next
    s_primary+="."
    s_resource+="."
    //? s_primary
    //? s_resource


****************************************************************************
static function readpar(parfil,opt,optx)
local par:=memoread(parfil),n,p,i

    if(empty(par))
        //2006.09.26
        //Először a megadott directoryban keres,
        //ha ott nincs, akkor megnézi a build directoryban.
        par:=memoread(getenv("BUILD_BAT")+dirsep()+parfil)
    end

    if(s_debug)
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
static function procpar(par)
local n,p

    while( 0<(n:=at("$$(",par)) )        // ...$$(...)...
        p:=left(par,n-1)
        par:=substr(par,n+3)
        n:=at(")",par)
        p+=left(par,n-1)+"/$(BUILD_OBJ)/"+left(par,n-1)
        p+=substr(par,n+1)
        par:=p
    end

    while( 0<(n:=at("$(",par)) )         // ...$(...)...
        p:=left(par,n-1)
        par:=substr(par,n+2)
        n:=at(")",par)
        p+=getenv(left(par,n-1)) 
        p+=substr(par,n+1)
        par:=p
    end
 
    par:=strtran(par,"\",dirsep())
    par:=strtran(par,"/",dirsep())
    
    return if(left(par,1)=="=",LOWER(par),par)


****************************************************************************
static function usage()
    ? @"BUILD -xExeNam|-lLibNam -dSrcDir -iIncDir -pLibDir -bLibFil -mMain"
    ?
    return NIL


****************************************************************************
static function root()

local srcroot,d,n
 
    if( !empty(srcroot:=getenv("BUILD_SRC")) )

        if( !right(srcroot,1)$"/\"  )
            srcroot+=dirsep()
        end
        
        if( s_srcdir==NIL )
            s_srcdir:="."
        end

        d:=xsplit(s_srcdir,",;")
        
        s_srcdir:=""
        for n:=1 to len(d)
            if( left(d[n],1) $ "/\" )
                s_srcdir+=d[n]+";" //abszolút path 1.2.17
            else
                s_srcdir+=srcroot+d[n]+";"
            end
        next
        

        if( s_incdir!=NIL )

            d:=xsplit(s_incdir,",;")
        
            s_incdir:=""
            for n:=1 to len(d)
                if( left(d[n],1) $ "/\" )
                    s_incdir+=d[n]+";" //abszolút path 1.2.17
                else
                    s_incdir+=srcroot+d[n]+";"
                end
            next
        end
    end
    
    return NIL
 

****************************************************************************
static function params() //paraméterek a fordítónak/linkernek

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
    txt+=if(s_srcdir==NIL,".",s_srcdir)+";"
    txt+=if(s_incdir==NIL,"",s_incdir)+";"
    txt+=getenv("BUILD_INC")+";"
    txt+=getenv("include")+";"
    txt:=strtran(txt,","," ")  //","->" "
    txt:=strtran(txt,";"," ")  //";"->" "
    #ifdef _UNIX_
    txt:=strtran(txt,":"," ")  //":"->" "
    #endif
    putenv("BUILD_INC="+txt)
    //memowrit(getenv("BUILD_OBJ")+dirsep()+"buildi",txt)
 
 
    //library directories 

    txt:=""
    txt+=if(s_libdir==NIL,"",s_libdir)+";"
    txt+=getenv("BUILD_LPT")+";"
    txt+=getenv("lib")+";"
    txt:=strtran(txt,","," ")  //","->" "
    txt:=strtran(txt,";"," ")  //";"->" "
    #ifdef _UNIX_
    txt:=strtran(txt,":"," ")  //":"->" "
    #endif
    putenv("BUILD_LPT="+txt)
    //memowrit(getenv("BUILD_OBJ")+dirsep()+"buildp",txt)


    //library files

    txt:=""
    txt+=if(s_libfil==NIL,"",s_libfil)+";"
    txt+=getenv("BUILD_LIB")+";"
    txt:=strtran(txt,","," ")  //","->" "
    txt:=strtran(txt,";"," ")  //";"->" "
    putenv("BUILD_LIB="+txt)
    s_libspec:=search_library()
    putenv("BUILD_LIB="+s_libspec)
    s_libspec::=split(" ")
    
    return NIL


****************************************************************************
static function build()
    
local dir:={}     //forrásdirektorik listája
local obj:={}     //elsődleges források (prg,cpp,c,asm)
local lib:={}     //main-t nem tartalmazó objectek 
local mmd:={}     //main-t tartalmazó objectek (csak prg-ből)
local todo:={}    //mit kell csinálni

local d1,f,o,n,i,txt,dep


    if( s_main!=NIL )
        mmd:=xsplit(LOWER(s_main),",;")
    end


    if( s_srcdir!=NIL  )
        dir:=xsplit(s_srcdir,",;") //a felsorolt directorykból
    else
        dir:={"."} //csak az aktuális directoryból
    end

    for n:=1 to len(dir)
        
        ?? "",dir[n]

        d1:=directory(dir[n]+dirsep()+"*.*","H") 
 
        for i:=1 to len(d1)
            
            f:=LOWER(d1[i][1])
            
            if( fext(f)+"."$s_primary  )
                if( omitted_hash[strtran(dir[n]+dirsep()+f,"\","/")]!=NIL )
                    //kihagy
                else
                    aadd(obj,dir[n]+dirsep()+f)
                end
            end
            //vigyazat: tdc$primary and tdc$resource!
            if( fext(f)+"."$s_resource )
                resource_hash[f]:=dir[n]+dirsep()+f
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
            if( s_main==NIL )
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


    if( s_debug )
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
        thread_mutex_lock(mutex_count)
        ++thread_count
        while( thread_count>MAXTHREAD )
            thread_cond_wait(cond_count,mutex_count)
        end
        thread_mutex_unlock(mutex_count)

        thread_create_detach({|i|makeobj(todo[i])},n)
        
        if( !fext(todo[n][1])==".obj" .and. n<len(todo) .and. fext(todo[n+1][1])==".obj" )
            //mindent megvár
            thread_mutex_lock(mutex_count)
            while( thread_count>0 )
                thread_cond_wait(cond_count,mutex_count)
            end
            thread_mutex_unlock(mutex_count)
        end
    next
    //mindent megvár
    thread_mutex_lock(mutex_count)
    while( thread_count>0 )
        thread_cond_wait(cond_count,mutex_count)
    end
    thread_mutex_unlock(mutex_count)

    //itt már megvan az összes object
    
    if( s_libnam!=NIL )
        makelib(s_libnam,lib)
        
        if( s_shared==.t. )
            makeso(s_libnam,lib)
        end
        
        //for n:=1 to len(mmd)
        //    makeexe1(mmd[n],s_libnam)
        //next
        manage_threads({|x|makeexe1(x,s_libnam)},mmd) 

    else
        //for n:=1 to len(mmd)
        //    makeexe(mmd[n],lib)
        //next
        manage_threads({|x|makeexe(x,lib)},mmd) 
    end
 
    return NIL



****************************************************************************
static function manage_threads(blk,a)
local thread:={},th,n
    for n:=1 to len(a)
        thread_mutex_lock(mutex_count)
        ++thread_count
        while( thread_count>MAXTHREAD )
            thread_cond_wait(cond_count,mutex_count)
        end
        thread_mutex_unlock(mutex_count)

        th:=thread_create({|i|eval(blk,a[i])},n)
        aadd(thread,th)
    next
    for n:=1 to len(thread)
        thread_join(thread[n] )
    next 


****************************************************************************
static function makeso(libnam,object)  //so-t az objectekből (UNIX)

local target:=getenv("BUILD_OBJ")+dirsep()+"lib"+libnam+".so",ttarget 
local depend,tdepend,update:=.f.
local torun:=getenv("BUILD_BAT")+dirsep()+"obj2so.bat"
local objdir:=getenv("BUILD_OBJ"), n 

    if( !file(torun) )
        ? "["+torun+"]", @"does not exist"
        ?
        errorlevel(1)
        quit 
    end
    
    torun+=" lib"+libnam
 
    ttarget:=ftime(target) 
    if( ttarget==NIL )
        ttarget:=""
    end

    if( s_debug )
        ? target, "["+ttarget+"]"
    end
    
    for n:=1 to len(object)
    
        depend:=object[n]
        torun+=" "+depend
        depend:=objdir+dirsep()+depend+".obj"
        update:=verifdep(ttarget,depend).or.update
    next

    if( s_debug )
        ? 
    end
    
    if( update )
        run1 (torun)
    end
    
    return NIL


****************************************************************************
static function makelib(libnam,object)  //lib-et az objectekből

local target:=getenv("BUILD_OBJ")+dirsep()+libnam+".lib",ttarget 
local depend,tdepend,update:=.f.
local torun:=getenv("BUILD_BAT")+dirsep()+"obj2lib.bat"
local objdir:=LOWER(getenv("BUILD_OBJ")), n 
local objlist

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

    if( s_debug )
        ? target, "["+ttarget+"]"
    end
    
    for n:=1 to len(object)
    
        depend:=object[n]
        depend:=objdir+dirsep()+depend+".obj"
        update:=verifdep(ttarget,depend).or.update
    next

    if( s_debug )
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
                if( "objmng"$objdir )
                    objlist+=object[n]+".obj"+endofline()
                elseif( "objmsc"$objdir )
                    objlist+=object[n]+".obj"+endofline()
                elseif( "objbor"$objdir )
                    objlist+="+"+object[n]+".obj &"+endofline()
                end
            next
            memowrit(objdir+dirsep()+"objects",objlist)
            memowrit(objdir+dirsep()+"objects-"+libnam,objlist)
        #endif

        run1 (torun)
    end
    
    return NIL
 

****************************************************************************
static function makeexe(exenam,object) //exe-t az objectekből

local target:=getenv("BUILD_EXE")+dirsep()+exenam+".exe",ttarget 
local depend,tdepend,update:=.f.
local torun:=getenv("BUILD_BAT")+dirsep()+"obj2exe.bat"
local objdir:=LOWER(getenv("BUILD_OBJ")), n 
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

    if( s_debug )
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
    
    for n:=1 to len(s_libspec)                           /**/
        if( s_libspec[n]::right(4)==".lib" )             /**/
            depend:=s_libspec[n]                         /**/
            update:=verifdep(ttarget,depend).or.update   /**/
        end                                              /**/
    next                                                 /**/

    if( s_debug )
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

                if( "objmng"$objdir )
                    objlist+=xobj+endofline()
                elseif( "objmsc"$objdir )
                    objlist+=xobj+endofline()
                elseif( "objbor"$objdir)
                    objlist+=xobj+if(n<len(object)," + ","")+endofline()
                end
            next
            memowrit(objdir+dirsep()+"objects",objlist)
            memowrit(objdir+dirsep()+"objects-"+exenam,objlist)
        #endif

        run1 (torun)
    end

    thread_mutex_lock(mutex_count)
    --thread_count
    thread_cond_signal(cond_count)
    thread_mutex_unlock(mutex_count)
    
    return NIL


****************************************************************************
static function makeexe1(mmod,libnam) //exe-t a main modulból + lib-ből

local target:=getenv("BUILD_EXE")+dirsep()+mmod+".exe",ttarget 
local depend,tdepend,update:=.f.
local torun:=getenv("BUILD_BAT")+dirsep()+"lib2exe.bat"
local objdir:=getenv("BUILD_OBJ"), n 

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

    if( s_debug )
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
 
    for n:=1 to len(s_libspec)                           /**/
        if( s_libspec[n]::right(4)==".lib" )             /**/
            depend:=s_libspec[n]                         /**/
            update:=verifdep(ttarget,depend).or.update   /**/
        end                                              /**/
    next                                                 /**/

    if( s_debug )
        ? 
    end
    
    if( update )
        run1 (torun)
    end

    thread_mutex_lock(mutex_count)
    --thread_count
    thread_cond_signal(cond_count)
    thread_mutex_unlock(mutex_count)
    
    return NIL

 
****************************************************************************
static function makeobj(deplist)  //object előállítása (egyenként)

local target:=deplist[1] 
local depend:=deplist[2]  
local objdir:=getenv("BUILD_OBJ") 
local ttarget,tdepend
local update:=.f.,torun
local n,p1,p2

    if( fext(target)==".obj" )
        target:=objdir+dirsep()+fname(target)+fext(target)
    end

    ttarget:=ftime(target) 
    if( ttarget==NIL )
        ttarget:=""
    end

    if( s_debug )
        ? target, "["+ttarget+"]"
    end
 
    for n:=2 to len(deplist)
        depend:=deplist[n] 
        update:=verifdep(ttarget,depend).or.update
    next

    if( s_debug )
        ? 
    end
    
    if( update )
        
        torun:=getenv("BUILD_BAT")+dirsep()
        torun+=strtran(fext(deplist[2])+"2"+fext(deplist[1]),".","")
        torun+=".bat"

        if( !file(torun) )
            ? "["+torun+"]", @"does not exist"
            ?
            errorlevel(1)
            quit 
        end
    
        p1:=fname(deplist[1])
        p2:=fpath0(deplist[2]); p2:=if(empty(p2),".",p2)
    
        run1(torun+" "+p1+" "+p2)
    end

    thread_mutex_lock(mutex_count)
    --thread_count
    thread_cond_signal(cond_count)
    thread_mutex_unlock(mutex_count)
    
    return NIL

 

****************************************************************************
static function run1(cmd)

static mutex_out:=thread_mutex_init()
static count:=0
local runtmp,out

    if( !s_dry )

        thread_mutex_lock(mutex_out)
        runtmp:="log-runtmp"+alltrim(str(++count))
        thread_mutex_unlock(mutex_out)

        run(cmd+" >"+runtmp)
        out:=memoread(runtmp)
        ferase(runtmp)

        thread_mutex_lock(mutex_out)
        ?? out
        thread_mutex_unlock(mutex_out)

        if( file("error") )
            #ifdef _UNIX_
              run ("cat error")
            #else
              run ("type error")
            #endif
            //?
            //quit
            s_dry:=.t.
        end
    end
 

****************************************************************************
static function ftime(fspec)
local d:=directory(fspec,"H")
    if( len(d)==1 )
        return dtos(d[1][F_DATE])+"-"+d[1][F_TIME]
    end
    return NIL


****************************************************************************
static function search_include(txt,dep,dir,todo) 

local nl:=chr(10)
local include:="#include" 
local lenincl:=len(include)
local n1,n2:=0,line,delim,dpos,f

    while( (n1:=at(include,txt,n2+1))>0 )
        
        if( 0==(n2:=at(nl,txt,n1+lenincl)) )
            n2:=len(txt)+1
        end

        line:=substr(txt,n1+lenincl,n2-n1-lenincl)
        line:=strtran(line,chr(9),"")
        line:=alltrim(line)
        
        if(left(line,1)=='"')
            delim:='"'
        elseif(left(line,1)=='<')
            delim:='>'
        else
            loop
        end
        
        if( 0==(dpos:=at(delim,line,2)) )
            loop
        end

        f:=substr(line,2,dpos-2)
        f:=strtran(f,"/",dirsep())
        f:=strtran(f,"\",dirsep())
            
        if( byrules(f,dep,dir,todo) )
            //a fordítási szabályok alapján előállítható
            
        elseif( byhand(f,dep,dir,todo) )
            //eredeti forrásállomány

        else
            //az include path-ból vett rendszerfilé
        end
    end


****************************************************************************
static function search_library()

//megkeresi a lib-eket libpath-ban,
//így a linker paraméterezése egyszerűbb

local dirlist:=split(getenv("BUILD_LPT")," ")
local liblist:=split(getenv("BUILD_LIB")," ")
local sharing:=LOWER(getenv("BUILD_SHR"))  //"shared" or "static" libraries

local n,i,txt:="" 
local f0,f1,f2,f3,pf1,pf2,pf3
    
 
    for n:=1 to len(liblist) 

        if( empty(f0:=liblist[n]) )
            loop
        end
        
        if( ".lib"$f0 .or. ".a"$f0 .or. ".so"$f0 )
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
static function search_file(dirlist,fnamext)

local n,pathname

    for n:=1 to len(dirlist) 
        pathname:=dirlist[n]+dirsep()+fnamext
        if( file(pathname) )
            return pathname
        end
    next
    return NIL
 

 
****************************************************************************
static function byrules(fil,dep,dir,todo) 

//resource-ból az implicit szabályok 
//valamelyikének alkalmazásával előállítható
//(nincs többszörös szabály alkalmazás)

local f:=fname(fil)     //az előállítandó filé neve
local e:=fext(fil)      //az előállítandó filé kiterjesztése
local p                 //az előállítandó filé directoryja
local r,e0              //resource name/kiterjesztés
local i,x
local result:=.f.

    if( e==".ch" .and. !f[1]=="_" )
        //csak olyan ch-kat probal resourcebol 
        //legyartani, amik '_' karakterrel kezdodnek
        return .f.
    end

    for i:=1 to len(s_rules) 
    
        if( s_rules[i][2]==e )

            e0:=s_rules[i][1]
        
            //előállítható, ha létezik az alábbi filé    

            //if( NIL!=(r:=search_file(dir,f+e0))  )
            if( NIL!=(r:=resource_hash[f+e0]) )
                p:=fpath(r)
                adddep(dep,p+f+e)
                if( 0==(x:=ascan(todo,{|x|x[1]==p+f+e})) )
                    aadd(todo,{p+f+e,p+f+e0})
                elseif( 0==ascan(todo[x],{|x|x==p+f+e0}) )
                    aadd(todo[x],p+f+e0)
                    // itt gyulnek az olyanok, mint 
                    //  {demo.say, demo.msk, demo.sor}
                    // a masodikbol akarja majd letrehozni az elsot
                    // hogy melyik a masodik/harmadik az az s_rules 
                    // rendezesetol fugg (abc szerint)
                end
                result:=.t.    
            end
        end
    next
    return result


****************************************************************************
static function byhand(f,dep,dir,todo) 
 
//eredeti forrásállomány
//nem állítható elő valamely resource-ból
//az implicit fordítási szabályok alkalmazásával
//viszont létezik valahol a forrás directorykban 

local pn:=search_file(dir,f)

    if( pn!=NIL )
        adddep(dep,pn)
        return .t.
    end
    return .f.


****************************************************************************
static function adddep(dep,x)
    if( 0==ascan(dep,{|d|d==x}))
        aadd(dep,x)
    end


****************************************************************************
function psort(x,y)
local ix:=ruleidx(fext(x[2]),fext(x[1]))
local iy:=ruleidx(fext(y[2]),fext(y[1]))
    return if(ix==iy,x[1]<y[1],ix<iy)


****************************************************************************
static function ruleidx(e1,e2)
local n
    for n:=1 to len(s_rules)
        if( e1==s_rules[n][1] .and. e2==s_rules[n][2] )
            return n
        end
    next
    return 0


****************************************************************************
static function xsplit(txt,sep)
local n,s
    for n:=1 to len(sep)

        s:=substr(sep,n,1)
        
        if( 0<at(s,txt) )
            exit
        else
            s:=NIL
        end
    next
    return split(txt,s)


****************************************************************************
static function normalize(todo)

// kiszedi a path-okból a felesleges "./" részeket
// a működéshez nem kell, csak a függőségi listákat teszi olvashatóbbá

local i,n,x

    for n:=1 to len(todo)
        for i:=1 to len(todo[n])
            x:=todo[n][i]
            x:=strtran(x,dirsep()+"."+dirsep(),dirsep())
            if( left(x,2)=="."+dirsep() )
                x:=substr(x,3)
            end
            todo[n][i]:=x
        next
    next


****************************************************************************
static function verifdep(ttarget,depend)

local update:=.f.
local tdepend:=ftime(depend)

    if( tdepend==NIL )
        if( s_dry )
            tdepend:=""
        else
            ? depend, @"does not exist"
            ?
            errorlevel(1)
            quit
        end

    elseif( ttarget<tdepend )
        update:=.t.
    end

    if( s_debug )
        ? "  ",depend, "["+tdepend+"]", if(ttarget<tdepend,"UPDATE","")
    end
    
    return update


****************************************************************************
