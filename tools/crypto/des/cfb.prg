
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
  DES_cfb_encrypt() encrypt/decrypts using cipher feedback mode. 
  This method takes an array of characters as input and outputs an  array 
  of characters. It does not require any padding to 8 character groups. 
  Note: the ivec variable is changed and the new changed value needs 
  to be passed to the next call to this function. Since this function runs 
  a complete DES ECB encryption per numbits, this function is only 
  suggested for use when sending small numbers of characters.
#endif  


function main()

local infile:="cfb.prg"

local key:=crypto_des_random_key()
local ks:=crypto_des_set_key_unchecked(key)
local ivec0:=crypto_des_random_key(), ivec
local numbit:=8 //<=64bit==8byte

local enctext:=a""
local dectext:=a""
local text,blk,blksiz:=8 //numbit többszöröse kell legyen

    ivec:=ivec0
    hexdump(ivec)
    text:=memoread(infile,.t.)    
    while( len(text)>0  )  
        if( len(text)>=blksiz )
            blk:=left(text,blksiz)
        else
            blk:=padr(text,blksiz,bin(0)) //numbit többszöröse adható
        end
        text:=substr(text,blksiz+1)
        enctext+=crypto_des_cfb_encrypt(blk,numbit,ks,@ivec,.t.)
        hexdump(ivec)
        
    end
    memowrit("enctext",enctext)
  
    ?

    blksiz:=16   //változhat, más érték is megfelel, pl. 56
    ivec:=ivec0  //rossz kezdőértékkel kijavul
    hexdump(ivec)
    text:= /*a"x"+*/ enctext //teljesen elromlik
    while( len(text)>0  )  
        blk:=left(text,blksiz)
        text:=substr(text,blksiz+1)
        dectext+=crypto_des_cfb_encrypt(blk,numbit,ks,@ivec,.f.)
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

//ABCD