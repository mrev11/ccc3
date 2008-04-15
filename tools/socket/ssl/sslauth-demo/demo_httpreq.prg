
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

//küld egy HTTPS requestet

#include "ssl.ch"

static crlf:=x"0d0a"

******************************************************************************
function main()

local ctx,s

local x:=<<REQ>>GET / HTTPS/1.1
Host: localhost
User-Agent: demo-client
Accept: text/html;text/plain;
Accept-Charset: UTF-8,*
Connection: keep-alive<<REQ>>+bin2str(crlf+crlf)

    ctx:=sslctxNew() 
    
    //ez alá van írva localhost.pem-mel
    ctx:use_certificate_file("demo-cert.pem")  
    ctx:use_privatekey_file("demo-key.pem")

    s:=sslconNew(ctx)
    s:connect("localhost",443)
    s:send(x)
    ? s:recvall(1000) //1 sec timeout
    s:close

    ?

******************************************************************************

