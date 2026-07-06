
function main(*)

local mq
local args:={*},n


    ? "PRODUCER"

    mq:=stomp.producerNew(queue())

    mq:host:=host()
    mq:port:=port()
    mq:persistent:=.f.
    mq:connect

    while( 27!=inkey(0) )
        mq:sendmessage(  if( (seconds()%2)==0,"Egyszer hopp","Máskor kopp")  )
    next

    mq:disconnect

    ?