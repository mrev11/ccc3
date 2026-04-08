
function main(*)

local mq
local args:={*},n


    ? "PRODUCER"

    mq:=stomp.producerNew(queuename())

    mq:host:=host()
    mq:connect
    mq:persistent:=.t.

    for n:=1 to len(args)
        mq:sendmessage( args[n] )
    next

    mq:disconnect

    ?