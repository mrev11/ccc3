
#include "inkey.ch"


***********************************************************************************************
static function getkey(key)
static skey:=0
local rkey
    if( key!=NIL )
        skey:=key
    elseif( skey!=NIL )
        sleep(100)
        rkey:=skey
        skey:=NIL
    else
        rkey:=inkey(1)
    end    
    return rkey


***********************************************************************************************
function main()

local con,err
local key
local page

    con:=pageman.dbconnectionNew("dbproba")
    

    while( getkey()!=K_ESC  )
        
        //most olvas egyet

        page:=con:read(a"0000000000000004")  //D-s page

        ? page:content

        //amit olvasott, módosítja

        if( page:content[1]==a"Z" ) //nagy Z
            page:content:="A"::replicate(10)
        elseif( page:content[1]==a"z" ) //kis z
            page:content:="a"::replicate(10)
        else
            page:content:=(page:content::asc()+1)::chr::replicate(10)
        end

        //majd megpróbálja kiírni

        begin
            sleep(1000) //többiek szivatása
            con:commit
            ?? " ->", page:content
            //siker

        recover err <pageman.dbserialerror>
            con:rollback
            ?? " ->", err:description
            getkey(32)
            //ismétel
        end

        //tranzakcióhatár
    end

    ?

***********************************************************************************************
