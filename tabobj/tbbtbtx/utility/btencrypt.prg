
// helyben BEtitkositja btfile-t

#include "table.ch"

******************************************************************************************
function main( btfile )

local tab,page,pgno

    tab:=tabResource(btfile)
    tabOpen(tab)

    pgno:=1
    while( NIL!=(page:=_db_rdpage(tab[2],pgno,1)) )
        ++pgno
    end
    
******************************************************************************************


