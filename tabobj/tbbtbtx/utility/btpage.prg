
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


// Listazza a bt fajl egy lapjanak tartalmat.
// Igy kell hasznalni: pgview <btfile> <pgno>
// A lapszamot (<pgno>) hexaban kell megadni,
// ha nincs megadva, akkor a pgno=0 lapot mutatja.

// #clang
// #include <cccapi.h>
// #cend


******************************************************************************************
static function usage()
    ? "Usage: btpage <btfile> [<pgno>]"
    ?
    quit


******************************************************************************************
function main(btfile,pgno:="0")

local tab
local btree
local page0,page
local pgsize
local map,pgraw,crc
local err

    begin
        if( btfile::right(3)!=".bt" )
            btfile+=".bt"
        end
        if( empty(map:=btopen(btfile)) )
            break()
        end
        tab:=tabResource(btfile)
        tabOpen(tab)
        //fd:=tab[1]
        btree:=tab[2]
    recover err
        //? err
        usage()
    end


    //set printer to log-btpage
    //set printer on

    page0:=_db_pgread(btree,0)
    pgsize:=page0[9..12]::num

    pgno::=hex2l
    page:=_db_pgread(btree,pgno)
    if( empty(page) )
        ? "pgno out of bound"
        ?
        quit
    end
    memowrit("log-PAGE",page)

    ? btfile, "pgno=0x"+pgno::l2hex, "offset=0x"+(pgsize*pgno)::l2hex

    if( pgno==0 )
        ?? " maxpgn=0x"+(len(map)/pgsize-1)::l2hex, "("+(len(map)/pgsize-1)::str::alltrim+")"
    else
        pgraw:=map::substr(pgno*pgsize+1,pgsize)
        crc:=crc32( pgraw[5..]  )::num2crc
        ?? " crc=["+crc+"]"
    end


    if( pgno==0 )
        page_header(page)

    elseif( pagetype(page)=="TREE" )
        page_tree(page)

    elseif( pagetype(page)=="LEAF" )
        page_leaf(page)

    elseif( pagetype(page)=="DATA" )
        page_data(page)

    elseif( pagetype(page)=="MEMO" )
        page_memo(page)

    elseif( pagetype(page)=="FREE" )
        page_free(page)

    end

    ?

******************************************************************************************
static function page_header(page)

local version
local nords
local offset
local n

    ? "magic    :", page[ 1.. 4]::bin2hex, "diskord="+dskord(), "swap="+if(swap(),"TRUE","FALSE")
    ? "version  :", page[ 5.. 8]::hex
    ? "pagesize :", page[ 9..12]::num , page[ 9..12]::hex
    ? "nrecords :", page[13..16]::num , page[13..16]::hex
    ? "freelist :", page[17..20]::num , page[17..20]::hex
    ? "lastdata :", page[21..24]::num , page[21..24]::hex
    ? "freememo :", page[25..28]::num , page[25..28]::hex
    ? "norders  :", page[29..32]::num , page[29..32]::hex

    version:=page[ 5.. 8]::num
    nords:=page[29..32]::num

    for n:=1 to nords
        if( version<=2 )
            offset:=32*n
        else
            offset:=16+32*n
        end
        ? page[offset+17..offset+32]::strtran(bin(0),bin(32)),;
         "root="+page[offset+1..offset+4]::hex,;
         "last="+page[offset+5..offset+8]::hex,;
         "free="+page[offset+9..offset+12]::hex
    next


******************************************************************************************
static function page_tree(page)

local type:="TREE"
local lower,upper
local idx,offset
local pos,len,pgn,key,rec


    ? "type  ",  type

    ? "link  ", "0x"+page[ 5.. 8]::hex
    ? "prev  ", "0x"+page[ 9..12]::hex
    ? "next  ", "0x"+page[13..16]::hex
    ? "flags ", "0x"+page[17..20]::hex
    ? "lower ", "0x"+page[21..22]::hex
    ? "upper ", "0x"+page[23..24]::hex

    lower:=page::substr(21,2)::num                  // elso szabad pozicio
    upper:=page::substr(23,2)::num                  // elso nemszabad pozicio
    ? "items", (lower-24)/2                         // ennyi rekord van benne
    ? "space", upper-lower

    idx:=0
    offset:=24
    while( offset<lower )
        pos:=page::substr(offset+1,2)::num          // record offset on page
        len:=page::substr(pos+1,4)::num             // key length
        pgn:=page::substr(pos+5,4)::hex::padl(8)    // page number
        key:=page::substr(pos+9,len)                // key
        pos::=l2hex::padr(4)
        if( len==0  )
            len::=str::alltrim::padl(4)
            ? str(idx,3),"0x"+pos, len, pgn
        else
            len::=str::alltrim::padl(4)
            ? str(idx,3),"0x"+pos, len, pgn, key::key2str
        end
        idx++
        offset+=2
    end


