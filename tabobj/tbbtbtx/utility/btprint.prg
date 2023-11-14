
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


#include "table.ch"

#define INDENT 6


******************************************************************************************
static function usage()
    ? "Usage: btprint <btfile> [<index>]"
    ?
    quit


******************************************************************************************
function main(btfile,index)

local table
local btree
local fd
local fsize
local page0
local maxpgno

local MAGIC
local VERSION
local ENCRYPT
local PGSIZE
local NRECS
local FREE
local LASTDATA
local MEMO
local NORDS

local ord,offset,order,iname,rootpgno,n
local page

    begin
        if( btfile::right(3)!=".bt" )
            btfile+=".bt"
        end
        table:=tabResource(btfile)
        tabOpen(table)
        fd:=table[1]
        btree:=table[2]
    recover
        usage()
    end

    fsize:=fstat_st_size(fd)
    page0:=_db_pgread(btree,0)

    MAGIC    := page0[ 1.. 4]
    VERSION  := page0[ 5.. 8]::num::numand(0xf)
    ENCRYPT  := page0[ 5.. 8]::num::numand(0x100)!=0
    PGSIZE   := page0[ 9..12]::num
    NRECS    := page0[13..16]::num
    FREE     := page0[17..20]::num
    LASTDATA := page0[21..24]::num
    MEMO     := page0[25..28]::num
    NORDS    := page0[29..32]::num
    maxpgno  := fsize/PGSIZE-1

    offset:=0x31
    for ord:=1 to NORDS
        order:=page0::substr(offset,32)
        rootpgno:=order[1..4]::num
        iname:=order::right(16)::strtran(bin(0),bin(32))::trim

        if( index==NIL .or. index::upper==iname::bin2str::upper )
            ? iname
            walk(btree,rootpgno,0)
            ?
        end
        
        offset+=32
    next
    
    ?
    ?
    

******************************************************************************************
static function walk(btree,pgno,indent)
local page:=_db_pgread(btree,pgno)
local type:=pagetype(page)

    if( pgno==0 )
        //
    elseif( type=="LEAF" )
        print_leaf(btree,page,indent)
    elseif( type=="TREE" )
        print_tree(btree,page,indent)
    else
        break({"unexpected page type",pgno,type})
    end



******************************************************************************************
static function print_tree(btree,page,indent)

local pgno
local pprev
local pnext
local lower
local upper
local idx,offset
local pos,pgn,len,key

    pgno:=page::substr(1,4)::num
    pprev:=page::substr(9,4)::num
    pnext:=page::substr(13,4)::num
    lower:=page::substr(21,2)::num
    upper:=page::substr(23,2)::num

    ?? "  <"+pprev::l2hex+"::"+pnext::l2hex+">"

    idx:=0
    offset:=24
    while( offset<lower )
        pos:=page::substr(offset+1,2)::num          // record offset 
        len:=page::substr(pos+1,4)::num             // key length
        pgn:=page::substr(pos+5,4)::num             // page number 
        key:=page::substr(pos+9,len)                // key value


        ? space(indent);
          +pgno::l2hex::padl(INDENT);
          +pgn::l2hex::padl(INDENT);
          +" -> "+key2str(key)

        walk(btree,pgn,indent+INDENT)

        idx++
        offset+=2
    end


******************************************************************************************
static function print_leaf(btree,page,indent)

local pgno
local pprev
local pnext

local lower
local upper
local idx,offset
local pos,len,key

    pgno:=page::substr(1,4)::num
    pprev:=page::substr(9,4)::num
    pnext:=page::substr(13,4)::num
    lower:=page::substr(21,2)::num
    upper:=page::substr(23,2)::num

    ?? "  <"+pprev::l2hex+"::"+pnext::l2hex+">"

    idx:=0
    offset:=24
    while( offset<lower )
        pos:=page::substr(offset+1,2)::num          // record offset 
        len:=page::substr(pos+1,4)::num             // key length
        key:=page::substr(pos+5,len)                // key value

        ? space(indent+INDENT)+"    "+key2str(key)

        idx++
        offset+=2
    end


******************************************************************************************


