
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
#include "ssl.ch"
#include "websrv.ch"
#include "websrv.ver"

static mutex:=thread_mutex_init()
static finish:=thread_cond_init()
static mutprn:=thread_mutex_init()
static mutspw:=thread_mutex_init()

static srvname:="CCC3-WebServer"
static srvversion:=VERSION

static threadcount:=0       //számolja az aktív threadeket
static sslcontext           //SSL context
static rootdir              //ez lesz a working directory
static dircharset           //dirpage-ekben deklarált charset
static virtualhost:=.f.     //rootdir -> rootdir/http_host
static cgipath              //itt van a cgi-bin directory
static phppath              //itt van a php interpreter (/usr/lib/cgi-bin/php)
static cgitime:=60          //ha a CGI nincs kész ennyi idő alatt, lelőjük
static inheritmode:=0       //minimális környezet továbbadva a CGI-knek
static excluded_url:=""     //kizárt url-ek
static secure_url:=""       //secure url-ek
static maxthread:=8         //max ennyi working threadet csinál

*****************************************************************************
//mutexes
*****************************************************************************
function mutex_mutex(); return mutex
function cond_finish(); return finish
function mutex_print(); return mutprn
function mutex_spawn(); return mutspw

*****************************************************************************
//globals
*****************************************************************************
function threadcount(x)
    if( x!=NIL )
        threadcount:=x
    else
        x:=threadcount
    end
    return x

function srvname();         return  srvname
function srvversion();      return  srvversion
function sslcontext();      return  sslcontext
function rootdir();         return  rootdir
function dircharset();      return  dircharset
function virtualhost();     return  virtualhost
function cgipath();         return  cgipath
function phppath();         return  phppath
function cgitime();         return  cgitime
function inheritmode();     return  inheritmode
function excluded_url();    return  excluded_url
function secure_url();      return  secure_url
function maxthread();       return  maxthread

*****************************************************************************
static function usage()
    ?? copyright()
    ? <<helptext>>
Usage: websrv.exe [OPTION]...

    -l  --listener      <if:pp:sp>      interface:plainport:secureport (:8080:)
        --reuseaddr                     reuse address on (off)
        --log           <fspec>         log file (2-nd fd)
    -r  --rootdir       <dspec>         root working directory (`pwd`)
        --dircharset    <charset>       charset in dirpages (ISO-8859-2/UTF-8)
        --virtualhost                   rootdir --> rootdir/http_host (off)
    -u  --userid        <uid>           switch to this effective userid (none)
        --maxthread     <number>        max number of working threads (8)
        --cgipath       <dspec>         path to cgi-bin (no CGI support)
        --phppath       <fspec>         file spec of php-cgi (no PHP support)
        --cgitime       <sec>           max CGI execution time (60)
        --inheritmode   <number>        environment inheritance mode (0=inherit minimal)
    -x  --excluded      <url>           list of exluded url elements (none)
    -s  --secure        <url>           list of secure url elements (none)
    -k  --keyfile       <fspec>         PEM file with a certificate and privatekey (none)
        --capath        <dspec>         certificate path to client authentication (none)
        --cafile        <fspec>         certificate file to client authentication (none)
    -h  --help                          print this help and quit

<<helptext>>    
    quit

*****************************************************************************
function copyright()
    return srvname+"/"+srvversion+" (C) ComFirm"

*****************************************************************************
static function includepar(opt,x)
local par,n,p,i

    par:=substr(opt[x],2)
    par:=memoread(par)
    par:=strtran(par,chr(13),"")
    par:=split(par,chr(10)) //sorokra bontva
    
    adel(opt,x)
    asize(opt,len(opt)-1)

    for n:=1 to len(par)
        p:=par[n]
        if( "#"$p )
            p:=left(p,at("#",p)-1) 
        end

        p:=split(p," ") //szavakra bontva
        for i:=1 to len(p)
            if( !empty(p[i]) )
                asize(opt,len(opt)+1)
                ains(opt,x)
                opt[x++]:=p[i]
            end
        next
    next

*****************************************************************************
static function procpar(par)
local x:="",pos,var
    while( 0<(pos:=at("$(",par)) )
        x+=left(par,pos-1)
        par:=substr(par,pos+2)
        pos:=at(")",par)
        var:=left(par,pos-1)
        x+=getenv(var)
        par:=substr(par,pos+1)
    end
    x+=par
    return x

*****************************************************************************
function main()

local listenerdef:={}      //definitions of listeners
local listenerlst:={}      //list of listener objects
local userid               //átvált erre, hogy ne rootként dolgozzon
local logfile              //ide írja a logot, default stderr
local reuseaddr:=.f.       //beállítsa-e reuseaddress socket opciót
local keyfile              //PEM filé specifikáció (szerver hitelesítés)
local cafile               //certificate file (bekapcsolja a kliens hitelesítést)
local capath               //certificate path (bekapcsolja a kliens hitelesítést)

