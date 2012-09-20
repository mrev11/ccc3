
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

//CCC-PGSQL interfész
//Vermes M., 2004. augusztus

//_pq_connectdb("info")            ->  conidx
//_pq_setdblogin(h,p,o,t,d,u,w)    ->  conidx
//_pq_finish(conn)                 ->  NIL
//_pq_status(conn)                 ->  code
//_pq_errormessage(conn)           ->  "errmsg"
//_pq_trace(conn,"tfile")          ->  NIL
//_pq_untrace(conn)                ->  NIL
//
//_pq_exec(conn,"query")           ->  stmidx/NIL
//_pq_clear(conn)                  ->  NIL
//_pq_resultstatus(result)         ->  code
//_pq_resulterrormessage(result)   ->  "errmsg"
//_pq_resulterrorfield(result,fld) ->  "field"
//_pq_resstatus(code)              ->  "status"
//_pq_cmdstatus(result)            ->  "cmd" (pl. "SELECT")
//_pq_cmdtuples(result)            ->  "affected"
//_pq_binarytuples(result)         ->  t/f
//
//_pq_nfields(result)              ->  nfields
//_pq_fname(result,x)              ->  "fname"
//_pq_ftype(result,x)              ->  typecode
//_pq_fsize(result,x)              ->  size
//_pq_fmod(result,x)               ->  mode
//
//_pq_ntuples(result)              ->  ntuples
//_pq_oidvalue(result)             ->  "oid" 
//_pq_getisnull(result,r,c)        ->  t/f
//_pq_getlength(result,r,c)        ->  length
//_pq_getvalue0(result,r,c)        ->  a"value"
//_pq_getvalue(result,r,c)         ->  {a"value"}
//
//_pq_escapebytea(string)          ->  esc_string
//_pq_unescapebytea(string)        ->  unesc_string
//_pq_escapestring(string)         ->  esc_string
 
//--------------------------------------------------------------------------
#include <stdio.h>
#include <error.ch>
#include <string.h>
#include <cccapi.h>

