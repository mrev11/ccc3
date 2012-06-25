
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
#include "sql.ch"

******************************************************************************
class sqlconnection(object)
    method  initialize

    attrib  __conhandle__
    attrib  __coninfo__
    attrib  __transactionid__
    attrib  __isolationlevel__
    attrib  __sessionisolationlevel__
    attrib  __statementhandles__

    method  driver                  {||"sql2.sqlite3"}
    method  version
    method  duplicate
    method  sqldisconnect
    method  sqlexecx
    method  sqlexec
    method  sqlisolationlevel
    method  sqlcommit
    method  sqlrollback
    method  sqlquerynew             {|this,stmt,bind|sql2.sqlite3.sqlqueryNew(this,stmt,bind)}
    method  sqlsequencenew          {|this,name|sql2.sqlite3.sqlsequenceNew(this,name)}
    method  __tableentityclass__    {|this|sql2.sqlite3.tableentityClass()}


******************************************************************************
static function sqlconnection.initialize(this,coninfo)  //coninfo egy filename

local err,errmsg
local attach:="attach database '$DBFILE' as $ALIAS"
local attach1,dbfali,n

    this:(object)initialize

    if( coninfo==NIL )
        coninfo:=getenv("SQLITE3_CONNECT")
    end
    this:__coninfo__:=coninfo

    //coninfo: 'dbfile1:dbfile2=alias2:dbfile3=alias3...'
    coninfo::=split(pathsep()) //{dbfile1, dbfile2=alias2, ... }

    this:__conhandle__:=_sqlite3_open(coninfo[1])

    if( this:__conhandle__==NIL )
        err:=sqlconnecterrorNew()
        err:operation:="sqlconnection.initialize"
        err:args:={this:__coninfo__}
        //err:subcode:=_sqlite3_errcode(this:__conhandle__)
        //err:description:=_sqlite3_errmsg(this:__conhandle__)
        break(err)
    else
        outerr("attach to "+coninfo[1]+endofline()) 
    end
    
    for n:=2 to len(coninfo)
        attach1:=attach
        dbfali:=coninfo[n]::split("=")
        attach1::=strtran("$DBFILE",dbfali[1])
        attach1::=strtran("$ALIAS",dbfali[2])
        _sqlite3_exec(this:__conhandle__,attach1,@errmsg)

        if( errmsg!=NIL )
            err:=sqlconnecterrorNew()
            err:operation:="sqlconnection.initialize"
            err:args:={attach1}
            err:subcode:=_sqlite3_errcode(this:__conhandle__)
            err:description:=errmsg
            break(err)
        else
            outerr(attach1+endofline()) 
        end
    next

    this:__transactionid__:=0
    this:__isolationlevel__:=ISOL_READ_COMMITTED
    this:__sessionisolationlevel__:=ISOL_READ_COMMITTED
    this:__statementhandles__:={}
    
    this:sqlexec("begin transaction")

    return this


******************************************************************************
static function sqlconnection.version(this)
    return "SQLite version "+_sqlite3_libversion() //string


******************************************************************************
static function sqlconnection.duplicate(this)
    return sqlconnectionNew(this:__coninfo__)


******************************************************************************
static function sqlconnection.sqldisconnect(this)
    this:sqlrollback
    _sqlite3_close(this:__conhandle__)
    this:__conhandle__:=NIL


******************************************************************************
static function sqlconnection.sqlexec(this,stmt,bind)
local err,code,msg

    if( bind!=NIL )
        stmt:=sql2.sqlite3.sqlbind(stmt,bind)
    end

    sql2.sqlite3.sqldebug(stmt)
    
    if( SQLITE_OK!=(code:=_sqlite3_exec(this:__conhandle__,stmt,@msg)) )
        //this:sqlrollback  //végtelen rekurziót okoz

        err:=sqlerrorNew()
        err:operation:="sqlexec"
        err:description:=msg
        err:args:={stmt}
        err:subcode:=code
        break(err)
    end

    return _sqlite3_changes(this:__conhandle__) //affected rows


#ifdef EMLEKEZTETO //* a Postgres automatikus abortjáról
    Hiba esetén a Postgres automatikusan és elkerülhetetlenül
    abortálja a tranzakciót, és a következő commit/rollback utasításig
    semmit sem hajt végre. Ezért jobb rögtön explicite rollbackelni.
    
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
    //tisztázatlan
    return this:__isolationlevel__


******************************************************************************
static function sqlconnection.sqlcommit(this)
    sqlconnection.finalizeall(this)
    this:sqlexec("commit transaction")
    this:sqlexec("begin transaction")
    this:__transactionid__++


******************************************************************************
static function sqlconnection.sqlrollback(this)
    sqlconnection.finalizeall(this)
    this:sqlexec("rollback transaction")
    this:sqlexec("begin transaction")
    this:__transactionid__++


******************************************************************************
static function sqlconnection.finalizeall(this)
local n
    for n:=1 to len(this:__statementhandles__)
        _sqlite3_finalize(this:__statementhandles__[n])
    next

// Az elképzelés, hogy commit/rollback alkalmával minden statementet
// automatikusan lezárunk -> nincs fetch across transaction.
// Az sqlexec-ben belsőleg használt stmt-ke nem érdekesek.
// A prepare-ből kapott stmt-t be kell tenni a listába.
// Ha az alkalmazás azt lezárja, akkor ki kell venni a listából (többszörös lezárás SIGSEGV).
// Ha az alkalmazás nem zárja le, akkor a tranzkció végén magától lezáródik.


******************************************************************************
