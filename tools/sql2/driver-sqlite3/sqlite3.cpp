
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

//CCC-sqlite3 interfész

#include <stdio.h>
#include <error.ch>
#include <string.h>

#define CPP_PROTOTYPES
#include <sqlite3.ch>

#include <cccapi.h>


//--------------------------------------------------------------------------
// public interface
//--------------------------------------------------------------------------
void _clp__sqlite3_libversion(int argno)  // -> version (string)
{
    CCC_PROLOG("_sqlite3_libversion",0);
    const char *p=sqlite3_libversion();
    _retcb(p);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__sqlite3_open(int argno)  // _sqlite3_open(filename[,@code]) -> db/NIL
{
    CCC_PROLOG("_sqlite3_open",2);
    convertfspec2nativeformat(base);
    const char *filename=_parb(1);
    sqlite3 *db=0;
    int code=sqlite3_open(filename,&db);
    if( ISREF(2) )
    {
        number(code);
        (base+1)->data.vref->value=*TOP();
        pop();
    }
    if( code==SQLITE_OK )
    {
        _retp(db); // db, ha sikeres
    }
    else
    {
        _ret();    // NIL, ha sikertelen
    }
    CCC_EPILOG();
}


//--------------------------------------------------------------------------
void _clp__sqlite3_open2(int argno)  // _sqlite3_open(filename,flags[,@code]) -> db/NIL
{
    CCC_PROLOG("_sqlite3_open2",3);
    convertfspec2nativeformat(base);
    const char *filename=_parb(1);
    int flags=ISNIL(2) ? (SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE) : _parni(2);
    sqlite3 *db=0;
    int code=sqlite3_open_v2(filename,&db,flags,0); // 1=ro, 2=rw, 4=create
    if( ISREF(3) )
    {
        number(code);
        (base+2)->data.vref->value=*TOP();
        pop();
    }
    if( code==SQLITE_OK )
    {
        _retp(db); // db, ha sikeres
    }
    else
    {
        _ret();    // NIL, ha sikertelen
    }
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__sqlite3_errcode(int argno)  // _sqlite3_errcode(db) -> code
{
    CCC_PROLOG("_sqlite3_errcode",1);
    sqlite3 *db=(sqlite3*)_parp(1);
    int code=sqlite3_errcode(db);
    _retni(code);
    CCC_EPILOG();
}    


//--------------------------------------------------------------------------
void _clp__sqlite3_extended_errcode(int argno)  // _sqlite3_extended_errcode(db) -> code
{
    CCC_PROLOG("_sqlite3_extended_errcode",1);
    sqlite3 *db=(sqlite3*)_parp(1);
    int code=sqlite3_extended_errcode(db);
    _retni(code);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_errmsg(int argno)  // _sqlite3_errmsg(db) -> errmsg
{
    CCC_PROLOG("_sqlite3_errmesg",1);
    sqlite3 *db=(sqlite3*)_parp(1);
    const char *msg=sqlite3_errmsg(db);
    if( msg )
    {
        stringsb(msg,strlen(msg));
    }
    else
    {
        string(CHRLIT(""));
    }
    _rettop();
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_close(int argno)  // _sqlite3_close(db) -> code
{
    CCC_PROLOG("_sqlite3_close",1);
    sqlite3 *db=(sqlite3*)_parp(1);
    int code=sqlite3_close(db);
    _retni(code);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_exec(int argno)   // _sqlite3_exec(db,sqltxt[,@errmsg]) -> code
{
    CCC_PROLOG("_sqlite3_exec",3);
    sqlite3 *db=(sqlite3*)_parp(1);
    str2bin(base+1);
    const char *sqltxt=_parb(2);
    char *errmsg=0;

    int code=sqlite3_exec(db,sqltxt,0,0,&errmsg);  //callback nélkül
    
    if( ISREF(3) )
    {
        if( errmsg!=0 )
        {
            stringnb(errmsg);
        }
        else
        {
            PUSHNIL();
        }
        (base+2)->data.vref->value=*TOP();
    }
    sqlite3_free(errmsg);

    _retni(code);
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__sqlite3_prepare(int argno)  //_sqlite3_prepare(db,sqltxt) -> stmt/NIL
{
    CCC_PROLOG("_sqlite3_prepare",2);
    sqlite3 *db=(sqlite3*)_parp(1);
    str2bin(base+1);
    const char *sqltxt=_parb(2);
    int nbyte=_parblen(2);
    sqlite3_stmt *stmt;

    int code=sqlite3_prepare_v2(db,sqltxt,nbyte,&stmt,0);  //tail nélkül
    
    if( stmt!=0 )
    {
        pointer(stmt);  // stmt, ha sikeres
    }
    else
    {
        PUSHNIL();      // NIL, ha sikertelen, hibakód utólag lekérdezhető
    }
    _rettop();
    CCC_EPILOG();
}

//--------------------------------------------------------------------------
void _clp__sqlite3_step(int argno)  // _sqlite3_step(stmt) -> code
{
    CCC_PROLOG("_sqlite3_step",1);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int code=sqlite3_step(stmt);
    _retni(code);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_finalize(int argno)  // _sqlite3_finalize(stmt) -> code
{
    CCC_PROLOG("_sqlite3_finalize",1);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int code=sqlite3_finalize(stmt);
    _retni(code);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_blob(int argno)
{
    CCC_PROLOG("_sqlite3_column_blob",2);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int col=_parni(2)-1; //nullától indul
    const char *p=(char*)sqlite3_column_blob(stmt,col);
    int nbyte=sqlite3_column_bytes(stmt,col);
    _retblen(p,nbyte);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_bytes(int argno)
{
    CCC_PROLOG("_sqlite3_column_bytes",2);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int col=_parni(2)-1; //nullától indul
    int nbyte=sqlite3_column_bytes(stmt,col);
    _retni(nbyte);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_double(int argno)
{
    CCC_PROLOG("_sqlite3_column_double",2);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int col=_parni(2)-1; //nullától indul
    double d=sqlite3_column_double(stmt,col);
    _retnd(d);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_int(int argno)
{
    CCC_PROLOG("_sqlite3_column_int",2);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int col=_parni(2)-1; //nullától indul
    int i=sqlite3_column_int(stmt,col);
    _retni(i);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_text(int argno)
{
    CCC_PROLOG("_sqlite3_column_text",2);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int col=_parni(2)-1; //nullától indul
    const char *p=(char*)sqlite3_column_text(stmt,col);
    int nbyte=sqlite3_column_bytes(stmt,col);
    _retcblen(p,nbyte);
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_type(int argno)
{
    CCC_PROLOG("_sqlite3_column_type",2);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int col=_parni(2)-1; //nullától indul
    int typecode=sqlite3_column_type(stmt,col);
    _retni( typecode );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_name(int argno)
{
    CCC_PROLOG("_sqlite3_column_name",2);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int col=_parni(2)-1; //nullától indul
    const char *name=sqlite3_column_name(stmt,col);
    _retcb( name );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_column_count(int argno)
{
    CCC_PROLOG("_sqlite3_column_count",1);
    sqlite3_stmt *stmt=(sqlite3_stmt*)_parp(1);
    int count=sqlite3_column_count(stmt);
    _retni( count );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_changes(int argno)
{
    CCC_PROLOG("_sqlite3_changes",1);
    sqlite3 *db=(sqlite3*)_parp(1);
    int affected_rows=sqlite3_changes(db);
    _retni( affected_rows );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
void _clp__sqlite3_last_insert_rowid(int argno)
{
    CCC_PROLOG("_sqlite3_last_insert_rowid",1);
    sqlite3 *db=(sqlite3*)_parp(1);
    sqlite3_int64 rowid=sqlite3_last_insert_rowid(db);
    _retnd( (double)rowid );
    CCC_EPILOG();
}    

//--------------------------------------------------------------------------
