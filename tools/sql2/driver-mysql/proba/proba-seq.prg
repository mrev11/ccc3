
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

function main(ini)

local con
local seq,val,n

    con:=sql2.mysql.sqlconnectionNew(":konto:konto:konto") //host,user,pw,db

    seq:=con:sqlsequenceNew("seqproba")
    seq:start:=1000

    if( !empty(ini) )
        begin 
            seq:drop
        end
        seq:create


        begin
            con:sqlexec("drop table proba")
        end
        con:sqlexec("create table  proba (id varchar(10) primary key)")

        quit
    end

    for n:=1 to 100
        val:=seq:nextval::str::alltrim::padl(10,"0")

        con:sqlexec("insert into  proba (id) values (:1)",{val} )
        
        
        if( n%10==0 )
            con:sqlcommit
            ?? "."
        end
    next

    con:sqlcommit


    con:sqldisconnect


    ?
    
