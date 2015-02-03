
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

namespace sql2.db2

#include "db2.ch"

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
    attrib  __selectlist__
    attrib  __db2coltype__
    attrib  __buffer__
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
local err
local fldcnt,coldesc,n
local rc

    if( bind!=NIL )
        query:=sql2.db2.sqlbind(query,bind)
    end

    this:connection:=con
    this:__querytext__:=query
    sql2.db2.sqldebug(this:__querytext__)
    this:__stmthandle__:=sql2.db2._db2_execdirect(this:connection:__conhandle__,this:__querytext__)
    rc:=sql2.db2._db2_retcode(this:__stmthandle__)

    if( rc!=SQL_SUCCESS )
        err:=sql2.db2.sqlerror_create(this:__stmthandle__)
        err:operation:="sqlquery.initialize"
        err:args:={query}
        this:close
        break(err)

    elseif( 0==(fldcnt:=sql2.db2._db2_numresultcols(this:__stmthandle__)) )  
        //? "nem select"
        //itt csak selectekkel foglalkozunk
        //de hagyni is lehetne (működik)

        this:close 
        //return this //nem select végrehajtva

        err:=sqlerrorNew()
        err:operation:="sqlquery.initialize"
        err:description:="select statement requiered"
        err:args:={this:__querytext__}
        err:subsystem:="sql2.db2"
        break(err)
        
    else
        // ? "select"
        this:__selectlist__:=array(fldcnt)
        this:__db2coltype__:=array(fldcnt)
        for n:=1 to len(this:__selectlist__)
            coldesc:=sql2.db2._db2_describecol(this:__stmthandle__,n)
            this:__selectlist__[n]:=coldesc[1]
            this:__db2coltype__[n]:=coldesc[2]
            //this:__selectlist__[n]:=sql2.db2._db2_colname(this:__stmthandle__,n)
        next

        this:__closestmtidx__:=this:connection:__addstatementtoclose__({||this:__closestmtidx__:=NIL,this:close})
    end
    return this


****************************************************************************
static function sqlquery.next(this)
local retcode:=.f.
local n,convtype
local result,err

    if( this:__stmthandle__==NIL )
        //closed

    elseif( SQL_SUCCESS!=(result:=sql2.db2._db2_fetch(this:__stmthandle__)) )
        if( result==SQL_NO_DATA  )
            this:close
        else
            err:=sql2.db2.sqlerror_create(this:__stmthandle__)
            err:operation:="sqlquery:next"
            this:close
            break(err)
        end
    else
        this:__buffer__:=array(this:fcount)
        for n:=1 to this:fcount
            if( this:__db2coltype__[n]==SQL_BLOB  )
                convtype:=SQL_BINARY
            else
                convtype:=SQL_CHAR
            end
            //más típusokat is számításba kéne venni
            this:__buffer__[n]:=sql2.db2._db2_getdata(this:__stmthandle__,n,convtype)
        next
        retcode:=.t.
    end

    return retcode

****************************************************************************
static function sqlquery.close(this)
    if( this:__stmthandle__!=NIL )
        sql2.db2._db2_closestatement(this:__stmthandle__) 
        this:__stmthandle__:=NIL
        this:__buffer__:=NIL
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
local idx:=if(valtype(x)=="N",x,this:findcolumn(x))
    return this:__buffer__[idx]==NIL

****************************************************************************
static function sqlquery.getbinary(this,x)
local idx:=if(valtype(x)=="N",x,this:findcolumn(x))
    return if(this:__buffer__[idx]==NIL,a"",this:__buffer__[idx])

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
    //return this:getbinary(x)==BINLIT('t')
    return val(this:getbinary(x))!=0

#ifdef EMLEKEZTETO //boolean típus
    Oracle-ben number(1) típust használtunk, mert nincs boolean.
    Postgresben van boolean, melynek értékét a TRUE/FALSE literál jelöli.
    MySQL-ben nincs valódi boolean: boolean,true,false -> tinyint,1,0 (alias?)
#endif

****************************************************************************
