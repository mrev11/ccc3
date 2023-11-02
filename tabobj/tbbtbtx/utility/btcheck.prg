
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


static writecrc:=.f.


******************************************************************************************
static function usage()
    ? "Usage: btcheck <btfile> [--writecrc]"
    ?
    quit


******************************************************************************************
function main(btfile)

local a:=argv(),n

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

local pgno
local blk:={|p|code(p)}
local create_time,access_time,modif_time
local err

    for n:=1 to len(a)
         if( a[n][1..1]=="-" )
            if( a[n]=="--writecrc" )
                writecrc:=.t.
            else
                usage()     
            end
        else
            btfile:=a[n]
        end
    next
 
    begin
        if( btfile::right(3)!=".bt" )
            btfile+=".bt"
        end
        {create_time,access_time,modif_time}:=getfiletime(btfile)
        table:=tabResource(btfile)
        tabOpen(table)
        fd:=table[1]
        btree:=table[2]
    recover err
        ? err
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

    for pgno:=1 to maxpgno
        _db_pgeval(btree,pgno,blk)
    next 

    setfiletime(btfile,create_time,access_time,modif_time)


******************************************************************************************
static function code(page)
    if( writecrc )
        return page // CRC32-vel visszairja a page-et
    else
        return NIL  // nem irja vissza a page-et
    end


******************************************************************************************