******************************************************************************************
static function page_leaf(page)

local type:="LEAF"
local lower,upper
local offset
local pos,len,rec
local idx

    ? "type  ",  type

    ? "link  ", "0x"+page[ 5.. 8]::hex
    ? "prev  ", "0x"+page[ 9..12]::hex
    ? "next  ", "0x"+page[13..16]::hex
    ? "flags ", "0x"+page[17..20]::hex
    ? "lower ", "0x"+page[21..22]::hex
    ? "upper ", "0x"+page[23..24]::hex

    lower:=page::substr(21,2)::num              // elso szabad pozicio
    upper:=page::substr(23,2)::num              // elso nemszabad pozicio
    ? "items", (lower-24)/2                     // ennyi rekord van benne
    ? "space", upper-lower

    idx:=0
    offset:=24
    while( offset<lower )
        pos:=page::substr(offset+1,2)::num      // rekord offset a lapon
        len:=page::substr(pos+1,4)::num         // rekordhossz 4 byte
        rec:=page::substr(pos+5,len)            // delflg + rekord adatok

        pos::=l2hex::padr(4)
        len::=str::alltrim::padl(4)

        rec::=key2str

        ? str(idx,3),"0x"+pos, len, rec

        idx++
        offset+=2
    end


******************************************************************************************
static function page_data(page)

local type:="DATA"
local lower,upper
local offset
local pos,len,rec
local idx

    ? "type  ",  type

    ? "link  ", "0x"+page[ 5.. 8]::hex
    ? "prev  ", "0x"+page[ 9..12]::hex
    ? "next  ", "0x"+page[13..16]::hex
    ? "flags ", "0x"+page[17..20]::hex
    ? "lower ", "0x"+page[21..22]::hex
    ? "upper ", "0x"+page[23..24]::hex

    lower:=page::substr(21,2)::num              // elso szabad pozicio
    upper:=page::substr(23,2)::num              // elso nemszabad pozicio
    ? "items", (lower-24)/2                     // ennyi rekord van benne
    ? "space", upper-lower

    idx:=0
    offset:=24
    while( offset<lower )
        pos:=page::substr(offset+1,2)::num      // rekord offset a lapon
        len:=page::substr(pos+1,4)::num         // rekordhossz 4 byte
        rec:=page::substr(pos+5,len)            // delflg + rekord adatok

        pos::=l2hex::padr(4)
        len::=str::alltrim::padl(4)

        rec::=bin2str
        if( len(rec)>100 )
            rec::=left(96)+"... "
        end
        rec:="["+rec+"]"

        ? str(idx,3),"0x"+pos, len, rec

        idx++
        offset+=2
    end


******************************************************************************************
static function page_memo(page)

local type:="MEMO"
local lower,upper,offset
local recmix,recno,memix
local poslen,pos,len
local pgnext,ixnext
local memseg

    ? "type  ",  type

    ? "link  ", "0x"+page[ 5.. 8]::hex
    ? "lower ", "0x"+page[ 9..12]::hex
    ? "upper ", "0x"+page[13..16]::hex

    lower:=page::substr(9,4)::num    // elso szabad pozicio
    upper:=page::substr(13,4)::num   // elso nemszabad pozicio
    ? "items", (lower-16)/16         // ennyi rekord van benne
    ? "space", upper-lower

    offset:=16
    while( offset<lower )
        recmix :=page::substr(offset+ 1,4)::num // MEMO_ID
        poslen :=page::substr(offset+ 5,4)::num // MEMO_DESC
        pgnext :=page::substr(offset+ 9,4)::num // MEMO_PGNEXT
        ixnext :=page::substr(offset+13,4)::num // MEMO_IXNEXT

        {recno,memix}:=parse_recmix(recmix)
        {pos,len}:=parse_poslen(poslen)
        memseg:=page::substr(pos+1,len)

        ? (offset/16-1)::str(3),;
          form_recmix(recno,memix,15),;
          len::transform(" 99999"),;
          form_memseg(memseg,64)

        if( pgnext!=0 )
            ?? " -> "+form_mempos(pgnext,ixnext)
        end

        offset+=16
    end


******************************************************************************************
static function page_free(page)

local type:="FREE"

    ? "type  ",  type
    ? "next  ", "0x"+page[13..16]::hex


******************************************************************************************
