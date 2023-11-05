
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
