
//összes lap (régi verziók is) fordított sorrendben

function main()

local con:=pageman.dbconnectionNew("dbproba")
local index,key,pgno,page


    con:database:lock
    con:database:metadata_load
    con:database:list
    ?
    
    index:=con:database:index
    
    key:=_db_last(index)
    while( key!=NIL )
        key::=split(a"|")

        pgno:=key[3]::pageman.hex2num
        page:=con:database:pageread(pgno) // sorszám szerint, akármelyik verzió (belső)
        ? key, page:content

        key:=_db_prev(index)
    end

    con:database:unlock

    ?
