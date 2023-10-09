
// Listazza a bt fajl egy lapjanak tartalmat.
// Igy kell hasznalni: pgview <btfile> <pgno>
// A lapszamot (<pgno>) hexaban kell megadni,
// ha nincs megadva, akkor a pgno=0 lapot mutatja.


#define ISMEMO(p) (p[5..8]::num>=0x80000000)


static pgtype:={"FREE","INTERNAL","BLEAF","DATA","MEMO"}

#clang
#include <cccapi.h>
#cend



******************************************************************************************
function main(btfile,pgno:="0")

local tab
local btree
local page0,page
local pgsize

    begin
        if( !".bt"$btfile )
            btfile+=".bt"
        end
        if( empty(btopen(btfile)) )
            break()
        end
        tab:=tabResource(btfile)
        tabOpen(tab)
        //fd:=tab[1]
        btree:=tab[2]
    recover
        usage()
    end


    set printer on
    set printer to log-pgview

    page0:=_db_rdpage(btree,0)
    pgsize:=page0[9..12]::num

    pgno::=hex2l
    page:=_db_rdpage(btree,pgno)
    if( empty(page) )
        ? "pgno out of bound"
        ?
        quit
    end
    memowrit("log-PAGE",page)

    ? btfile, "pgno=0x"+pgno::l2hex, "offset=0x"+(pgsize*pgno)::l2hex

    if( pgno==0 )
        page_root(page)
    elseif( ISMEMO(page) )
        page_memo(page)
    else
        page_data(page)
    end

    ?
    ?

******************************************************************************************
static function usage()
    ? "Usage: pgview <btfile> [<pgno>]"
    callstack()
    ?
    quit


******************************************************************************************
static function page_root(page)

local nords
local offset
local n

    ? "magic    :", page[ 1.. 4]::bin2hex, "dskord="+dskord(), "swap="+if(swap(),"TRUE","FALSE")
    ? "version  :", page[ 5.. 8]::hex
    ? "pagesize :", page[ 9..12]::num , page[ 9..12]::hex
    ? "nrecords :", page[13..16]::num , page[13..16]::hex
    ? "freelist :", page[17..20]::num , page[17..20]::hex
    ? "lastdata :", page[21..24]::num , page[21..24]::hex
    ? "freememo :", page[25..28]::num , page[25..28]::hex
    ? "norders  :", page[29..32]::num , page[29..32]::hex

    nords:=page[29..32]::num
    for n:=1 to nords
        offset:=32*n
        ? page[offset+17..offset+32]::strtran(bin(0),bin(32)),;
         "root="+page[offset+1..offset+4]::hex,;
         "last="+page[offset+5..offset+8]::hex,;
         "flags="+page[offset+9..offset+12]::hex
    next


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
static function page_data(page)

// INTERNAL
// BLEAF
// DATA

local type:=pgtype[ page[17..20]::num+1 ]
local lower,upper
local offset
local pos,len,rec

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

        offset:=24
        while( offset<lower )
            pos:=page::substr(offset+1,2)::num      // rekord offset a lapon
            len:=page::substr(pos+1,4)::num         // rekordhossz 4 byte
            rec:=page::substr(pos+5,len)            // delflg + rekord adatok

            pos::=l2hex::padr(4)
            len::=str::alltrim::padl(4)
            if( type=="DATA" )
                rec::=bin2str
                if( len(rec)>100 )
                    rec::=left(96)+"... "
                end
            else
                rec:=""
            end
            ? "0x"+pos, len, "["+rec+"]"

            offset+=2
        end


******************************************************************************************
