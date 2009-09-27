
#include "sql.ch"

function main()

local con:=connect()  

    con:sqlexec("delete from isol")

    con:sqlcommit
    con:sqldisconnect    
    
