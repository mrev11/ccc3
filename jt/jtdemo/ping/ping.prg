


function main()

local ver


    if( empty(ver:=jtversion(1000*10)) )  //10 másodperc
        ? "nem jterminal kapcsolat"
        quit
    end
    
    ? ver
    ?