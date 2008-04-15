
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
class httprequest(object)
    method  initialize

    attrib  wcon            //webcon objektum
    attrib  req             //a request teljes szövege
    attrib  line1           //a request első sora
    attrib  op              //támogatott: GET,POST,HEAD
    attrib  url             //ezt kérik (? előtti rész)
    attrib  par             //ezt kérik (? utáni rész vagy NIL)

    attrib  host            //Host header (: előtti rész)
    attrib  hostport        //Host header (teljes)

    method  redir           //ugyanaz az url a másik porton
    method  same            //ugyanaz az url ugyanazon a porton

    method  isexcluded
    method  issecure

*****************************************************************************
static function httprequest.initialize(this,wcon)
local line1

    this:(object)initialize

    this:wcon:=wcon    

    this:req:=http_readmessage(wcon,10000)
    if( empty(this:req) )
        return NIL
    end

    #ifdef DEBUG0
        ? "<<<<< recv <<<<<<<<<<<<<<<"
        ? this:req
    #endif

    line1:=left(this:req,at(bin(10),this:req))
    line1:=strtran(line1,bin(13))
    line1:=strtran(line1,bin(10))
    this:line1:=line1

    line1:=split(this:line1," ") 
    this:op  := line1[1]
    this:url := line1[2] //dirsep=="/"

    if( a"?"$this:url )
        this:par:=substr(this:url,at(a"?",this:url)+1)
        this:url:=left(this:url,at(a"?",this:url)-1)
    end

    this:url:=websrv.hexdecode(this:url)

    if( left(this:url,1)!=a"/" )
        this:url:=a"/"+this:url
    end
    
    this:hostport:=http_getheader(this:req,"Host")
    if( NIL==this:hostport )
        this:hostport:=a""
        this:host:=a""
    else
        this:host:=split(this:hostport,a":")[1]
    end

    return this

*****************************************************************************
static function httprequest.redir(this)
local redir:=this:wcon:redirport
    if( redir!=NIL  )
        if( redir==80 )
            redir:=this:host
        else
            redir:=this:host+a":"+str2bin(alltrim(str(redir)))
        end
        if( this:wcon:secure )
            redir:=a"http://"+redir //váltás plain/ssl között
        else
            redir:=a"https://"+redir
        end
    end
    return redir

*****************************************************************************
static function httprequest.same(this)
local redir:=this:hostport
    if( this:wcon:secure )
        redir:=a"https://"+redir
    else
        redir:=a"http://"+redir
    end
    return redir

*****************************************************************************
static function httprequest.isexcluded(this)
    return isurlinlist(this:url,excluded_url())

*****************************************************************************
static function httprequest.issecure(this)
    return isurlinlist(this:url,secure_url())

*****************************************************************************
    