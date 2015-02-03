
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
#include "sql.ch"

******************************************************************************
class sqlconnection(object)
    method  initialize
    attrib  __conhandle__
    attrib  __coninfo__
    attrib  __transactionid__
    attrib  __isolationlevel__
    attrib  __sessionisolationlevel__
    attrib  __statementstoclose__
    attrib  __cursorcount__
    method  __addstatementtoclose__
    method  __clearstatement__
    method  driver              {||"sql2.postgres"}
    method  version
    method  duplicate
    method  sqldisconnect
    method  sqlexecx
    method  sqlexec
    method  sqlisolationlevel
    method  sqlcommit
    method  sqlrollback
    method  sqlquerynew         {|this,stmt,bind|sql2.postgres.sqlqueryNew(this,stmt,bind)}
    method  sqlsequencenew      {|this,name|sql2.postgres.sqlsequenceNew(this,name)}
    method  __tableentityclass__{|this|sql2.postgres.tableentityClass()}

******************************************************************************
static function sqlconnection.initialize(this,coninfo)
    this:(object)initialize

    if( coninfo==NIL )
        coninfo:=getenv("POSTGRES_CONNECT")
    end
    this:__coninfo__:=coninfo
    this:__conhandle__:=sql2.postgres._pq_connectdb(coninfo)
    sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"set session characteristics as transaction isolation level read committed"))
    //sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"set autocommit to off"))
    sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"begin transaction"))
    this:__transactionid__:=0
    this:__isolationlevel__:=ISOL_COM
    this:__sessionisolationlevel__:=ISOL_COM
    this:__statementstoclose__:=array(64)
    this:__cursorcount__:=0

#ifdef EMLEKEZTETO  //a Postgres autocommitról
    A Postgres 7.4-ben megszűnt a szerver oldali autocommit,
    ezért a tranzakciók automatikus indítását kliens oldalon
    kell csinálni. Korábban autocommit=off módban dolgoztunk.
#endif

    return this

******************************************************************************
static function sqlconnection.version(this)
local q:=this:sqlquerynew("select version()")
local v:=if(q:next,q:getchar(1),"")
    q:close
    return v

******************************************************************************
static function sqlconnection.duplicate(this)
    return sqlconnectionNew(this:__coninfo__)

******************************************************************************
static function sqlconnection.sqldisconnect(this)
    sql2.postgres._pq_finish(this:__conhandle__)
    this:__conhandle__:=NIL
    return NIL

******************************************************************************
static function sqlconnection.sqlexec(this,stmt,bind)
local result,status,err
local rowcount:=0

    if( bind!=NIL )
        stmt:=sql2.postgres.sqlbind(stmt,bind)
    end

    sql2.postgres.sqldebug(stmt)

    result:=sql2.postgres._pq_exec(this:__conhandle__,stmt)
    status:=sql2.postgres._pq_resultstatus(result)

    if( status==PGRES_COMMAND_OK )
        rowcount:=val(sql2.postgres._pq_cmdtuples(result))
        sql2.postgres._pq_clear(result)

    elseif( status==PGRES_TUPLES_OK )
        sql2.postgres._pq_clear(result)

    else
        err:=sql2.postgres.sqlerrorCreate(result)
        err:operation:="sqlexec"
        err:args:={stmt}

        sql2.postgres._pq_clear(result)
        sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"rollback"))
        sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"begin transaction"))
        this:__transactionid__++
        break(err)
    end
    return rowcount

#ifdef EMLEKEZTETO //a Postgres automatikus abortjáról
    Hiba esetén a Postgres automatikusan és elkerülhetetlenül
    abortálja a tranzakciót, és a következő commit/rollback utasításig
    semmit sem hajt végre. Ezért jobb rögtön explicite rollbackelni.
    
    A Postgres 7.4-től kezdve nincs szerver oldali autocommit=on/off
    management, azért a kliens oldalon kell csinálni a tranzakciók
    automatikus kezdését a korábbi autocommit=off módnak megfelelően.
    
    Az Oracle úgy működik, mintha minden utasítás előtt volna
    egy implicit savepoint, és ha az utasítás sikertelen, akkor
    eddig az implicit savepointig rollbackel. A Postgresben
    azonban nincsenek savepointok.
#endif

******************************************************************************
static function sqlconnection.sqlexecx(this,stmt,bind)
local err
    begin
        this:sqlexec(stmt,bind)
    recover err <sqlerror>
    end
    return err

