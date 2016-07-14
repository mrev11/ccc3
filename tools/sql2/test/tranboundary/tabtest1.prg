
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

//teszt tábla generálás kamu adatokkal

function main(db,recnum:="0")   //db: P,M,O,D,L.
local con,tab,row
local seq,seqval,i,e

    set date format 'yyyy-mm-dd'
    
    if( db$'M')
        con:=sql2.mysql.sqlconnectionNew() 
    elseif( db$'P')
        con:=sql2.postgres.sqlconnectionNew() 
    elseif( db$'D')
        con:=sql2.db2.sqlconnectionNew() 
    elseif( db$'O')
        con:=sql2.oracle.sqlconnectionNew() 
    elseif( db$'L')
        con:=sql2.sqlite3.sqlconnectionNew() 
    end
    ? con:version
    
    recnum::=val  //rekordszám

    tab:=proba.tableEntityNew(con)
    begin           
        tab:drop   
    recover e
        ? e:description
    end             
    tab:create      

    seq:=con:sqlsequenceNew("konto.seqproba")
    seq:start:=1000   
    begin             
        seq:drop      
    recover e
        ? e:description
    end               
    seq:create        
    
    for i:=1 to recnum
        seqval:=seq:nextval
        row:=tab:instance
        row:szamlaszam  := seqval::str::alltrim::padl(24,"0")
        row:devnem      := "HUF"
        row:nev         := (asc('a')+seqval%26)::chr::replicate(20)
        row:egyenleg    := seqval+seqval/10
        row:sorszam     := seqval
        row:tulmenflag  := seqval%3==0
        row:konyvkelt   := date()+seqval%100
        row:megjegyzes  := "XXXXXXX"+str(seqval)+replicate("x",10)
        row:insert
        
        if( i%1000==0  )
            con:sqlcommit
            ?? "."
        end
    next
    con:sqlcommit

    con:sqldisconnect
    
