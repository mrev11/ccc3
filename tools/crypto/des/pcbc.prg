
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
  DES_pcbc_encrypt() encrypt/decrypts using the propagating 
  cipher block chaining mode used by Kerberos v4. Its parameters 
  are the same as  DES_ncbc_encrypt().
#endif  

function main()

local infile:="pcbc.prg"

local key:=crypto_des_random_key()
local ks:=crypto_des_set_key_unchecked(key)
local ivec0:=crypto_des_random_key(), ivec

local enctext:=a""
local dectext:=a""
local text,blk,blksiz:=128 //8 többszöröse kell legyen

    ivec:=ivec0
    hexdump(ivec)
    text:=memoread(infile,.t.)    
    while( len(text)>0  )  
        blk:=left(text,blksiz)
        text:=substr(text,blksiz+1)
        enctext+=crypto_des_pcbc_encrypt(blk,ks,@ivec,.t.)
        hexdump(ivec)
    end
    memowrit("enctext",enctext)
    
    ?

    //ivec:=ivec0 //nem változik
    //ivec:=crypto_des_random_key() //rossz kezdőértékkel nem javul ki

    hexdump(ivec)
    text:=enctext    
    while( len(text)>0  )  
        blk:=left(text,blksiz)
        text:=substr(text,blksiz+1)
        dectext+=crypto_des_pcbc_encrypt(blk,ks,@ivec,.f.)
        hexdump(ivec)
    end

    //a végén nullák lehetnek
    while( right(dectext,1)==bin(0) )
        dectext:=left(dectext,len(dectext)-1)
    end
    
    memowrit("dectext",dectext)

    ? memoread(infile,.t.)==dectext
    ?
    run("diff dectext "+infile)
    ?
