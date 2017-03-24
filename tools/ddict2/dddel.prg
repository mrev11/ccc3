


#include "table.ch"
#include "_ddict.ch"


****************************************************************************
function main(ddfile,delete)

local prg

    if( ddfile==NIL )
        ? "Usage: dddel.exe ddfile [delete]"
        ?
        quit
    end


    DDICT:file:=ddfile
    DDICT:open(OPEN_EXCLUSIVE)
    DDICT:control:="table"
    DDICT:gotop
    
    while( !DDICT:eof )
        prg:="_"+DDICT_TABLE::alltrim::lower+".prg"

        if( file(prg) )
            //megtart
            DDICT:skip

        elseif( delete=="delete" )
            //torol
            DDICT:delete

        else
            //mutatja, mit fog torolni
            ? "delete", DDICT_TABLE
            DDICT:skip
        end
    end
    
    

