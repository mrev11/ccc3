
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

//a klienst hitelesito, onmagat igazolo zerver

#include "ssl.ch"

******************************************************************************
function main(sslflag)

local ctx,mode
local ss,s,err,result

//local cafile,capath:="cert"
local cafile:="cert/localhost-cert.pem",capath

// A cafile/capath-ban a kliens hitelesiteshez
// hasznalhato certificate-ek vannak megadva.
// Az 1 db cafile-ban sok certificate section lehet.
// A capath directory fileiben egy-egy certificate lehet.
// Egy kliens akkor lesz elfogadva, ha olyan certificate-je van,
// amit alairtak egy cafile/capath-ban levo certificate-hez
// tartozo kulccsal. A ket legegyszerubb eset:
// 1. Berakjuk capath-ba a kliensek onalairt certificate-jeit.
// 2. Egy kozos kulccsal alairjuk a kliensek certificate-jeit.
// A demoban hasznalt demo-cert ala van irva loclahost.pem-mel.
//
// A demoban localhost.pem ket szerepet is jatszik.
// 1. Szerver azonositas es titkositas.
// 2. Kliens hitelesites.
// Elesben ehhez kulon kulcsokat ajanlatos hasznalni.

    ctx:=sslctxNew("SSLv23_server") 
    ctx:use_certificate_file("localhost.pem")
    ctx:use_privatekey_file("localhost.pem")

    if( capath!=NIL .or. cafile!=NIL )
        mode := SSL_VERIFY_PEER_CERT
        ctx:set_verify(mode)
        ctx:set_verify_depth(1)
        ctx:load_verify_locations(cafile,capath)
    end

    ss:=socketNew()
    ss:reuseaddress(.t.)
    ss:bind("127.0.0.1",40000)
    ss:listen
    
    while( .t. )
        begin
            s:=ss:accept()
            if( sslflag!=NIL )        
                s:=sslconAccept(ctx,s) //socket -> sslcon
            end
            
            ?
            while( s:waitforrecv )
                ?? result:=s:recv(128,0) //socket VAGY sslcon (nem var)

                if( result==NIL )            
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

******************************************************************************

