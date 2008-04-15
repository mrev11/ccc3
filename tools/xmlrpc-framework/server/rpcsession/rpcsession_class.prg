
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

#include "table.ch"
#include "_rpcuser.ch"

static session_number:=0

****************************************************************************
class rpcsession(object)

    method  initialize
    
    attrib  uid
    attrib  tid
    attrib  sno
    attrib  start
    attrib  seconds
    attrib  random

    method  hash

****************************************************************************
static function rpcsession.initialize(this,u,p) 

local e

    this:(object)initialize
    
    if( valtype(u)=="A" )
        this:=iniobjectfromarray(this,u)

    else
        if( !RPCUSER:seek(u) .or.;
            !alltrim(RPCUSER_PASSWORD)==p .or.;
            !empty(RPCUSER_STARTDATE) .and. date()<RPCUSER_STARTDATE .or.;
            !empty(RPCUSER_ENDDATE) .and. date()>RPCUSER_ENDDATE )

            e:=xmlrpcsessionerrorNew("rpcsession.initialize")
            e:description:="incorrect password"
            break(e)
        end
    
        this:uid:=alltrim(RPCUSER_UID)
        this:tid:=alltrim(RPCUSER_TID)
        this:sno:=++session_number
        this:start:=time()
        this:seconds:=seconds()
        this:random:=rnd()
    end
    
    return this

****************************************************************************
static function rpcsession.hash(this)
    return base64_encode( crypto_md5(arr2bin(this:asarray)) )

****************************************************************************
static function rnd()
    return base64_encode(crypto_rand_pseudo_bytes(8))
 
****************************************************************************

 