
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

#define ENTITYLIB(x,c)  testdata(x,c)

// Az ENITYLIB-ben definiált táblákat tudja importálni 
// btbtx, datidx, vagy dbfctx formátumú fájlokból.
// A könyvtárnevet bele kell írni a programba
// (azaz a fenti makrót alkalmanként módosítani kell)
// és a könyvtárat bele kell linkelni a programba.
//
// Ha az osztálydefiníciókat nem a könyvtárból venné,
// hanem közvetlenül az XML alapján készítené,
// akkor nem kellene belinkelni a könyvtárat.
// Általános alkalmazások is működhetnének úgy,
// hogy a tableentity osztálydefiníciókat nem a generált
// prg-kből készített könyvtárból vennék, hanem közvetlenül
// az XML-ből. Akkor minden program XML elemzéssel indulna.

#include "table.ch"


static s_entname
static s_tabfile
static s_tabname
static s_skipfld:=""
static s_driver

#define PRINT(x) ? #x, x

*****************************************************************************
function usage()
local x:=<<usage>>
Usage: btimport -d driver -e entity -f btfile [-n table] [-s skipfld]*

    driver  : O[racle]/P[ostgres]
    entity  : tableentity class name in the linked entitylib
    btfile  : bt (dat/dbf) file specification to be imported
    table   : qulified table name in the SQL database
    skipfld : omitted field
<<usage>>
    ?? x
    ?
    quit

*****************************************************************************
function main()

local tent,tab,ent,cname,blklst,n
local err,errcnt:=0
local skipfld:={}
local cnt:=0,sec:=seconds()
local con

    set date format "yyyy-mm-dd"

    set printer to ("log-"+alltrim(str(getpid())))
    set printer on

    n:=0
    while( NIL!=argv(++n) )

        if( argv(n)=="-e" )
            s_entname:=argv(++n)
        elseif( argv(n)=="-f" )
            s_tabfile:=argv(++n)
        elseif( argv(n)=="-n" )
            s_tabname:=argv(++n)
        elseif( argv(n)=="-s" )
            s_skipfld:=":"+upper(argv(++n))+":"
        elseif( argv(n)=="-d" )
            s_driver:=left(upper(argv(++n)),1)
            if( !s_driver$"OP" )
                usage()
            end
        end
    end
 
    if( NIL==s_entname )
        usage()
    end
    if( NIL==s_tabfile )
        usage()
    end
    if( NIL==s_driver )
        usage()
    end


    tab:=tabResource(s_tabfile)
    if( tab==NIL )
        ? s_tabfile, "not a valid database file"
        usage()
    end
    tabOpen(tab)
    

    if( s_driver=="O" )
        con:=sql2.oracle.sqlconnectionNew()
    elseif( s_driver=="P" )
        con:=sql2.postgres.sqlconnectionNew()
    end
    
    tent:=ENTITYLIB(s_entname,con)
    if( tent==NIL )
        ? s_entname, "not in entity lib"
        usage()
    end
    
    if( !empty(s_tabname) )
        tent:tablist:={s_tabname}
    else
        s_tabname:=tent:tablist[1]
    end

    PRINT(s_entname)
    PRINT(s_tabfile)
    PRINT(s_tabname)
    PRINT(s_skipfld)
    PRINT(s_driver)
    ?

    blklst:=array(tabFCount(tab))
    for n:=1 to tabFCount(tab)
        cname:=lower(tabColumn(tab)[n][COL_NAME])

        if( left(cname,3)=="dbm" .and.;
            tabColumn(tab)[n][COL_TYPE]=="C" .and.;
            tabColumn(tab)[n][COL_WIDTH]==10 )
            cname:=substr(cname,4)
        end
        
        blklst[n]:=getmethod(tent:__rowclassid__,cname)

        //ezeket kihagyjuk        
        if( ":"+upper(cname)+":" $ s_skipfld )
            aadd(skipfld,n)
        end
    next
    
    tent:drop
    tent:create
    
    tabGotop(tab)
    while( !tabEof(tab) )

        ent:=tent:instance
        
        for n:=1 to tabFCount(tab)
            if( 0==ascan(skipfld,n) )
                eval(blklst[n],ent,tabEvalcolumn(tab,n))
            end
        next
        
        begin sequence
            ent:insert
            con:sqlcommit()
        recover err <sqlerror>
            con:sqlrollback()
            ? ++errcnt,tabPosition(tab),err:description
        end sequence
        
        if( (++cnt%100)==0 )
            ? cnt
            fflush()
        end
        
        tabSkip(tab)
    end

    con:sqlcommit()
    
    ? alltrim(str(cnt)),"records inserted,",;
      "elapsed time", alltrim(str(seconds()-sec)), "sec,",;
      "errcnt", alltrim(str(errcnt))
    ?

    return NIL
    
*****************************************************************************

