
function main(*)

local mq
local args:={*},n


    ? "PRODUCER"

    mq:=stomp.producerNew(queuename())

    mq:host:=host()
    mq:connect
    mq:persistent:=.f.

    while( 27!=inkey(0) )
        mq:sendmessage(  if( (seconds()%2)==0,"Hopp","Kopp")  )
    next

    mq:disconnect

    ?