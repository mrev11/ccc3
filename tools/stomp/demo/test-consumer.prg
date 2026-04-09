
******************************************************************************************
function main()

local mq
local message

    ? "CONSUMER"

    mq:=stomp.consumerNew(queuename())
    mq:host:=host()
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
