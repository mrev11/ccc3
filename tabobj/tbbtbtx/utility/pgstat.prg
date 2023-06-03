
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
function main(btfile)

local map:=btopen(@btfile)

local fsize
local MAGIC
local VERSION
local PGSIZE
local NRECS
local FREE
local LASTDATA
local MEMO
local NORDS

local link
local offset,page,pgno,type
local n,lower,upper,space

    if( map::empty )
        ? "Usage:", "pgstat", "<btfile>"
        ?
        quit
    end

    set printer to log-pgstat
    set printer on

    fsize    := map::len
    MAGIC    := map[ 1.. 4]
    VERSION  := map[ 5.. 8]::num
    PGSIZE   := map[ 9..12]::num
    NRECS    := map[13..16]::num
    FREE     := map[17..20]::num
    LASTDATA := map[21..24]::num
    MEMO     := map[25..28]::num
    NORDS    := map[29..32]::num

    ? btfile, "dskord="+dskord(), "version="+VERSION::str::alltrim, "pagesize="+PGSIZE::str::alltrim
    ? "size :", fsize::transform("999,999,999")::alltrim, "byte"
    ? "nrecs:", NRECS::str::alltrim
    ? "nords:", NORDS::str::alltrim
    ? "free :", "0x"+free::l2hex
    ?

    for n:=1 to len(pgtype)
        stat::aadd(pageNew(pgtype[n],PGSIZE))
    next

    // vegigmegy a freelisten
    // a freelistben csakis felszabadulo index lapok lehetnek
    // a pagetype-ban nem P_FREE van, hanem az eredeti tipus
    // onnan tudhato csak, hogy free, hogy a listaban van
    link:=FREE
    while( link!=0 )        
        page:=map::substr(link*PGSIZE+1,PGSIZE)
        link:=page[5..8]::num
        stat[1]:count+=1
        stat[1]:space+=PGSIZE
    end

    offset:=PGSIZE
    pgno:=1
    while( offset<fsize )
        page:=substr(map,offset+1,PGSIZE)

        if( ISMEMO(page) )
            type:=5
            lower:=page[ 9..12]::num
            upper:=page[13..16]::num
        else
            type:=page[17..20]::num+1
            if( pgtype[type]=="FREE" )
                // ide nem jon
                lower:=0
                upper:=PGSIZE
            else
                lower:=page[21..22]::num
                upper:=page[23..24]::num
            end
        end
        space:=upper-lower

        //? pgno, pgtype[type]::padr(4),space

        stat[type]:count+=1
        stat[type]:space+=space
 
        offset+=PGSIZE
        pgno++
    end    

    for n:=1 to len(stat)
        ? stat[n]:type::padr(4),; 
          stat[n]:count,;
          " space", (stat[n]:space/1024)::transform("999999,999 K"),;
          " used", stat[n]:used::str(5,1),"%"
    next

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
