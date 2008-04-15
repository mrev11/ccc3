
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
  A socket attrib egy socket/sslcon osztályú objektum,
  a socket műveletek mind ennek vannak továbbadva.
  
  Tárolja a listener-t, amiből accept-tel létrejött,
  ebben van az átirányításhoz szükséges infó.
  
  A secure flag mutatja, hogy SSL kapcsolatra kell-e áttérni.
  Kezdetben a socket osztálya nem sslcon csak socket
  és később konvertálódik a sslconAccept-tal sslcon-ná.
  
  A redirport megadja az átirányításhoz használandó portot,
  vagy NIL-t, ha a listenernek nem volt párja.
#endif

#include "websrv.ch"

******************************************************************************
class webcon(object)
    attrib  socket
    attrib  listener
    attrib  secure

    method  initialize
    method  fd
    method  peer
    method  inherit
    method  send
    method  recv
    method  pending
    method  waitforrecv
    method  recvall
    method  close
    method  redirport

******************************************************************************
static function webcon.initialize(this,listener)
    this:(object)initialize
    this:listener:=listener
    this:secure:=listener:secure
    this:socket:=listener:accept
    this:inherit(.f.)
    return this

******************************************************************************
static function webcon.fd(this)
    return this:socket:fd

static function webcon.peer(this)
    return getpeername(this:socket:fd)

static function webcon.inherit(this,flag)
    return this:socket:inherit(flag)

static function webcon.send(this,buf)
    return this:socket:send(buf)

static function webcon.recv(this,nbyte,timout)
    return this:socket:recv(nbyte,timout)

static function webcon.pending(this)
    return this:socket:pending()

static function webcon.waitforrecv(this,wtime)
    return this:socket:waitforrecv(wtime)

static function webcon.recvall(this,wtime)
    return this:socket:recvall(wtime)

******************************************************************************
static function webcon.close(this)

    //if( this:socket:isderivedfrom(sslconClass()) )
    //ssl támogatás nélkül nem linkelődik

    if( !this:socket:classname=="socket" )
        // a shutdown kell, 
        // hogy a session bekerüljön a session cache-be
        // a síma socketeknek nincs shutdown-juk
        this:socket:shutdown
    end
    return this:socket:close

******************************************************************************
static function webcon.redirport(this)
    return this:listener:redirport

******************************************************************************
    