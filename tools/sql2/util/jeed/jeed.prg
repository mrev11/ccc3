
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

******************************************************************************
local con:=sqlconnect()
local tds
local dom
local table
local viewer
local n

    set date format "yyyy-mm-dd"

    for n:=1 to argc()-1
        if( argv(n)=="-jtsocket" )
            n++ //socket átugorva
        elseif( left(argv(n),1)=="-" )
            //további opciók (kihagy)
        elseif( file(argv(n)) )
            tds:=argv(n)
        else
            ? "File not found:", argv(n)
        end
    next
    
    if( tds==NIL )
        ? "Usage: jeed <tdsspec>"
        ?
        quit
    end

    dom:=tdsutil.tds2dom(tds)
    table:=tdsutil.dom2tabent(con,dom)    

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})

    //viewer:=jtentityeditorNew(8,16,24,100,table,.t.)
    viewer:=jtentityeditorNew(table,.t.)
    viewer:show


******************************************************************************
function sqlconnect()

local con,arg:=argv(),n,x,ora,ser
    
    for n:=1 to len(arg)
        x:=upper(arg[n])
        if( x=="-O" )
            ora:=.t.
        elseif( x=="-P" )
            ora:=.f.
        elseif( x=="-S" )
            ser:=.t.
        end
    next

    if( ora==.t. )
        con:=sql2.oracle.sqlconnectionNew()
    else
        con:=sql2.postgres.sqlconnectionNew() //default Postgres
    end
    
    if( ser==.t. )
        con:sqlisolationlevel(ISOL_SERIALIZABLE,.t.)
    else
        //default: ISOL_READ_COMMITTED
    end

    return  con


******************************************************************************
    