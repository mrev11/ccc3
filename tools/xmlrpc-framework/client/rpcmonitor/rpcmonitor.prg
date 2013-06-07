
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

#include "ssl.ch"

#define VERSION "0.9.02"   //2013.06.07 hitelesítés
//#define VERSION "0.9.02"

*****************************************************************************
function main(host,port,ssl,keyfile,capath,cafile)

local b, w, sid
local ctx,mode
    
    set printer to log-rpcmonitor
    set printer on
    
    if(host==NIL)
        host:="localhost"
    end

    if(port==NIL)
        port:=45000
    end
    
    w:=xmlrpcclientNew(host,port)
    w:keepalive:=.t.
    

    if(ssl!='SSL')
        ? "PLAIN connection"
    else
        ? "SSL connection enabled"
        ctx:=sslctxNew()

        if( !empty(keyfile) )  //kliens hiteles?t?s
            ? "KEYFILE",keyfile
            ctx:use_certificate_file(keyfile)  
            ctx:use_privatekey_file(keyfile)
        end

        if( !empty(capath) .or. !empty(cafile) ) //szerver hiteles?t?s
            if( !empty(capath) )
                ? "CAPATH",capath
            else
                capath:=NIL
            end
            if( !empty(cafile) )
                ? "CAFILE",cafile
            else
                cafile:=NIL
            end
            mode:=SSL_VERIFY_PEER_CERT
            ctx:set_verify(mode)
            ctx:set_verify_depth(1)
            ctx:load_verify_locations(cafile,capath)
        end

        w:sslcontext:=ctx
    end
    
    
    login({|g|loadlogin(g)},{|g|readmodal(g)},{|g|storelogin(g,w,@sid)})
    if(sid==NIL)
        quit
    end
    
    b:=brwCreate(0,0,maxrow(),maxcol())
    brwArray(b,listservices(w,sid))

    brwColumn(b,"Service",brwABlock(b,1),"XXXXXXXXXXXXXXXX")
    brwColumn(b,"Version",brwABlock(b,7),8)
    brwColumn(b,"Counter",brwABlock(b,6),"@RZ 9999999")
    brwColumn(b,"Address",brwABlock(b,5),"XXXXXXXXXXXXXXXXXXXXX")
    brwColumn(b,"Protocol",brwABlock(b,2),"XXXXXXXX")
    brwColumn(b,"Socket",brwABlock(b,3),"@RZ 9999")
    brwColumn(b,"StrtTime",brwABlock(b,4),"XXXXXXXX")
 
    brwMenu(b,"Refresh","Reread information",{||refresh(b,w,sid)})
    brwMenu(b,"Down","Stop selected service",{||down(b,w,sid)})
    brwMenu(b,"Clients","List of active clients",{||listclients(w,sid)})
    
    brwMenuName(b,"[RPCMONITOR "+VERSION+"]" )
    
    brwShow(b)
    brwLoop(b)
    brwHide(b)

    begin
        w:call("session.logout",{sid})
    end


*****************************************************************************
static function refresh(b,w,sid)
local pos:=brwArrayPos(b)
    brwArray(b,listservices(w,sid))
    if( pos>len(brwArray(b)) )
        b:gobottom
    end
    b:refreshall
    return .t.


*****************************************************************************
static function down(b,w,sid) 
local service:=brwArray(b)[brwArrayPos(b)][1]
local errblk:=errorblock({|x|break(x)}), e
    begin sequence
        w:call("system.down",{sid,service}) 
    recover using e
        if( service=="system" )
            alert("SYSTEM DOWN")
            quit
        else
            eval(errblk,e)       
        end
    end sequence
    errorblock(errblk)       
    refresh(b,w,sid)  
    return .t.
 

*****************************************************************************
static function listservices(w,sid)
local list:=w:call("system.listservices")
local n, service, version
local errblk:=errorblock(), e
    for n:=1 to len(list)
        service:=list[n][1]
        errorblock({|x|break(x)})
        begin sequence
            version:=w:call(service+".getversion",sid) 
        recover using e
            version:="n.a."
        end sequence
        errorblock(errblk)
        aadd(list[n],version)
    next
    asort(list,,,{|x,y|x[1]=="system".or.x[1]<y[1]})
    return list


*****************************************************************************
static function listclients(w,sid)
local list:=w:call("system.listclients")
local b:=brwCreate(0,0,maxrow(),maxcol())
    brwArray(b,list)
    brwColumn(b,"TimeOut",brwABlock(b,1),"XXXXXXX")
    brwColumn(b,"Counter",brwABlock(b,6),"@RZ 9999999")
    brwColumn(b,"Address",brwABlock(b,5),"XXXXXXXXXXXXXXXX")
    brwColumn(b,"Protocol",brwABlock(b,2),"XXXXXXXX")
    brwColumn(b,"Socket",brwABlock(b,3),"@RZ 9999")
    brwColumn(b,"StrtTime",brwABlock(b,4),"XXXXXXXX")
    brwMenuName(b,"[RPCMONITOR "+VERSION+"]" )
    brwMenu(b,"Refresh","Reread information",{||refresh_clients(b,w,sid)})
    brwShow(b)
    brwLoop(b)
    brwHide(b)
    return .t.

*****************************************************************************
static function refresh_clients(b,w,sid)
local pos:=brwArrayPos(b)
local list:=w:call("system.listclients")
    brwArray(b,list)
    if( pos>len(brwArray(b)) )
        b:gobottom
    end
    b:refreshall
    return .t.

*****************************************************************************
#include "login.say"
*****************************************************************************
static function loadlogin(getlist) 
    g_uid:picture:="@K AAAAAAAAAAAAAAAA"
    g_password:picture:="@K* XXXXXXXXXXXXXXXX"
    g_uid:varput(getenv("RPCUSER"))
    g_password:varput(getenv("RPCPASSW"))

*****************************************************************************
static function storelogin(getlist,w,sid) 
local e, success:=.f.
local uid:=g_uid:varget
local password:=g_password:varget
local eblk:=errorblock({|e|break(e)})
    begin sequence
        sid:=w:call("session.login",{uid,password})
        success:=.t.
    recover using e
        sid:=NIL
        alert("LOGIN FAILED;;"+e:operation+" ("+e:description+")")
    end sequence
    errorblock(eblk)
    return success

*****************************************************************************
