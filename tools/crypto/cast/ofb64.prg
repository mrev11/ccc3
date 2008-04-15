
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

function main()

local infile:="ofb64.prg"

local key:=a"proba szerencse"
local ks:=crypto_cast_set_key(key)
local ivec0:=replicate(a" ",8),ivec
local num

local enctext:=a""
local dectext:=a""
local text,blk,blksiz:=47 //tetszőleges adagok

    ivec:=ivec0
    num:=0
    hexdump(ivec)
    text:=memoread(infile,.t.)    
    while( len(text)>0  )  
        blk:=left(text,blksiz)
        text:=substr(text,blksiz+1)
        enctext+=crypto_cast_ofb64_encrypt(blk,ks,@ivec,@num)
        hexdump(ivec)
        ?? num
    end
    memowrit("enctext",enctext)
    
    ?

    ivec:=ivec0
    num:=0
    hexdump(ivec)
    text:=enctext    
    while( len(text)>0  )  
        blk:=left(text,blksiz)
        text:=substr(text,blksiz+1)
        dectext+=crypto_cast_ofb64_encrypt(blk,ks,@ivec,@num)
        hexdump(ivec)
        ?? num
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

//ABCDE