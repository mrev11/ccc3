
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

local pass:="Próba szerencse"
local parm:="$2a$11$"
local rand //:=crypto_rand_bytes(16)  //X tipus, kriksz-kraksz
local salt:=bcrypt_salt(rand)
local hash

    ? "parm=",parm
    ? "salt=",space(7); ?? salt


    // ezt kell eltarolni
    ? "hash=",hash:=bcrypt_hash(pass,parm+salt)

    // igy lehet ellenorizni
    ? hash==bcrypt_hash(pass,hash)
    
    ? valtype(pass)
    ? valtype(parm), len(parm)
    ? valtype(salt), len(salt)
    ? valtype(hash), len(hash)

    ?

/*
  parm: "$2a$11$"
    $ jellel határolva az algoritmuskód és az iterációszám logaritmusa

    az algoritmuskód mindig "2a" vagy "2b"

    az iterációk logaritmusát két jeggyel kell megadni 
    pl. 17 esetén 2**17-szer iterálja a blowfish titkosítást

    17 kb. 8 sec (ezt akarják)
    16 kb. 4 sec  
    15 kb. 2 sec  
    14 kb. 1 sec  
    13 kb. 1/2 sec  
    12 kb. 1/4 sec  
    11 kb. 1/8 sec  
    stb.

  rand: 128 bites véletlen sorozat
    ha nincs megadva, akkor automatikusan generálódik
    
  salt: rand base64 kódolással konvertálva
    eltér a standard base64-től (más abc-t használ)  
    
  hash: a hash számítás eredménye
    ezt kell tárolni az ellenőrzéshez 
*/

    