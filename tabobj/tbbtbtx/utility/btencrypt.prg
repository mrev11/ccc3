
// helyben BEtitkositja btfile-t

#include "table.ch"

******************************************************************************************
function main( btfile )

local tab,btree,pgno

    tab:=tabResource(btfile)
    tabOpen(tab,OPEN_EXCLUSIVE)
    btree:=tab[2]
    
    if( _db_cryptflg(btree) )
        // mar titkositva van
        quit
    end

    pgno:=1
    while( _db_pgrewrite(btree,pgno,.t.) )
        // kilep, ha nincs btpasswd
        ++pgno
    end

    // cryptflg utolag!
    _db_cryptflg(btree,.t.)

    tabClose(tab)
    
******************************************************************************************


