
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

#ifdef NOT_DEFINED
    Van olyan eset, amikor az SSL alatt levo fd-t a select 
    nem olvashatonak mutatja, de maga az SSL megis olvashato. 
    Ez akkor fordul elo, ha az ssl az fd-bol eloreolvasott, 
    es vannak "pending" byteok.
#endif

******************************************************************************
function main(sslflag)

local ctx,ss,s,err,result

    printpid()
    printexe()

    if( sslflag!=NIL )
        ctx:=sslctxNew() 
        ctx:use_certificate_file("localhost.pem")
        ctx:use_privatekey_file("localhost.pem")
        ss:=sslconNew(ctx)
    else
        ss:=socketNew()
    end

    ss:reuseaddress(.t.)
    ss:bind("127.0.0.1",40000)
    ss:listen
    
    while( .t. )
        begin
            s:=ss:accept()

            ?
            while( 0<s:pending .or. 0<select({s:fd}) )
                ?? result:=s:recv(128,0) //socket VAGY sslcon (nem var)

                if( result==NIL )            
                    exit
                end
            end

        recover err <socketerror>
            ? err:description

        finally
            if( s!=NIL )
                s:close //socket VAGY sslcon
            end
            s:=NIL
            ? "closed"
        end
    end

******************************************************************************