******************************************************************************
static function sqlconnection.sqlisolationlevel(this,numlevel,flag:=.f.)

//flag==.t. az egész sessionre
//flag==.f. egy tranzakcióra

local stmt,txtlevel:=""
local previous_level

    if( numlevel==ISOL_READ_COMMITTED )
        //compatibility
        numlevel:=ISOL_COM
    end

    if( flag )
        previous_level:=this:__sessionisolationlevel__
    else
        previous_level:=this:__isolationlevel__
    end

    if( numlevel==NIL )
        //csak lekérdezés
        return previous_level
    end

    if( 0!=numand(numlevel,ISOL_SER) )
        txtlevel+=", isolation level SERIALIZABLE"
    end
    if( 0!=numand(numlevel,ISOL_REP) )
        txtlevel+=", isolation level REPEATABLE READ"
    end
    if( 0!=numand(numlevel,ISOL_COM) )
        txtlevel+=", isolation level READ COMMITTED"
    end
    if( 0!=numand(numlevel,ISOL_RO) )
        txtlevel+=", READ ONLY"
    end
    if( 0!=numand(numlevel,ISOL_RW) )
        txtlevel+=", READ WRITE"
    end
    txtlevel::=substr(2) //kezdő "," levéve
    
    
    if( flag )
        //a session-re
        stmt:="set session characteristics as transaction "+txtlevel

        sqlconnection.close_pending_statements(this,"set isolation")
        sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"rollback"))
        this:sqlexec(stmt) // ennek rollback és begin között kell lennie 
        sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"begin transaction"))

    else
        //egy tranzakcióra
        stmt:="set transaction "+txtlevel

        sqlconnection.close_pending_statements(this,"set isolation")
        sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"rollback"))
        sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"begin transaction"))
        this:sqlexec(stmt) // ennek közvetlenül a begin után kell lennie
    end
 
    this:__transactionid__++

    this:__isolationlevel__:=numlevel
    if( flag )
        this:__sessionisolationlevel__:=numlevel
    end

    return previous_level

// A beállítások lekérdezhetők:
//  select current_setting('transaction_read_only')
//  select current_setting('transaction_isolation')

******************************************************************************
static function sqlconnection.sqlcommit(this)
    sqlconnection.close_pending_statements(this,"commit transaction")
    this:sqlexec("commit")
    sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"begin transaction"))
    this:__transactionid__++
    this:__isolationlevel__:=this:__sessionisolationlevel__
    return NIL

******************************************************************************
static function sqlconnection.sqlrollback(this)
    sqlconnection.close_pending_statements(this,"rollback transaction")
    this:sqlexec("rollback")
    sql2.postgres._pq_clear(sql2.postgres._pq_exec(this:__conhandle__,"begin transaction"))
    this:__transactionid__++
    this:__isolationlevel__:=this:__sessionisolationlevel__
    return NIL

#ifdef EMLEKEZTETO //autocommit
    A Postgres 7.4-ben megszűnt a szerver oldali autocommit,
    ezért a tranzakciók automatikus indítását kliens oldalon
    kell csinálni. Korábban autocommit=off módban dolgoztunk.
    Ekkor minden commit után automatikusan indult a következő
    tranzakció, ami a következő commit-ig tartott.
#endif


******************************************************************************
static function sqlconnection.__addstatementtoclose__(this,blk)
local idx,err
    for idx:=1 to len(this:__statementstoclose__)
        if( this:__statementstoclose__[idx]==NIL )
            this:__statementstoclose__[idx]:=blk
            return idx
        end
    next
    err:=sqlerrorNew()
    err:operation:="sqlconnection.__addstatementtoclose__"
    err:description:="too many statements"
    break(err)

******************************************************************************
static function sqlconnection.__clearstatement__(this,idx)
    this:__statementstoclose__[idx]:=NIL


******************************************************************************
static function sqlconnection.close_pending_statements(this,txt)
local idx,n:=0,err
    for idx:=1 to len(this:__statementstoclose__)
        if( this:__statementstoclose__[idx]!=NIL )
            eval(this:__statementstoclose__[idx])
            this:__statementstoclose__[idx]:=NIL
            n++
        end
    next
    if( n>0 )
        err:=sqlerrorNew()
        err:operation:="sqlconnection.close_pending_statements"
        err:description:="cannot TXT - SQL statements in progress"::strtran("TXT",txt)
        break(err)
    end

******************************************************************************
