
// Mutatja a "repeatable read" tulajdonságot.

#define WAIT   ? "press any key"; inkey(0)


#include "sql.ch"

****************************************************************************************
function main()

local con:=connect()  
local tab:=isol.tableEntityNew(con)

local con1:=connect()  
local tab1:=isol.tableEntityNew(con1)


    ? "látja?"
    query(tab)
 

    concurrent(tab1)

    WAIT

    ? "nem látja?"
    query(tab)

    con:sqlcommit
    
    WAIT
    
    ? "na látja!"
    query(tab)

    con:sqlcommit
    con:sqldisconnect    
    
    WAIT

****************************************************************************************
function query(tab)
local rowset,row
    rowset:=tab:select_name("a")
    while( NIL!=(row:=rowset:next) )
        ? row:key, row:name, row:number
    end

****************************************************************************************
function concurrent(tab)

local row

    row:=tab:find({"1"})
    row:delete

    row:=tab:find({"2"})
    row:name:="aa"
    row:update

    row:=tab:find({"3"})
    row:number:=11
    row:update

    row:=tab:find({"5"})
    row:name:="a"
    row:number:=12
    row:update
    
    row:=tab:instance
    row:key:="8"
    row:name:="a"
    row:number:=10
    row:insert

    tab:connection:sqlcommit
    tab:connection:sqldisconnect    

****************************************************************************************
