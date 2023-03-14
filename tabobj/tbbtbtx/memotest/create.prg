
#include "table.ch"


******************************************************************************************
function main()
local proba:=tabobj.probaNew()
local n, a:="a",x

    set dosconv fileshare

    proba:create
    proba:open(OPEN_EXCLUSIVE)
    proba:zap

    rand(seconds())
    
    for n:=0 to 999
        proba:append
        x:=chr(asc(a)+n%26)
        proba:proba:=x
        x::=replicate(random()%500)
        proba:dbmchr:="<"+x+">"
        proba:dbmbin:=upper(proba:dbmchr)
        proba:length:=len(proba:dbmchr)
    next


    prn(proba)

    proba:close

    ?     
    
******************************************************************************************
static function prn(proba)
    proba:gotop
    while(!proba:eof)
        ? proba:proba, proba:length,  proba:dbmchr , proba:dbmbin
        proba:skip
    end


******************************************************************************************
