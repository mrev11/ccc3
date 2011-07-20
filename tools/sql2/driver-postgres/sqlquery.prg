
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


static _crs_count:=0

****************************************************************************
class sqlquery(object)
    method  initialize

    attrib  connection
    attrib  __querytext__
    attrib  __stmthandle__  //PQresult
    attrib  __cursor__
    attrib  __prefetched__
    attrib  __selectlist__
    attrib  __buffer__
    attrib  __indvar__

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
local status,err

    if( bind!=NIL )
        query:=sql2.postgres.sqlbind(query,bind)
    end

    this:(object)initialize

    this:connection:=con
    this:__cursor__:="query_"+alltrim(str(++_crs_count))
    this:__querytext__:="declare "+this:__cursor__+" cursor for "+query
    sql2.postgres.sqldebug(this:__querytext__)
    this:__stmthandle__:=sql2.postgres._pq_exec(this:connection:__conhandle__,this:__querytext__)
    status:=sql2.postgres._pq_resultstatus(this:__stmthandle__)

    if( status!=PGRES_COMMAND_OK )
        err:=sql2.postgres.sqlerrorCreate(this:__stmthandle__)
        err:operation:="sqlqueryIni"
        err:args:={query}
        this:close
        break(err)
    else
        this:__prefetched__:=this:next //felszedi az oszlopadatokat
    end

    return this
    
//Ez nem működik, ha a selectben "for update" van.
//Kéne egy cursor nélküli változat is lockoláshoz.
//Lehet lockolni így: con:sqlexec("select ... for update").
    
****************************************************************************
static function sqlquery.next(this)

local n,stmt,result,status,retcode:=.f.

    if( this:__stmthandle__==NIL )
        retcode:=.f.

    elseif( this:__prefetched__==.t. )
        retcode:=.t.
        this:__prefetched__:=.f.

    else
        stmt:="fetch forward 1 in "+this:__cursor__
        sql2.postgres.sqldebug(stmt)
        result:=sql2.postgres._pq_exec(this:connection:__conhandle__,stmt)
        status:=sql2.postgres._pq_resultstatus(result)

        if( status==PGRES_TUPLES_OK )

            if( this:__selectlist__==NIL )
                //első alkalommal feltöltjük az oszlopneveket
                this:__selectlist__:=array(sql2.postgres._pq_nfields(result))
                this:__buffer__:=array(sql2.postgres._pq_nfields(result))
                this:__indvar__:=array(sql2.postgres._pq_nfields(result))
                for n:=1 to len(this:__selectlist__)
                    this:__selectlist__[n]:=sql2.postgres._pq_fname(result,n)
                next
            end

            if( sql2.postgres._pq_ntuples(result)==1 )
                for n:=1 to len(this:__indvar__)
                    this:__buffer__[n]:=sql2.postgres._pq_getvalue0(result,1,n) //binary string
                    this:__indvar__[n]:=sql2.postgres._pq_getisnull(result,1,n)
                next
                retcode:=.t.
            else
                this:close
                retcode:=.f.
            end

        else
            this:close
            retcode:=.f.
        end

        sql2.postgres._pq_clear(result)
    end

    return retcode

****************************************************************************
static function sqlquery.close(this)
    if( this:__stmthandle__!=NIL )
        sql2.postgres._pq_clear(this:__stmthandle__) 
        this:__stmthandle__:=NIL
    end
    return NIL

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
