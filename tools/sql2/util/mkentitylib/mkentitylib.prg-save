
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

******************************************************************************
function main( entitylib )

local src,prg,n,p
local srcname,prgname
local force:=!empty(getenv("MKENTITYLIB_FORCE"))

    
    //1. lépés: tds
    
    src:=directory("*.tds")
    prg:=directory("*.prg")
 
    for n:=1 to len(src)
        srcname:=src[n][F_NAME] 
        prgname:=left(srcname,len(srcname)-4)+".prg"
        p:=ascan(prg,{|x|x[F_NAME]==prgname})

        if( force .or. p<1 .or.;
            dtos(src[n][F_DATE])+src[n][F_TIME] >;
            dtos(prg[p][F_DATE])+prg[p][F_TIME] )
            ?? srcname; ?
            if( 0!=run("tds2prg.exe "+srcname) )
                errorlevel(1)
                quit
            end
        end
    next


    //2. lépés: ted
    
    src:=directory("*.ted")
    prg:=directory("*.prg")
 
    for n:=1 to len(src)
        srcname:=src[n][F_NAME] 
        prgname:=left(srcname,len(srcname)-4)+".prg"
        p:=ascan(prg,{|x|x[F_NAME]==prgname})

        if( force .or. p<1 .or.;
            dtos(src[n][F_DATE])+src[n][F_TIME] >;
            dtos(prg[p][F_DATE])+prg[p][F_TIME] )
            ?? srcname; ?
            if( 0!=run("ted2prg.exe "+srcname) )
                errorlevel(1)
                quit
            end
        end
    next
    
    //Ha az entitylib argumentum meg van adva,
    //csinálunk egy listát, amiből név szerint 
    //kikereshetők az objektumok

    if( entitylib!=NIL )
        mkentitylib(entitylib)
    end
    
    return NIL
    

******************************************************************************
static function mkentitylib(entitylib) 

local skel:=<<SKELETON>>
function entitylib._NAME_(name,conn)
static libdata:={_ENTITIES_}
local x
    if( name==NIL )
        return libdata
    elseif( conn==NIL )
        x:=ascan(libdata,{|e|e[1]==name})
        if( x>0 )
            return libdata[x][2]
        end
    else
        x:=ascan(libdata,{|e|e[1]==name})
        if( x>0 )
            return eval(libdata[x][2],conn)
        end
    end
    return NIL
<<SKELETON>>

local src,n
local srcname
local entname
local prgname 

    src:=directory("*.prg")
    
    for n:=1 to len(src)

        srcname:=fname(src[n][F_NAME])
        
        if( file(srcname+".ted") )
            entname:=readtedname(srcname+".ted")
            skel:=strtran(skel,"_ENTITIES_",";"+crlf()+'{"'+entname+'",{|c|.'+entname+'.tableEntityNew(c)}},_ENTITIES_')

        elseif( file(srcname+".tds") )
            entname:=readtdsname(srcname+".tds")
            skel:=strtran(skel,"_ENTITIES_",";"+crlf()+'{"'+entname+'",{|c|.'+entname+'.tableEntityNew(c)}},_ENTITIES_')

        else
            //nem script
        end
    next

    skel:=strtran(skel,"_NAME_",entitylib)
    skel:=strtran(skel,",_ENTITIES_","")
    
    prgname:="entitylib."+entitylib+".prg" 
    
    if( !skel==memoread(prgname) )
        memowrit(prgname,skel)
    end
    
    return NIL
 

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