local srvblk:={|x|client_thread(x)}
local opt:=aclone(argv()),n
local listener,wcon,fdlog

    set date format "yyyy-mm-dd"
    signalblock({|s|sighandler(s)})
    
    for n:=1 to len(opt)

        if( left(opt[n],1)=="@"  )
            includepar(opt,n--)

        elseif( opt[n]=="-l" .or. opt[n]=="--listener" )
            aadd(listenerdef,procpar(opt[++n]))

        elseif( opt[n]=="--reuseaddr"  )
            reuseaddr:=.t.

        elseif( opt[n]=="--log" )
            logfile:=procpar(opt[++n])

        elseif( opt[n]=="-r" .or. opt[n]=="--rootdir" )
            rootdir:=procpar(opt[++n])

        elseif( opt[n]=="--dircharset" )
            dircharset:=procpar(opt[++n])

        elseif( opt[n]=="--virtualhost"  )
            virtualhost:=.t.

        elseif( opt[n]=="-u" .or. opt[n]=="--userid" )
            userid:=val(procpar(opt[++n]))

        elseif( opt[n]=="--maxthread" )
            maxthread:=val(procpar(opt[++n]))

        elseif( opt[n]=="--cgipath"  )
            cgipath:=procpar(opt[++n])

        elseif( opt[n]=="--phppath"  )
            phppath:=procpar(opt[++n])

        elseif( opt[n]=="--cgitime"  )
            cgitime:=val(procpar(opt[++n]))

        elseif( opt[n]=="--inheritmode"  )
            inheritmode:=val(procpar(opt[++n]))

        elseif( opt[n]=="-x" .or. opt[n]=="--excluded" )
            excluded_url+=":"+procpar(opt[++n])+":"

        elseif( opt[n]=="-s" .or. opt[n]=="--secure" )
            secure_url+=":"+procpar(opt[++n])+":"

        elseif( opt[n]=="-k" .or. opt[n]=="--keyfile" )
            keyfile:=procpar(opt[++n])

        elseif( opt[n]=="--capath" )
            capath:=procpar(opt[++n])

        elseif( opt[n]=="--cafile" )
            cafile:=procpar(opt[++n])

        elseif( opt[n]=="-h" .or. opt[n]=="--help" )
            usage()
        else
            ? "Invalid option:", opt[n]
            ?
            usage()
        end
    end

    if( logfile!=NIL )
        fdlog:=fopen(logfile,FO_CREATE+FO_WRITE+FO_APPEND)
        if( fdlog<0 )
            ? "ERROR logfile:",logfile,"open failed",ferror(); ?;quit
        end
        fdup(fdlog,2)
    end

    if( rootdir!=NIL )
        if( 0>dirchange(rootdir) )
            ? "ERROR rootdir:",rootdir,"dirchange failed",ferror(); ?;quit
        end
    end
    rootdir:=xdirname()

    if( dircharset==NIL )
        #ifdef _CCC2_
            dircharset:="ISO-8859-2"
        #endif
        #ifdef _CCC3_
            dircharset:="UTF-8"
        #endif
    end

    if( empty(listenerdef) )
        aadd(listenerdef,":8080:") //minden interfész, plain:8080, ssl:-
    end

    PRINT(listenerdef)
    PRINT(reuseaddr)
    PRINT(logfile)
    PRINT(rootdir)
    PRINT(dircharset)
    PRINT(virtualhost)
    PRINT(userid)
    PRINT(maxthread)
    PRINT(cgipath)
    PRINT(phppath)
    PRINT(cgitime)
    PRINT(inheritmode)
    PRINT(excluded_url)
    PRINT(secure_url)
    PRINT(keyfile)
    PRINT(capath)
    PRINT(cafile)

    #ifdef HTTPS_SUPPORT
        if( keyfile!=NIL )
            sslcontext:=sslctxNew()
            sslcontext:use_certificate_file(keyfile)
            sslcontext:use_privatekey_file(keyfile)
            sslcontext:check_private_key
            sslcontext:set_session_id_context("websrv") //CCC default=argv(0)+pid
            //sslcontext:session_cache_mode:=0 //default=SSL_SESS_CACHE_SERVER
            //sslcontext:session_cache_timeout:=60 //default=300
            sslcontext:session_cache_size:=1024 //default=1024*20
            sslcontext:quiet_shutdown:=.t.

            if( capath!=NIL .or. cafile!=NIL )
                sslcontext:set_verify(SSL_VERIFY_PEER_CERT)
                sslcontext:set_verify_depth(1)
                sslcontext:load_verify_locations(cafile,capath)
                if( cafile!=NIL )
                    sslcontext:load_client_ca_file(cafile)
                    //kérdés, hogy nem kellene-e külön filé,
                    //így a firefox csak olyan certificate-et küld,
                    //amit a cafile-beli ca írt alá
                end
            end
        end
    #endif //HTTPS_SUPPORT

    for n:=1 to len(listenerdef)
        makelistener(listenerlst,listenerdef[n])
    next

    for n:=1 to len(listenerlst)
        listenerlst[n]:socket:reuseaddress(reuseaddr)
        listenerlst[n]:bind
        listenerlst[n]:listen
    next

    if( userid!=NIL )
        if( setuid(userid)<0 )
            ? "ERROR userid:",userid,"setuid failed",ferror(); ?;quit
        end
    end
    
    ? "Server started ", date(), time()
    ?

    while( .t. )
        thread_mutex_lock(mutex)
        while( threadcount>=maxthread )
            thread_cond_wait(finish,mutex)
        end
        thread_mutex_unlock(mutex)

        listener:=aclone(listenerlst)
        while( 0>=select(listener,,,10000) )
            #ifdef _UNIX_
                while( 0<waitpid(,,1) ) //1==WNOHANG (csak UNIX)
                    //szabad idejében takarít
                end
            #endif
            #ifdef HTTPS_SUPPORT
                if( sslcontext!=NIL )
                    sslcontext:flush_sessions //szabad idejében takarít
                end
            #endif //HTTPS_SUPPORT
            listener:=aclone(listenerlst)
        end

        for n:=1 to len(listener)
            thread_mutex_lock(mutspw)
            wcon:=webconNew(listener[n])
            thread_mutex_unlock(mutspw)

            if( wcon!=NIL ) //FreeBSD-n néha NIL
                thread_mutex_lock(mutex)
                ++threadcount
                thread_mutex_unlock(mutex)
                thread_create_detach(srvblk,wcon) 
            end
        next
    end

*****************************************************************************
