
#include "param.h"

function main(*)

local mq
local args:={*},n

    ? "PRODUCER"

    mq:=stomp.producerNew()
    mq:host:=host()
    mq:port:=port()
    mq:connect
    mq:persistent:=.t.

    mq:destination:=queue()
    for n:=1 to len(args)
        mq:sendmessage( args[n] )
        if( args[n]=="QUIT" )
            mq:disconnect
            ?
            quit
        end
    next

#ifdef MULTIPLE_QUEUE
    // teszt tobb message queue-val
    for n:=1 to len(args)
        mq:begin
        mq:destination:=queue()+"x";  mq:sendmessage( args[n]+"-xxx" )
        mq:destination:=queue()+"y";  mq:sendmessage( args[n]+"-yyy" )
        mq:destination:=queue()+"z";  mq:sendmessage( args[n]+"-zzz" )
        //mq:abort
        mq:commit
    next
#endif

    mq:disconnect
    ?