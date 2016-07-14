
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

function main()

local con,q,n

    //con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db
    con:=sql2.mysql.sqlconnectionNew(":root::mysql") //host,user,pw,db
    con:list
    ? con:version
    ? sql2.mysql._my_character_set_name(con:__conhandle__)  // latin1!
    


    q:=con:sqlqueryNew("select host,user,password from user")
    ? q:__selectlist__
    
    while(q:next)
        ?

        for n:=1 to q:fcount
            ? q:fname(n), q:isnull(n), q:getchar(n)
        next
    end

/*

    sql2.mysql.sqlqueryNew(con,"select host,user,password from user where host='X!!X'")


//    sql2.mysql.sqlqueryNew(con,"delete from user where user='XXXXX'")
//    sql2.mysql.sqlqueryNew(con,"set autocommit=0")
    
    ? con:sqlexec("delete from user where user='XXXXX'")
    ? con:sqlexec("set autocommit=0")

*/

    con:sqldisconnect


    ?
    
