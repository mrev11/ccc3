
function main(*)

local mq

    ? "PRODUCER"

    mq:=stomp.producerNew(queuename())
    mq:host:=host()
    mq:connect
    
    
    mq:sendmessage( memoread("stomp.prg") )
    mq:disconnect
 
    ?   