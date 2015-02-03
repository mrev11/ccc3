
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

namespace sql2.postgres

#include "pq.ch"

#ifdef EMLEKEZTETO //sqlquery program használat

    query:=con:sqlquerynew("select * from szamla")

    while( query:next )
        for n:=1 to query:fcount
            ? query:fname(n), query:isnull(n), query:getchar(n)
        next
        ? query:getchar('szamlaszam')
        ? query:getnumber('osszeg')
        ? query:getdate('konyvkelt')
        ? query:getlogical('tulmenflag')
    end
    query:close //magától is lezáródik

    Postgres-ben a fetchelés nem tud átnyúlni a tranzakcióhatáron!
#endif


****************************************************************************
class sqlquery(object)
    method  initialize

    attrib  connection
    attrib  __querytext__
    attrib  __stmthandle__
    attrib  __cursorid__    // SQL azonosító
    attrib  __prefetched__
    attrib  __selectlist__
    attrib  __buffer__
    attrib  __indvar__
    attrib  __closestmtidx__
    attrib  __ntuples__
    attrib  __next__
    attrib  __transactionid__

    method  next
    method  close
    method  fcount          {|t|len(t:__selectlist__)}
    method  fname           {|t,x|t:__selectlist__[x]}
    method  findcolumn
    method  isnull
    method  getbinary
    method  getchar
    method  getnumber
    method  getdate
    method  getlogical

****************************************************************************
static function sqlquery.initialize(this,con,query,bind)
local status,pos,n,err

    if( bind!=NIL )
        query:=sql2.postgres.sqlbind(query,bind)
    end

    this:connection:=con
    this:__transactionid__:=con:__transactionid__
    this:__querytext__:=(query::=alltrim)

    if( query[1..8]::lower=="declare " )
        if( 0<(pos:=at(" cursor",lower(query))) )
            //declare CURSORID cursor for ...
            this:__cursorid__:=query[9..pos-1]::alltrim  
            if( empty(this:__cursorid__) )
                this:__cursorid__:="query_"+alltrim(str(++this:connection:__cursorcount__)) //automatikus cursorid
                query:="declare "+this:__cursorid__+query[8..]
                this:__querytext__:=query
            end
        end
    end

    this:__closestmtidx__:=this:connection:__addstatementtoclose__({||this:__closestmtidx__:=NIL,this:close})

    sql2.postgres.sqldebug(this:__querytext__)
    this:__stmthandle__:=sql2.postgres._pq_exec(this:connection:__conhandle__,this:__querytext__)
    status:=sql2.postgres._pq_resultstatus(this:__stmthandle__)

    if( this:__cursorid__!=NIL .and. status==PGRES_COMMAND_OK )
        this:__prefetched__:=this:next //felszedi az oszlopadatokat

    elseif( this:__cursorid__==NIL .and. status==PGRES_TUPLES_OK )
        this:__ntuples__:=sql2.postgres._pq_ntuples(this:__stmthandle__)
        this:__next__:=0

        //feltöltjük az oszlopneveket
        this:__selectlist__:=array(sql2.postgres._pq_nfields(this:__stmthandle__))
        this:__buffer__:=array(sql2.postgres._pq_nfields(this:__stmthandle__))
        this:__indvar__:=array(sql2.postgres._pq_nfields(this:__stmthandle__))
        for n:=1 to len(this:__selectlist__)
            this:__selectlist__[n]:=sql2.postgres._pq_fname(this:__stmthandle__,n)
        next

    elseif( status==PGRES_COMMAND_OK )
        //Ide akkor jön, ha az utasítás nem select,
        //hanem pl. update (aminek persze nincs értelme).
        //Itt csak selectekkel foglalkozunk,
        //de hagyni is lehetne (működik).

        this:close
        this:__ntuples__:=0
        this:__next__:=0

        //return this //nem select végrehajtva

        err:=sqlerrorNew()
        err:operation:="sqlquery.initialize"
        err:description:="select statement requiered"
        err:args:={this:__querytext__}
        err:subsystem:="sql2.postgres"
        break(err)

    else
        err:=sql2.postgres.sqlerrorCreate(this:__stmthandle__)
        err:operation:="sqlquery.initialize"
        err:args:={query}
        this:close
        break(err)
    end

    return this
    
    
****************************************************************************
static function sqlquery.next(this)

