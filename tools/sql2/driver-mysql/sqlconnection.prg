
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

namespace sql2.mysql

#include "my.ch"
#include "sql.ch"

******************************************************************************
class sqlconnection(object)
    method  initialize
    attrib  __conhandle__
    attrib  __coninfo__
    attrib  __transactionid__
    attrib  __isolationlevel__
    attrib  __sessionisolationlevel__
    method  driver              {||"sql2.mysql"}
    method  version
    method  duplicate
    method  sqldisconnect
    method  sqlexecx
    method  sqlexec
    method  sqlisolationlevel
    method  sqlcommit
    method  sqlrollback
    method  sqlquerynew         {|this,stmt,bind|sql2.mysql.sqlqueryNew(this,stmt,bind)}
    method  sqlsequencenew      {|this,name|sql2.mysql.sqlsequenceNew(this,name)}
    method  __tableentityclass__{|this|sql2.mysql.tableentityClass()}

******************************************************************************
static function sqlconnection.initialize(this,coninfo)
    this:(object)initialize

    if( coninfo==NIL )
        coninfo:=getenv("MYSQL_CONNECT")
    end

    this:__coninfo__:=coninfo

    //        1    2    3      4  5    6    7    
    //coninfo=host:user:passwd:db:port:usck:cflag
    //példa ":konto:konto:konto" (default host=localhost, default port ...)

    coninfo::=split(":")::asize(7)
    if( coninfo[5]::empty )
        coninfo[5]:=0
    end
    if( coninfo[7]::empty )
        coninfo[7]:=0
    end
    coninfo[7]::=numor(2) //CLIENT_FOUND_ROWS (update rowcount error!)

    //a többi paraméter defaultja ''
    
    this:__conhandle__:=sql2.mysql._my_connect(coninfo[1],coninfo[2],coninfo[3],coninfo[4],coninfo[5],coninfo[6],coninfo[7])

    sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"set session transaction isolation level read committed"))
    sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"set autocommit=0"))
    sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"start transaction"))

    this:__transactionid__:=0
    this:__isolationlevel__:=ISOL_READ_COMMITTED
    this:__sessionisolationlevel__:=ISOL_READ_COMMITTED

    return this

******************************************************************************
static function sqlconnection.version(this)
local v:=sql2.mysql._my_get_server_info(this:__conhandle__)
    return v

******************************************************************************
static function sqlconnection.duplicate(this)
    return sqlconnectionNew(this:__coninfo__)

******************************************************************************
static function sqlconnection.sqldisconnect(this)
    sql2.mysql._my_close(this:__conhandle__)
    this:__conhandle__:=NIL

******************************************************************************
static function sqlconnection.sqlexec(this,stmt,bind)

local err
local stmidx,fldcnt
local rowcount:=0

    if( bind!=NIL )
        stmt:=sql2.mysql.sqlbind(stmt,bind)
    end

    sql2.mysql.sqldebug(stmt)

    stmidx:=sql2.mysql._my_real_query(this:__conhandle__,stmt)
    
    if( stmidx==NIL )
        //error, stmidx nincs tárolva

        err:=sql2.mysql.sqlerrorCreate(this:__conhandle__)
        err:operation:="sqlexec"
        err:args:={stmt}
        sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"rollback"))
        sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"start transaction"))
        //az itteni rollback nincs benne az sqldebug listában
        this:__transactionid__++
        break(err)
        return 0
    end
    
    fldcnt:=sql2.mysql._my_field_count(this:__conhandle__)
    if( fldcnt==0 )
        //insert, update, delete, ...
        rowcount:=sql2.mysql._my_affected_rows(this:__conhandle__)
    else
        //select
        rowcount:=0 //itt nem foglalkozunk selectekkel
    end
    sql2.mysql._my_free_result(stmidx)
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

local stmt,txtlevel
local previous_level

    if( flag )
        previous_level:=this:__sessionisolationlevel__
    else
        previous_level:=this:__isolationlevel__
    end

    if( numlevel==NIL )
        //csak lekérdezés
        return previous_level

    elseif( numlevel==ISOL_READ_COMMITTED )
        txtlevel:="READ COMMITTED"

    elseif( numlevel==ISOL_SERIALIZABLE )
        txtlevel:="SERIALIZABLE"

    else
        txtlevel:="UNSUPPORTED_ISOLATION_LEVEL"
    end
    
    
    if( !flag )
        //egy tranzakcióra
        stmt:="set transaction isolation level "+txtlevel
    else
        //a session-re
        stmt:="set session transaction isolation level "+txtlevel
    end

    sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"rollback"))
    this:sqlexec(stmt)
    sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"start transaction"))


    this:__transactionid__++

    this:__isolationlevel__:=numlevel
    if( flag )
        this:__sessionisolationlevel__:=numlevel
    end

    return previous_level

******************************************************************************
static function sqlconnection.sqlcommit(this)
    this:sqlexec("commit")
    sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"start transaction"))
    this:__transactionid__++
    this:__isolationlevel__:=this:__sessionisolationlevel__

******************************************************************************
static function sqlconnection.sqlrollback(this)
    this:sqlexec("rollback")
    sql2.mysql._my_free_result(sql2.mysql._my_real_query(this:__conhandle__,"start transaction"))
    this:__transactionid__++
    this:__isolationlevel__:=this:__sessionisolationlevel__

******************************************************************************
