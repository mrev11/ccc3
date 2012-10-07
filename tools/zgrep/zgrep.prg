
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

#define ZGREP  "Grep Viewer 2.0.00-Unicode"

#define FIND    getenv("FIND") 
#define GREP    getenv("GREP")
#define TEMPFD  getenv("TEMP")+dirsep()+"zgrep_find" 
#define TEMPGR  getenv("TEMP")+dirsep()+"zgrep_grep"  

*****************************************************************************
function main(search,replace)

local gf,fd,b,n,m 

    //alert( FIND+" >"+TEMPFD )
    run( FIND+" >"+TEMPFD )
    fd:=lines(memoread(TEMPFD))

    ferase(TEMPGR)
    for n:=1 to len(fd)
        fd[n]:=strtran(fd[n],chr(13),"")
        //alert( GREP+' "'+search+'" '+fd[n]+" >>"+TEMPGR )
        run( GREP+' "'+search+'" '+fd[n]+" >>"+TEMPGR )
    next

    gf:=memoread(TEMPGR)

    if( empty(gf) )
        quit
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
 
    brwShow(b)
    brwLoop(b)
    brwHide(b)
    
    return NIL
    

*****************************************************************************
static function view(b,search,replace)

local a:=brwArray(b)
local p:=brwArrayPos(b)
local x:=split(a[p][1],":")
local fspec:=x[1]
local line:=x[2]
local cmd:="z.exe "+fspec  //"z" nem jó!
local screen

  #ifdef _UNIX_
    if( line!=NIL )
        cmd+=" '-l"+line+"'"
    end

    if( search!=NIL )
        cmd+=" '-S"+search+"'"
    end

    if( replace!=NIL )
        cmd+=" '-p"+replace+"'" 
    end
 
    if( getenv("CCC_TERMINAL")=="term" ) //2002.12.31
        brwHide(b)
        run ( cmd )
        brwShow(b)
    else
        //alert(cmd+"&")
        run( cmd+"&" ) //külön ablak 
    end
    

  #else
    if( line!=NIL )
        cmd+=' "-l'+line+'"' 
    end

    if( search!=NIL )
        cmd+=' "-S'+search+'"'
    end

    if( replace!=NIL )
        cmd+=' "-p'+replace+'"'
    end
 
    run ( "start /b " + cmd  )

  #endif

    return .t.


*****************************************************************************
static function lines(txt)  //z-ből átvéve

local a:={},n1,n:=1,i:=0

    while( .t. )

        if( ++i>len(a) )
            asize(a,i+256)
        end

        if( 0<(n1:=at(chr(10),txt,n)) )
            a[i]:=substr(txt,n,n1-n)
            n:=n1+1
        else
            a[i]:=substr(txt,n)
            if( empty(a[i]) )
                i--
            end
            exit
        end
    end

    return asize(a,i)

**************************************************************************** 
        