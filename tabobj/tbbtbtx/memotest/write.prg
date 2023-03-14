
#include "table.ch"


******************************************************************************************
function main()
local proba:=tabobj.probaNew()
local n,x
local cnt:=0

    set dosconv fileshare

    set printer to ("log-write-"+getpid()::str::alltrim)
    set printer on

    proba:create
    proba:open(OPEN_SHARED)

    rand(seconds())

    while(.t.)
        proba:gotop
        while( !proba:eof )
            proba:rlock
                proba:dbmchr:=""
                proba:dbmbin:=a""
                proba:length:=len(proba:dbmchr)
            proba:unlock
            proba:skip
        end
    
        proba:gotop
        while( !proba:eof )
            proba:rlock
                x:=proba:proba::left(1)
                x::=replicate(random()%1000)
                proba:dbmchr:="<"+x+">"
                proba:dbmbin:=proba:dbmchr::upper
                proba:length:=len(proba:dbmchr)
            proba:unlock
            proba:skip
        end
        
        ? ++cnt
        run( "pgstat.exe proba.bt" )
        
        if( 27==inkey(0.1) )
            exit
        end
    end
    
    proba:close

    ?     
    
******************************************************************************************
