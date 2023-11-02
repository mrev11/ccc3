
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

static pages

#clang
#include <cccapi.h>
#cend


******************************************************************************************
static function usage()
    ? "Usage: btlink <btfile>"
    ?
    quit

******************************************************************************************
function main(btfile)

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
local create_time,access_time,modif_time
local page

    begin
        if( btfile::right(3)!=".bt" )
            btfile+=".bt"
        end
        {create_time,access_time,modif_time}:=getfiletime(btfile)
        table:=tabResource(btfile)
        tabOpen(table,OPEN_EXCLUSIVE)
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

    _db_header_read(btree,.t.) //for writing
    offset:=0x31
    for ord:=1 to NORDS
        order:=page0::substr(offset,32)
        rootpgno:=order[1..4]::num
        iname:=order::right(16)::strtran(bin(0),bin(32))::trim

        pages:={}
        walk(btree,rootpgno)
        //? iname, pages::tohex::arev
        relink(btree,ord)

        offset+=32
    next
    _db_header_write(btree)
    setfiletime(btfile,create_time,access_time,modif_time)


******************************************************************************************
static function relink(btree,ord)
local n,pgno
local blk:={|p|code(p,n)}
    for n:=len(pages) to 2 step -1
        pgno:=pages[n]
        _db_pgeval(btree,pgno,blk)
    next
    setlast(btree,ord,pages[1],pages::atail)

static function code(page,n)
    //? n, pages[n]::l2hex
    if( xvgetlong(page,4)==pages[n-1] )
        //nem kell visszairni
        return NIL 
    else
        xvputlong(page,4,pages[n-1])
        return page
    end

function setlast(btree,ord,root,last)
#clang
    unsigned *header=(unsigned*)_parp(1);
    unsigned order=_parni(2);
    unsigned root=_parni(3);
    unsigned last=_parni(4);

    unsigned offs=12+(order-1)*8;
    unsigned hroot=header[offs+0];
    unsigned hlast=header[offs+1];
    char *name=(char*)(&header[offs+4]);
    //printf("\n>>>> root=%x last=%x->%x name=%s\n",hroot,hlast,last,name); // stimmelnek

    if( root!=hroot )
    {
        // ellenorzes
        printf("ERROR: hroot=%x != root=%x\n",hroot,root);
    }
    else
    {
        header[offs+1]=last;  // hlast felulirva
    }
#cend


******************************************************************************************
static function walk(btree,pgno)
local page:=_db_pgread(btree,pgno)
local type:=pagetype(page)
    aadd(pages,pgno)
    if( type=="LEAF" )
        // rekorzio vege
    elseif( type=="TREE" )
        walk1(btree,page)
    else
        ?? "unexpected page type", type
    end


static function walk1(btree,page)
local lower
local upper
local idx,offset
local pos,len,pgn,key

    lower:=page::substr(21,2)::num
    upper:=page::substr(23,2)::num
    idx:=0
    offset:=24

    while( offset<lower )
        pos:=page::substr(offset+1,2)::num          // record offset on page
        len:=page::substr(pos+1,4)::num             // key length
        pgn:=page::substr(pos+5,4)::num             // page number

        // rekurzio"
        walk(btree,pgn)

        idx++
        offset+=2
    end


******************************************************************************************
static function tohex(a)
local n
    a::=aclone
    for n:=1 to len(a)
        a[n]:=a[n]::l2hex
    next
    return a


******************************************************************************************
