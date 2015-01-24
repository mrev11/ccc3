
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

    attrib  __statementstoclose__
    method  __addstatementtoclose__
    method  __clearstatement__

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
static function sqlconnection.initialize(this,coninfo,cflags:="rwc")  //coninfo egy filename

local err,code,errmsg
local attach:="attach database '$DBFILE' as $ALIAS"
local attach1,dbfali,n
local flags

    this:(object)initialize

    if( coninfo==NIL )
        coninfo:=getenv("SQLITE3_CONNECT")
    end
    this:__coninfo__:=coninfo

    //coninfo: 'dbfile1:dbfile2=alias2:dbfile3=alias3...'
    coninfo::=split(pathsep()) //{dbfile1, dbfile2=alias2, ... }


    // A cflags paraméterrel nincs értelme játszani:
    // Egyedül az SQLITE_OPEN_READONLY-nak lehetne értelme, 
    // tapasztalat szerint azonban nem javítja a konkurencia kezelést,
    // ráadásul readonlyban nem működik a WAL (Write Ahead Logging).
    
    // default journaling mode: rollback journal (delete)
    // ehelyett beállítjuk a WAL módot: "PRAGMA journal_mode=WAL;"
    //
    // Előnye:)
    //    az író és olvasó tranzakciók nem akadályozzák egymást!
    //    (csak az író/író tranzakciók ütköznek)
    //    gyorsabb
    //
    // Hátránya:(
    //    a több adatbázisra kiterjedő tranzakciók nem atomiak
    //    db-shm, db-wal fájlok megjelenése (többé nem egyfájlos a formátum)
    //    csak lokális fájlrendszeren lehet az adatbázis
    //    kisebb tranzakciókat bír el
    //
    // Egyelőre nem világos, hogy ez fájlformátum,  vagy csak 
    // hozzáférési módszer kérdése, ami alkalmanként változhat.
    // Úgy  tűnik a fájlformátumban van benne.
    // Ha egyszer be volt állítva a WAL, akkor úgy marad.
    
    
    flags:=0
    if( "ro"$cflags )
        flags::=numor(SQLITE_OPEN_READONLY)

    elseif( "rw"$cflags )
        flags::=numor(SQLITE_OPEN_READWRITE)
        if( "c"$cflags )
            flags::=numor(SQLITE_OPEN_CREATE)
        end
    end

    //flags::=numor(SQLITE_OPEN_NOMUTEX)
    //flags::=numor(SQLITE_OPEN_FULLMUTEX)
    //flags::=numor(SQLITE_OPEN_PRIVATECACHE)
    //flags::=numor(SQLITE_OPEN_SHAREDCACHE)  //nem enged többszörösen attachelni

    this:__conhandle__:=_sqlite3_open2(coninfo[1],flags,@code)

    if( this:__conhandle__==NIL )
        err:=sqlconnecterrorNew()
        err:operation:="sqlconnection.initialize"
        err:args:={this:__coninfo__}
        err:subcode:=code
        //err:description:=_sqlite3_errmsg(this:__conhandle__)
        break(err)
    else
        outerr("attach to "+coninfo[1]+endofline()) 
    end

    this:sqlexec("PRAGMA journal_mode=WAL")  //WAL 

    
    for n:=2 to len(coninfo)
        attach1:=attach
        dbfali:=coninfo[n]::split("=")
        attach1::=strtran("$DBFILE",dbfali[1])
        attach1::=strtran("$ALIAS",dbfali[2])
        set_journal_mode_to_wal(dbfali[1])
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
    this:__statementstoclose__:=array(64)
    
    this:sqlexec("begin transaction")

    return this


static function set_journal_mode_to_wal(dbfile)
local db:=_sqlite3_open(dbfile),msg
    if(db!=NIL)
        _sqlite3_exec(db,"PRAGMA journal_mode=WAL;",@msg)
        _sqlite3_close(db)
        if(msg!=NIL)
            outerr(msg)
        end
    end


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
        
        if( code==SQLITE_BUSY )
            err:=sqlserialerrorNew()
        elseif( code==SQLITE_LOCKED )
            err:=sqllockerrorNew()
        else
            err:=sqlerrorNew()
        end
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
    sqlconnection.close_pending_statements(this)
    this:sqlexec("commit transaction")
    this:sqlexec("begin transaction")
    this:__transactionid__++


******************************************************************************
static function sqlconnection.sqlrollback(this)
    sqlconnection.close_pending_statements(this)
    this:sqlexec("rollback transaction")
    this:sqlexec("begin transaction")
    this:__transactionid__++


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
static function sqlconnection.close_pending_statements(this)
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
        err:description:="cannot commit/rollback transaction - SQL statements in progress"
        break(err)
    end

******************************************************************************
