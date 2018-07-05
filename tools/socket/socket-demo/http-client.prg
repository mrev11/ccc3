
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

//e.g. http-client.exe ok 80 /robots.txt
 

******************************************************************************
function main(host,port,fspec)

local s:=socket(), req, rsp
 
    connect(s,host,val(port))

    ? req:=a"GET "+str2bin(fspec)+a" HTTP/1.1"+x"0d0a0d0a"

    ? "send:", swrite(s,req)
    rsp:=http_readmessage(s,10000)
    ? "recv:", len(rsp)
    
    if( !empty(rsp) )
        memowrit("log-response",rsp)
    else
        ferase("log-response")
    end
    
    
******************************************************************************
    