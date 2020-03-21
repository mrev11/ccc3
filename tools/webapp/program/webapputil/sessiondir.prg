
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

namespace webapp

***************************************************************************************
function session.id()
    return argv(1)


function session.socket()
    return argv(2)


function session.user()
local user:=argv(3)
local err

    if( user==NIL )
        err:=errorNew()
        err:operation:="webapp.session.user()"
        err:description:="nincs bejelentkezett felhasználó"
        //break(err)
    end
    if( user==NIL )
        user:="notloggedin" //teszt célra
    end    

    return user


//  a wlogin indítja így a programot:
//  exec(default_app(),session_id,session_sck,session_user,.t.) 




***************************************************************************************
function sessiondir(sessionid:=session.id())
local dspec:="session"

    if( !direxist(dspec) )
        dirmake(dspec)
    end
    
    dspec+=dirsep()+sessionid[1..2]

    if( !direxist(dspec) )
        dirmake(dspec)
    end

    dspec+=dirsep()+sessionid

    if( !direxist(dspec) )
        dirmake(dspec)
    end
    
    return dspec+dirsep()


***************************************************************************************
function sessiondel(sessionid:=session.id())
local dspec:="session"+dirsep()+sessionid[1..2]+dirsep()+sessionid
    run( "rm -rf "+dspec )
    ? "SESSIONDEL", sessionid, argv(0)

***************************************************************************************

