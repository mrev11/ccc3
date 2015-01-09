
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

//libmysql.so betöltése futás közben

#ifdef WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <my.h>

typedef MYSQL *mysql_init_t(MYSQL *mysql);
typedef void mysql_close_t(MYSQL *mysql);
typedef unsigned int mysql_errno_t(MYSQL *mysql);
typedef const char *mysql_error_t(MYSQL *mysql);
typedef MYSQL *mysql_real_connect_t(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag);
typedef const char *mysql_get_server_info_t(MYSQL *mysql);
typedef const char *mysql_character_set_name_t(MYSQL *mysql);

typedef int mysql_real_query_t(MYSQL *mysql, const char *stmt_str, unsigned long length);
typedef MYSQL_RES *mysql_store_result_t(MYSQL *mysql);
typedef void mysql_free_result_t(MYSQL_RES *result);
typedef unsigned int mysql_field_count_t(MYSQL *mysql);
typedef unsigned int mysql_num_fields_t(MYSQL_RES *result);
typedef my_ulonglong mysql_affected_rows_t(MYSQL *mysql);
typedef MYSQL_FIELD *mysql_fetch_field_direct_t(MYSQL_RES *result, unsigned int fieldnr);
typedef MYSQL_ROW mysql_fetch_row_t(MYSQL_RES *result);
typedef unsigned long* mysql_fetch_lengths_t(MYSQL_RES *result);

//----------------------------------------------------------------------------
static void error(const char *entryname)
{
    if( NULL==entryname )
    {
        #ifdef WIN32
            printf("libmysql.dll not found\n");
        #else
            printf("libmysqlclient_r.so not found\n");
        #endif
    }
    else
    {
        printf("%s not in library\n",entryname);
    }
    getchar();
    exit(1);
}

//----------------------------------------------------------------------------
#ifdef WIN32
//----------------------------------------------------------------------------
static HINSTANCE load_libmysqlclient_dll()
{
    HINSTANCE dll=LoadLibraryEx("libmysql",NULL,0);

    if( dll==0 ) 
    {
        error(0);
    }
    else
    {
        //char modname[512];
        //GetModuleFileName(dll,modname,sizeof(modname));    
        //printf("%s loaded\n",modname); fflush(0);
    }
    return dll;
}

//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static HINSTANCE dll=load_libmysqlclient_dll();

    void *proc=(void*)GetProcAddress(dll,entryname); 
    if( !proc ) 
    {
        error(entryname);
    }
    else
    {
        //printf("%s\n",entryname); fflush(0);
    }
    return proc;
}

//----------------------------------------------------------------------------
#else //UNIX
//----------------------------------------------------------------------------
static void *load_libmysqlclient_so()
{
    void *so=dlopen("libmysqlclient_r.so",RTLD_NOW|RTLD_GLOBAL); 

    if( so==0 ) 
    {
        error(0);
    }
    else
    {
        //printf("libmysqlclient_r.so library loaded\n"); fflush(0);
    }
    return so;
}

//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static void *so=load_libmysqlclient_so();

    void *proc=dlsym(so,entryname);
    if( proc==0 )
    {
        error(entryname);
    }
    else
    {
        //printf("%s\n",entryname); fflush(0);
    }
    return proc;
}

//----------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------
MYSQL *mysql_init(MYSQL *mysql)
{
    static void *p=getproc("mysql_init");
    return ((mysql_init_t*)p)(mysql);
}

//----------------------------------------------------------------------------
void mysql_close(MYSQL *mysql)
{
    static void *p=getproc("mysql_close");
    ((mysql_close_t*)p)(mysql);
}


//----------------------------------------------------------------------------
unsigned int mysql_errno(MYSQL *mysql)
{
    static void *p=getproc("mysql_errno");
    return ((mysql_errno_t*)p)(mysql);
}

//----------------------------------------------------------------------------
const char *mysql_error(MYSQL *mysql)
{
    static void *p=getproc("mysql_error");
    return ((mysql_error_t*)p)(mysql);
}

//----------------------------------------------------------------------------
MYSQL *mysql_real_connect(MYSQL *mysql, const char *host, const char *user, const char *passwd, const char *db, unsigned int port, const char *unix_socket, unsigned long client_flag)
{
    static void *p=getproc("mysql_real_connect");
    return ((mysql_real_connect_t*)p)(mysql,host,user,passwd,db,port,unix_socket,client_flag);
}

//----------------------------------------------------------------------------
const char *mysql_get_server_info(MYSQL *mysql)
{
    static void *p=getproc("mysql_get_server_info");
    return ((mysql_get_server_info_t*)p)(mysql);
}

//----------------------------------------------------------------------------
const char *mysql_character_set_name(MYSQL *mysql)
{
    static void *p=getproc("mysql_character_set_name");
    return ((mysql_character_set_name_t*)p)(mysql);
}






//----------------------------------------------------------------------------
int mysql_real_query(MYSQL *mysql, const char *stmt_str, unsigned long length)
{
    static void *p=getproc("mysql_real_query");
    return ((mysql_real_query_t*)p)(mysql,stmt_str,length);
}

//----------------------------------------------------------------------------
MYSQL_RES *mysql_store_result(MYSQL *mysql)
{
    static void *p=getproc("mysql_store_result");
    return ((mysql_store_result_t*)p)(mysql);
}

//----------------------------------------------------------------------------
void mysql_free_result(MYSQL_RES *result)
{
    static void *p=getproc("mysql_free_result");
    ((mysql_free_result_t*)p)(result);
}


//----------------------------------------------------------------------------
unsigned int mysql_field_count(MYSQL *mysql)
{
    static void *p=getproc("mysql_field_count");
    return ((mysql_field_count_t*)p)(mysql);
}

//----------------------------------------------------------------------------
unsigned int mysql_num_fields(MYSQL_RES *result)
{
    static void *p=getproc("mysql_num_fields");
    return ((mysql_num_fields_t*)p)(result);

}

//----------------------------------------------------------------------------
my_ulonglong mysql_affected_rows(MYSQL *mysql)
{
    static void *p=getproc("mysql_affected_rows");
    return ((mysql_affected_rows_t*)p)(mysql);
}


//----------------------------------------------------------------------------
MYSQL_FIELD *mysql_fetch_field_direct(MYSQL_RES *result, unsigned int fieldnr)
{
    static void *p=getproc("mysql_fetch_field_direct");
    return ((mysql_fetch_field_direct_t*)p)(result,fieldnr);
}


//----------------------------------------------------------------------------
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result)
{
    static void *p=getproc("mysql_fetch_row");
    return ((mysql_fetch_row_t*)p)(result);
}


//----------------------------------------------------------------------------
unsigned long* mysql_fetch_lengths(MYSQL_RES *result)
{
    static void *p=getproc("mysql_fetch_lengths");
    return ((mysql_fetch_lengths_t*)p)(result);
}

//----------------------------------------------------------------------------
