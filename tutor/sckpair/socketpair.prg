
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


// Nem kizart, hogy
// a listen es a kovetkezo connect kozott
// egy idegen processz konnektaljon a portra.
// Akkor a connect es az accept is sikeres,
// de nem ugyanannak a kapcsolatnak a ket vege.
// Hogyan lehetne ezt az esetet kiszurni?
// Az idegen connect valoszinuseget noveli,
// ha a REUSEADDR opciot a defaultrol no-rol
// yes-re allitjak.

*****************************************************************************
function socketpair() //egyszeru

local cnt:=0
local s:=socket(),p,a,c

    rand(gettickcount())
    p:=numor(0xf000,random())
    while( 0>bind(s,"127.0.0.1",p) .and. ++cnt<1024 )
        p:=numor(0xf000,random())
    end
    //? "port",p; inkey(1)

    listen(s)
    connect(c:=socket(),"127.0.0.1",p)
    a:=accept(s)
    sclose(s)
    return {a,c}  //ellenorizni:  sckpair[1]>0

*****************************************************************************
function socketpairx() //hibakezeles kivetelekkel (socketerror)

local cnt:=0,e
local s:=socket(),p,a,c

    //veletlenszeruen portot valaszt
    //a 0xc000-0xffff intervallumbol

    rand(gettickcount())
    p:=numor(0xc000,random())
    while( 0>bind(s,"127.0.0.1",p) )
        if( ++cnt>1024 )
            e:=socketerrorNew()
            e:operation:="socketpair"
            e:description:="bind failed"
            e:canretry:=.t.
            break(e)
            cnt:=0  //ujrakezdi
        end
        p:=numor(0xc000,random())
    end
    //? "port",p; inkey(1)

    if( 0>listen(s,1) )
        e:=socketerrorNew()
        e:operation:="socketpair"
        e:description:="listen failed"
        break(e)
    end

    //Idegen connect!?

    if( 0>connect(c:=socket(),"127.0.0.1",p) )
        e:=socketerrorNew()
        e:operation:="socketpair"
        e:description:="connect failed"
        break(e)
    end

    if( 0>(a:=accept(s)) )
        e:=socketerrorNew()
        e:operation:="socketpair"
        e:description:="accept failed"
        break(e)
    end

    sclose(s)
    return {a,c}

*****************************************************************************
