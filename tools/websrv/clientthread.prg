
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

#include "fileio.ch"
#include "directry.ch"
#include "websrv.ch"

*****************************************************************************
function client_thread(wcon)

local err

    begin

#ifdef HTTPS_SUPPORT
        if( wcon:secure )
            wcon:socket:=sslconAccept(sslcontext(),wcon:socket)
        end
#endif //HTTPS_SUPPORT

        do_client_thread(wcon)

#ifdef HTTPS_SUPPORT
    recover err <sslerror>
        #ifdef DEBUG1
            ? "SSLERROR:", err:description, date(), time(), wcon:peer
        #endif
#endif //HTTPS_SUPPORT

/*
    recover err
        set alternate to websrv-error additive
        set alternate on
        ? "-------------------------------"
        ? date(),time()
        ? "-------------------------------"
        ? err
        set alternate off
        set alternate to
*/
    finally
        client_close(wcon)
    end

*****************************************************************************
static function do_client_thread(wcon)

local thrcnt:=0
local request,workdir
local dirlst,page,repl,env,wd
local fd,size,buffer,nbyte

    while( thrcnt<=maxthread()/2 .and. NIL!=(request:=httprequestNew(wcon)) )

        thread_mutex_lock(mutex_mutex())
        thrcnt:=threadcount()
        thread_mutex_unlock(mutex_mutex())
        #ifdef DEBUG1
            ? "REQ*",str(thrcnt,2),date(),time(),wcon:peer,request:hostport,request:line1
        #endif

        if( virtualhost() )
            workdir:=rootdir()+a"/"+request:host
        else
            workdir:=rootdir()
        end

        if( right(request:url,1)==a"/" )
            request:url:=indexpage(workdir,request:url)
        end
        
        if( request:op $ a".GET.HEAD.POST." )
 
            if( a".."$request:url .and. a"/../"$a"/"+request:url+a"/" )
                repl:=mkerror(a"403 Forbidden")

            elseif( request:isexcluded )
                repl:=mkerror(a"404 Not Found (x)")

            elseif( !wcon:secure .and. request:issecure )
                if( wcon:redirport==NIL )
                    repl:=mkerror(a"404 Not Found (s)")
                else
                    if( xdirexist(workdir+request:url) .and. right(request:url,1)!=a"/" )
                        request:url+=a"/"
                    end
                    repl:=mkredir(a"302 Moved Temporarily",request:redir,request:url)
                end

            elseif( cgipath()!=NIL .and. left(request:url,9)==a"/cgi-bin/"  )
                cgienv(env:=inheritenv(),request,workdir)
                wd:=fpath0(cgiscript(request:url))
                repl:=cgipage(cgiscript(request:url),env,request,wd)

            elseif( xdirexist(workdir+request:url) )
                if( !right(request:url,1)==a"/" )  //see: 2.2.03
                    repl:=mkredir(a"301",request:same,request:url+a"/")
                else
                    repl:=mkheader(a"200 OK",page:=dirpage(workdir,request))
                    if( !request:op==a"HEAD" )
                        repl+=page
                    end
                end

            elseif( len(dirlst:=directory(workdir+request:url,"H"))!=1 )
                repl:=mkerror(a"404 Not Found")

            elseif( a".shtml"==right(request:url,6) )
                repl:=mkheader(a"200 OK",page:=ssipage(workdir,workdir+request:url))
                if( !request:op==a"HEAD" )
                    repl+=page
                end

            elseif( phppath()!=NIL .and. a".php"==right(request:url,4) )
                cgienv(env:=inheritenv(),request,workdir)
                phpenv(env,request,workdir) //továbbiak
                wd:=fpath0(workdir+request:url)
                repl:=cgipage(phpscript(request:url),env,request,wd)
                
            elseif( !modified(request,dirlst[1]) )
                repl:=mkerror(a"304 Not Modified")

            elseif( dirlst[1][F_SIZE]>1024*1024 ) //nagy filé
                repl:=mkheader(a"200 OK",dirlst[1])
                if( !request:op==a"HEAD" )
                    size:=dirlst[1][F_SIZE]
                end

            else
                repl:=mkheader(a"200 OK",dirlst[1])
                if( !request:op==a"HEAD" )
                    repl+=memoread(workdir+request:url,.t.)
                end
            end
        else
            repl:=mkerror(a"501 Not Implemented")
        end

        if( empty(repl) )
            exit
        else
            http_writemessage(wcon:socket,repl) 
        end

        if( !empty(size) )
            fd:=fopen(workdir+request:url,FO_READ)
            if( fd>0 )
                buffer:=replicate(x"20",4096)
                while( 0<(nbyte:=fread(fd,@buffer,4096)) )
                    wcon:socket:send(left(buffer,nbyte))
                end
                fclose(fd)
            end
            size:=NIL
        end
    end

