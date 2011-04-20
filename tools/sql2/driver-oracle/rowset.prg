
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

namespace sql2.oracle

#ifdef EMLEKEZTETO //a rowsetekről

    Ezeket az objektumokat a tableEntityClass leszármazottai
    gyártják a find és select metódusaikkal. Az alkalmazások csak a 

        next
        close

    metódusokat használják, minden mást a tableentity elintéz.

    A next metódus mindaddig új rowentity objektumokat ad, 
    amíg a fetch sikeres, azután NIL-t. Ha a fetch-ek kimerítették
    a rowset-et, akkor az automatikusan lezáródik, ha nem, akkor
    explicite le kell zárni (máskülönben elfogynak a handlerek).

    A tableEntity objektum find metódusa rowentity objektumot ad.
    A tableEntity objektum select metódusai rowset objektumot adnak,
    ennek a next metódusa adogatja a rowentity objektumokat.

#endif

#include "oci.ch"

******************************************************************************
class rowset(object) 
    method  initialize
    method  __table__           {|this|eval(this:__tableblk__)}
    attrib  __tableblk__
    attrib  __transactionid__
    attrib  __stmthandle__
    method  __select__
    method  next
    method  close

******************************************************************************
static function rowset.initialize(this,tab) 
    this:(object)initialize()
    this:__tableblk__:={||tab} //rekurzivitás ellen blockba!
    this:__transactionid__:=tab:connection:__transactionid__
    return this


******************************************************************************
static function rowset.__select__(this,filterclause,orderbyclause,bindarray,wait)

local stmt,dst,n,c,t,deftyp,err

    if( filterclause==NIL .or. filterclause!="distinct" )
        dst:=" "
    else
        filterclause:=substr(filterclause,9) //distinct levágva
        dst:=" distinct "
    end

    stmt:="select"+dst+this:__table__:__selectlist__
    stmt+=" from "+this:__table__:__fromclause__

    if( filterclause!=NIL )
        stmt+=" "+sql2.oracle.sqlbind(filterclause,bindarray)
    end
 
    if( NIL!=orderbyclause )
        stmt+=" order by "+orderbyclause
    end
    
    if( wait==NIL )
        //no lock
    elseif( wait==0 )
        //Az eredménytábla sorait lockolja,
        //a lock független a fetcheléstől (előre minden sort lockol),
        //a lockokat csak a commit/rollback szünteti meg, rowset:close nem,
        //ha a lock nem sikerül, kivételt dob.
        stmt+=" for update nowait "
    elseif( wait==-1 )
        //Mint az előbbi eset, de korlátlan ideig vár .
        stmt+=" for update "
    else
        //Mint az előbbi eset, de a megadott másodpercig vár.
        stmt+=" for update wait "+alltrim(str(wait))
    end

    stmt:=sql2.oracle.sqlidcase(stmt,.t.)
    
    sql2.oracle.sqldebug(stmt)

    this:__stmthandle__:=sql2.oracle._oci_preparestatement(this:__table__:connection:__conhandle__,stmt)

    for n:=1 to len(this:__table__:columnlist)
        c:=this:__table__:columnlist[n]
        t:=left(c:type,1)

        if( t=="C" )
            deftyp:=SQLT_AFC
        elseif( t=="N" )
            deftyp:=SQLT_FLT
        elseif( t=="D" )
            deftyp:=SQLT_DAT
        elseif( t=="L" )
            deftyp:=SQLT_INT
        elseif( t=="M" )
            deftyp:=SQLT_BLOB
        end

        sql2.oracle._oci_definebypos(this:__stmthandle__,n,this:__table__:__buffer__,c:offset+4,deftyp,c:size-4,c:offset)
    next
    
    begin
        sql2.oracle._oci_executestatement(this:__stmthandle__,0,OCI_DEFAULT)
    recover err
        this:close
        break(err)
    end
    
    //Ha lock volt előírva, és az nem sikerült,
    //akkor kivételt dobunk: sqllockerror, sqldeadlockerror.


******************************************************************************
static function rowset.next(this) //rowentity objektumgyártó
local rowentity
local columnlist,n

    if( this:__stmthandle__==NIL )
        //az eredmény NIL

    elseif( this:__table__:connection:__transactionid__!=this:__transactionid__ )
        //fetch across commit/rollback
        //az eredmény NIL
        //Az Oracle tudna tranzakcióhatáron át is fetchelni,
        //de csak annyit engedünk, amennyit a Postgres is tud.
        this:close

    elseif( sql2.oracle._oci_fetch(this:__stmthandle__) )
        rowentity:=objectNew(this:__table__:__rowclassid__)
        rowentity:initialize(this:__table__)

        if( this:__table__:__rereadflag__!=.t. .and. this:__table__:__memocount__!=NIL )
            columnlist:=this:__table__:columnlist
            for n:=1 to len(columnlist)
                if( columnlist[n]:type=="M"  )
                    columnlist[n]:eval(rowentity)  //behozza a memót
                end
            next
        end

    else
        this:close
        //az eredmény NIL
    end

    return rowentity
 

******************************************************************************
static function rowset.close(this)
    if(this:__stmthandle__!=NIL)
        sql2.oracle._oci_freestatement(this:__stmthandle__) 
        this:__stmthandle__:=NIL
    end
    return NIL
 

******************************************************************************
 