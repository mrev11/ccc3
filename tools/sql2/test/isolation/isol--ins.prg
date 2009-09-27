


function main()

local con:=connect()  
local tab:=isol.tableEntityNew(con)
local row
local err

    begin
        tab:create
    recover err <sqlerror>
        //err:list
    end
    
    row:=tab:instance

    row:key:="1"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="2"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="3"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="4"
    row:name:="a"
    row:number:=1
    row:insert

    row:key:="5"
    row:name:="b"
    row:number:=1
    row:insert

    row:key:="6"
    row:name:="c"
    row:number:=1
    row:insert

    row:key:="7"
    row:name:="d"
    row:number:=1
    row:insert
    
    con:sqlcommit
    con:sqldisconnect    
    
    