*****************************************************************************
static function client_close(wcon)
    wcon:close
    thread_mutex_lock(mutex_mutex())
    threadcount(threadcount()-1)
    thread_cond_signal(cond_finish())
    thread_mutex_unlock(mutex_mutex())
    #ifdef DEBUG1
        ?? "!"
    #endif

    #ifdef _UNIX_
        while(0<waitpid(,,1));end //zombiek, 1==WNOHANG
    #endif

    thread_exit()

*****************************************************************************
function mkerror(code)
local head:=strtran(a"HTTP/1.1 xxx"+CRLF,a"xxx",code) 

    head+=a"Content-Type: text/plain"+CRLF
    head+=a"Content-Length: "+str2bin(alltrim(str(len(code))))+CRLF

    #ifdef DEBUG1
        ?? "",code
    #endif
 
    #ifdef DEBUG0
      ? ">>>>> send >>>>>>>>>>>>>>>"
      ? head
    #endif
    return head+CRLF+code //binary

*****************************************************************************
static function mkredir(code,host,url)
local head:=strtran(a"HTTP/1.1 xxx"+CRLF,"xxx",code) 
local absurl:=url
    if( left(absurl,1)==a"." )
        absurl:=substr(absurl,2)
    end
    if( left(absurl,1)!=a"/" )
        absurl:=a"/"+absurl
    end
    absurl:=str2bin(host)+absurl

    head+=a"Content-Type: text/plain"+CRLF
    head+=a"Location: "+absurl+CRLF
    head+=a"Content-Length: "+str2bin(alltrim(str(len(absurl))))+CRLF

    #ifdef DEBUG1
        ?? "",code
    #endif

    #ifdef DEBUG0
      ? ">>>>> send >>>>>>>>>>>>>>>"
      ? head
    #endif
    return head+CRLF+absurl //binary

*****************************************************************************
static function mkheader(code,dirent)
local head:=strtran(a"HTTP/1.1 xxx"+CRLF,"xxx",code) 

    if( valtype(dirent)=="A" )
        head+=a"Content-Type: "+contenttype(dirent[F_NAME])+CRLF
        head+=a"Content-Length: "+str2bin(alltrim(str(dirent[F_SIZE])))+CRLF 
        //head+=a"Last-Modified: "+str2bin(ctime(dati2ostime(dirent[F_DATE],dirent[F_TIME])))
        head+=a"Last-Modified: "+str2bin(gmtime2httpdate(dati2ostime(dirent[F_DATE],dirent[F_TIME])))
        head+=a"Connection: Keep-Alive"+CRLF
    else
        head+=a"Content-Type: text/html"+CRLF
        head+=a"Content-Length: "+str2bin(alltrim(str(len(dirent))))+CRLF 
        head+=a"Connection: Keep-Alive"+CRLF
    end

    #ifdef DEBUG1
        ?? "",code
    #endif
        
    #ifdef DEBUG0
      ? ">>>>> send >>>>>>>>>>>>>>>"
      ? head
    #endif
    return head+CRLF //binary


*****************************************************************************
static function modified(request,dirent)
local since:=http_getheader(request:req,"if-modified-since"),da,ti
    if( empty(since) )
        return .t.
    end
    da:=dirent[F_DATE]
    ti:=dirent[F_TIME]
    return httpdate_value(since) < dati2ostime(da,ti)::gmtime2httpdate::httpdate_value

*****************************************************************************
