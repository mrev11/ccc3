
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


//deadlock-or demonstráló program
//SQLite3 elszáll "database is locked", mert egyfelhasználós
//
//DB2 már az update előtti find-on fennakad, mert nem MVCC,
//a beolvasni kívánt rekord módosult, de még nem commitolták.


#define WAIT   ? "press any key"; inkey(0)


#include "sql.ch"

#define UPDATE(x)   ?#x+"-update-before"; row##x:update;    ?#x+"-update-after"
#define COMMIT(x)   ?#x+"-commit-before"; con##x:sqlcommit; ?#x+"-commit-after"

#define SELECTW(x)  ?#x+"-selectw-before"; rs##x:=tab##x:select(,LOCK_WAIT); ?#x+"-selectw-after"; rs##x:close
#define SELECTW0(x) ?#x+"-selectw0-before"; rs##x:=tab##x:select(,LOCK_NOWAIT); ?#x+"-selectw0-after"; rs##x:close
#define SELECTW2(x) ?#x+"-selectw2-before"; rs##x:=tab##x:select(,2); ?#x+"-selectw2-after"; rs##x:close

#define SELECTX(x)  ?#x+"-selectx-before"; rs##x:=tab##x:select(,"x"); ?#x+"-selectx-after"; rs##x:close
#define SELECTS(x)  ?#x+"-selects-before"; rs##x:=tab##x:select(,"s"); ?#x+"-selects-after"; rs##x:close
#define SELECTX0(x) ?#x+"-selectx0-before"; rs##x:=tab##x:select(,"x0"); ?#x+"-selectx0-after"; rs##x:close
#define SELECTX2(x) ?#x+"-selectx2-before"; rs##x:=tab##x:select(,"x2"); ?#x+"-selectx2-after"; rs##x:close
#define SELECTS0(x) ?#x+"-selects0-before"; rs##x:=tab##x:select(,"s0"); ?#x+"-selects0-after"; rs##x:close
#define SELECTS2(x) ?#x+"-selects2-before"; rs##x:=tab##x:select(,"s2"); ?#x+"-selects2-after"; rs##x:close



****************************************************************************************
function main(db,isolev)

local con1:=connect(db,isolev)
local tab1:=isol.tableEntityNew(con1)

local con2:=connect(db,isolev)
local tab2:=isol.tableEntityNew(con2)

local rs1,rs2

    thread_create({||sleep(5000),qout("deadlock"+chr(10)),quit()})

    SELECTX(1)

                                    SELECTS(2)
                                    COMMIT(2)

    COMMIT(1)

    con1:sqldisconnect    
    con2:sqldisconnect    
    
    ?
    

****************************************************************************************
function query(tab)
local rowset,row
    rowset:=tab:select_ordered
    while( NIL!=(row:=rowset:next) )
        ? row:key, row:name, row:number
    end

****************************************************************************************
