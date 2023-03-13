

#define ISMEMO(p) (p[5..8]::hex::len==10.and.p[5..8]::hex>="0x8")

static pgtype:={"FREE","TREE","LEAF","DATA","MEMO"}

static stat:={}


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
function main(btfile)

local fd:=fopen(btfile)
local map:=filemap.open(fd)
local PGSIZE:=map[9..12]::num
local FREE:=map[17..20]::num,link
local fsize:=map::len
local offset,page,pgno,type
local n,lower,upper,space

    fclose(fd)


    for n:=1 to len(pgtype)
        stat::aadd(pageNew(pgtype[n],PGSIZE))
    next

    set printer to log-pgstat
    set printer on

    ? btfile 
    ? "size:", fsize::transform("999,999,999")::alltrim, "byte"
    ? "page:", PGSIZE::str::alltrim
    ? "free:", "0x"+free::l2hex
    ?


    // vegigmegy a freelisten
    // a freelistben csakis felszabadulo index lapok lehetnek
    // a pagetype-ban nem P_FREE van, hanem az eredeti tipus
    // onnan tudhato csak, hogy free, hogy a listaban van
    link:=free
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
static function num(x)  // N tipus
    return x::dec::val


******************************************************************************************
static function dec(x)  // C tipus decimalisan
    if( len(x)==2 )
        x+=x"0000"
    end
    return x::bin2u::str::alltrim


******************************************************************************************
static function hex(x)  // C tipus hexa
    if( len(x)==2 )
        x+=x"0000"
    end
    return "0x"+x::bin2u::l2hex


******************************************************************************************
