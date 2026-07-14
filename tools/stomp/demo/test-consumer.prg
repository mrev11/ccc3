
#include "param.h"

******************************************************************************************
function main( ack:="client-individual" ) 

local mq
local message
local tstamp

    ? "CONSUMER"

    mq:=stomp.consumerNew(queue())
    mq:host:=host()
    mq:port:=port()

    mq:ack:=ack
    // mq:ack=="client-individual" modban az interfesz kuldi az ack-ot (egyenkent)
    // mq:ack=="client" modban az alkalmazas kuldi az ack-ot (kumulativ)
    // mq:ack=="auto" modban nincs ack kuldes

    mq:connect
    mq:subscribe() // default

#ifdef MULTIPLE_QUEUE
    // teszt tobb message queue-val
    mq:subscribe("COMFIRMx")    //, mq:subscriptions, mq:subscrids
    mq:subscribe("COMFIRMy")    //, mq:subscriptions, mq:subscrids
    mq:subscribe("COMFIRMz")    //, mq:subscriptions, mq:subscrids

    // megjegyzes:
    // nem szabad hasznalni az mq:unsubscribe-ot,
    // mert (tevesen) megis kuld uzenetet a sorbol,
    // majd a tevesen kuldott uzenet ack-ja utan ERROR-t kuld  
#endif
    
    while( (message:=mq:getmessage)!=NIL  )
        ? "message from",mq:destination
    
        // elerhetoek a headerek, peldaul
        tstamp:=mq:getheader("timestamp")
        ? "timestamp:", tstamp
        ? "UCT:",tstamp::val::epoch2xmldate

        if( mq:ack=="client" )
            mq:sendack()
        end

        ?  ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ",time(), a"["+message+a"]"
        if( message==a"QUIT" )
            exit
        end
    end

    mq:disconnect

    ?


******************************************************************************************
