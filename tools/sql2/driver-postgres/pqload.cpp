
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

//libpq.dll/libpq.so betöltése futás közben

#ifdef WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <postgresql/libpq-fe.h>


typedef void PQclear_t (PGresult *res);
typedef void PQfinish_t (PGconn *conn);
typedef PGconn *PQconnectdb_t (const char *conninfo);
typedef ConnStatusType PQstatus_t (const PGconn *conn);
typedef char *PQerrorMessage_t (const PGconn *conn);
typedef PGconn *PQsetdbLogin_t (const char *host, const char *port, const char *opt, const char *tty, const char *db, const char *usr, const char *psw);
typedef void PQtrace_t (PGconn *conn, FILE *debug_port);
typedef void PQuntrace_t (PGconn *conn);
typedef PGresult *PQexec_t (PGconn *conn, const char *query);
typedef ExecStatusType PQresultStatus_t (const PGresult *res);
typedef char *PQresStatus_t (ExecStatusType status);
typedef char *PQcmdStatus_t (PGresult *res);
typedef int PQntuples_t (const PGresult *res);
typedef char *PQresultErrorMessage_t (const PGresult *res);
typedef char *PQresultErrorField_t (const PGresult *res, int fieldcode);
typedef char *PQcmdTuples_t (PGresult *res);
typedef int PQbinaryTuples_t (const PGresult *res);
typedef int PQnfields_t (const PGresult *res);
typedef char *PQfname_t (const PGresult *res, int field_num);
typedef Oid PQftype_t (const PGresult *res, int field_num);
typedef int PQfsize_t (const PGresult *res, int field_num);
typedef int PQfmod_t (const PGresult *res, int field_num);
typedef Oid PQoidValue_t (const PGresult *res);
typedef int PQgetisnull_t (const PGresult *res, int tup_num, int field_num);
typedef int PQgetlength_t (const PGresult *res, int tup_num, int field_num);
typedef char *PQgetvalue_t (const PGresult *res, int tup_num, int field_num);
typedef unsigned char *PQescapeBytea_t (const unsigned char *bintext, size_t binlen, size_t *bytealen);
typedef unsigned char *PQunescapeBytea_t (const unsigned char *strtext, size_t *retbuflen);
typedef size_t PQescapeString_t (char *to, const char *from, size_t length);
typedef void PQfreemem_t (void *ptr);

