
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

//a klienst hitelesítő, önmagát igazoló zerver

#include "ssl.ch"

#include "case.ch"


******************************************************************************************
function main()

local ip:="127.0.0.1"
local port:=40000
local sslflag:=.t.
local ctx,mode
local ss,s,err,result

local capath
local cafile

// A cafile/capath-ban a kliens hitelesítéshez
// használható certificate-ek vannak megadva.
// Az 1 db cafile-ban sok certificate section lehet.
// A capath directory filéiben egy-egy certificate lehet.
// Egy kliens akkor lesz elfogadva, ha olyan certificate-je van,
// amit aláírtak egy cafile/capath-ban levő certificate-hez
// tartozó kulccsal. A két legegyszerűbb eset:
// 1. Berakjuk capath-ba a kliensek önaláírt certificate-jeit.
// 2. Egy közös kulccsal aláírjuk a kliensek certificate-jeit.
//
// server1.pem-mel van alairva a kliens cert-je
// server2.pem-mal igazolja magat a szerver a kliens fele

    set printer on 
    set printer to log-server1

    ? CERTS

    if( CERTS=="SERVER_SIGNED"  )
        // hitelesites (1)
        // a server1.pem-mel alairt 
        // kliens cert-eket elfogadjuk
        cafile:="pem_server/server1.pem"
    end

    if( CERTS=="SELF_SIGNED"  )
        // hitelesites (2)
        // a cafile-ban levo onalairt 
        // kliens cert-eket elfogadjuk
        cafile:="pem_server/clientss-cert.pem"
    end

    ctx:=sslctxNew("TLS_server") 
    // a szerver server2.pem-mel igazolja magat
    // ugyanez a kulcs kell a titkositashoz 
    ctx:use_certificate_file("pem_server/server2.pem")
    ctx:use_privatekey_file("pem_server/server2.pem")

    if( capath!=NIL .or. cafile!=NIL )
        mode := SSL_VERIFY_PEER_CERT
        ctx:set_verify(mode)
        ctx:set_verify_depth(1)
        ctx:load_verify_locations(cafile,capath)
    end

    ss:=socketNew()
    ss:reuseaddress(.t.)
    ss:bind(ip,port)
    ss:listen

    ? "listen at: ",ip,port
    
    while( .t. )
        begin
            s:=ss:accept()
            if( sslflag!=NIL )        
                s:=sslconAccept(ctx,s) //socket -> sslcon
            end
            
            ?
            while( s:waitforrecv )
                result:=s:recv(128,0) //socket VAGY sslcon (nem vár)
                if( result!=NIL )            
                    ?? result
                else
                    exit
                end
            end

        recover err <socketerror>
            ? err:description

        finally
            if( s!=NIL )
                s:close //socket VAGY sslcon
            end
            s:=NIL
            ? "closed"
        end
    end
    

******************************************************************************************

