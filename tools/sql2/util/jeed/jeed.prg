
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

******************************************************************************
function main()

local con
local qb:=quitblock()
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

    con:=sqlconnect()
    quitblock({||con:sqldisconnect(),eval(qb)})

    dom:=tdsutil.tds2dom(tds)
    table:=tdsutil.dom2tabent(con,dom)    

    jtencoding("UTF-8")
    alertblock({|t,a|jtalert(t,a)})

    //viewer:=jtentityeditorNew(8,16,24,100,table,.t.)
    viewer:=jtentityeditorNew(table,.t.)
    viewer:maxrow(32)
    viewer:show


******************************************************************************
function sqlconnect()

local con,arg:=argv(),n,x,ora,pgr,sl3,mys,ser
    
    for n:=1 to len(arg)
        x:=upper(arg[n])
        if( x=="-O" )
            ora:=.t.
        elseif( x=="-P" )
            pgr:=.t.
        elseif( x=="-L" )
            sl3:=.t.
        elseif( x=="-M" )
            mys:=.t.
        elseif( x=="-S" )
            ser:=.t.
        end
    next

    if( ora==.t. )
        con:=sql2.oracle.sqlconnectionNew()
    elseif( sl3==.t. )
#ifdef _CCC3_
        con:=sql2.sqlite3.sqlconnectionNew()
#else
        ? "sqlite3 not supported"
        quit
#endif
    elseif( mys==.t. )
        con:=sql2.mysql.sqlconnectionNew()
    else
        con:=sql2.postgres.sqlconnectionNew() //default Postgres
    end
    
    if( ser==.t. )
        con:sqlisolationlevel(ISOL_SER,.t.)
    else
        //default: ISOL_COM
    end

    return  con


******************************************************************************
    