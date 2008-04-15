
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

//a szervert hitelesítő, önmagát igazoló kliens

#include "ssl.ch"

function main()

local ctx,mode
local s,x:=a"Öt szép szűzlány őrült írót nyúz",n

local cafile:="cert/localhost-cert.pem"
//local cafile:="demo-cert.pem" //ellenpróba: ezzel nem megy

    ctx:=sslctxNew() 
    
    //ez alá van írva localhost.pem-mel
    ctx:use_certificate_file("demo-cert.pem")  
    ctx:use_privatekey_file("demo-key.pem")
    
    if( cafile!=NIL )
        mode := SSL_VERIFY_PEER_CERT
        ctx:set_verify(mode)
        ctx:set_verify_depth(1)
        ctx:load_verify_locations(cafile)
        
        //szerver/kliens hitelesítése egyformán
    end

    s:=sslconNew(ctx)
    s:connect("localhost",40000)
    
    for n:=1 to len(x)
        ? n
        s:send( substr(x,n,1)  )
        sleep(30)
    next

    s:close

    ?

