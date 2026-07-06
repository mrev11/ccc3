
function main(*)

local mq

    ? "PRODUCER"

    mq:=stomp.producerNew(queue())
    mq:host:=host()
    mq:port:=port()
    mq:connect
    
    
    mq:sendmessage( a"abcdefgh"::replicate(1024*128)   )
    mq:disconnect
 
    ?   