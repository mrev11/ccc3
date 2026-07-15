
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

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
