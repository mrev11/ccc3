
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

*****************************************************************************
function xmlrpc_wrapper() // -> {host,port,SSL/PLAIN/NIL}
static w
    if( w==NIL )
        w:=split(getenv("XMLRPC_WRAPPER")) 
        w:=asize(w,3)
    end
    return w

*****************************************************************************
function xmlrpc_sslcontext(ctx)

// A konnektálás előtt egy program meghívhatja ezt a függvényt,
// és ekkor beállíthat egy tetszőleges sslcontextet, ami szükséges
// neki a kliens/szerver hitelesítéshez. Alapesetben hitelesítés
// nélküli sslctx jön létre, ilyenkor csak titkosítás van.

static sslcontext

    if( ctx!=NIL )
        sslcontext:=ctx
    end
    if( sslcontext==NIL )
        sslcontext:=sslctxNew()
    end
    return sslcontext

*****************************************************************************
function xmlrpc_client() // -> client to wrapper
local w,c
    w:=xmlrpc_wrapper()
    c:=xmlrpcclientNew(w[1],w[2])
    //c:=xmlrpcclientstatisticsNew(w[1],w[2])
    if( w[3]!=NIL .and. upper(w[3])=="SSL" )
        c:sslcontext:=xmlrpc_sslcontext()
    end
    c:keepalive:=.t.
    //c:debug:=.t.
    return c

*****************************************************************************
function xmlrpc_register(server,module,version)

local c,n:=0
local success:=.f.

    c:=xmlrpc_client()
    
    while( !success .and. ++n<200 )
        begin
            ? module, version
            c:call("system.register",module)
            ?? " registered successfully at", date(), time()
            aadd(server:socketlist,c:socket)
            success:=.t.
        recover
            ?? " wait to register..." 
            sleep(500)
        end
    end
    return success

*****************************************************************************
function xmlrpc_verifyconnection(server,r)
local e
    if( server:socketlist[1]==r )
        e:=xmlrpcerrorNew("xmlrpc_verifyconnection")
        e:description:="wrapper died"
        break(e)
    end

*****************************************************************************
function xmlrpc_invalidsid() //throws an invalidsid
local e:=xmlrpcinvalidsiderrorNew("xmlrpc_invalidsid")
    //callstack()
    break(e)
 
*****************************************************************************
