
//nyersen, ahogy fizikailag vannak
//de kihagyja a törölt (szabad) lapokat


#include "fileio.ch"


function main()

local con:=pageman.dbconnectionNew("dbproba")
local ps:=con:database:pagesize
local page:=pageman.pageNew()


    con:database:lock
    con:database:metadata_load
    con:database:list
    ?

    fseek(con:database:fd,ps,FS_SET)  //az elsőt (meta) kihagyja
    while( ps==xvread(con:database:fd,page:buffer,0,ps) )
        if( !page:pgid==a"0"::replicate(16)  )
            ? page:pgid, page:trid, page:content
        end
    end

    con:database:unlock

    ?
