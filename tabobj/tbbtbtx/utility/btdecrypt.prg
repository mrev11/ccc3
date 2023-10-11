
// helyben KItitkositja btfile-t

#include "table.ch"

******************************************************************************************
function main( btfile )

local tab,btree,pgno

    tab:=tabResource(btfile)
    tabOpen(tab,OPEN_EXCLUSIVE)
    btree:=tab[2]

    if( !_db_cryptflg(btree) )
        //? "nincs titkositva"
        quit
    end

    pgno:=1
    while( _db_pgrewrite(btree,pgno,.f.) )
        // kilep, ha nincs btpasswd
        ++pgno
    end

    // cryptflg utolag!
    _db_cryptflg(btree,.f.)

    tabClose(tab)

******************************************************************************************


