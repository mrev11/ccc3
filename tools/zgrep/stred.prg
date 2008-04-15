
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

#include "inkey.ch"

#define STRED  "String Editor 1.0.00-Unicode"


#ifdef EMLEKEZTETO
    A fordító (ppo2cpp) által kigyűjtött string tábla nézegetésére
    való program. A stringeket az eredeti helyükön lehet editálni.
#endif

*****************************************************************************
function main(strtab)

local n,b

    if( strtab==NIL )
        strtab:="ppo/STRTAB"
    end

    if( !file(strtab) )
        ?? "Usage: stred strtab"; ?
        quit
    end

    strtab:=memoread(strtab)

    if( empty(strtab) )
        ?? strtab, "is empty"; ?
        quit
    end

    strtab:=lines(strtab)
    for n:=1 to len(strtab)
        strtab[n]:={strtab[n]}
    next
    
    b:=brwCreate()
    b:headsep:=""
    brwArray(b,strtab)
    brwColumn(b,"",brwABlock(b,1),replicate("X",maxcol()))
    brwMenu(b,"",STRED,{||view(b),.t.})
    
    brwMenuName(b,alltrim(str(len(strtab))))
    brwApplyKey(b,{|b,k|appkey(b,k)})
 
    brwShow(b)
    brwLoop(b)
    brwHide(b)
    
    return NIL
    

*****************************************************************************
static function appkey(b,k)

local blk0:=brwApplyKey(b) //save
local blk1:=brwApplyKey(b,{||NIL}) //off
local stat:=brwDoApplyKey(b,k)
local blk2:=brwApplyKey(b,blk0) //restore

local a:=brwArray(b)
local p:=brwArrayPos(b)
local sa:=alltrim(str(len(a)))
local sp:=alltrim(str(p))

    brwMenuName(b,sp+"/"+sa)
    brwSetFocus(b)
    
    if( k==K_ESC )
        return NIL
    end
    
    return .t.

*****************************************************************************
static function view(b)

local a:=brwArray(b)
local p:=brwArrayPos(b)
local x:=a[p][1]
local fspec,line,search,cmd

    search:=split(x,left(x,1))[2]

    x:=alltrim(substr(x,at("from",x)+5))
    x:=split(x," ")
    fspec:=x[1]
    line:=substr(atail(x),2)
    line:=strtran(line,"(","")
    line:=strtran(line,")","")

    cmd:="z.exe "+fspec  //"z" nem jó!


  #ifdef _UNIX_
    if( line!=NIL )
        cmd+=" '-l"+line+"'"
    end

    if( search!=NIL )
        cmd+=" '-S"+search+"'"
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

    run ( "start " + cmd  )

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
        