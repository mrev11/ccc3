
******************************************************************************************
function main()

local mq
local message

    ? "CONSUMER"

    mq:=stomp.consumerNew(queue())
    mq:host:=host()
    mq:port:=port()
    mq:ack:="client"

    mq:connect
    mq:subscribe

    while( (message:=mq:getmessage)!=NIL  )
        ?  time(), a"["+message+a"]"
        if( message==a"QUIT" )
            exit
        end
    end

    mq:disconnect

    ?


******************************************************************************************
