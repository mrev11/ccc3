
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
        rkey:=inkey(3)
    end    
    return rkey


***********************************************************************************************
function main()

local con,err
local key
local page

    set date format "yyyy-mm-dd"
    
    con:=pageman.dbconnectionNew("dbproba")
    
    
    while( (key:=getkey())!=K_ESC )

        if( key==0 )
            //nem nyomtak semmit,
            //nincs tranzakcióhatár, 
            //ugyanabban a tranazkcióban újra végrehajtja a selectet,
            //ugyanazt kell kapnia akkor is, ha egy másik program közben változtatott!

        elseif( key==32 )

            con:rollback //tranzakcióhatár

            //az új tranzakcióban a select már látja
            //az adatbázisban időközben bekövetkezett változásokat
        end
    
        //most olvas egyet

        page:=con:read(a"0000000000000005")  //E-s page
        ? page:content
        
        if( key!=0 .and. key!=32  ) 
            // amit olvasott, módosítja

            if( page:content::isupper )
                page:content::=lower  //NAGY -> kisbetű
            else
                page:content::=upper  //kis -> NAGYBETŰ
            end

            //majd megpróbálja kiírni

            begin
                sleep(1000) //többiek szivatása
                con:commit //tranzakcióhatár
                ?? " ->", page:content
                //siker

            recover err <pageman.dbserialerror>
                ?? " ->", err:description
                con:rollback //tranzakcióhatár

                //ismétel 
                getkey(64) //várakozás nélkül
            end
        end
    end

    ?
