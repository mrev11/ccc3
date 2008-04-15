
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

#include "fileattr.ch"
#include "directry.ch"
 
static s_descript   //directory() egy sora
static s_filtattr   //szám: FA_NORMAL,...
static s_exact      //.t./.f.


*************************************************************************
function fileseek(fspec,nattr,exact)  //CA-tools function

local name

    if( fspec!=NIL )    
    
        if( nattr==NIL )
            nattr:=FA_NORMAL
        end
 
        if( exact==NIL )
            exact:=.f.
        end

        s_filtattr := nattr //szám
        s_exact    := exact
        s_descript := findfirst(fspec,nattr2sattr(s_filtattr))

    else        
        s_descript := findnext()
    end

    findfilter()
    
    if( s_descript!=NIL )
        name:=s_descript[F_NAME] 
    else
        name:=""
        s_filtattr:=NIL
        s_exact:=NIL
    end
    
    return name
    

*************************************************************************
function savefseek()
    return {findsave(),s_descript,s_filtattr,s_exact}


*************************************************************************
function restfseek(state)
    findrest(state[1])
    s_descript:=state[2] 
    s_filtattr:=state[3]  
    s_exact   :=state[4]  
    return ""


*************************************************************************
static function findfilter()

//attribútum szerint szűri a filéket
//azaz átugorja a nem megfelelőket

local a,b

    while( s_descript!=NIL )

        a:=sattr2nattr(s_descript[F_ATTR]) 
 
        if( !s_exact )

            a:=numand(a         ,FA_DIRECTORY+FA_HIDDEN+FA_SYSTEM)
            b:=numand(s_filtattr,FA_DIRECTORY+FA_HIDDEN+FA_SYSTEM)
         
            if( a<=b )
                exit
            end
    
        elseif( a==s_filtattr )
            exit
        end

        s_descript:=findnext()
    end
  
    return NIL


*************************************************************************
function fileattr(fspec) //CA-tools

local attr:=0, f

    if( fspec==NIL ) 
        if( s_descript!=NIL )
            attr:=sattr2nattr(s_descript[F_ATTR])
        end
    else
        f:=findfirst(fspec,"RSDAV") 

        if( NIL!=f )
            attr:=sattr2nattr(f[F_ATTR])
            findclose()
        end
    end
    return attr


*************************************************************************
function filesize(fspec,nattr) //CA-tools 

local size:=-1, f 

    if( nattr==NIL )
        nattr:=FA_NORMAL
    end
 
    if( fspec==NIL ) 
        if( s_descript!=NIL )
            size:=s_descript[F_SIZE]
        end
    else
        f:=findfirst(fspec,nattr2sattr(nattr)) 

        if( NIL!=f )
            size:=f[F_SIZE]
            findclose()
        end
    end
    return size


*************************************************************************
function filedate(fspec,nattr) //CA-tools 

local date:=ctod(""), f 

    if( nattr==NIL )
        nattr:=FA_NORMAL
    end
 
    if( fspec==NIL ) 
        if( s_descript!=NIL )
            date:=s_descript[F_DATE]
        end
    else
        f:=findfirst(fspec,nattr2sattr(nattr)) 

        if( NIL!=f )
            date:=f[F_DATE]
            findclose()
        end
    end

    return date


*************************************************************************
function filetime(fspec,nattr) //CA-tools 

local time:="", f 

    if( nattr==NIL )
        nattr:=FA_NORMAL
    end
 
    if( fspec==NIL ) 
        if( s_descript!=NIL )
            time:=s_descript[F_TIME]
        end
    else
        f:=findfirst(fspec,nattr2sattr(nattr)) 

        if( NIL!=f )
            time:=f[F_TIME]
            findclose()
        end
    end

    return time
 

********************************************************************
function filedelete(fspec,attr) //CA-tools  

local delcnt:=0, fname

    if( attr==NIL )
        attr:=FA_ARCHIVE
    end
    
    fname:=fileseek(fspec,attr)
    
    while( !empty(fname) )
        if( deletefile(fname)==0 ) //OK
            delcnt++
        end
        
        fname:=fileseek()
    end
    
    return delcnt>0


********************************************************************
static function sattr2nattr(s)

local n:=0

    if( "R"$s )
        n+=FA_READONLY 
    end

    if( "H"$s )
        n+=FA_HIDDEN
    end

    if( "S"$s )
        n+=FA_SYSTEM
    end

    if( "V"$s )
        n+=FA_VOLUME
    end

    if( "D"$s )
        n+=FA_DIRECTORY
    end

    if( "A"$s )
        n+=FA_ARCHIVE
    end

    return n
        
 
********************************************************************
static function nattr2sattr(n)
 
local s:=""
 
    if( numand(n,FA_READONLY)!=0 )
        s+="R"
    end

    if( numand(n,FA_HIDDEN)!=0 )
        s+="H"
    end

    if( numand(n,FA_SYSTEM)!=0 )
        s+="S"
    end

    if( numand(n,FA_VOLUME)!=0 )
        s+="V"
    end

    if( numand(n,FA_DIRECTORY)!=0 )
        s+="D"
    end

    if( numand(n,FA_ARCHIVE)!=0 )
        s+="A"
    end
    
    return s
 

********************************************************************
 