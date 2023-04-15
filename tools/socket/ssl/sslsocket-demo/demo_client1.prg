
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

function main(sslflag)
local s
local ctx
local x:=a"Ot szep szuzlany orult irot nyuz",n

    s:=socketNew()
    s:connect("localhost",40000)

    if( sslflag!=NIL ) 
        ctx:=sslctxNew("TLS_client") 
        s:=sslconConnect(ctx,s) //socket -> sslcon
    end
    
    for n:=1 to len(x)
        ? n
        s:send( substr(x,n,1)  )
        sleep(30)
    next

    s:close

    ?
    


