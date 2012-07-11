
//kurrens lapok fordított sorrendben

static zero:=a"0000000000000000"

function main()

local con:=pageman.dbconnectionNew("dbproba")
local index,key,pgid,page


    con:database:lock
    con:database:metadata_load
    con:database:list
    ?
    
    index:=con:database:index
    
    key:=_db_last(index)
    while( key!=NIL .and. key>zero ) //a törölteknél abbahagyja
        key::=split(a"|")

        if( pgid!=key[1] ) //új pgid
            pgid:=key[1]
            page:=con:read(pgid)  //readmark-nál nem nagyobb utolsó verzió (API)
            ? key, page:content
        end

        key:=_db_prev(index)
    end

    con:database:unlock

    ?
