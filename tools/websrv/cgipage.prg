
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
function cgipage(script,env,request,wd) //CGI/PHP support

local op,req,sck
local pp,pr,pw,ps,n
local page:=x"",buf:=replicate(x"20",1024) 
local pos,hdr,bod,len
local status,repl

    op:=request:op
    req:=request:req
    sck:=request:wcon:socket

    if( xdirexist(script) )
        repl:=mkerror(a"403 Forbidden")
    elseif( !fileexist(script) )
        repl:=mkerror(a"404 Not Found")
    elseif( !fileisexecutable(script) )
        repl:=mkerror(a"403 Forbidden")
    elseif( !op$a".GET.POST." )
        repl:=mkerror(a"403 Forbidden")
    else
        pp:=cgichild({script},env,wd,sck)
        pr:=pp[1]
        pw:=pp[2]
        ps:=pp[3]
        
        if( op==a"POST" )
            #ifdef DEBUG2
                //? "POST>>>",http_body(req)
                memowrit("querystring",http_body(req))
            #endif
            fwrite(pw,http_body(req))
        end
        fclose(pw)
        
        while( 0<(n:=fread(pr,@buf,len(buf))) )
            page+=left(buf,n)
        end
        fclose(pr)
        if(ps!=NIL);fclose(ps);end //kész: cgishutdown elengedve

        #ifdef DEBUG2
            ? "===CGI-BEG==="
            ? page //CGI output
            ? "===CGI-END==="
        #endif

        //Mindig kell legyen Content-Length.
        //Egyes programok a szabványos CRLF sorvégek helyett 
        //szimpla LF-et használnak, ezeket kijavítjuk.
 
        if( 0<(pos:=at(x"0d0a0d0a",page)) )
            len:=len(page)-(pos-1)-4
            page:=http_setheader(page,"Content-Length",alltrim(str(len)))
        elseif( 0<(pos:=at(x"0a0a",page)) )
            len:=len(page)-(pos-1)-2
            hdr:=left(page,pos+1)
            bod:=substr(page,pos+2)
            page:=strtran(hdr,x"0a",x"0d0a")+bod
            page:=http_setheader(page,"Content-Length",alltrim(str(len)))
        else
            //??
        end

        if( !empty(page) )
            status:=http_getheader(CRLF+page,"Status")
            if( status!=NIL )
                page:=a"HTTP/1.1 "+status+CRLF+page
            elseif( !left(page,5)==a"HTTP/" )
                page:=a"HTTP/1.1 200 Ok"+CRLF+page
            end
        end
        repl:=page
    end
    
    return repl

*****************************************************************************
function phpscript(url) //url -> executable
    return phppath()

*****************************************************************************
function cgiscript(url)  //url -> executable
    return cgipath()+substr(bin2str(url),9)  //kivágva: "/cgi-bin"

*****************************************************************************
