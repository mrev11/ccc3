
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