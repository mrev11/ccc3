
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

//Ez ugyanaz, mint zgrep,
//de a keresest elozoleg kezzel kell megcsinalni.
//Az osszetett keresesekhez egyszerubb a grep-et tobbszor futtatni.

#define ZGREP  zgrep_version()

#define FIND    getenv("FIND") 
#define GREP    getenv("GREP")
#define TEMPFD  getenv("TEMP")+dirsep()+"zgrep_find" 
#define TEMPGR  getenv("TEMP")+dirsep()+"zgrep_grep"  

*****************************************************************************
function main(grepresult,search,replace)

local gf,fd,b,n,m 

    gf:=memoread(grepresult)

    if( empty(gf) )
        quit
    end
    
    if( search==NIL )
        search:=""
    end

    gf:=lines(gf)
    for n:=1 to len(gf)
        gf[n]:={gf[n]}
    next
    
    b:=brwCreate(0,0,maxrow(),maxcol())
    b:headsep:=""
    brwArray(b,gf)
    brwColumn(b,"",brwABlock(b,1),replicate("X",maxcol()))
    brwMenu(b,"",ZGREP,{||view(b,search,replace),.t.})
    
    m:=alltrim(str(len(gf)))
    if( !empty(search) )
        m+=" Search:"+search
    end
    if( !empty(replace) )
        m+=" Replace:"+replace 
    end
    brwMenuName(b,m)

    setcursor(0)
 
    brwShow(b)
    brwLoop(b)
    brwHide(b)
    

*****************************************************************************
