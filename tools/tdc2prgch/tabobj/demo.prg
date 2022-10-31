

******************************************************************************************
function main()

local t1,t2,n:=0

    set dosconv fileshare
    
    t1:=tabobj.cassaNew(); t1:open
    t2:=tabobj.cassaNew(); t2:open

    while( ++n<=10 )
        t1:append
        t1:soregyeb:=n
        t1:penztaros:=crypto_rand_bytes(4)::crypto_bin2hex
        t1:szamlaszam:=crypto_rand_bytes(8)::crypto_bin2hex
        t1:unlock

        if((n%1000)==0)
            ?? "."
        end
    end

    t1:control:="soregyeb"; t1:gotop
    t2:control:="penztaros"; t2:gotop

    while( !t1:eof .or. !t2:eof )
         ?  t1:position, t1:soregyeb
        ??  t2:position, t2:penztaros

        t1:skip
        t2:skip
    end

    t1:close
    t2:close
    
    ? "OK"
    ?


******************************************************************************************
