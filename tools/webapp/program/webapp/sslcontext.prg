
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

#include "ssl.ch"

static ctx:=init_ssl_context()


***************************************************************************************
function ssl_context()
    return ctx

//megjegyzés: csak akkor érdekes, ha param_ssl() true-t ad.


***************************************************************************************
static function init_ssl_context()

local keyfile:=option_hash()["keyfile"]
local cafile:=option_hash()["cafile"]
local capath:=option_hash()["capath"]
local ctx

    if( keyfile==NIL )
        ? "cannot use SSL without keyfile"
        ?
        quit
    elseif( !file(keyfile) )
        ? "keyfile not found:", keyfile
        ?
        quit
    else
        ? "ssl_context_keyfile:",keyfile
    end


    if(cafile==NIL)
        //ok
    elseif( !file(cafile) )
        ? "cafile does not exist:", cafile
        ?
        quit
    else 
        ? "ssl_context_cafile:",cafile
    end

    if(capath==NIL)
        //ok
    elseif( !direxist(capath) )    
        ? "capath does not exist:", capath
        ?
        quit
    else
        ? "ssl_context_capath:",capath
    end

    ctx:=sslctxNew()

    ctx:use_certificate_file(keyfile)
    ctx:use_privatekey_file(keyfile)

    if( capath!=NIL .or. cafile!=NIL )
        ctx:set_verify(SSL_VERIFY_PEER_CERT)
        ctx:set_verify_depth(99)
        ctx:load_verify_locations(cafile,capath)
    end

    return ctx


***************************************************************************************

