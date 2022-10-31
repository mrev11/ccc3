


******************************************************************************************
function main()
local t, n:=0
    set dosconv fileshare

    t:=tabobj.cassaNew()
    while( ++n<10 )
        test(t)
        ?
    end
    
    ? "OK"
    ?


******************************************************************************************
static function test(t)

    t:open
    t:control:="penztaros"
    t:gotop

    while( !t:eof )
        ? t:position, t:soregyeb, t:penztaros
        t:skip
    end

    t:close
    
******************************************************************************************

