
******************************************************************************************
function main( ack:="client-individual" ) 

local mq
local message

    ? "CONSUMER"

    mq:=stomp.consumerNew(queue())
    mq:host:=host()
    mq:port:=port()
    mq:ack:=ack

    mq:connect
    mq:subscribe
    
    //mq:list

    while( (message:=mq:getmessage)!=NIL  )

        // elerhetoek a headerek
        ? "message-id:",mq:getheader("message-id")
        ? "ack:",mq:getheader("ack")

        // mq:ack=="client-individual" modban az interfesz kuldi az ack-ot
        // mq:ack=="client" modban az alkalmazas kuldi az ack-ot
        // mq:ack=="auto" modban nincs ack kuldes

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
