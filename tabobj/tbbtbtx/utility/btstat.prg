
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


// Kiirja, hogy a bt fajlban a kulonbozo tipusu lapokbol
// hany darab van ("FREE","INTERNAL","BLEAF","DATA","MEMO"),
// es azokban mennyi a foglalt es a szabad hely.
// Igy kell hasznalni: pgstat <btfile>

#define ISMEMO(p) (p[5..8]::num>=0x80000000)

static pgtype:={"FREE","TREE","LEAF","DATA","MEMO"}
static stat:={}

#clang
#include <cccapi.h>
#cend

******************************************************************************************
static function usage()
    ? "Usage:  btstat <btfile>"
    ?
    quit


******************************************************************************************
function main(btfile)

local tab
local fd
local btree
local fsize

local MAGIC
local VERSION
local ENCRYPT
local PGSIZE
local NRECS
local FREE
local LASTDATA
local MEMO
local NORDS

local link
local page,pgno,type
local n,lower,upper,space
local freelist:={},flx
local total


    begin
        if( btfile::right(3)!=".bt" )
            btfile+=".bt"
        end
        if( empty(btopen(btfile)) )
            // btopen nyersen beolvassa a fajlt,
            // es megjegyez olyan adatokat (pl. dskord),
            // amit a _db_pgread mar nem lathat,
            // mert az csak a swapolt adatokat latja
            break()
        end
        tab:=tabResource(btfile)
        tabOpen(tab)
        fd:=tab[1]
        btree:=tab[2]
    recover
        usage()
    end

    //set printer to log-btstat
    //set printer on


    fsize:=fstat_st_size(fd)
    page:=_db_pgread(btree,0)

    MAGIC    := page[ 1.. 4]
    VERSION  := page[ 5.. 8]::num::numand(0xf)
    ENCRYPT  := page[ 5.. 8]::num::numand(0x100)!=0
    PGSIZE   := page[ 9..12]::num
    NRECS    := page[13..16]::num
    FREE     := page[17..20]::num
    LASTDATA := page[21..24]::num
    MEMO     := page[25..28]::num
    NORDS    := page[29..32]::num

    ? btfile
    ? "  diskord  :" , dskord()
    ? "  version  :" , VERSION::str::alltrim
    ? "  encrypt  :" , if(ENCRYPT,"true","false")
    ? "  pgsize   :" , PGSIZE::str::alltrim
    ? "  filesize :" , fsize::transform("999,999,999")::alltrim
    ? "  numpges  :" , (fsize/PGSIZE)::str::alltrim
    ? "  numrecs  :" , NRECS::str::alltrim
    ? "  numords  :" , NORDS::str::alltrim
    ? "  freelist :" , "0x"+FREE::l2hex
    ?

    for n:=1 to len(pgtype)
        stat::aadd(pageNew(pgtype[n],PGSIZE))
    next

    // vegigmegy a freelisten
    // a freelistben csakis eldobott indexek (dropindex) lapjai vannak
    // a pagetype-ban tobbnyire nem P_FREE van, hanem az eredeti tipus
    // kulcstorlesek miatt kiurult indexlap tipusa P_FREE==0
    link:=FREE
    while( link!=0 )
        page:=_db_pgread(btree,link)
        pgno:=page[1..4]::num
        link:=page[5..8]::num
        freelist::aadd(pgno)
        stat[1]:count+=1
        stat[1]:space+=PGSIZE-20
    end
    freelist::asort

    flx:=1
    pgno:=0
    while( (page:=_db_pgread(btree,++pgno))!=NIL  )

        while( flx<=len(freelist) .and. freelist[flx]<pgno )
            flx++
        end
        if( flx <= len(freelist) .and. freelist[flx] == pgno )
            // freelist elemei kihagyva
            loop
        end

        if( ISMEMO(page) )
            type:=5
            lower:=page[ 9..12]::num
            upper:=page[13..16]::num
        else
            type:=page[17..20]::num+1
            if( pgtype[type]=="FREE" )
                // kulcstorlesek miatt kiurult indexlap
                lower:=20
                upper:=PGSIZE
            else
                lower:=page[21..22]::num
                upper:=page[23..24]::num
            end
        end
        space:=upper-lower

        stat[type]:count+=1
        stat[type]:space+=space
    end


    ? "HEAD",;
      1,;
      " space", ((PGSIZE-48-NORDS*32)/1024)::transform("999999,999.9 K"),;
      " used", ((48+NORDS*32)/(PGSIZE/100))::str(5,1),"%"

    total:=1    
    for n:=1 to len(stat)
        ? stat[n]:type::padr(4),;
          stat[n]:count,;
          " space", (stat[n]:space/1024)::transform("999999,999.9 K"),;
          " used", stat[n]:used::str(5,1),"%"
          
        if( n==1 )
            ? "---------------------------------------------------"
        end
        total+=stat[n]:count  
    next

    ? "---------------------------------------------------"
    ? "total"+str(total,10)

    ?


******************************************************************************************
static class page(object)
    attrib  type
    attrib  pgsize
    attrib  count
    attrib  space

    method  initialize
    method  used

static function page.initialize(this,type,pgsize)
    this:type:=type
    this:pgsize:=pgsize
    this:count:=0
    this:space:=0
    return this

static function page.used(this)
local used:=0
    if( this:count!=0 )
        used:=(1-this:space/this:count/this:pgsize)*100::round(1)
    end
    return used


******************************************************************************************
