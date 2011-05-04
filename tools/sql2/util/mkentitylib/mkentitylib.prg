
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

#ifdef NOT_DEFINED //Változások

2009.03.14
  A generált prg-ket a --prgdir opcióban  megadott directoryba teszi.
  Default az aktuális working directory.

  Egyszerű array helyett hashtable-t használ a libdata-hoz. 
#endif


#include "directry.ch"

static prgdir
static prgmove
static libname
static genforced

******************************************************************************
function main(*)

local src,prg,n,p
local srcname,prgname
local move:=if(dirsep()=="/","mv","move")
local args:={*}

    genforced:=!empty(getenv("MKENTITYLIB_FORCE"))

    for n:=1 to len(args)
        if( args[n]=="--prgdir" )
            prgdir:=args[++n]

        elseif( args[n]=="--libname" )
            libname:=args[++n]

        elseif( args[n]=="--force" )
            genforced:=.t.

        elseif( args[n][1..2]=="--" )
            ? "invalid option:",args[n]
            ?
            errorlevel(1)
            quit

        else
            //compatibility
            libname:=args[n]
        end
    next
    
    if( prgdir==NIL )
        prgdir:="."+dirsep()
        prgmove:=.f.
    else
        if( !right(prgdir,1)$"/\"  )
            prgdir+=dirsep()
        end
        dirmake(prgdir)
        prgmove:=.t.
    end

   
    //1. lépés: tds
    
    src:=directory("*.tds")
    prg:=directory(prgdir+"*.prg")
 
    for n:=1 to len(src)
        srcname:=src[n][F_NAME] 
        prgname:=left(srcname,len(srcname)-4)+".prg"
        p:=ascan(prg,{|x|x[F_NAME]==prgname})

        if( genforced .or. p<1 .or.;
            dtos(src[n][F_DATE])+src[n][F_TIME] >;
            dtos(prg[p][F_DATE])+prg[p][F_TIME] )
            ?? srcname; ?
            if( 0!=run("tds2prg.exe "+srcname) )
                ? "ERROR: tds2prg.exe "+srcname, "failed"; ?
                errorlevel(1)
                quit
            end
            if( prgmove )
                run(move+" "+prgname+" "+prgdir)
            end
        end
    next


    //2. lépés: ted
    
    src:=directory("*.ted")
    prg:=directory(prgdir+"*.prg")
 
    for n:=1 to len(src)
        srcname:=src[n][F_NAME] 
        prgname:=left(srcname,len(srcname)-4)+".prg"
        p:=ascan(prg,{|x|x[F_NAME]==prgname})

        if( genforced .or. p<1 .or.;
            dtos(src[n][F_DATE])+src[n][F_TIME] >;
            dtos(prg[p][F_DATE])+prg[p][F_TIME] )
            ?? srcname; ?
            if( 0!=run("ted2prg.exe "+srcname) )
                ? "ERROR: ted2prg.exe "+srcname, "failed"; ?
                errorlevel(1)
                quit
            end
            if( prgmove )
                run(move+" "+prgname+" "+prgdir)
            end
        end
    next
    
    //Ha a libname argumentum meg van adva,
    //csinálunk egy listát, amiből név szerint 
    //kikereshetők az objektumok

    if( libname!=NIL )
        mkentitylib(libname)
    end
    

******************************************************************************
static function mkentitylib(libname) 

local skel:=<<SKELETON>>
static function _LIBNAME_.init()
local libdata:=simplehashNew()_ENTITIES_
    return libdata

function _LIBNAME_(name,conn)
static libdata:=_LIBNAME_.init(),blk
    if( name==NIL )
        return libdata //hashtable
    elseif( conn==NIL )
        return libdata[name] //codeblk
    else
        blk:=libdata[name]
        if( blk!=NIL )
            return eval(blk,conn) //tableentity
        end
    end
<<SKELETON>>

local src,n
local srcname
local entname
local prgname 
local entities:=""

    src:=directory(prgdir+"*.prg")
    
    for n:=1 to len(src)

        srcname:=fname(src[n][F_NAME])
        
        if( file(srcname+".ted") )
            entname:=readtedname(srcname+".ted")
        elseif( file(srcname+".tds") )
            entname:=readtdsname(srcname+".tds")
        else
            entname:=NIL  //nem script
        end
        
        if( entname!=NIL )
            entities+=endofline()+"    libdata['"+entname+"']:="+'{|c|.'+entname+'.tableEntityNew(c)}'
        end
    next

    skel:=strtran(skel,"_LIBNAME_",libname)
    skel:=strtran(skel,"_ENTITIES_",entities)
    
    prgname:=libname+".prg" 
    
    if( !skel==memoread(prgdir+prgname) )
        memowrit(prgdir+prgname,skel)
    end
    

******************************************************************************
static function readtedname(fspec)
local dom:=xmlparserNew(fspec):parse
    return lower(dom:content[1]:content[1]:gettext)


******************************************************************************
static function readtdsname(fspec)
local tds:=memoread(fspec)
local name:=alltrim(substr(tds,at("name:",tds)+5))
    name:=cut(name," ")
    name:=cut(name,";")
    name:=cut(name,chr(9))
    name:=cut(name,chr(10))
    name:=cut(name,chr(13))
    return name


******************************************************************************
static function cut(x,c)
    if( c$x )
        x:=left(x,at(c,x)-1)
    end
    return x


******************************************************************************

