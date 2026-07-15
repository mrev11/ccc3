
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