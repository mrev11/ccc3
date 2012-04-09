
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

#include "table.ch"

static s_tdsfile
static s_tabfile
static s_tabname
static s_skipfld:=""
static s_driver:="P"
static s_dbginfo:=.f.

#define PRINT(x) ? #x, x

*****************************************************************************
function usage()
local x:=<<usage>>
Usage: btimport -d driver -e tdsfile -f btfile [-n table] [-s skipfld]*

    driver  : O=oracle, P=postgres
    tdsfile : tableentity definition script filespec
    btfile  : bt (dat/dbf) filespec to import
    table   : qulified table name in SQL database
    skipfld : omitted field
<<usage>>
    ?? x
    ?
    quit

*****************************************************************************
function main()

local dom
local tableentity
local rowentity
local tableobj
local cname,col,blklst,n
local err,errcnt:=0
local cnt:=0,sec:=seconds()
local con

    set date format "yyyy-mm-dd"

    //set printer to ("log-"+alltrim(str(getpid())))
    //set printer on

    n:=0
    while( NIL!=argv(++n) )

        if( argv(n)=="-e" )
            s_tdsfile:=argv(++n)
        elseif( argv(n)=="-f" )
            s_tabfile:=argv(++n)
        elseif( argv(n)=="-n" )
            s_tabname:=argv(++n)
        elseif( argv(n)=="-s" )
            s_skipfld+=":"+upper(argv(++n))+":"
        elseif( argv(n)=="-d" )
            s_driver:=left(upper(argv(++n)),1)
            if( !s_driver$"OP" )
                usage()
            end
        elseif( argv(n)=="-b" )
            s_dbginfo:=.t.
        end
    end
 
    if( NIL==s_tdsfile )
        usage()
    end
    if( NIL==s_tabfile )
        usage()
    end
    if( NIL==s_driver )
        usage()
    end


    tableobj:=tabResource(s_tabfile)
    if( tableobj==NIL )
        ? s_tabfile, "not a valid database file"
        usage()
    end
    tabOpen(tableobj)
    

    if( s_driver=="O" )
        con:=sql2.oracle.sqlconnectionNew()
    elseif( s_driver=="P" )
        con:=sql2.postgres.sqlconnectionNew()
    end
    
    dom:=tdsutil.tds2dom(s_tdsfile)
    tableentity:=tdsutil.dom2tabent(con,dom)
    
    if( !empty(s_tabname) )
        tableentity:tablist:={s_tabname}
    else
        s_tabname:=tableentity:tablist[1]
    end

    PRINT(s_tdsfile)
    PRINT(s_tabfile)
    PRINT(s_tabname)
    PRINT(s_skipfld)
    PRINT(s_driver)
    ?

    blklst:={}
    for n:=1 to tabFCount(tableobj)
        cname:=lower(tabColumn(tableobj)[n][COL_NAME])

        if( left(cname,3)=="dbm" .and.;
            tabColumn(tableobj)[n][COL_TYPE]=="C" .and.;
            tabColumn(tableobj)[n][COL_WIDTH]==10 )
            cname:=substr(cname,4)
        end

        if( ":"+upper(cname)+":" $ s_skipfld )
            //kihagyjuk
        elseif( NIL==(col:=tableentity:getcolumn(cname)) )  
            //kihagyjuk
        else
            aadd(blklst,{col:block,tabBlock(tableobj,n)})
            if( s_dbginfo )
                ? cname, "-->", col:expr, col:type
            end
        end
    next
    
    tableentity:drop
    tableentity:create
    
    tabGotop(tableobj)
    while( !tabEof(tableobj) )

        rowentity:=tableentity:instance
        
        for n:=1 to len(blklst)
             eval(blklst[n][1],rowentity,eval(blklst[n][2]))
        next
        
        begin
            rowentity:insert
            con:sqlcommit
        recover err <sqlerror>
            con:sqlrollback
            ? ++errcnt,tabPosition(tableobj),err:description
        end
        
        if( (++cnt%100)==0 )
            ? cnt
        end
        
        tabSkip(tableobj)
    end

    con:sqlcommit()
    
    ? alltrim(str(cnt)),"records inserted,",;
      "elapsed time", alltrim(str(seconds()-sec)), "sec,",;
      "errcnt", alltrim(str(errcnt))
    ?

    return NIL
    
*****************************************************************************