//#include <pgsql/libpq-fe.h>
//#include <postgresql/libpq-fe.h>
#include <pq.h>

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
namespace _nsp_postgres{


static struct{
    int       active;
    PGconn    *conhnd;
} postgres_connection[MAX_CONNECTION];
MUTEX_CREATE(mutex_con);

static struct{
    int        conidx;
    PGresult  *result;
} postgres_result[MAX_STATEMENT];
MUTEX_CREATE(mutex_stm);


//----------------------------------------------------------------------------
static int postgres_init()
{
    MUTEX_LOCK(mutex_con);
    MUTEX_LOCK(mutex_stm);
    
    static int initialized=0;
    
    if( !initialized  )
    {
        int i;
        for( i=0; i<MAX_CONNECTION; i++ )
        {
            postgres_connection[i].active=0;
        }

        for( i=0; i<MAX_STATEMENT; i++ )
        {
            postgres_result[i].conidx=-1;
        }

        initialized=1;
    }

    MUTEX_UNLOCK(mutex_con);
    MUTEX_UNLOCK(mutex_stm);
    return 1;
}

static int init=postgres_init();


//----------------------------------------------------------------------------
static void pusherror()
//
//  stack:  --- errobj
//
{
    _clp_sqlerrornew(0);
    dup(); string(CHRLIT("PGSQL2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

static void pushconnecterror()
//
//  stack:  --- errobj
//
{
    _clp_sqlconnecterrornew(0);
    dup(); string(CHRLIT("PGSQL2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

//----------------------------------------------------------------------------
static int verify_conidx(int x)
{
    if( (x<0) || (MAX_CONNECTION<=x) || !postgres_connection[x].active )
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
    if( (x<0) || (MAX_STATEMENT<=x) || (postgres_result[x].conidx==-1) )
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
        if( postgres_result[i].conidx==-1 )
        {
            postgres_result[i].conidx=conidx; 
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
    if( postgres_result[stmidx].conidx!=-1 )
    {
        PQclear(postgres_result[stmidx].result);
        postgres_result[stmidx].conidx=-1;
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
        if( 0==postgres_connection[i].active )
        {
            postgres_connection[i].active=1;
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
    if( postgres_connection[conidx].active )
    {
        int i;
        for(i=0; i<MAX_STATEMENT; i++)
        {
            if( postgres_result[i].conidx==conidx )
            {
                drop_statement_handle(i); 
            }
        }

        PQfinish(postgres_connection[conidx].conhnd);
        postgres_connection[conidx].active=0;
    }
    MUTEX_UNLOCK(mutex_con);
}


//--------------------------------------------------------------------------
// public interface
//--------------------------------------------------------------------------
void _clp__pq_connectdb(int argno)  // "info" --> conidx
{
    CCC_PROLOG("_pq_connectdb",1);
    const char *p=ISNIL(1)?"":_parcb(1);
    PGconn *conhnd=PQconnectdb(p);
    int status=PQstatus(conhnd);

    if( status==CONNECTION_OK )
    {
        int conidx=get_connection_handle();
        postgres_connection[conidx].conhnd=conhnd;
        _retni(conidx);
    }
    else
    {
        pushconnecterror();
        char *errmsg=PQerrorMessage(conhnd);
        dup();stringnb(errmsg);_o_method_description.eval(2);pop();
        dup();number(status);_o_method_subcode.eval(2);pop();
        _clp_break(1);pop();
        _ret();
    }

    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_setdblogin(int argno) //host,...dbase,user,passw,... --> conidx
{
    CCC_PROLOG("_pq_setdblogin",7);
    char *host  = ISNIL(1)?0:_parcb(1);
    char *port  = ISNIL(2)?0:_parcb(2);
    char *opt   = ISNIL(3)?0:_parcb(3);
    char *tty   = ISNIL(4)?0:_parcb(4);
    char *db    = ISNIL(5)?0:_parcb(5);
    char *user  = ISNIL(6)?0:_parcb(6);
    char *passw = ISNIL(7)?0:_parcb(7);
    PGconn *conhnd=PQsetdbLogin(host,port,opt,tty,db,user,passw);
    int status=PQstatus(conhnd);

    if( status==CONNECTION_OK )
    {
        int conidx=get_connection_handle();
        postgres_connection[conidx].conhnd=conhnd;
        _retni(conidx);
    }
    else
    {
        pushconnecterror();
        char *errmsg=PQerrorMessage(conhnd);
        dup();stringnb(errmsg);_o_method_description.eval(2);pop();
        dup();number(status);_o_method_subcode.eval(2);pop();
        _clp_break(1);pop();
        _retni(-1);
    }

    CCC_EPILOG();
}    
 
//--------------------------------------------------------------------------
void _clp__pq_finish(int argno)  // conidx/NIL --> NIL 
{
    CCC_PROLOG("_pq_finish",1);
    if( !ISNIL(1) )
    {
        int conidx=verify_conidx(_parni(1));
        drop_connection_handle(conidx);
    }
    else
    {
        int i;
        for(i=0; i<MAX_CONNECTION; i++)
        {
            drop_connection_handle(i);
        }
    }
    _ret();
    CCC_EPILOG();
}    
 
//--------------------------------------------------------------------------
void _clp__pq_status(int argno) // conidx --> conn_status
{
    CCC_PROLOG("_pq_status",1);
    int conidx=verify_conidx(ISNIL(1)?0:_parni(1));
    _retni( PQstatus(postgres_connection[conidx].conhnd) );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_errormessage(int argno) // conidx --> conn_errmsg
{
    CCC_PROLOG("_pq_errormessage",1);
    int conidx=verify_conidx(ISNIL(1)?0:_parni(1));
    char *msg=PQerrorMessage(postgres_connection[conidx].conhnd);
    _retcb( msg?msg:"" );
    CCC_EPILOG();
}    
 
//--------------------------------------------------------------------------
void _clp__pq_trace(int argno)  // conidx,logfile --> NIL
{
    CCC_PROLOG("_pq_trace",2);
    int conidx=verify_conidx(ISNIL(1)?0:_parni(1));
    char *tfile=_parcb(2);
    PQtrace(postgres_connection[conidx].conhnd,fopen(tfile,"w"));
    _ret();
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_untrace(int argno) // conidx --> NIL
{
    CCC_PROLOG("_pq_untrace",1);
    int conidx=verify_conidx(ISNIL(1)?0:_parni(1));
    PQuntrace(postgres_connection[conidx].conhnd);
    _ret();
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_exec(int argno) // conidx,stmt --> stmidx
{
    CCC_PROLOG("_pq_exec",2);
    int conidx=verify_conidx(ISNIL(1)?0:_parni(1));
    char *query=_parcb(2);
    PGresult *result=PQexec(postgres_connection[conidx].conhnd,query);

    #ifdef DEBUG
        int status=PQresultStatus(result);
        char *resstatus=PQresStatus((enum ExecStatusType)status);
        char *cmdstatus=PQcmdStatus(result);
        int ntuples=PQntuples(result);
        char *errmsg=PQresultErrorMessage(result);
        //printf("\n%s",query);
        printf("\nexec %d, %s, %s, %d, %s",
                       status,
                       resstatus,
                       cmdstatus,
                       ntuples,
                       errmsg);
        fflush(0);
    #endif //DEBUG

    int stmidx=get_statement_handle(conidx);
    postgres_result[stmidx].result=result;
    _retni(stmidx);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_clear(int argno) // stmidx --> NIL
{
    CCC_PROLOG("_pq_clear",1);
    int stmidx=verify_stmidx(_parni(1));
    drop_statement_handle(stmidx);
    _ret();
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_resultstatus(int argno) // stmidx --> res_status
{
    CCC_PROLOG("_pq_resultstatus",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    _retni( PQresultStatus(result) );
    CCC_EPILOG();

    //ezek vannak:
    //PGRES_EMPTY_QUERY
    //PGRES_COMMAND_OK
    //PGRES_TUPLES_OK
    //PGRES_COPY_OUT
    //PGRES_COPY_IN
    //PGRES_BAD_RESPONSE
    //PGRES_NONFATAL_ERROR
    //PGRES_FATAL_ERROR
}    
 
//--------------------------------------------------------------------------
void _clp__pq_resulterrormessage(int argno) // stmidx --> res_errmsg
{
    CCC_PROLOG("_pq_resulterrormessage",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    char *msg=PQresultErrorMessage(result);
    _retcb( msg?msg:"" );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_resulterrorfield(int argno) // stmidx,fld --> res_errmsg_field
{
    CCC_PROLOG("_pq_resulterrorfield",2);
    int stmidx=verify_stmidx(_parni(1));
    int field=_parni(2);
    PGresult *result=postgres_result[stmidx].result;
    char *msg=PQresultErrorField(result,field);
    _retcb( msg?msg:"" );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_resstatus(int argno) // res_status --> res_status_string
{
    CCC_PROLOG("_pq_resstatus",1);
    int status=_parni(1);
    char *str=PQresStatus((ExecStatusType)status);
    _retcb( str?str:"" );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_cmdstatus(int argno)  // stmidx --> stmt_type_string
{
    CCC_PROLOG("_pq_cmdstatus",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    char *cmd=PQcmdStatus(result);
    _retcb( cmd?cmd:"" );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_cmdtuples(int argno) // stmidx --> affected_rows_string
{
    //insert, update, delete után az érintett rekordok száma
    //(szövegesen), minden más utasításra üres string

    CCC_PROLOG("_pq_cmdtuples",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    char *str=PQcmdTuples(result);
    _retcb( str?str:"" );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_binarytuples(int argno)
{
    CCC_PROLOG("_pq_binarytuples",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    _retl( PQbinaryTuples(result) );
    CCC_EPILOG();
}    
 
//--------------------------------------------------------------------------
void _clp__pq_nfields(int argno) // stmidx --> number_of_fields 
{
    CCC_PROLOG("_pq_nfields",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    _retni( PQnfields(result) );
    CCC_EPILOG();
}    

 
//--------------------------------------------------------------------------
void _clp__pq_fname(int argno) // stmidx,fldidx --> field_name 
{
    CCC_PROLOG("_pq_fname",2);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    int fldidx=ISNIL(2)?0:_parni(2);
    int fldnum=PQnfields(result); 

    if( fldidx )
    {
        stringnb( PQfname(result,fldidx-1) );
    }
    else
    {
        for( int i=0; i<fldnum; i++)
        {
            stringnb(PQfname(result,i));
        }
        array(fldnum);
    }
    _rettop();
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_ftype(int argno) // stmidx,fldidx --> field_type
{
    CCC_PROLOG("_pq_ftype",2);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    int fldidx=_parni(2);
    _retni( PQftype(result,fldidx-1) );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_fsize(int argno) // stmidx,fldidx --> field_size
{
    CCC_PROLOG("_pq_fsize",2);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    int fldidx=_parni(2);
    _retni( PQfsize(result,fldidx-1) );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_fmod(int argno)
{
    CCC_PROLOG("_pq_fmod",2);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    int fldidx=_parni(2);
    _retni( PQfmod(result,fldidx-1) );
    CCC_EPILOG();
}    
 
//--------------------------------------------------------------------------
void _clp__pq_ntuples(int argno) // stmidx --> number_of_rows
{
    CCC_PROLOG("_pq_ntuples",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    _retni( PQntuples(result) );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_oidvalue(int argno)
{
    CCC_PROLOG("_pq_oidvalue",1);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    Oid oid=PQoidValue(result);
    _retblen( (char*)&oid, sizeof(oid) );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_getisnull(int argno) // stmidx,row,col --> null_flag
{
    CCC_PROLOG("_pq_getisnull",3);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    int row=_parni(2);
    int col=_parni(3);
    _retl( PQgetisnull(result,row-1,col-1) );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_getlength(int argno) // stmidx,row,col --> length
{
    CCC_PROLOG("_pq_getlength",3);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    int row=_parni(2);
    int col=_parni(3);
    _retni( PQgetlength(result,row-1,col-1) );
    CCC_EPILOG();
}    
 
//--------------------------------------------------------------------------
void _clp__pq_getvalue0(int argno) // stmidx,row,col --> "value"/NIL
{
    CCC_PROLOG("_pq_getvalue0",3);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;
    int row=_parni(2);
    int col=_parni(3);
    
    if( PQgetisnull(result,row-1,col-1) )
    {
        push(&NIL);
    }
    else
    {
        binaryn( PQgetvalue(result,row-1,col-1) );
        //printf("\ngetvalue:");
        //char *p=PQgetvalue(result,row-1,col-1);
        //while( *p )
        //{
        //    printf("%02x ",(unsigned)*p);
        //    p++;
        //}
    }
    _rettop();
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__pq_getvalue(int argno)  // stmidx,row,col --> {"value"}
{
    CCC_PROLOG("_pq_getvalue",3);
    int stmidx=verify_stmidx(_parni(1));
    PGresult *result=postgres_result[stmidx].result;

    int row=ISNIL(2)?0:_parni(2);
    int col=ISNIL(3)?0:_parni(3);
    int nrow=PQntuples(result);
    int ncol=PQnfields(result);
 

    if( col )
    {
        binaryn( PQgetvalue(result,row-1,col-1) );
    }
    else if( row )
    {
        for( int j=0; j<ncol; j++)
        {
            binaryn( PQgetvalue(result,row-1,j) );
        }
        array(ncol);
    }
    else
    {
        for( int i=0; i<nrow; i++)
        {
            for( int j=0; j<ncol; j++)
            {
                binaryn( PQgetvalue(result,i,j) );
            }
            array(ncol);
        }
        array(nrow);
    }
    _rettop();
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
static unsigned char *escape(const unsigned char *from, size_t from_length, size_t *to_length)
{
    //format: E'proba \\ooo \\ooo szerencse'
    
    const unsigned char *vp;
    unsigned char *rp;
    unsigned char *result;
    size_t len,i;

    len=1; //záró 0

    vp=from;
    for( i=from_length; i>0; i--, vp++ )
    {
        if( *vp<0x20 || 0x7e<*vp || *vp=='\'' || *vp=='\\' )
        {
            len+=5;
        }
        else
        {
            len++;
        }
    }

    *to_length=len;
    rp=result=(unsigned char*)malloc(len);

    vp=from;
    for( i=from_length; i>0; i--, vp++)
    {
        if( *vp<0x20 || 0x7e<*vp || *vp=='\'' || *vp=='\\' )
        {
            sprintf((char*)rp,"\\\\%03o",*vp);
            rp+=5;
        }
        else
        {
            *rp++=*vp;
        }
    }
    *rp++='\0';

    return result;
}

//--------------------------------------------------------------------------
void _clp__pq_escapebytea(int argno)
{
    CCC_PROLOG("_pq_escapebytea",1);
    char *from=_parb(1);
    int fleng=_parblen(1);
    size_t tleng;
    char *to=(char*)escape((unsigned char*)from,fleng,&tleng); //PQescapeByteaConn nem jó!
    _retblen(to,(tleng?tleng-1:0)); //záró 0 byte elhagyva
    free(to);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__pq_unescapebytea(int argno)
{
    CCC_PROLOG("_pq_unescapebytea",1);
    char *from=_parb(1);
    size_t tleng;
    char *to=(char*)PQunescapeBytea((unsigned char*)from,&tleng);
    _retblen(to,tleng); //itt nincs záró 0 byte 
    PQfreemem(to);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__pq_escapestring(int argno) //az "'" és "\" karaktereket duplázza
{
    CCC_PROLOG("_pq_escapestring",1);
    char *from=_parcb(1);
    int fleng=_parblen(1);
    char *to=binaryl(2*fleng+1);

    int tleng=0;
    for(int i=0; i<fleng; i++)  //PQescapeStringConn nem jó!
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



//--------------------------------------------------------------------------
#ifdef EMLEKEZTETO //az "escapelésről"

  Régen a Postgres stringek C-szerűen escapeltek voltak, vagyis
      a '\n' karakter-literál egy soremelést jelentett,
      a '\\' karakter-literál jelentette a backslasht, stb.
  Az SQL standard azonban nem ismeri az ilyen escape szekvenciákat,
  és a backslasheket sem kell duplázni. 
  
  A standard közelítése érdekében a Postgres 8.x-ben bevezettek egy 
  szerver-paramétert: standard_conforming_strings.  Ez a paraméter 
  a postgresql.conf-ban állítható, azt határozza meg, hogy a szerver 
  értelmezze-e az escape szekvenciáat. Jelenleg 

    standard_conforming_strings = off  # értelmezi (nem standard)
  
  a default beállítás, de a dokumentációban figyelmeztetnek, hogy 
  a default a jövőben változni fog. A lényeg, hogy a különböző szerverek 
  különféleképpen escapelnek, sőt ugyanaz a szerver is escapelhet
  a változó konfigurációtól függően egyszer így, másszor úgy.

  A standard_conforming_strings paraméterrel egyidőben megjelent az 
  E'...' alakú, azaz escapelt string. Ez a Postgres speciális szintaktikája, 
  olyan stringet jelöl, aminek a belsejében a \-t mindig escape szekvencia 
  bevezetőjeként kell értelmezni (standard_conforming_strings értékétől
  függetlenül).
  
  Hogyan függetlenítjük magunkat standard_conforming_strings-től?
  Az SQL2 interfész a saját maga által generált parancsokban mindig E'...' 
  stringet küld a szervernek, ennek értelmezése független a konfigurációtól.
  A stringben levő backslasheket viszont mindig megduplázza (hatástalanítja).
  Az "\n" érték tehát E'\\n'-ként lesz elküldve a szervernek, így az nem 
  újsor karaktert, hanem 1 darab \-t és egy darab n-t eredményez. Újsor 
  karakter akkor kerül az adatbázisba, ha az SQL parancs chr(10) értéket 
  tartalmaz, de ezt nem kell külön escapelni.
  
  Hibás volna  E'...' stringek belsejének escapelésre a könyvtári 
  PQescapeBytea, PQescapeByteaConn, PQescapeString függvényeket használni, 
  mert ezek figyelik a szerveren beállított standard_conforming_strings-t,
  holott az E'...' értelme éppen az, hogy ettől független az escapelés.
  
  Az PQunescapeBytea függvénnyel baj lehet, ha a 9.x szerver olyan
  (hex) escapelt stringet küld, amit a 8.x kliens nem tud értelmezni. 
  Egy unescape függvény azonban trükkös, ezért maradunk a könyvtári 
  verziónál.

  Az sqlexec metódus a parancs-stringet úgy küldi a szervernek, ahogy 
  azt a program(ozó) elkészítette, probléma lehet a hordozhatósággal
  Postgres és Oracle között. Ha a parancs E'...' alakú string literált
  tartalmaz, azt az Oracle hibásnak jelzi. Az '...\n...' literálban
  (síma string) az Oracle \n-t nem értelmezi újsornak, a Postgres
  viszont standard_conforming_strings-től függően értelmezi újsornak
  (vagy warningnak vagy errornak).
  
  Megj: Viszont sqlexec-ben az sqlbind-dal behelyettesített értékek
  automatikusan escapelődnek, tehát ebben az esetben is az interfész
  kiegyenlíti az Oracle és Postgres különbségét.
  
  A bytea (memó) típusokban így escapelünk: E'...\\ooo...', tehát 
  5 hosszú szekvenciák vannak: \\ plusz 3-jegyű oktális szám.
  Miért kell duplázni a \\-t? Nem éppen így oltja ki a hatását?
  Válasz, _két_ elemzésen megy át a szekvencia:
    1) string syntax elemző :  \\ooo  ->  \ooo
    2) bytea  input  elemző :   \ooo  ->   ooo értékű byte

#endif

//--------------------------------------------------------------------------
