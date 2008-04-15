
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

// 2006.11.16
// eval(errorblock,e) helyett break(e)
// socketerror-t és invalidformaterror-t (CRC) dob

****************************************************************************
class smessage(object)
    method initialize
    method receive
    method send
    method message
    attrib cargo
    attrib socket
    attrib counter

****************************************************************************
static function smessage.initialize(this,socket) 
    this:(object)initialize
    this:socket:=socket
    this:counter:=1
    return this

****************************************************************************
static function smessage.receive(this)
local r,hdr,err

    hdr:=sread(this:socket,16)


    if( len(hdr)<=0 )
        return NIL

    elseif( len(hdr)!=16 )
        err:=socketerrorNew()
        err:operation:="smessageReceive"
        err:description:="sread failed"
        break(err)
    end

    //? "recv_header",hdr2len(hdr),hdr2cnt(hdr)
 
    r:=sread(this:socket,hdr2len(hdr))

    if( len(r)!=hdr2len(hdr) )
        err:=socketerrorNew()
        err:operation:="smessageReceive"
        err:description:="sread failed"
        err:args:={hdr2cnt(hdr)}
        break(err)
    end
    
    if( crc(r)!=hdr2crc(hdr) )
        err:=invalidformaterrorNew()
        err:operation:="smessageReceive"
        err:description:="different CRC"
        err:args:={hdr2cnt(hdr)}
        break(err)
    end
    
    this:counter:=hdr2cnt(hdr)
    return bin2arr(r)

****************************************************************************
static function smessage.send(this,a)

local err,m,hdr,wlen

    m:=arr2bin(a)
    
    //? "send_header",len(m),this:counter

    hdr:=l2bin(len(m))+;
         l2bin(this:counter)+;
         l2bin(0)+;
         l2bin(crc(m))
           
    wlen:=swrite(this:socket,hdr+m)         

    if( wlen!=len(hdr)+len(m) )
        err:=socketerrorNew()
        err:operation:="smessageSend"
        err:description:="swrite failed"
        err:args:={hdr2cnt(hdr)}
        break(err)
    end
          
    return wlen

****************************************************************************
static function smessage.message(this,a)
    this:counter++
    this:send(a)
    return this:receive 

****************************************************************************
static function crc(m)
local sum:=0, i
    for i:=1 to len(m)
        sum+=asc(substr(m,i,1))
    next
    return sum

****************************************************************************
static function hdr2len(h)
    return bin2l(substr(h,1,4))

****************************************************************************
static function hdr2cnt(h)
    return bin2l(substr(h,5,4))

****************************************************************************
static function hdr2crc(h)
    return bin2l(substr(h,13,4))

****************************************************************************

#ifdef HEADER
  1- 4 byte hossz
  5- 8 byte sorszám 
  9-12 byte flagek
 13-16 byte CRC
#endif

