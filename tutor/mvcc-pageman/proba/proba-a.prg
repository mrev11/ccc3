
#include "inkey.ch"

function main()

local con:=pageman.dbconnectionNew("dbproba")
local page,err

    while(.t.);begin

        page:=con:read(a"0000000000000003")  //C-s page
        page:content+=a"AA"
        ? page:content  //ezt akarja kiírni

        if( inkey(0)==K_ESC )
            exit
        end
        con:commit

    recover err <pageman.dbserialerror>
        ? err:classname, err:description
        con:rollback
    end;end
    

