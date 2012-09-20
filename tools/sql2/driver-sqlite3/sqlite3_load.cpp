
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

//libsqlite3.so betöltése futás közben

#ifdef WIN32
    #include <windows.h>
#else
    #include <dlfcn.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#define CPP_PROTOTYPES
#include <sqlite3.ch>

typedef const char *sqlite3_libversion_t(void);
typedef int sqlite3_open_t(const char *filename,sqlite3 **ppDb);
typedef int sqlite3_open_v2_t(const char *filename,sqlite3 **ppDb,int flags,const char *zVfs);
typedef int sqlite3_errcode_t(sqlite3 *db);
typedef int sqlite3_extended_errcode_t(sqlite3 *db);
typedef const char *sqlite3_errmsg_t(sqlite3*);
typedef int sqlite3_close_t(sqlite3 *db);
typedef int sqlite3_free_t(void*p);
typedef int sqlite3_exec_t(sqlite3* db, const char *sql, int (*callback)(void*,int,char**,char**), void *arg1, char **errmsg);
typedef int sqlite3_prepare_v2_t(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail);
typedef int sqlite3_step_t(sqlite3_stmt *stmt);
typedef int sqlite3_finalize_t(sqlite3_stmt *stmt);
typedef const void *sqlite3_column_blob_t(sqlite3_stmt*, int iCol);
typedef int sqlite3_column_bytes_t(sqlite3_stmt*, int iCol);
typedef double sqlite3_column_double_t(sqlite3_stmt*, int iCol);
typedef int sqlite3_column_int_t(sqlite3_stmt*, int iCol);
typedef const unsigned char *sqlite3_column_text_t(sqlite3_stmt*, int iCol);
typedef int sqlite3_column_type_t(sqlite3_stmt*, int iCol);
typedef const char *sqlite3_column_name_t(sqlite3_stmt*, int iCol);
typedef int sqlite3_column_count_t(sqlite3_stmt* stmt);
typedef int sqlite3_changes_t(sqlite3 *db);
typedef sqlite3_int64 sqlite3_last_insert_rowid_t(sqlite3 *db);


