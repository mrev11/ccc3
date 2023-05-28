

function main()

local channel:=channelNew("log-proba2")

    channel:open
    channel:writeln("egy",2,{3})
    channel:close

    channel:open(.t.) //additive
    channel:writeln("négy",5,{6})
    channel:close

    ?

