

#include "fileio.ch"


function main()

local con:=dbconnectionNew("dbproba")
local ps:=con:database:pagesize
local page:=pageNew()


    con:database:lock
    con:database:metadata_load
    con:database:list
    ?

    fseek(con:database:fd,ps,FS_SET)  //az elsőt (meta) kihagyja
    while( ps==xvread(con:database:fd,page:buffer,0,ps) )
        ? page:pgid, page:trid, page:content
    end

    con:database:unlock

    ?
