
#include "table.ch"
#include "_cassa.ch"

******************************************************************************************
function main()
local n:=0
    set dosconv fileshare

    while( ++n<10 )
        test()
        ?
    end
    
    ? "OK"
    ?


******************************************************************************************
static function test()

    CASSA:open
    CASSA:control:="penztaros"
    CASSA:gotop

    while( !CASSA:eof )
        ? CASSA:position, CASSA_SOREGYEB, CASSA_PENZTAROS
        CASSA:skip
    end

    CASSA:close
    
******************************************************************************************

