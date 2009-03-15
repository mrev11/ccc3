
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

//primitív process manager FreeBSD-re

static PIDPOS:=1

*********************************************************************************************
function main()

local b, sig:={}
 
//  set printer to log 
//  set printer on
//  setcolor("w/b,b/w")
    setcursor(0)
    
    b:=brwCreate()    
    brwColumn(b,"",{|p|p:=brwArrayPos(b),brwArray(b)[p][1]},maxcol()-2)

    reload(b)
 
    brwMenuName(b,"["+getenv("HOME")+"]")
    brwMenu(b,"Reload","Reload process info",{||reload(b),.t.})
    aadd(sig,{"SIGTERM",{||send(b,"TERM")}})
    aadd(sig,{"SIGHUP",{||send(b,"HUP")}})
    aadd(sig,{"SIGINT",{||send(b,"INT")}})
    aadd(sig,{"SIGABRT",{||send(b,"ABRT")}})
    aadd(sig,{"SIGSTOP",{||send(b,"STOP")}})
    aadd(sig,{"SIGCONT",{||send(b,"CONT")}})
    aadd(sig,{"SIGKILL",{||send(b,"KILL")}})
    brwMenu(b,"Send","Send signal to process",sig)

    //Ezek nem működnek
    //brwMenu(b,"Files","View open files",{||files(b),.t.})
    //brwMenu(b,"Status","View process status",{||status(b),.t.})
    //brwMenu(b,"Envir","View environment variables",{||envir(b),.t.})
 
    brwShow(b)
    brwLoop(b)
    brwHide(b)
    
    return NIL

*********************************************************************************************
static function reload(b)
local t, n, ps, line1, args:=argv()

    //run( "ps  >"+pmtemp() ); PIDPOS:=1
    //run( "ps -A  >"+pmtemp() ); PIDPOS:=1
    //run( "ps -jA >"+pmtemp() ); PIDPOS:=2
    //run( "ps -uA >"+pmtemp() ); PIDPOS:=2

    if( empty(args) )
        args:={"-A"}
    end
    ps:="ps "
    for n:=1 to len(args)
        ps+=args[n]+" "
    next
    run( ps+">"+pmtemp() )

    t:=memoread( pmtemp() )
    ferase( pmtemp() )
    t:=split(t,chr(10))
        
    line1:=t[1]
    while("  "$line1)
        line1::=strtran("  "," ")
    end
    line1::=split(" ")
    PIDPOS:=ascan(line1,{|x|x=="PID"}) //signal küldéshez kell


    b:column[1]:heading:=t[1]
    for n:=2 to len(t)
        t[n-1]:={t[n]}
    next
    asize(t,len(t)-1)
    asort(t,,,{|x,y| x[1]<y[1] })

    brwArray(b,t)     
    if( brwArrayPos(b)>len(t) )
        brwArrayPos(b,len(t))
    end
    b:refreshall
    return NIL

*********************************************************************************************
static function send(b,sig)

local pid:=getrow(b)[PIDPOS]
local cmd:="kill -"+sig+" "+pid
local rsp

    if( 2==alert(cmd,{"Cancel","Send"}) )

        run( cmd+" >"+pmtemp()+" 2>&1" )
 
        rsp:=memoread(pmtemp())
        if( !empty(rsp) )
            rsp:=strtran(rsp,chr(10),";")
            alert(rsp)
        end
    end
    reload(b)
    return .t.
 
*********************************************************************************************
static function files(b)

local pid:=getrow(b)[1]
local heading:=getcmd(b)
local t,n,p

    run( "ls -al /proc/"+pid+"/fd/* >"+pmtemp()+" 2>"+pmtemp2() )

    t:=memoread( pmtemp2() ) 
    ferase( pmtemp2() )
    if( !empty(t) )
        alert(t)
        return NIL
    end

    t:=memoread( pmtemp() )
    ferase( pmtemp() )
    t:=split(t,chr(10))
    if( empty(t) )
        return NIL
    end
    for n:=1 to len(t)
        p:=at("/proc",t[n])
        t[n]:=substr(t[n],p)
        t[n]:={t[n]}
    next

    pshow("[Open files]",heading,t)
    return NIL


*********************************************************************************************
static function status(b)

local pid:=getrow(b)[1]
local heading:=getcmd(b)
local t, n

    run( "cat /proc/"+pid+"/status >"+pmtemp()  )

    t:=memoread( pmtemp() )
    ferase( pmtemp() )
    t:=split(t,chr(10))
    for n:=1 to len(t)
        t[n]:={t[n]}
    next
    if( empty(t) )
        return NIL
    end

    pshow("[Process status]",heading,t)
    return NIL

*********************************************************************************************
static function envir(b)

local pid:=getrow(b)[1]
local heading:=getcmd(b)
local t, n

    run( "cat /proc/"+pid+"/environ >"+pmtemp()+" 2>"+pmtemp2()) 

    t:=memoread( pmtemp2() ) 
    ferase( pmtemp2() )
    if( !empty(t) )
        alert(t)
        return NIL
    end
    t:=memoread( pmtemp() )
    ferase( pmtemp() )
    t:=split(t,chr(0))
    for n:=1 to len(t)
        t[n]:={t[n]}
    next
    if( empty(t) )
        return NIL
    end
    asort(t,,,{|x,y|x[1]<y[1]})

    pshow("[Process environment]",heading,t)
    return NIL

*********************************************************************************************
static function pshow(caption,heading,data)
local b:=brwCreate()    
    brwColumn(b,heading,{|p|p:=brwArrayPos(b),brwArray(b)[p][1]},maxcol()-2)
    brwArray(b,data)
    brwMenuName(b,caption)
    brwMenu(b,"","",{||.f.})
    brwShow(b)
    brwLoop(b)
    brwHide(b)
    return NIL

*********************************************************************************************
static function getcmd(b)
local r:=getrow(b)
local cmd:="", n
    for n:=8 to len(r)
        cmd+=r[n]+" "
    next
    return cmd
 
*********************************************************************************************
static function getrow(b)
local pos:=brwArrayPos(b)
local row:=alltrim(brwArray(b)[pos][1])
    while( "  "$row  )
        row:=strtran(row,"  "," ")
    end
    row:=split(row," ")
    return row

*********************************************************************************************
static function pmtemp()
    return getenv("HOME")+"/.temp/pm"

*********************************************************************************************
static function pmtemp2()
    return pmtemp()+"2"
 
*********************************************************************************************
    