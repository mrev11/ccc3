
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

#ifdef NOT_DEFINED
  A listenereket általában párosával hozzuk létre.
  Az egyik tipikusan a 80-as porton figyel (plain port).
  A másik tipikusan a 443-as porton figyel (SSL port).
  A listener tud a párjáról, hogy könnyebb legyen ide-oda 
  irányítani a requesteket.
  
  A socket-ben egy socket objektum van (sosem sslcon!).
  A secure egy flag, .t. értéke mutatja, hogy SSL lesz.
  Itt fog figyelni: iface:port
  Ha iface helye üres pl. :port, akkor minden interfészen figyel.

  Az fd, accept, bind, listen metódusokat továbbadja a socket-nak.
  Ezek egyúttal egy objektuminterfacet adnak, amire működik a select.

  redirlistener-ben egy block van, ami a másik listenert adja vagy NIL-t.  
  redirport a másik listener portját vagy NIL-t ad.
#endif

#include "websrv.ch"

*****************************************************************************
class listener(object)
    method  initialize
    method  fd
    method  accept
    method  bind
    method  listen

    attrib  socket
    attrib  secure
    attrib  iface
    attrib  port

    attrib  redirlistener
    method  redirport

*****************************************************************************
static function listener.initialize(this)
    this:(object)initialize
    return this

static function listener.fd(this)
    return this:socket:fd

static function listener.accept(this)
    return this:socket:accept

static function listener.bind(this)
    return this:socket:bind(this:iface,this:port)

static function listener.listen(this,q)
    return this:socket:listen(q)

static function listener.redirport(this)
local redirlistener:=eval(this:redirlistener),redirport
    if( redirlistener!=NIL )
        redirport:=redirlistener:port
    end
    return redirport

*****************************************************************************
function makelistener(listener,iface)
local l1, l2
    iface:=split(iface,":")  //{ip,port1[,port2]}
    asize(iface,3)
    
    if( !empty(iface[2])  )
        l1:=listenerNew()
        l1:socket:=socketNew()
        l1:socket:inherit(.f.)
        l1:secure:=.f.
        l1:iface:=if(!empty(iface[1]),iface[1],NIL)
        l1:port:=val(iface[2])
    end

    if( !empty(iface[3]) )
        l2:=listenerNew()
        l2:socket:=socketNew()  //ez is csak socket
        l2:socket:inherit(.f.)
        l2:secure:=.t.
        l2:iface:=if(!empty(iface[1]),iface[1],NIL)
        l2:port:=val(iface[3])
    end
    
    if( l1!=NIL )
        l1:redirlistener:={||l2} //rekurzió ellen
        aadd(listener,l1)
    end

    if( l2!=NIL )
        l2:redirlistener:={||l1} //rekurzió ellen
        aadd(listener,l2)
    end

*****************************************************************************
