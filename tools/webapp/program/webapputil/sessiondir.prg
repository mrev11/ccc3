
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
    
    return dspec


***************************************************************************************
function sessiondel(sessionid:=session.id())
local dspec:="session"+dirsep()+sessionid[1..2]+dirsep()+sessionid
    run( "rm -rf "+dspec )
    ? "SESSIONDEL", sessionid

***************************************************************************************