//----------------------------------------------------------------------------
static void error(const char *entryname)
{
    if( NULL==entryname )
    {
        #ifdef WIN32
            printf("libpq.dll not found\n");
        #else
            printf("libpq.so not found\n");
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
static HINSTANCE load_libpq_dll()
{
    HINSTANCE dll=LoadLibraryEx("libpq",NULL,0);

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
    static HINSTANCE dll=load_libpq_dll();

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
static void *load_libpq_so()
{
    void *so=dlopen("libpq.so",RTLD_NOW|RTLD_GLOBAL); 

    if( so==0 ) 
    {
        error(0);
    }
    else
    {
        //printf("libpq.so library loaded\n"); fflush(0);
    }
    return so;
}

//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static void *so=load_libpq_so();

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
void PQclear(PGresult *res)
{
    static void *p=getproc("PQclear");
    ((PQclear_t*)p)(res);
}

//----------------------------------------------------------------------------
void PQfinish(PGconn *conn)
{
    static void *p=getproc("PQfinish");
    ((PQfinish_t*)p)(conn);
}

//----------------------------------------------------------------------------
PGconn *PQconnectdb(const char *conninfo)
{
    static void *p=getproc("PQconnectdb");
    return ((PQconnectdb_t*)p)(conninfo);
}

//----------------------------------------------------------------------------
ConnStatusType PQstatus(const PGconn *conn)
{
    static void *p=getproc("PQstatus");
    return ((PQstatus_t*)p)(conn);
}

//----------------------------------------------------------------------------
char *PQerrorMessage(const PGconn *conn)
{
    static void *p=getproc("PQerrorMessage");
    return ((PQerrorMessage_t*)p)(conn);
}

//----------------------------------------------------------------------------
PGconn *PQsetdbLogin( const  char *host,
                      const  char *port,
                      const  char *opt,
                      const  char *tty,
                      const  char *db,
                      const  char *usr,
                      const  char *psw)
{
    static void *p=getproc("PQsetdbLogin");
    return ((PQsetdbLogin_t*)p)(host,port,opt,tty,db,usr,psw);
}

//----------------------------------------------------------------------------
void PQtrace(PGconn *conn, FILE *debug_port)
{
    static void *p=getproc("PQtrace");
    ((PQtrace_t*)p)(conn,debug_port);
}

//----------------------------------------------------------------------------
void PQuntrace(PGconn *conn)
{
    static void *p=getproc("PQuntrace");
    ((PQuntrace_t*)p)(conn);
}

//----------------------------------------------------------------------------
PGresult *PQexec(PGconn *conn, const char *query)
{
    static void *p=getproc("PQexec");
    return ((PQexec_t*)p)(conn,query);
}

//----------------------------------------------------------------------------
ExecStatusType PQresultStatus(const PGresult *res)
{
    static void *p=getproc("PQresultStatus");
    return ((PQresultStatus_t*)p)(res);
}

//----------------------------------------------------------------------------
char *PQresStatus(ExecStatusType status)
{
    static void *p=getproc("PQresStatus");
    return ((PQresStatus_t*)p)(status);
}

//----------------------------------------------------------------------------
char *PQcmdStatus(PGresult *res)
{
    static void *p=getproc("PQcmdStatus");
    return ((PQcmdStatus_t*)p)(res);
}

//----------------------------------------------------------------------------
int PQntuples(const PGresult *res)
{
    static void *p=getproc("PQntuples");
    return ((PQntuples_t*)p)(res);
}

//----------------------------------------------------------------------------
char *PQresultErrorMessage(const PGresult *res)
{
    static void *p=getproc("PQresultErrorMessage");
    return ((PQresultErrorMessage_t*)p)(res);
}

//----------------------------------------------------------------------------
char *PQresultErrorField(const PGresult *res, int fieldcode)
{
    static void *p=getproc("PQresultErrorField");
    return ((PQresultErrorField_t*)p)(res,fieldcode);
}

//----------------------------------------------------------------------------
char *PQcmdTuples(PGresult *res)
{
    static void *p=getproc("PQcmdTuples");
    return ((PQcmdTuples_t*)p)(res);
}

//----------------------------------------------------------------------------
int PQbinaryTuples(const PGresult *res)
{
    static void *p=getproc("PQbinaryTuples");
    return  ((PQbinaryTuples_t*)p)(res);
}

//----------------------------------------------------------------------------
int PQnfields(const PGresult *res)
{
    static void *p=getproc("PQnfields");
    return  ((PQnfields_t*)p)(res);
}

//----------------------------------------------------------------------------
char *PQfname(const PGresult *res, int field_num)
{
    static void *p=getproc("PQfname");
    return ((PQfname_t*)p)(res,field_num);
}

//----------------------------------------------------------------------------
Oid PQftype(const PGresult *res, int field_num)
{
    static void *p=getproc("PQftype");
    return  ((PQftype_t*)p)(res,field_num);
}

//----------------------------------------------------------------------------
int PQfsize(const PGresult *res, int field_num)
{
    static void *p=getproc("PQfsize");
    return ((PQfsize_t*)p)(res,field_num);
}

//----------------------------------------------------------------------------
int PQfmod(const PGresult *res, int field_num)
{
    static void *p=getproc("PQfmod");
    return ((PQfmod_t*)p)(res,field_num);
}

//----------------------------------------------------------------------------
Oid PQoidValue(const PGresult *res)
{
    static void *p=getproc("PQoidValue");
    return ((PQoidValue_t*)p)(res);
}

//----------------------------------------------------------------------------
int PQgetisnull(const PGresult *res, int tup_num, int field_num)
{
    static void *p=getproc("PQgetisnull");
    return ((PQgetisnull_t*)p)(res,tup_num,field_num);
}

//----------------------------------------------------------------------------
int PQgetlength(const PGresult *res, int tup_num, int field_num)
{
    static void *p=getproc("PQgetlength");
    return ((PQgetlength_t*)p)(res,tup_num,field_num);
}

//----------------------------------------------------------------------------
char *PQgetvalue(const PGresult *res, int tup_num, int field_num)
{
    static void *p=getproc("PQgetvalue");
    return ((PQgetvalue_t*)p)(res,tup_num,field_num);
}

//----------------------------------------------------------------------------
unsigned char *PQescapeBytea(const unsigned char *bintext, size_t binlen, size_t *bytealen)
{
    static void *p=getproc("PQescapeBytea");
    return ((PQescapeBytea_t*)p)(bintext,binlen,bytealen);
}

//----------------------------------------------------------------------------
unsigned char *PQunescapeBytea(const unsigned char *strtext, size_t *retbuflen)
{
    static void *p=getproc("PQunescapeBytea");
    return ((PQunescapeBytea_t*)p)(strtext,retbuflen);
}

//----------------------------------------------------------------------------
size_t PQescapeString(char *to, const char *from, size_t length)
{
    static void *p=getproc("PQescapeString");
    return ((PQescapeString_t*)p)(to,from,length);
}

//----------------------------------------------------------------------------
void PQfreemem(void *ptr)
{
    static void *p=getproc("PQfreemem");
    ((PQfreemem_t*)p)(ptr);
}

//----------------------------------------------------------------------------

