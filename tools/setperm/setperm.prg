
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

#ifdef MITCSINAL

directories     2775
regular files   664/775
symbolic links  skip

vegrehajthatoak:
  az "m" nevu filek
  a .b kiterjesztesu bash scriptek
  a #! kezdetu scriptek
  a (7f)ELF kezdetu ELF filek

#endif

#include "directry.ch"

static dirstack:={}

static s_listonly :=.t.
static s_next     :=".bak.zip.tar.gz.prg.ppo.cpp.obj.o.lib.dbf.y.lex.tex.dvi.aux.toc.log.html.msys2."
static s_xext     :=".b.bash."    
static s_exec     :=":m:"    

*****************************************************************************
function main( arg )
    
    set dosconv off
    
    if( arg=="set" )
        s_listonly:=.f.
    end
    
    doproc()
    ?
    return NIL


*****************************************************************************
static function doproc()    

local m,name,n,d,d1:={}

    d:=directory(,"DH")
    
    for n:=1 to len(d)

        name:=d[n][F_NAME]

        //if( !(name=="." .or. name=="..") )  // 2013.11.28  (kihagy: .git, .svn, .ssh)
        if( !name[1]=="." )

            if( "D"$d[n][F_ATTR] )
            
                m:=lstat_st_mode(name)

                if( !s_islnk(m) )
                    aadd(d1,name)
                end
            end

            setperm(name)
        end
    next
    
    d:=NIL
    
    for n:=1 to len(d1)
        name:=d1[n] 
        if(  0<=dirchange(name) )
            aadd(dirstack,name)
            //? dirstack
            doproc()
            dirchange("..")
            asize(dirstack,len(dirstack)-1)
        end
    next
    
    return NIL


*****************************************************************************
static function setperm(dentry)

local mode:=stat_st_mode(dentry)
local nmode:=mode
local xmode,ymode

    if(mode==NIL)
        // directory() C tipusban adja az eredmenyeket, de 
        // nem minden fajlnev konvertalhato hibatlanul C-re
        ? "!!!!!!! cannot stat:",  dirsep()+curdir()+dirsep()+dentry
        return NIL
    end
 
    if( s_isdir(mode) )
        nmode:=oct2l("2775")

    elseif( s_isreg(mode) )

        if( executable(dentry) )
            nmode:=oct2l("775")
        else
            nmode:=oct2l("664")
        end
    end
    
    xmode:=numand(mode,oct2l("7777"))
    ymode:=numand(nmode,oct2l("7777"))
    
    if(  xmode!=ymode  )
        ?  fullname(dentry), l2oct(xmode), "->", l2oct(ymode)
        if( !s_listonly )
            chmod(dentry,nmode)
        end
    end

    return NIL


*****************************************************************************
static function fullname(f)
local n
    for n:=len(dirstack) to 1 step -1
        f:=dirstack[n]+dirsep()+f
    next
    return f


*****************************************************************************
static function executable(name)

local fd,buf,res:=.f.

    if( ":"+name+":"$s_exec )
        res:=.t.

    elseif( fext(name)+"."$s_next )
        res:=.f.

    elseif( fext(name)+"."$s_xext )
        res:=.t.

    elseif( 0<=(fd:=fopen(name)) )

        buf:=x"00000000"
        fread(fd,@buf,4)
        fclose(fd)
        
        if( buf==bin(127)+a"ELF" )
            res:=.t.
        elseif( left(buf,2)==a"#!" )
            res:=.t.
        end
    end
    
    //? ">>",name,res 
    
    return res

*****************************************************************************
 