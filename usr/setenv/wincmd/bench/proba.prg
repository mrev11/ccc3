
// teszt program


function main()

local counter 

    counter:=memoread("counter")::val

    if( counter==1000  )
        ? seconds()
    end

    if( counter>0  )
        memowrit( "counter", (--counter)::str::alltrim )
    else
        ferase( "counter" )
        ? seconds()
    end

    