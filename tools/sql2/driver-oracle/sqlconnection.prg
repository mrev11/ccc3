
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

#include "oci.ch"
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
    method  driver              {||"sql2.oracle"}
    method  version
    method  duplicate
    method  sqldisconnect
    method  sqlexecx
    method  sqlexec
    method  sqlisolationlevel
    method  sqlcommit
    method  sqlrollback
    method  sqlquerynew         {|this,stmt,bind|sql2.oracle.sqlqueryNew(this,stmt,bind)}
    method  sqlsequencenew      {|this,name|sql2.oracle.sqlsequenceNew(this,name)}
    method  __tableentityclass__{|this|sql2.oracle.tableentityClass()}

******************************************************************************
static function sqlconnection.initialize(this,coninfo)
local usr,psw,dbs

    this:(object)initialize

    if( coninfo==NIL )
        coninfo:=getenv("ORACLE_CONNECT")
    end
    this:__coninfo__:=coninfo
    
    coninfo::=parseconstr
    usr:=coninfo[1]
    dbs:=coninfo[2]
    psw:=coninfo[3]
    
    this:__conhandle__:=sql2.oracle._oci_logon(usr,psw,dbs)
    this:__isolationlevel__:=ISOL_COM
    this:__sessionisolationlevel__:=ISOL_COM
    this:sqlexec("alter session set isolation_level=read committed")
    this:__transactionid__:=0
    this:__statementstoclose__:=array(64)
    return this

******************************************************************************
static function parseconstr(constr) // -> {usr,dbs,psw}

// constr:  user@database/password
// constr:  user/password@database

local x:=constr::strtran("@",",@,")::strtran("/",",/,")::split,n
local usr:="",dbs:="",psw:=""

    for n:=1 to len(x)
        if(x[n]=="@")
            dbs:=x[++n]
        elseif(x[n]=="/")
            psw:=x[++n]
        elseif(n==1)
            usr:=x[n]
        end
    end
    return {usr,dbs,psw}

******************************************************************************
static function sqlconnection.version(this)
    return sql2.oracle._oci_getserverversion(this:__conhandle__)

******************************************************************************
static function sqlconnection.duplicate(this)
    return sqlconnectionNew(this:__coninfo__)

******************************************************************************
static function sqlconnection.sqldisconnect(this)
    sql2.oracle._oci_logoff(this:__conhandle__)
    this:__conhandle__:=NIL
    return NIL

******************************************************************************
static function sqlconnection.sqlexec(this,stmt,bind)
local hstmt, rowcount:=0

    if( bind!=NIL )
        stmt:=sql2.oracle.sqlbind(stmt,bind)
    end

    sql2.oracle.sqldebug(stmt)

    hstmt:=sql2.oracle._oci_preparestatement(this:__conhandle__,stmt) 
    begin
        if( sql2.oracle._oci_stmtattrget(hstmt,OCI_ATTR_STMT_TYPE)==OCI_STMT_SELECT )
            sql2.oracle._oci_executestatement(hstmt,0,OCI_DEFAULT) //select
        else
            sql2.oracle._oci_executestatement(hstmt,1)
        end
        rowcount:=sql2.oracle._oci_stmtattrget(hstmt,OCI_ATTR_ROW_COUNT)
    finally
        sql2.oracle._oci_freestatement(hstmt)
    end

    return rowcount

#ifdef EMLEKEZTETO //automatikus rollback a Postgresben
    Hiba esetén a Postgres automatikusan és elkerülhetetlenül
    abortálja a tranzakciót, és a következő commit/rollback utasításig
    semmit sem hajt végre. Ezért jobb rögtön explicite rollbackelni.
    
    Az Oracle úgy működik, mintha minden utasítás előtt volna
    egy implicit savepoint, és ha az utasítás sikertelen, akkor
    eddig az implicit savepointig rollbackel. A Postgresben
    azonban nincsenek savepointok.
#endif

#ifdef EMLEKEZTETO //lockolás sqlexec-kel
    Van értelme az sqlexec-kel selectet végrehajtani,
    ezzel ugyanis lockolni lehet a sorok egy halmazát:
    con:sqlexec("select ... for update")
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

local stmt,txtlevel
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


    sqlconnection.close_pending_statements(this,"set isolation")
    this:sqlexec("rollback")
    this:__transactionid__++

    
    if( flag )
        //session

        txtlevel:=NIL
        if( 0!=numand(numlevel,ISOL_SER) )
            txtlevel:="SERIALIZABLE"

        elseif( 0!=numand(numlevel,ISOL_REP) ) //not supported
            txtlevel:="SERIALIZABLE"

        elseif( 0!=numand(numlevel,ISOL_COM) )
            txtlevel:="READ COMMITTED"
        else
            //ISOL_RO not supported
            //ISOL_RW default
        end
        if( txtlevel!=NIL  )
            stmt:="alter session set isolation_level="+txtlevel
            this:sqlexec(stmt)
        end

    else
        //transaction

        txtlevel:=NIL
        if( 0!=numand(numlevel,ISOL_RO) )
            txtlevel:="READ ONLY"
        elseif( 0!=numand(numlevel,ISOL_RW) )
            txtlevel:="READ WRITE"
        end

        if( txtlevel!=NIL )
            stmt:="set transaction "+txtlevel
            this:sqlexec(stmt)

            //READ ONLY => transaction read stability
            //READ WRITE => statement read stability
            //ezeknek adunk elsőbbséget

        else
            //az Oracle 'set transaction' csak egy attribútomot fogad el
            //csakis a tranzakció első utasítása lehet 'set transaction'
            //=> egy tranzakcióban csak egy attribútumot lehet beállítani

            txtlevel:=NIL
            if( 0!=numand(numlevel,ISOL_SER) )
                txtlevel:="SERIALIZABLE"

            elseif( 0!=numand(numlevel,ISOL_REP) )
                txtlevel:="SERIALIZABLE"

            elseif( 0!=numand(numlevel,ISOL_COM) )
                txtlevel:="READ COMMITTED"
            end
            if( txtlevel!=NIL )
                stmt:="set transaction isolation level "+txtlevel
                this:sqlexec(stmt)
            end
        end
    end

    this:__isolationlevel__:=numlevel
    if( flag )
        this:__sessionisolationlevel__:=numlevel
    end

    return previous_level


******************************************************************************
static function sqlconnection.sqlcommit(this)
    sqlconnection.close_pending_statements(this,"commit transaction")
    this:sqlexec("commit")
    this:__transactionid__++
    this:__isolationlevel__:=this:__sessionisolationlevel__
    return NIL

******************************************************************************
static function sqlconnection.sqlrollback(this)
    sqlconnection.close_pending_statements(this,"rollback transaction")
    this:sqlexec("rollback")
    this:__transactionid__++
    this:__isolationlevel__:=this:__sessionisolationlevel__
    return NIL

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

