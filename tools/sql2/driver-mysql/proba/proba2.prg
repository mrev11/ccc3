
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

    set date format 'yyyy-mm-dd'

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db
    con:list
    ? con:version
    ? sql2.mysql._my_character_set_name(con:__conhandle__)  // latin1!
    


    q:=con:sqlqueryNew("select * from proba")
    ? q:__selectlist__
    
    while(q:next)
        ?   q:getchar(1),;
            q:getchar(2),;
            q:getchar(3),;
            q:getnumber(4)::str(10,2),;
            q:getnumber(5),;
            q:getlogical(6),;
            q:getdate(7),;
            q:getbinary(8)
    end

    con:sqldisconnect


    ?
    


//1 szamla        C   
//2 devnem        C
//3 megnevezes    C
//4 osszeg        N
//5 sorszam       N
//6 tulmenflag    L
//7 konyvkelt     D
//8 megjegyzes    M
