
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

//kuld egy HTTPS requestet

#include "ssl.ch"

static crlf:=x"0d0a"

******************************************************************************
function main()

local ctx,s,names:={}

local x:=<<REQ>>GET / HTTPS/1.1
Host: comfirm.hu
User-Agent: demo-client
Accept: text/html;text/plain;
Accept-Charset: UTF-8,*
Connection: keep-alive<<REQ>>+bin2str(crlf+crlf)

    ctx:=sslctxNew() 
    
    //ez ala van irva localhost.pem-mel
    ctx:use_certificate_file("demo-cert.pem")  
    ctx:use_privatekey_file("demo-key.pem")

#define VERIFY
#ifdef VERIFY
    ctx:set_verify(SSL_VERIFY_PEER_CERT)
    ctx:set_verify_depth(5)
    ctx:load_verify_locations("comfirm.hu-cert.pem")
#endif

    s:=sslconNew(ctx)
    s:connect("comfirm.hu",443,{|x|aadd(names,x)})
    ? names
    s:send(x)
    ? s:recvall(1000) //1 sec timeout
    s:close
    ?


******************************************************************************

