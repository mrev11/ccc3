
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


#define WAIT        ? "press any key"; inkey(0)


#define BEFORE      id+"-"+state+"-before"
#define AFTER       id+"-"+state+"-after"

#define UPDATE      ? BEFORE;  row:update;      ? AFTER
#define COMMIT      ? BEFORE;  con:sqlcommit;   ? AFTER
#define ROLLBACK    ? BEFORE;  con:sqlrollback; ? AFTER


****************************************************************************************
function main(db,isolev,commit:="yes")

local id:="1"
local con,tab,row
local err,state
local thr

    commit:=(commit=="yes")

    con:=connect(db,isolev)
    tab:=isol.tableEntityNew(con)
    
    thr:=thread_create({||concurrent(db,isolev,.t.)})

    ? "================================================================"
    query(tab) //tranzakció indul

    ? id+"-begin",commit

    begin

        sleep(2000)
        state:="update1"
        row:=tab:find({"1"})
        row:name::=(trim()+id)
        UPDATE 


        sleep(2000)
        state:="update2"
        row:=tab:find({"2"})
        row:name::=(trim()+id)
        UPDATE 


        sleep(2000)
        if(commit)
            state:="commit"
            COMMIT
        else
            state:="rollback"
            ROLLBACK
        end

        ? id+"-OK"


    recover err <sqlerror>
        con:sqlrollback
        ? id+"-FAILED in "+state, err:classname, "("+err:description+")"
    
    end

    ? id+"-end"
    
    thread_join(thr)

    ? "joined"
    query(tab)
    con:sqldisconnect    
    ?

****************************************************************************************
function concurrent(db,isolev,commit:=.t.)


local id:="2"
local con,tab,row
local err,state

    con:=connect(db,isolev)
    tab:=isol.tableEntityNew(con)


    ? id+"-begin",commit

    begin
        //fordított sorrendben update-el

        sleep(2000)
        state:="update2"
        row:=tab:find({"2"})
        row:name::=(trim()+id)
        UPDATE 

        sleep(2000)
        state:="update1"
        row:=tab:find({"1"})
        row:name::=(trim()+id)
        UPDATE 

        sleep(2000)
        if(commit)
            state:="commit"
            COMMIT
        else
            state:="rollback"
            ROLLBACK
        end

        ? id+"-OK"

    recover err <sqlerror>
        con:sqlrollback
        ? id+"-FAILED in "+state, err:classname, "("+err:description+")"
    
    finally
        con:sqldisconnect    
    end

    ? id+"-end"
    ?
    

****************************************************************************************
function query(tab)
local rowset,row
    rowset:=tab:select_ordered
    while( NIL!=(row:=rowset:next) )
        ? row:key, row:name, row:number
    end

****************************************************************************************






























