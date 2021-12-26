
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

#define CRLF x"0d0a"

******************************************************************************
function main()

local n
local envx:=a"", env:=environment()
local post:=a"", buf:=replicate(a" ",1024)
local args:=a""

    errorblock({|*|cgi.error(*)})

    for n:=1 to len(env)
        envx+=str2bin(env[n])+CRLF
    end

    if( getenv("REQUEST_METHOD")=="POST" )
        while( 0<(n:=fread(0,@buf,len(buf))) )
            args+=left(buf,n)
        end
    else
        args:=str2bin(getenv("QUERY_STRING"))
    end

    post+=args
    post+=arghash(args)

    post+=CRLF+a"Öt szép szűzlány őrült írót nyúz."
    post+=CRLF+a"Kázmér füstölgő fűnyírót húz."
    
    cgi.response("200 Ok","text/plain",envx+CRLF+post)


******************************************************************************
static function arghash(args)
local hash,item,n,pos

    hash:=simplehashNew()
    args::=strtran(a"+",a" ")::split(a"&")
    for n:=1 to len(args)
        item:=args[n]::websrv.hexdecode
        pos:=at("=",item)
        if( pos>0 )
            hash[item[1..pos-1]]:=item[pos+1..]
        end
    next
    
    //return hash

    set console off 
    set printer to log-temp
    set printer on 

    hash:list

    set printer off 
    set printer to
    set console on
    
    return  memoread("log-temp",.t.)


******************************************************************************
function cgi.response(rcode,ctype,content)
    if( rcode!=NIL )
        ?? strtran(a"HTTP/1.1 xXx"+CRLF,"xXx",str2bin(rcode)) 
    end
    ?? a"Content-Type: "+str2bin(ctype)+a";charset=UTF-8"+CRLF
    if( content!=NIL )
        ?? a"Content-Length: "+str2bin(alltrim(str(len(content))))+CRLF 
        ?? CRLF
        ?? str2bin(content)
    end

******************************************************************************
function cgi.error(e) //el nem kapott kivételek kezelése

local i,env 

    cgi.response("500 Internal Error","text/plain")

    ? "unrecovered CGI error occurred"

    if( valtype(e)=="O" .and. e:isderivedfrom(errorClass()) )

        ? "errorclass:",e:classname

        if(!empty(e:operation))
            ? "operation:",e:operation
        end
    
        if(!empty(e:description))
            ? "description:",e:description
        end
    
        if( valtype(e:args)=="A" )
            ? "args:{"
            for i:=1 to len(e:args)
                if(i>1)
                    ?? ", "
                end
                __varprint(e:args[i])
            next
            ?? "}"
        end
    
        if(!empty(e:candefault))
            ? "candefault:",e:candefault
        end
    
        if(!empty(e:canretry))
            ? "canretry:",e:canretry
        end
    
        if(!empty(e:cansubstitute))
            ? "cansubstitute:",e:cansubstitute
        end
    
        if(!empty(e:filename))
            ? "filename:",e:filename  
        end
    
        if(!empty(e:gencode))   
            ? "gencode:",e:gencode
        end
    
        if(!empty(e:oscode))  
            ? "oscode:",e:oscode
        end
    
        if(!empty(e:severity))
            ? "severity:",e:severity
        end
    
        if(!empty(e:subcode))    
            ? "subcode:", e:subcode
        end
    
        if(!empty(e:subsystem))
            ? "subsystem:",e:subsystem
        end
    
        if(!empty(e:tries))
            ? "tries:",e:tries
        end
    else
        ? "errorclass:", valtype(e), e
    end

    callstack()
    varstack()

    env:=environment()
    for i:=1 to len(env)
        ? str2bin(env[i])
    end

    errorlevel(1)
    quit

******************************************************************************
