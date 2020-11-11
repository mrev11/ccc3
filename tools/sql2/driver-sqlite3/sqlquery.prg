
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

namespace sql2.sqlite3

#include "sqlite3.ch"

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
    attrib  __cursor__
    attrib  __selectlist__
    attrib  __closestmtidx__

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
local err,n

    if( bind!=NIL )
        query:=sql2.sqlite3.sqlbind(query,bind)
    end

    this:(object)initialize

    this:connection:=con
    this:__querytext__:=query
    sql2.sqlite3.sqldebug(this:__querytext__)
    this:__stmthandle__:=_sqlite3_prepare(this:connection:__conhandle__,this:__querytext__)
    
    if( this:__stmthandle__==NIL )
        err:=sqlerrorNew()
        err:operation:="sqlquery.initialize"
        err:description:=_sqlite3_errmsg(this:connection:__conhandle__)
        err:subcode:=_sqlite3_errcode(this:connection:__conhandle__)
        err:subsystem:="sql2.sqlite3"
        err:args:={this:__querytext__}
        break(err)
    end

    if( 0==_sqlite3_column_count(this:__stmthandle__) )
        //nem select (hanem pl. update)
        //itt csak selectekkel foglalkozunk
        //de hagyni is lehetne (működik)
        
        this:next //ez kell, hogy tényelegesen végrehajtsa
        this:close
        
        //return this //nem select végrehajtva

        err:=sqlerrorNew()
        err:operation:="sqlquery.initialize"
        err:description:="select statement required"
        err:args:={this:__querytext__}
        err:subsystem:="sql2.sqlite3"
        break(err)
    else
        this:__selectlist__:=array(_sqlite3_column_count(this:__stmthandle__))
        for n:=1 to len(this:__selectlist__)
            this:__selectlist__[n]:=_sqlite3_column_name(this:__stmthandle__,n)
        next

        this:__closestmtidx__:=this:connection:__addstatementtoclose__({||this:__closestmtidx__:=NIL,this:close})
    end

    return this

    
****************************************************************************
static function sqlquery.next(this)

local n,result,err,retcode:=.f.

    if( this:__stmthandle__==NIL )
        retcode:=.f.

    else
        result:=_sqlite3_step(this:__stmthandle__)
        if( result==SQLITE_ROW )
            retcode:=.t.

        elseif( result==SQLITE_DONE )
            this:close
            retcode:=.f.

        else
            err:=sqlerrorNew()
            err:operation:="sqlquery.next"
            err:description:=_sqlite3_errmsg(this:onnection:__conhandle__)
            err:subcode:=_sqlite3_errcode(this:connection:__conhandle__)
            err:subsystem:="sql2.sqlite3"
            break(err)
        end
    end
    return retcode

****************************************************************************
static function sqlquery.close(this)
    if( this:__stmthandle__!=NIL )
        _sqlite3_finalize(this:__stmthandle__)
        this:__stmthandle__:=NIL
    end
    if( this:__closestmtidx__!=NIL )
        //? "CLEAR-qu"
        this:connection:__clearstatement__(this:__closestmtidx__)
        this:__closestmtidx__:=NIL
    end

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
    x:=if(valtype(x)=="N",x,this:findcolumn(x))
    return SQLITE_NULL==_sqlite3_column_type(this:__stmthandle__,x)

****************************************************************************
static function sqlquery.getbinary(this,x)
    x:=if(valtype(x)=="N",x,this:findcolumn(x))
    if( SQLITE_NULL!=_sqlite3_column_type(this:__stmthandle__,x) )
        return _sqlite3_column_blob(this:__stmthandle__,x)
    end
    return a""

****************************************************************************
static function sqlquery.getchar(this,x)
    x:=if(valtype(x)=="N",x,this:findcolumn(x))
    if( SQLITE_NULL!=_sqlite3_column_type(this:__stmthandle__,x) )
        return _sqlite3_column_text(this:__stmthandle__,x)
    end
    return ""

****************************************************************************
static function sqlquery.getnumber(this,x)
    x:=if(valtype(x)=="N",x,this:findcolumn(x))
    if( SQLITE_NULL!=_sqlite3_column_type(this:__stmthandle__,x) )
        return _sqlite3_column_double(this:__stmthandle__,x)
    end
    return 0

****************************************************************************
static function sqlquery.getdate(this,x)
    x:=if(valtype(x)=="N",x,this:findcolumn(x))
    if( SQLITE_NULL!=_sqlite3_column_type(this:__stmthandle__,x) )
        return _sqlite3_column_text(this:__stmthandle__,x)::ctod
    end
    return 0

****************************************************************************
static function sqlquery.getlogical(this,x)
    x:=if(valtype(x)=="N",x,this:findcolumn(x))
    if( SQLITE_NULL!=_sqlite3_column_type(this:__stmthandle__,x) )
        return _sqlite3_column_double(this:__stmthandle__,x)!=0
    end
    return .f.

****************************************************************************

