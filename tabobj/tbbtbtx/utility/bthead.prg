

// Kiirja a bt header nehany adatat egy sorba.
// Ha az osszes bt-re lefuttatjuk, listat kapunk, minden sorban egy bt-vel.
// A listabol grep-pel tulajdonsagaik szerint gyujhetjuk a fajlokat.
// Peldaul a big endian formatumu, vagy a nem titkositott fajlokat.
// Sort-tal rendezhetjuk a fajlokat meret, rekordszam, indexek szama szerint.

******************************************************************************************
function main(btfile)

local MAGIC
local VERSION
local ENCRYPT
local PGSIZE
local NRECS
local FREE
local LASTDATA
local MEMO
local NORDS

local map

    begin
        if( !".bt"$btfile )
            btfile+=".bt"
        end
        if( empty(map:=btopen(btfile)) )
            break()
        end
    recover
        usage()
    end

    MAGIC    := map[ 1.. 4]
    VERSION  := map[ 5.. 8]::numswap::numand(0xf)
    ENCRYPT  := map[ 5.. 8]::numswap::numand(0x100)!=0
    PGSIZE   := map[ 9..12]::numswap
    NRECS    := map[13..16]::numswap
    FREE     := map[17..20]::numswap
    LASTDATA := map[21..24]::numswap
    MEMO     := map[25..28]::numswap
    NORDS    := map[29..32]::numswap

    ??  "size=" + len(map)::transform("999,999,999")::alltrim::padr(15)
    ??  "rec="  + NRECS::str::alltrim::padr(10)
    ??  "ind="  + NORDS::str::alltrim::padr(3)
    ??  "ord="  + dskord()::padr(8)
    ??  "ver="  + VERSION::str::alltrim::padr(3)
    ??  "enc="  + if(ENCRYPT,"true","false")::padr(7)
    ??  "pge="  + PGSIZE::str::alltrim::padr(6)
    ??  btfile
    ?

******************************************************************************************
static function usage()
    ? "Usage:  bthead <btfile>"
    callstack()
    ?
    quit


******************************************************************************************
