
function main(*)

local mq
local args:={*},n


    ? "PRODUCER"

    mq:=stomp.producerNew(queue())
    mq:host:=host()
    mq:port:=port()
    if( login()!=NIL )
        mq:login:=login()
        mq:passcode:=passcode()
    end
    mq:persistent:=.f.

    for n:=1 to 2000
        mq:connect
        mq:sendmessage( time()+if( (seconds()%2)==0," Egyszer hopp"," Máskor kopp")  )
        mq:disconnect
        //sleep(100)
    next


    ?