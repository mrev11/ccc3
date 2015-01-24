
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

 
//--------------------------------------------------------------------------
#include <stdio.h>
#include <error.ch>
#include <string.h>
#include <db2.h>

#include <cccapi.h>

DEFINE_METHOD(operation);
DEFINE_METHOD(description);
DEFINE_METHOD(subsystem);
DEFINE_METHOD(gencode);
DEFINE_METHOD(subcode);
DEFINE_METHOD(severity);

#define MAX_CONNECTION  8
#define MAX_STATEMENT  64

extern void _clp_sqlerrornew(int);
extern void _clp_sqllockerrornew(int);
extern void _clp_sqldeadlockerrornew(int);
extern void _clp_sqlserialerrornew(int);
extern void _clp_sqlconnecterrornew(int);


namespace _nsp_sql2{
namespace _nsp_db2{



static struct{
    int       active;
    SQLHDBC   conhnd;
} db2_connection[MAX_CONNECTION];
MUTEX_CREATE(mutex_con);

static struct{
    int        conidx;
    SQLHSTMT   stmhnd;
    SQLRETURN  retcode;
} db2_statement[MAX_STATEMENT];
MUTEX_CREATE(mutex_stm);

MUTEX_CREATE(mutex_env);

//----------------------------------------------------------------------------
static void getdiag(SQLSMALLINT htype, SQLHANDLE hndl)
{
    SQLCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
    SQLINTEGER sqlcode=0;
    SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
    SQLSMALLINT length;

    if( SQLGetDiagRec(   htype,
                         hndl,
                         1,
                         sqlstate,
                         &sqlcode,
                         message,
                         SQL_MAX_MESSAGE_LENGTH + 1,
                         &length) == SQL_SUCCESS )
                         
    {
        dup();
               stringnb("<");
               stringnb((char*)sqlstate);add();
               stringnb(">");add();
               stringnb((char*)message);add();
                               _o_method_description.eval(2);pop();  
 
        dup(); number(sqlcode);_o_method_subcode.eval(2);pop();  

        dup(); string(CHRLIT("SQL2.DB2"));_o_method_subsystem.eval(2);pop(); 
        dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
        dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
    }
}

static void pusherror()
//
//  stack:  --- errobj
//
{
    _clp_sqlerrornew(0);
    dup(); string(CHRLIT("SQL2.DB2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

static void pushconnecterror()
//
//  stack:  --- errobj
//
{
    _clp_sqlconnecterrornew(0);
    dup(); string(CHRLIT("SQL2.DB2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}


//----------------------------------------------------------------------------
static int db2_init_handles()
{
    MUTEX_LOCK(mutex_con);
    MUTEX_LOCK(mutex_stm);
    
    static int initialized=0;
    
    if( !initialized  )
    {
        int i;
        for( i=0; i<MAX_CONNECTION; i++ )
        {
            db2_connection[i].active=0;
        }

        for( i=0; i<MAX_STATEMENT; i++ )
        {
            db2_statement[i].conidx=-1;
        }

        initialized=1;
    }

    MUTEX_UNLOCK(mutex_con);
    MUTEX_UNLOCK(mutex_stm);
    return 1;
}

static int init=db2_init_handles();

//----------------------------------------------------------------------------
static SQLHANDLE db2_global_henv()
{
    static SQLHANDLE global_henv=0; // global environment handle

    MUTEX_LOCK(mutex_env);
    if(global_henv==0)
    {
        SQLRETURN rc=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&global_henv);
        if(rc!=SQL_SUCCESS)
        {
            pusherror();
            dup(); string(CHRLIT("could not allocate environment handle"));_o_method_description.eval(2);pop(); 
            _clp_break(1);pop();
        }
    }
    MUTEX_UNLOCK(mutex_env);
    return global_henv;
}

//----------------------------------------------------------------------------
static int verify_conidx(int x)
{
    if( (x<0) || (MAX_CONNECTION<=x) || !db2_connection[x].active )
    {
        pusherror();
        dup(); string(CHRLIT("invalid connection handle"));_o_method_description.eval(2);pop(); 
        _clp_break(1);pop();
    }
    return x;
}

//----------------------------------------------------------------------------
static int verify_stmidx(int x)
{
    if( (x<0) || (MAX_STATEMENT<=x) || (db2_statement[x].conidx==-1) )
    {
        pusherror();
        dup(); string(CHRLIT("invalid statement handle"));_o_method_description.eval(2);pop(); 
        _clp_break(1);pop();
    }
    return x;
}

//----------------------------------------------------------------------------
static int get_statement_handle(int conidx)  // üres stmidx, vagy error
{
    MUTEX_LOCK(mutex_stm);
    int i;
    for( i=0; i<MAX_STATEMENT; i++ )
    {
        if( db2_statement[i].conidx==-1 )
        {
            SQLHANDLE hdbc=db2_connection[conidx].conhnd;
            SQLRETURN rc=SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &db2_statement[i].stmhnd);
            if( rc!=SQL_SUCCESS )
            {
                pusherror();
                dup();string(CHRLIT("could not allocate statement handle"));_o_method_description.eval(2);pop();
                _clp_break(1);pop();
            }
            db2_statement[i].conidx=conidx; 
            MUTEX_UNLOCK(mutex_stm);
            return i;
        }
    }
    MUTEX_UNLOCK(mutex_stm);

    //ERROR
   
    pusherror();
    dup();string(CHRLIT("no more statement handle"));_o_method_description.eval(2);pop();
    _clp_break(1);pop();

    return -1;
}

//----------------------------------------------------------------------------
static void drop_statement_handle(int stmidx)
{
    MUTEX_LOCK(mutex_stm);
    if( db2_statement[stmidx].conidx!=-1 )
    {
        SQLFreeHandle(SQL_HANDLE_STMT,db2_statement[stmidx].stmhnd);
        db2_statement[stmidx].conidx=-1;
    }
    MUTEX_UNLOCK(mutex_stm);
}

//----------------------------------------------------------------------------
static int get_connection_handle() // üres conidx, vagy error
{
    MUTEX_LOCK(mutex_con);
    int i;
    for( i=0; i<MAX_CONNECTION; i++ )
    {
        if( 0==db2_connection[i].active )
        {
            db2_connection[i].active=1;
            SQLRETURN rc=SQLAllocHandle(SQL_HANDLE_DBC, db2_global_henv(), &db2_connection[i].conhnd);
            if( rc!=SQL_SUCCESS )
            {
                pusherror();
                dup();string(CHRLIT("could not allocate connection handle"));_o_method_description.eval(2);pop();
                _clp_break(1);pop();
            }
            MUTEX_UNLOCK(mutex_con);
            return i;
        }
    }
    MUTEX_UNLOCK(mutex_con);

    //ERROR
    pusherror();
    dup();string(CHRLIT("no more connection handle"));_o_method_description.eval(2);pop();
    _clp_break(1);pop();
 
    return -1;
}
 
//----------------------------------------------------------------------------
static void drop_connection_handle(int conidx)
{
    MUTEX_LOCK(mutex_con);
    if( db2_connection[conidx].active )
    {
        int i;
        for(i=0; i<MAX_STATEMENT; i++)
        {
            if( db2_statement[i].conidx==conidx )
            {
                drop_statement_handle(i); 
            }
        }
        SQLHANDLE hdbc=db2_connection[conidx].conhnd;
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        db2_connection[conidx].active=0;
    }
    MUTEX_UNLOCK(mutex_con);
}


//--------------------------------------------------------------------------
// public interface
//--------------------------------------------------------------------------
void _clp__db2_connect(int argno)  //  --> conidx/NIL
{
    CCC_PROLOG("_db2_connect",3);
    int conidx=get_connection_handle();
    
    const char *dbs=ISNIL(1)?"":_parcb(1);
    const char *usr=ISNIL(2)?"":_parcb(2);
    const char *psw=ISNIL(3)?"":_parcb(3);

    SQLHANDLE hdbc=db2_connection[conidx].conhnd;
    SQLRETURN retcode=SQLConnect( hdbc, 
                                  (SQLCHAR*)dbs, SQL_NTS, 
                                  (SQLCHAR*)usr, SQL_NTS, 
                                  (SQLCHAR*)psw, SQL_NTS);
                                    
    if( retcode==SQL_SUCCESS )
    {
        _retni(conidx);
    }
    else
    {
        pushconnecterror();
        getdiag(SQL_HANDLE_DBC,hdbc);
        drop_connection_handle(conidx);
        _clp_break(1);pop();
        _ret();
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__db2_disconnect(int argno)
{
    CCC_PROLOG("_db2_disconnect",1);
    int conidx=verify_conidx(_parni(1));
    SQLHANDLE hdbc=db2_connection[conidx].conhnd;
    drop_connection_handle(conidx);
    SQLRETURN rc=SQLDisconnect(hdbc);
    _retni(rc);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__db2_closestatement(int argno)
{
    CCC_PROLOG("_db2_closestatement",1);
    int stmidx=verify_stmidx(_parni(1));
    drop_statement_handle(stmidx);
    _ret();
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_execdirect(int argno) // conidx,stmt --> stmidx
{
    CCC_PROLOG("_db2_execdirect",2);
    int conidx=verify_conidx(_parni(1));
    //SQLHANDLE hdbc=db2_connection[conidx].conhnd;
    char *query=_parcb(2);
    int length=_parblen(2);
    int stmidx=get_statement_handle(conidx);
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    SQLRETURN rc=SQLExecDirect(hstm,(SQLCHAR*)query,length);
    db2_statement[stmidx].retcode=rc;
    _retni(stmidx);
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_retcode(int argno) // stmidx --> retcode
{
    CCC_PROLOG("_db2_retcode",1);
    int stmidx=verify_stmidx(_parni(1));
    _retni(db2_statement[stmidx].retcode);
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_getdiagrec(int argno) // errobj,stmidx --> errobj
{
    CCC_PROLOG("_db2_getdiagrec",2);
    int stmidx=verify_stmidx(_parni(2));
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    
    push(base); //errobj
    getdiag(SQL_HANDLE_STMT,hstm);
    _rettop();
    
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__db2_fetch(int argno) // stmidx --> retcode
{
    CCC_PROLOG("_db2_fetch",1);
    int stmidx=verify_stmidx(_parni(1));
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    SQLRETURN rc=SQLFetch(hstm);
    db2_statement[stmidx].retcode=rc;
    _retni(rc);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__db2_getdata(int argno) // stmidx,colnum,ctype --> adat
{
    CCC_PROLOG("_db2_getdata",3);
    int stmidx=verify_stmidx(_parni(1));
    int colnum=_parni(2);
    int ctype=ISNIL(3)?SQL_CHAR:_parni(3);
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    char buffer[1024];
    SQLINTEGER lenind; //outlen/indicator

    SQLRETURN rc=SQLGetData(hstm,
                            colnum,
                            ctype,
                            buffer,
                            (int)sizeof(buffer),
                            &lenind);
    db2_statement[stmidx].retcode=rc;

    //printf("\n>>> %d colnum=%d ctype=%d lenind=%3d ",rc,colnum,ctype,lenind );

    if( rc==SQL_SUCCESS  )
    {
        if( lenind>=0 )
        {
            _retblen(buffer,lenind);
        }
        else //if(lenind==SQL_NULL_DATA )
        {
            _ret();
        }
    }
    else if( rc==SQL_SUCCESS_WITH_INFO && lenind>=(int)sizeof(buffer) )
    {
        binaryl(lenind);
        char *bufext=BINARYPTR0(TOP());
        int lenext;

        int chrflg=(ctype==SQL_CHAR?1:0); //van-e záró 0 byte?
        //ha karakteres a kimenet, akkor egy záró 0-t is kiír
        //ha bináris a kimenet, akkor nem ír záró 0-t
        
        //most csak a fennmaradó részt olvassa 
        memmove(bufext,buffer,sizeof(buffer));
        rc=SQLGetData(hstm,
                            colnum,
                            ctype,
                            bufext+(int)sizeof(buffer)-chrflg,
                            lenind-(int)sizeof(buffer)+chrflg+1,
                            &lenext);
        db2_statement[stmidx].retcode=rc;

        //printf(" >>> rc=%d lenext=%3d ",rc,lenext );

        if( rc==SQL_SUCCESS  )
        {
            if( lenind>=0 )
            {
                _retblen(bufext,lenind);
            }
            else //if(lenind==SQL_NULL_DATA )
            {
                _ret();
            }
        }

        //printf(">>[%s]",bufext);
    }
    else
    {
        //error
        pusherror();
        getdiag(SQL_HANDLE_STMT,hstm);
        _clp_break(1);pop();
        _ret();
    }

    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_numresultcols(int argno) // stmidx --> numcols
{
    CCC_PROLOG("_db2_numresultcols",1);
    int stmidx=verify_stmidx(_parni(1));
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    SQLSMALLINT numcols=0;
    SQLRETURN rc=SQLNumResultCols(hstm,&numcols);
    db2_statement[stmidx].retcode=rc;
    _retni(numcols);
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_rowcount(int argno) // stmidx --> affected rows
{
    CCC_PROLOG("_db2_rowcount",1);
    int stmidx=verify_stmidx(_parni(1));
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    SQLINTEGER rowcount=0;
    SQLRETURN rc=SQLRowCount(hstm,&rowcount);
    db2_statement[stmidx].retcode=rc;
    _retni(rowcount);
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_describecol(int argno) // stmidx,colnum --> {name,type,size,dec,null}/NIL
{
    CCC_PROLOG("_db2_rdescribecol",2);
    int stmidx=verify_stmidx(_parni(1));
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    SQLSMALLINT colnum=_parni(2);

    SQLCHAR colname[256];
    SQLSMALLINT namelength=0;
    SQLSMALLINT datatype=0;
    SQLUINTEGER columnsize=0;
    SQLSMALLINT decdigits=0;
    SQLSMALLINT nullable=0;
    SQLRETURN rc=SQLDescribeCol(hstm,colnum,colname,256,&namelength,&datatype,&columnsize,&decdigits,&nullable);
    db2_statement[stmidx].retcode=rc;
    
    if( rc==SQL_SUCCESS )
    {
        stringsb((char*)colname,namelength);
        number(datatype);
        number(columnsize);
        number(decdigits);
        logical(nullable);
        array(5);
        _rettop();
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_colname(int argno) // stmidx,colnum --> colname/NIL
{
    CCC_PROLOG("_db2_colname",2);
    int stmidx=verify_stmidx(_parni(1));
    SQLHANDLE hstm=db2_statement[stmidx].stmhnd;
    SQLSMALLINT colnum=_parni(2);

    SQLCHAR colname[256];
    SQLSMALLINT namelength=0;
    SQLSMALLINT datatype=0;
    SQLUINTEGER columnsize=0;
    SQLSMALLINT decdigits=0;
    SQLSMALLINT nullable=0;
    SQLRETURN rc=SQLDescribeCol(hstm,colnum,colname,256,&namelength,&datatype,&columnsize,&decdigits,&nullable);
    db2_statement[stmidx].retcode=rc;
    
    if( rc==SQL_SUCCESS )
    {
        _retcblen((char*)colname,namelength);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_endtran(int argno) // conidx, commit --> rc
{
    CCC_PROLOG("_db2_endtran",2);
    int conidx=verify_conidx(_parni(1));
    SQLHANDLE hdbc=db2_connection[conidx].conhnd;
    SQLSMALLINT commit=_parni(2); //SQL_COMMIT or SQL_ROLLBACK
    SQLRETURN rc=SQLEndTran(SQL_HANDLE_DBC,hdbc,commit);
    if(rc!=SQL_SUCCESS)
    {
        pusherror();
        getdiag(SQL_HANDLE_DBC,hdbc);
        _clp_break(1);pop();
    }
    _retni(rc);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__db2_setautocommit(int argno) // conidx, flag --> rc
{
    CCC_PROLOG("_db2_setautocommit",2);
    int conidx=verify_conidx(_parni(1));
    SQLHANDLE hdbc=db2_connection[conidx].conhnd;
    int flag=_parl(2);
    SQLRETURN rc=SQLSetConnectAttr(hdbc,SQL_ATTR_AUTOCOMMIT,(void*)(flag?1L:0L),SQL_NTS); //hihetetlen baromság
    if(rc!=SQL_SUCCESS)
    {
        pusherror();
        getdiag(SQL_HANDLE_DBC,hdbc);
        _clp_break(1);pop();
    }
    _retni(rc);
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__db2_setisolation(int argno) // conidx, level --> rc
{
    CCC_PROLOG("_db2_setisolation",2);
    int conidx=verify_conidx(_parni(1));
    SQLHANDLE hdbc=db2_connection[conidx].conhnd;
    long level=_parni(2); //0: read committed, 1: serializable
    
    if(level==0)
    {
        level=SQL_TXN_READ_COMMITTED;
    }
    else
    {
        //level=SQL_TXN_REPEATABLE_READ;
        level=SQL_TXN_SERIALIZABLE;  //nincs különbség?
    }

    SQLRETURN rc=SQLSetConnectAttr(hdbc,SQL_ATTR_TXN_ISOLATION,(void*)level,SQL_NTS);
    if(rc!=SQL_SUCCESS)
    {
        pusherror();
        getdiag(SQL_HANDLE_DBC,hdbc);
        _clp_break(1);pop();
    }
    _retni(rc);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__db2_escapestring(int argno) //az "'" és "\" karaktereket duplázza
{
    CCC_PROLOG("_db2_escapestring",1);
    char *from=_parcb(1);
    int fleng=_parblen(1);
    char *to=binaryl(2*fleng+1);

    int tleng=0;
    for(int i=0; i<fleng; i++)
    {
        int c=from[i];
        if( c=='\\' || c=='\'')
        {
            to[tleng++]=c;
        }
        to[tleng++]=c;
    }
    
    _retcblen(to,tleng);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------

}} //namespace

