
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
#include <cccapi.h>

#include <my.h>

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
namespace _nsp_mysql{


static struct{
    int       active;
    MYSQL     *conhnd;
} mysql_connection[MAX_CONNECTION];
MUTEX_CREATE(mutex_con);

static struct{
    int        conidx;
    MYSQL_RES  *result;
} mysql_result[MAX_STATEMENT];
MUTEX_CREATE(mutex_stm);


//----------------------------------------------------------------------------
static int mysql_init_handles()
{
    MUTEX_LOCK(mutex_con);
    MUTEX_LOCK(mutex_stm);
    
    static int initialized=0;
    
    if( !initialized  )
    {
        int i;
        for( i=0; i<MAX_CONNECTION; i++ )
        {
            mysql_connection[i].active=0;
        }

        for( i=0; i<MAX_STATEMENT; i++ )
        {
            mysql_result[i].conidx=-1;
        }

        initialized=1;
    }

    MUTEX_UNLOCK(mutex_con);
    MUTEX_UNLOCK(mutex_stm);
    return 1;
}

static int init=mysql_init_handles();


//----------------------------------------------------------------------------
static void pusherror()
//
//  stack:  --- errobj
//
{
    _clp_sqlerrornew(0);
    dup(); string(CHRLIT("MYSQL2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

static void pushconnecterror()
//
//  stack:  --- errobj
//
{
    _clp_sqlconnecterrornew(0);
    dup(); string(CHRLIT("MYSQL2"));_o_method_subsystem.eval(2);pop(); 
    dup(); stringnb(trace->func);_o_method_operation.eval(2);pop();
    dup(); number(ES_ERROR);_o_method_severity.eval(2);pop();  
}

//----------------------------------------------------------------------------
static int verify_conidx(int x)
{
    if( (x<0) || (MAX_CONNECTION<=x) || !mysql_connection[x].active )
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
    if( (x<0) || (MAX_STATEMENT<=x) || (mysql_result[x].conidx==-1) )
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
        if( mysql_result[i].conidx==-1 )
        {
            mysql_result[i].conidx=conidx; 
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
    if( mysql_result[stmidx].conidx!=-1 )
    {
        mysql_free_result(mysql_result[stmidx].result);
        mysql_result[stmidx].conidx=-1;
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
        if( 0==mysql_connection[i].active )
        {
            mysql_connection[i].active=1;
            mysql_connection[i].conhnd=mysql_init(0);
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
    if( mysql_connection[conidx].active )
    {
        int i;
        for(i=0; i<MAX_STATEMENT; i++)
        {
            if( mysql_result[i].conidx==conidx )
            {
                drop_statement_handle(i); 
            }
        }

        mysql_close(mysql_connection[conidx].conhnd);
        mysql_connection[conidx].active=0;
    }
    MUTEX_UNLOCK(mutex_con);
}


//--------------------------------------------------------------------------
// public interface
//--------------------------------------------------------------------------
void _clp__my_connect(int argno)  //  --> conidx/NIL
{
    CCC_PROLOG("_my_connect",7);
    int conidx=get_connection_handle();

    MYSQL *mysql=mysql_connection[conidx].conhnd;
    char *host          = ISNIL(1)?0:_parcb(1);
    char *user          = ISNIL(2)?0:_parcb(2);
    char *passwd        = ISNIL(3)?0:_parcb(3);
    char *db            = ISNIL(4)?0:_parcb(4);
    unsigned int port   = ISNIL(5)?0:_parnu(5);
    char *unixsck       = ISNIL(6)?0:_parcb(6);
    unsigned long cflag = ISNIL(7)?0:_parnl(7);

    if( mysql_real_connect(mysql,
                           host, 
                           user, 
                           passwd, 
                           db, 
                           port, 
                           unixsck, 
                           cflag)   )
    {
        _retni(conidx);
    }
    else
    {
        pushconnecterror();
        const char *errmsg=mysql_error(mysql);
        dup();stringnb(errmsg);_o_method_description.eval(2);pop();
        dup();number(mysql_errno(mysql));_o_method_subcode.eval(2);pop();
        drop_connection_handle(conidx);  //ezt hova (break után?)
        _clp_break(1);pop();
        _ret();
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__my_close(int argno)
{
    CCC_PROLOG("_my_close",1);
    int conidx=verify_conidx(_parni(1));
    drop_connection_handle(conidx);
    _ret();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__my_errno(int argno) // conidx --> errno
{
    CCC_PROLOG("_my_errno",1);
    int conidx=verify_conidx(_parni(1));
    _retni( mysql_errno(mysql_connection[conidx].conhnd) );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__my_error(int argno) // conidx --> errmsg
{
    CCC_PROLOG("_my_error",1);
    int conidx=verify_conidx(_parni(1));
    const char *msg=mysql_error(mysql_connection[conidx].conhnd);
    _retcb( msg?msg:"" );
    CCC_EPILOG();
}    
 

//--------------------------------------------------------------------------
void _clp__my_get_server_info(int argno) // conidx --> info
{
    CCC_PROLOG("_my_get_server_info",1);
    int conidx=verify_conidx(_parni(1));
    const char *info=mysql_get_server_info( mysql_connection[conidx].conhnd );
    _retcb(info);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__my_character_set_name(int argno) // conidx --> charset name
{
    CCC_PROLOG("_my_character_set_name",1);
    int conidx=verify_conidx(_parni(1));
    const char *name=mysql_character_set_name( mysql_connection[conidx].conhnd );
    _retcb(name);
    CCC_EPILOG();
}    







//--------------------------------------------------------------------------
void _clp__my_real_query(int argno) // conidx,stmt --> stmidx
{
    CCC_PROLOG("_my_real_query",2);
    int conidx=verify_conidx(_parni(1));
    MYSQL *conhnd=mysql_connection[conidx].conhnd;
    char *query=_parcb(2);
    int length=_parblen(2);

    if( mysql_real_query(conhnd,query,length) )
    {
        _ret(); // error: NIL
    }
    else
    {
        int stmidx=get_statement_handle(conidx);
        mysql_result[stmidx].result=mysql_store_result(conhnd);
        _retni(stmidx); // success: >=0
    }
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__my_free_result(int argno) // stmidx --> NIL
{
    CCC_PROLOG("_my_free_result",1);
    int stmidx=verify_stmidx(_parni(1));
    drop_statement_handle(stmidx);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__my_field_count(int argno) // conidx --> fldcnt
{
    CCC_PROLOG("_my_field_count",1);
    int conidx=verify_conidx(_parni(1));
    _retni( mysql_field_count(mysql_connection[conidx].conhnd) );
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__my_num_fields(int argno) // stmidx --> fldcnt
{
    CCC_PROLOG("_my_num_fields",1);
    int stmidx=verify_stmidx(_parni(1));
    _retni( mysql_num_fields(mysql_result[stmidx].result) );
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__my_affected_rows(int argno) // conidx --> num
{
    CCC_PROLOG("_my_affected_rows",1);
    int conidx=verify_conidx(_parni(1));
    _retni( mysql_affected_rows( mysql_connection[conidx].conhnd ) );
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__my_field_name(int argno) // stmidx,n --> name
{
    CCC_PROLOG("_my_field_name",2);
    int stmidx=verify_stmidx(_parni(1));
    unsigned int fieldnr=_parnu(2);
    MYSQL_FIELD *field=mysql_fetch_field_direct(mysql_result[stmidx].result,fieldnr);
    _retcb( field->name );
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__my_fetch_row(int argno) // stmidx --> {fld1,fld2,...}
{
    CCC_PROLOG("_my_fetch_row",1);
    int stmidx=verify_stmidx(_parni(1));
    MYSQL_ROW row=mysql_fetch_row(mysql_result[stmidx].result);

    if( !row )
    {
        _ret(); //nincs sor -> NIL
    }
    else
    {
        unsigned int num_fields=mysql_num_fields(mysql_result[stmidx].result);
        unsigned long *length=mysql_fetch_lengths(mysql_result[stmidx].result);
        
        for( unsigned int n=0; n<num_fields; n++ )
        {
            if( row[n] )
            {
                binarys(row[n],length[n]);
            }
            else
            {
                PUSHNIL();
            }
        }
        array(num_fields);
        _rettop();
    }
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__my_escapestring(int argno) //az "'" és "\" karaktereket duplázza
{
    CCC_PROLOG("_my_escapestring",1);
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

