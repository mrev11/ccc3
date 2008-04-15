
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

//ECB Electronic Code Book

function main()

local key,ks,ks2,ks3
local x:=a"abcdefgh",ex,dx

    key:=crypto_des_random_key()
    hexdump(key) 

    key:=crypto_des_set_odd_parity(key)
    hexdump(key) 
    
    ? "is_weak", crypto_des_is_weak_key(key)
    ?

    ks:=crypto_des_set_key_unchecked(key)
    hexdump(ks) 
    ?

    ks:=crypto_des_set_key_checked(key)
    hexdump(ks) 
    ?

    //egy blokk titkosítása oda-vissza

    hexdump(x)
    ex:=crypto_des_ecb_encrypt(x,ks,.t.)
    hexdump(ex)
    dx:=crypto_des_ecb_encrypt(ex,ks,.f.)
    hexdump(dx)
    ?? dx
    ?
    
    ks2:=crypto_des_set_key_unchecked(crypto_des_random_key())

    hexdump(x)
    ex:=crypto_des_ecb2_encrypt(x,ks,ks2,.t.)
    hexdump(ex)
    dx:=crypto_des_ecb2_encrypt(ex,ks,ks2,.f.)
    hexdump(dx)
    ?? dx
    ?

    ks3:=crypto_des_set_key_unchecked(crypto_des_random_key())

    hexdump(x)
    ex:=crypto_des_ecb3_encrypt(x,ks,ks2,ks3,.t.)
    hexdump(ex)
    dx:=crypto_des_ecb3_encrypt(ex,ks,ks2,ks3,.f.)
    hexdump(dx)
    ?? dx
    ?
    