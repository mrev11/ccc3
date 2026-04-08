
function main(*)

local mq

    ? "PRODUCER"

    mq:=stomp.producerNew(queuename())
    mq:host:=host()
    mq:connect
    
    
    mq:sendmessage( a"abcdefgh"::replicate(1024*128)   )
    mq:disconnect
 
    ?   