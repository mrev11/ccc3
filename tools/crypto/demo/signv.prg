
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

******************************************************************************
function main()

local data:=memoread("data.x",.t.)
local cert:=memoread("cert.pem",.t.)
local pubk:=memoread("pub.pem",.t.)
local sign:=memoread("signature",.t.)

    ? "verify-EGYLEPES"
    ? v1( data, cert, sign )
    ? v1( data, pubk, sign )
 
    ? "verify-RESZLETEKBEN"
    ? v2( data, cert, sign )
    ? v2( data, pubk, sign )

    ?
    return NIL
 
******************************************************************************
static function v1(d,x,s) 
    return crypto_verify(d,x,s) 
 
******************************************************************************
static function v2(d,x,s) 
local v,n
    v:=crypto_verify_init()
    for n:=1 to len(d)
        crypto_verify_update(v,substr(d,n,1))
    next
    return  crypto_verify_final(v,x,s) 
 
******************************************************************************
 