local n,stmt,result,status,err,retcode:=.f.

    if( this:__stmthandle__==NIL )
        retcode:=.f.

    elseif( this:__prefetched__==.t. )
        retcode:=.t.
        this:__prefetched__:=.f.

    elseif( this:__cursorid__!=NIL )

        stmt:="fetch forward 1 in "+this:__cursorid__
        sql2.postgres.sqldebug(stmt)
        result:=sql2.postgres._pq_exec(this:connection:__conhandle__,stmt)
        status:=sql2.postgres._pq_resultstatus(result)

        if( status!=PGRES_TUPLES_OK )
            //error, kivételt dob
            err:=sql2.postgres.sqlerrorCreate(result)
            err:operation:="sqlquery:next"
            sql2.postgres._pq_clear(result)
            this:close
            break(err)
            retcode:=.f.

        else

            if( this:__selectlist__==NIL )
                //első alkalommal feltöltjük az oszlopneveket
                this:__selectlist__:=array(sql2.postgres._pq_nfields(result))
                this:__buffer__:=array(sql2.postgres._pq_nfields(result))
                this:__indvar__:=array(sql2.postgres._pq_nfields(result))
                for n:=1 to len(this:__selectlist__)
                    this:__selectlist__[n]:=sql2.postgres._pq_fname(result,n)
                next
            end

            if( sql2.postgres._pq_ntuples(result)!=1 )
                //nincs adat, az eredmény .f.
                sql2.postgres._pq_clear(result)
                this:close
                retcode:=.f.
            else
                //van adat, az eredmény .t.
                for n:=1 to len(this:__indvar__)
                    this:__buffer__[n]:=sql2.postgres._pq_getvalue0(result,1,n) //binary string
                    this:__indvar__[n]:=sql2.postgres._pq_getisnull(result,1,n)
                next
                sql2.postgres._pq_clear(result)
                retcode:=.t.
            end
        end

    elseif( ++this:__next__>this:__ntuples__ )
        //kurzor nélkül, elfogyott az adat
        this:close
        retcode:=.f.

    else
        //kurzor nélkül, van adat
        for n:=1 to len(this:__indvar__)
            this:__buffer__[n]:=sql2.postgres._pq_getvalue0(this:__stmthandle__,this:__next__,n) //binary string
            this:__indvar__[n]:=sql2.postgres._pq_getisnull(this:__stmthandle__,this:__next__,n)
        next
        retcode:=.t.
    end

    return retcode

****************************************************************************
static function sqlquery.close(this)
    if( this:__stmthandle__!=NIL )
        sql2.postgres._pq_clear(this:__stmthandle__) 
        this:__stmthandle__:=NIL
        this:__cursorid__:=NIL
    end
    if( this:__closestmtidx__!=NIL )
        //? "CLEAR-qu"
        this:connection:__clearstatement__(this:__closestmtidx__)
        this:__closestmtidx__:=NIL
    end


#ifdef NOT_DEFINED
  Megjegyzés, Postgresben két dolgot kell/lehet lezárni:

  i) A "declare CID cursor for select..." utasítást handlerét,
    ez mindenképpen szükséges, másképp fogy a memória. 

  ii) Magát a cursort egy "close CID" SQL utasítással,
    ez automatikusan is megtörténik a commit/rollbacknél.
    Mivel automatikusan lezáródik, nem érdemes vele bajlódni.
    Ha rossz helyen próbáljuk lezárni, az hibát okoz.
    Ha hagyjuk, akkor ugyanazt a kurzor azonosítót 
    a tranzación belül nem lehet újra használni.
#endif

****************************************************************************
static function sqlquery.findcolumn(this,name)
local x
    name:=lower(name)
    for x:=1 to len(this:__selectlist__)
        if( lower(this:__selectlist__[x])==name )
            return x
        end
    next
    return 0

****************************************************************************
static function sqlquery.isnull(this,x)
    return this:__indvar__[if(valtype(x)=="N",x,this:findcolumn(x))]

****************************************************************************
static function sqlquery.getbinary(this,x)
local idx:=if(valtype(x)=="N",x,this:findcolumn(x))
    return if(this:__indvar__[idx],a"",sql2.postgres._pq_unescapebytea(this:__buffer__[idx]))

****************************************************************************
static function sqlquery.getchar(this,x)
    return bin2str(this:getbinary(x))

****************************************************************************
static function sqlquery.getnumber(this,x)
    return val(this:getbinary(x))

****************************************************************************
static function sqlquery.getdate(this,x)
    return ctod(this:getchar(x))

****************************************************************************
static function sqlquery.getlogical(this,x)
    return this:getbinary(x)==BINLIT('t')

****************************************************************************
