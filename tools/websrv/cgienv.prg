
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

#include "websrv.ch"

*****************************************************************************
function cgienv(env,request,root)

local sck,req,op,url,par
local hdr,host,addr

    sck:=request:wcon:socket
    req:=request:req
    op:=bin2str(request:op)
    url:=bin2str(request:url)
    if( request:par!=NIL )
        par:=bin2str(request:par)
    end
    root:=bin2str(root)
    
    if(NIL!=(hdr:=http_getheader(req,"Content-Length")))
        aadd(env,"CONTENT_LENGTH="+bin2str(hdr))
    end
    
    if(NIL!=(hdr:=http_getheader(req,"Content-Type")))
        aadd(env,"CONTENT_TYPE="+bin2str(hdr))
    end

    aadd(env,"DOCUMENT_ROOT="+root)
    aadd(env,"GATEWAY_INTERFACE=CGI/1.1")
    
    if(NIL!=(hdr:=http_getheader(req,"Accept")))
        aadd(env,"HTTP_ACCEPT="+bin2str(hdr))
    end

    if(NIL!=(hdr:=http_getheader(req,"Accept-Charset")))
        aadd(env,"HTTP_ACCEPT_CHARSET="+bin2str(hdr))
    end
    
    if(NIL!=(hdr:=http_getheader(req,"Accept-Encoding")))
        aadd(env,"HTTP_ACCEPT_ENCODING="+bin2str(hdr))
    end
    
    if(NIL!=(hdr:=http_getheader(req,"Accept-Language")))
        aadd(env,"HTTP_ACCEPT_LANGUAGE="+bin2str(hdr))
    end

    if(NIL!=(hdr:=http_getheader(req,"Cache-Control")))
        aadd(env,"HTTP_CACHE_CONTROL="+bin2str(hdr))
    end
    
    if(NIL!=(hdr:=http_getheader(req,"Connection")))
        aadd(env,"HTTP_CONNECTION="+bin2str(hdr))
    end
    
    if(NIL!=(hdr:=http_getheader(req,"Cookie")))
        aadd(env,"HTTP_COOKIE="+bin2str(hdr))
    end

    if(NIL!=(hdr:=http_getheader(req,"Host")))
        host:=split(bin2str(hdr),":")
        aadd(env,"HTTP_HOST="+host[1])
        aadd(env,"SERVER_NAME="+host[1])
        aadd(env,"SERVER_ADMIN=webmaster@"+host[1])
        if( NIL!=(addr:=gethostbyname(host[1])) )
            aadd(env,"SERVER_ADDR="+bin2str(addr)) 
        end
        if( len(host)>=2 )
            aadd(env,"SERVER_PORT="+host[2])
        else
            aadd(env,"SERVER_PORT=80")
        end
    end

    if(NIL!=(hdr:=http_getheader(req,"Keep-Alive")))
        aadd(env,"HTTP_KEEP_ALIVE="+bin2str(hdr))
    end
    
    if(NIL!=(hdr:=http_getheader(req,"Referer")))
        aadd(env,"HTTP_REFERER="+bin2str(hdr))
    end
    
    if(NIL!=(hdr:=http_getheader(req,"User-Agent")))
        aadd(env,"HTTP_USER_AGENT="+bin2str(hdr))
    end

    aadd(env,"QUERY_STRING="+if(par==NIL,"",par))
    aadd(env,"REMOTE_ADDR="+bin2str(getpeername(sck:fd)))
    //aadd(env,"REMOTE_PORT=") //??
    aadd(env,"REQUEST_METHOD="+op)
    aadd(env,"REQUEST_URI="+url+if(par==NIL,"","?"+par))
    aadd(env,"SCRIPT_FILENAME="+if(cgipath()==NIL,"",cgiscript(url)))
    aadd(env,"SCRIPT_NAME="+url)
    aadd(env,"SERVER_PROTOCOL=HTTP/1.1")
    aadd(env,"SERVER_SIGNATURE=<address>"+copyright()+"</address>"+crlf())
    aadd(env,"SERVER_SOFTWARE="+srvname()+"/"+srvversion())

*****************************************************************************
function phpenv(env,request,root)
local hdr,sck,op,url,par

    sck:=request:wcon:socket
    op:=bin2str(request:op)
    url:=bin2str(request:url)
    if( request:par!=NIL )
        par:=bin2str(request:par)
    end
    root:=bin2str(root)

    aadd(env,"REDIRECT_STATUS=200")
    aadd(env,"REDIRECT_URL="+url)
    aadd(env,"PATH_TRANSLATED="+root+url) //kötelező
    aadd(env,"PATH_INFO="+url)
    
    xaadd(env,"SCRIPT_FILENAME=","SCRIPT_FILENAME="+phppath())
    xaadd(env,"SCRIPT_NAME=","SCRIPT_NAME=/cgi-bin/php")

*****************************************************************************
function inheritenv(env)
    if( inheritmode()>=1 )
        env:=environment()//mindent továbbad
    else
        env:={}
        aadd(env,"PATH="+getenv("PATH"))
        #ifdef _UNIX_
            aadd(env,"LD_LIBRARY_PATH="+getenv("LD_LIBRARY_PATH"))
        #else
            aadd(env,"SYSTEMROOT="+getenv("SYSTEMROOT"))
        #endif
    end
    return env

*****************************************************************************
