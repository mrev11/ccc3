
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

#include "sql.ch"


function main()

local con,query,fc,rc,n

    con:=sql2.db2.sqlconnectionNew("@sample")
    query:=con:sqlqueryNew("select * from employee")
    ? fc:=query:fcount
    ? query:__selectlist__

    rc:=0    
    while( query:next  )
        ? ++rc 
        for n:=1 to fc
            ?? "|  |"+query:getchar(n)
        next
    end
    query:close


    query:=con:sqlqueryNew("values nextval for seqproba")
    query:next
    ? query:getnumber(1)
    query:close



    con:sqldisconnect
    
    
/*
    stmidx:=sql2.db2._db2_execdirect(con,"values nextval for seqproba")
    ? rc:=sql2.db2._db2_retcode(stmidx)
    if( rc!=0 )
        err:=sqlerrorNew()
        sql2.db2._db2_getdiagrec(err,stmidx)
        break(err)
    end


    for n:=1 to 5
        ? sql2.db2._db2_fetch(stmidx)
        ?? sql2.db2._db2_getdata(stmidx,1)
    next


    sql2.db2._db2_closestatement(stmidx)
*/    
    
    ?