//----------------------------------------------------------------------------
static void error(const char *entryname)
{
    if( NULL==entryname )
    {
        #ifdef WIN32
            printf("sqlite3.dll not found\n");
        #else
            printf("libsqlite3.so not found\n");
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
static HINSTANCE load_sqlite3_dll()
{
    HINSTANCE dll=LoadLibraryEx("sqlite3",NULL,0);

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
    static HINSTANCE dll=load_sqlite3_dll();

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
static void *load_libsqlite3_so()
{
    void *so=dlopen("libsqlite3.so",RTLD_NOW|RTLD_GLOBAL); 

    if( so==0 ) 
    {
        error(0);
    }
    else
    {
        //printf("libsqlite3.so library loaded\n"); fflush(0);
    }
    return so;
}

//----------------------------------------------------------------------------
static void* getproc(const char *entryname)
{
    static void *so=load_libsqlite3_so();

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
const char *sqlite3_libversion()
{
    static void *p=getproc("sqlite3_libversion");
    return ((sqlite3_libversion_t*)p)();
}

//----------------------------------------------------------------------------
int sqlite3_open(const char *filename,sqlite3 **ppDb)
{
    static void *p=getproc("sqlite3_open");
    return ((sqlite3_open_t*)p)(filename,ppDb);
}

//----------------------------------------------------------------------------
int sqlite3_open_v2(const char *filename,sqlite3 **ppDb,int flags,const char *zVfs)
{
    static void *p=getproc("sqlite3_open_v2");
    return ((sqlite3_open_v2_t*)p)(filename,ppDb,flags,zVfs);
}

//----------------------------------------------------------------------------
int sqlite3_errcode(sqlite3 *db)
{
    static void *p=getproc("sqlite3_errcode");
    return ((sqlite3_errcode_t*)p)(db);
}

//----------------------------------------------------------------------------
int sqlite3_extended_errcode(sqlite3 *db)
{
    static void *p=getproc("sqlite3_extended_errcode");
    return ((sqlite3_extended_errcode_t*)p)(db);
}

//----------------------------------------------------------------------------
const char *sqlite3_errmsg(sqlite3 *db)
{
    static void *p=getproc("sqlite3_errmsg");
    return ((sqlite3_errmsg_t*)p)(db);
}

//----------------------------------------------------------------------------
int sqlite3_close(sqlite3 *db)
{
    static void *p=getproc("sqlite3_close");
    return ((sqlite3_close_t*)p)(db);
}

//----------------------------------------------------------------------------
void sqlite3_free(void*ptr)
{
    static void *p=getproc("sqlite3_free");
    ((sqlite3_free_t*)p)(ptr);
}

//----------------------------------------------------------------------------
int sqlite3_exec(sqlite3 *db, const char *sql, int (*callback)(void*,int,char**,char**), void *arg1, char **errmsg)
{
    static void *p=getproc("sqlite3_exec");
    return ((sqlite3_exec_t*)p)(db,sql,callback,arg1,errmsg);
}

//----------------------------------------------------------------------------
int sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail)
{
    static void *p=getproc("sqlite3_prepare_v2");
    return ((sqlite3_prepare_v2_t*)p)(db,zSql,nByte,ppStmt,pzTail);
}

//----------------------------------------------------------------------------
int sqlite3_step(sqlite3_stmt *stmt)
{
    static void *p=getproc("sqlite3_step");
    return ((sqlite3_step_t*)p)(stmt);
}

//----------------------------------------------------------------------------
int sqlite3_finalize(sqlite3_stmt *stmt)
{
    static void *p=getproc("sqlite3_finalize");
    return ((sqlite3_finalize_t*)p)(stmt);
}

//----------------------------------------------------------------------------
const void *sqlite3_column_blob(sqlite3_stmt *stmt, int iCol)
{
    static void *p=getproc("sqlite3_column_blob");
    return ((sqlite3_column_blob_t*)p)(stmt,iCol);
}

//----------------------------------------------------------------------------
int sqlite3_column_bytes(sqlite3_stmt *stmt, int iCol)
{
    static void *p=getproc("sqlite3_column_bytes");
    return ((sqlite3_column_bytes_t*)p)(stmt,iCol);
}

//----------------------------------------------------------------------------
double sqlite3_column_double(sqlite3_stmt *stmt, int iCol)
{
    static void *p=getproc("sqlite3_column_double");
    return ((sqlite3_column_double_t*)p)(stmt,iCol);
}

//----------------------------------------------------------------------------
int sqlite3_column_int(sqlite3_stmt *stmt, int iCol)
{
    static void *p=getproc("sqlite3_column_int");
    return ((sqlite3_column_int_t*)p)(stmt,iCol);
}

//----------------------------------------------------------------------------
const unsigned char *sqlite3_column_text(sqlite3_stmt *stmt, int iCol)
{
    static void *p=getproc("sqlite3_column_text");
    return ((sqlite3_column_text_t*)p)(stmt,iCol);
}

//----------------------------------------------------------------------------
int sqlite3_column_type(sqlite3_stmt *stmt, int iCol)
{
    static void *p=getproc("sqlite3_column_type");
    return ((sqlite3_column_type_t*)p)(stmt,iCol);
}

//----------------------------------------------------------------------------
const char *sqlite3_column_name(sqlite3_stmt *stmt, int iCol)
{
    static void *p=getproc("sqlite3_column_name");
    return ((sqlite3_column_name_t*)p)(stmt,iCol);
}

//----------------------------------------------------------------------------
int sqlite3_column_count(sqlite3_stmt* stmt)
{
    static void *p=getproc("sqlite3_column_count");
    return ((sqlite3_column_count_t*)p)(stmt);
}

//----------------------------------------------------------------------------
int sqlite3_changes(sqlite3 *db)
{
    static void *p=getproc("sqlite3_changes");
    return ((sqlite3_changes_t*)p)(db);
}

//----------------------------------------------------------------------------
sqlite3_int64 sqlite3_last_insert_rowid(sqlite3 *db)
{
    static void *p=getproc("sqlite3_last_insert_rowid");
    return ((sqlite3_last_insert_rowid_t*)p)(db);
}

//----------------------------------------------------------------------------


