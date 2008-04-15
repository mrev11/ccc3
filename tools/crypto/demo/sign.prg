
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

#define EGYLEPES

function main()

local data:=memoread("data.x",.t.) //binary
local pkey:=memoread("priv.pem",.t.) //binary
local sign:=""
local s,n

#ifdef EGYLEPES

    ? "sign-EGYLEPES"

    sign:=crypto_sign(data,pkey) 
#else

    ? "sign-RESZLETEKBEN"

    s:=crypto_sign_init()
    for n:=1 to len(data)
        crypto_sign_update(s,substr(data,n,1))
    next
    sign:=crypto_sign_final(s,pkey) 

#endif

    memowrit("signature",sign)
    ?
    return NIL


