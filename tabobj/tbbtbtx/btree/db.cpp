
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

#include <stdio.h>

#ifdef WINDOWS
#include <io.h>
#endif

#include <fileio.ch>
#include <btree.h>

//---------------------------------------------------------------------------
void _clp__db_version(int argno)
{
    CCC_PROLOG("_db_version",2);
    BTREE *db=(BTREE*)_parp(1);
    if( !ISNIL(2) )
    {
        SETVER(db,_parni(2));
    }
    _retni(GETVER(db));
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_cryptflg(int argno)
{
    CCC_PROLOG("_db_cryptflg",2);
    BTREE *db=(BTREE*)_parp(1);
    int encflg=GETENC(db);
    if( !ISNIL(2) )
    {
        __bt_header_read(db,1);
        SETENC(db,_parl(2)?1:0);        // szinkronban kell tartani ezt a kettot
        db->bt_mp->cryptflg=GETENC(db); // szinkronban kell tartani ezt a kettot
        __bt_header_write(db);
    }
    _retl(encflg);
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_create(int argno)
{
    CCC_PROLOG("_db_create",2);
    str2bin(base);
    char *fname=ISBINARY(1)?_parb(1):0;
    int  fdesc=ISNUMBER(1)?_parni(1):-1;
    int  psize=ISNUMBER(2)?_parni(2):0;

    if( fname )
    {
        extern void _clp_fcreate(int);
        stringnb(fname);
        _clp_fcreate(1);
        fdesc=D2INT(TOP()->data.number);
        POP();
    }

    BTREE *db=__bt_open(fdesc,psize,1);
    if( db )
    {
        _retp( db );
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_open(int argno)
{
    CCC_PROLOG("_db_open",2);

    str2bin(base);
    char *fname=ISBINARY(1)?_parb(1):0;
    int  fdesc=ISNUMBER(1)?_parni(1):-1;
    int  psize=ISNUMBER(2)?_parni(2):0;

    if( fname )
    {
        extern void _clp_fopen(int);
        stringnb(fname);
        number(FO_READWRITE+FO_EXCLUSIVE);
        _clp_fopen(2);
        fdesc=D2INT(TOP()->data.number);
        POP();
    }

    BTREE *db=__bt_open(fdesc,psize,0);
    if( db )
    {
        _retp( db );
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_close(int argno)
{
    CCC_PROLOG("_db_close",1);
    BTREE *db=(BTREE*)_parp(1);
    _retni( __bt_close(db) );
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_fd(int argno)
{
    CCC_PROLOG("_db_fd",2);
    BTREE *db=(BTREE*)_parp(1);
    if( !ISNIL(2) )
    {
        __bt_fd(db,_parni(2));
    }
    _retni( __bt_fd(db));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_getcur(int argno) // cursor info (debug)
{
    CCC_PROLOG("_db_getcur",1);
    BTREE *db=(BTREE*)_parp(1);
    pgno_t pgno=0;
    indx_t index=0;
    DBT key;
    if( __bt_getcur(db,&pgno,&index,&key) )
    {
        number(pgno);
        number(index);
        binarys((const char*)key.data,key.size);
        array(3);
        _rettop();
    }
    else
    {
        _ret(); //NIL
    }
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_pagesize(int argno)
{
    CCC_PROLOG("_db_pagesize",1);
    BTREE *db=(BTREE*)_parp(1);
    _retni( __bt_pagesize(db));
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_creord(int argno)
{
    CCC_PROLOG("_db_creord",2);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *name=_parb(2);
    _retni( __bt_creord(db,name) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_setord(int argno)
{
    CCC_PROLOG("_db_setord",2);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *name=_parb(2);
    _retni( __bt_setord(db,name) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_delord(int argno)
{
    CCC_PROLOG("_db_delord",2);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *name=_parb(2);
    _retni( __bt_delord(db,name) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_renord(int argno)
{
    CCC_PROLOG("_db_renord",3);
    BTREE *db=(BTREE*)_parp(1);
    str2bin(base+1);
    char *nameold=_parb(2);
    str2bin(base+2);
    char *namenew=_parb(3);
    _retni( __bt_renord(db,nameold,namenew) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_del(int argno)
{
    CCC_PROLOG("_db_del",2);
    BTREE *db=(BTREE*)_parp(1);
    DBT key;
    str2bin(base+1);
    key.data=_parb(2);
    key.size=_parblen(2);
    _retni( __bt_delete(db,&key) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_put(int argno)
{
    CCC_PROLOG("_db_put",3);
    BTREE *db=(BTREE*)_parp(1);

    DBT key;
    str2bin(base+1);
    key.data=_parb(2);
    key.size=_parblen(2);

    int crs=ISNIL(3)?0:_parl(3);

    _retni( __bt_put(db,&key,crs) );

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_seek(int argno)
{
    CCC_PROLOG("_db_seek",2);
    BTREE *db=(BTREE*)_parp(1);

    DBT key;
    str2bin(base+1);
    key.data=_parb(2);
    key.size=_parblen(2);

    if( 0==__bt_seq(db,&key,R_CURSOR|R_LOCKFILE) )
    {
        _retblen((char*)key.data,key.size);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_first(int argno)
{
    CCC_PROLOG("_db_first",1);
    BTREE *db=(BTREE*)_parp(1);
    int result;

    DBT key;
    if( 0==__bt_seq(db,&key,R_FIRST|R_LOCKFILE) )
    {
        _retblen((char*)key.data,key.size);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_last(int argno)
{
    CCC_PROLOG("_db_last",1);
    BTREE *db=(BTREE*)_parp(1);

    DBT key;
    if( 0==__bt_seq(db,&key,R_LAST|R_LOCKFILE) )
    {
        _retblen((char*)key.data,key.size);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_next(int argno)
{
    CCC_PROLOG("_db_next",1);
    BTREE *db=(BTREE*)_parp(1);

    DBT key;
    if( 0==__bt_seq(db,&key,R_NEXT|R_LOCKFILE) )
    {
        _retblen((char*)key.data,key.size);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_prev(int argno)
{
    CCC_PROLOG("_db_prev",1);
    BTREE *db=(BTREE*)_parp(1);

    DBT key;
    if( 0==__bt_seq(db,&key,R_PREV|R_LOCKFILE) )
    {
        _retblen((char*)key.data,key.size);
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_addresource(int argno)
{
    CCC_PROLOG("_db_addresource",3);
    BTREE *db=(BTREE*)_parp(1);
    DBT data;
    data.data=_parb(2);
    data.size=_parblen(2);
    int index=_parni(3);

    RECPOS rp=__bt_addresource(db,&data,index);

    char buf[6];
    store32(buf,rp.pgno);
    store16(buf+4,rp.index);

    _retblen(buf,sizeof(buf));

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_append(int argno)
{
    CCC_PROLOG("_db_append",3);
    BTREE *db=(BTREE*)_parp(1);

    DBT data;
    data.data=_parb(2);
    data.size=_parblen(2);
    int recno;

    RECPOS rp=__bt_append(db,&data,&recno);

    number( recno );
    assign(base+2);

    char buf[6];
    store32(buf,rp.pgno);
    store16(buf+4,rp.index);

    _retblen(buf,sizeof(buf));

    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_read(int argno)
{
    CCC_PROLOG("_db_read",3);
    BTREE *db=(BTREE*)_parp(1);

    DBT data;
    data.data=_parb(2);
    data.size=_parblen(2);

    char *buf=_parb(3);
    RECPOS rp;
    rp.pgno=load32(buf);
    rp.index=load16(buf+4);

    _retni( __bt_read(db,&data,&rp) );

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_read1(int argno)
{
    CCC_PROLOG("_db_read1",4);
    BTREE *db=(BTREE*)_parp(1);

    DBT data;
    data.data=_parb(2);
    data.size=_parblen(2);

    pgno_t pgno=_parni(3);
    indx_t index=_parni(4);

    _retni( __bt_read1(db,&data,pgno,index) );

    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_rewrite(int argno)
{
    CCC_PROLOG("_db_rewrite",3);
    BTREE *db=(BTREE*)_parp(1);

    DBT data;
    data.data=_parb(2);
    data.size=_parblen(2);

    char *buf=_parb(3);
    RECPOS rp;
    rp.pgno=load32(buf);
    rp.index=load16(buf+4);

    _retni( __bt_rewrite(db,&data,&rp) );

    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_pagelock(int argno)
{
    CCC_PROLOG("_db_pagelock",3);
    BTREE *db=(BTREE*)_parp(1);
    pgno_t pgno=_parnu(2);
    int mode=_parl(3);
    __bt_pagelock(db,pgno,mode);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_pageunlock(int argno)
{
    CCC_PROLOG("_db_pageunlock",2);
    BTREE *db=(BTREE*)_parp(1);
    pgno_t pgno=_parnu(2);
    __bt_pageunlock(db,pgno);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_header_read(int argno)
{
    CCC_PROLOG("_db_header_read",2);
    BTREE *db=(BTREE*)_parp(1);
    int mode=_parl(2);
    __bt_header_read(db,mode);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_header_write(int argno)
{
    CCC_PROLOG("_db_header_write",1);
    BTREE *db=(BTREE*)_parp(1);
    __bt_header_write(db);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_header_sync(int argno)
{
    CCC_PROLOG("_db_header_sync",1);
    BTREE *db=(BTREE*)_parp(1);
    __bt_header_sync(db);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_header_release(int argno)
{
    CCC_PROLOG("_db_header_release",1);
    BTREE *db=(BTREE*)_parp(1);
    __bt_header_release(db);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_lastrec(int argno)
{
    CCC_PROLOG("_db_lastrec",1);
    BTREE *db=(BTREE*)_parp(1);
    _retni( __bt_lastrec(db) );
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_recpos2array(int argno) //diagnostics
{
    CCC_PROLOG("_db_recpos2array",1);
    char *buf=_parb(1);
    RECPOS rp;
    rp.pgno=load32(buf);
    rp.index=load16(buf+4);
    number(rp.pgno);
    number(rp.index);
    array(2);
    _rettop();
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_pgeval(int argno)
{
    CCC_PROLOG("_db_pgeval",3);
    BTREE *db=(BTREE*)_parp(1);
    pgno_t pgno=_parni(2);
    VALUE *block=ISBLOCK(3)?PARPTR(3):0;
    __bt_pgeval(db,pgno,block);
    _ret();
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
void _clp__db_pgread(int argno)
{
    // statisztikakhoz

    CCC_PROLOG("_db_pgread",2);
    BTREE *db=(BTREE*)_parp(1);
    pgno_t pgno=_parni(2);

    int fd=__bt_fd(db);
    off_t totalsize=lseek(fd,0,SEEK_END);
    int pagesize=__bt_pagesize(db);
    unsigned int maxpgno=totalsize/pagesize-1;

    if( 0<=pgno && pgno<=maxpgno )
    {
        DBT data;
        data.data=binaryl(pagesize);
        data.size=pagesize;

        if( pagesize==__bt_pgread(db,pgno,&data) )
        {
            _rettop();
        }
        else
        {
            _ret();
        }
    }
    else
    {
        _ret();
    }
    CCC_EPILOG();
}


//---------------------------------------------------------------------------
void _clp__db_pgrewrite(int argno)
{
    // titkositashoz

    CCC_PROLOG("_db_pgrewrite",3);
    BTREE *db=(BTREE*)_parp(1);
    pgno_t pgno=_parni(2);
    int cryptflg=_parl(3);

    int fd=__bt_fd(db);
    off_t totalsize=lseek(fd,0,SEEK_END);
    int pagesize=__bt_pagesize(db);
    unsigned int maxpgno=totalsize/pagesize-1;

    if( 0<=pgno && pgno<=maxpgno )
    {
        __bt_pgrewrite(db,pgno,cryptflg);
        _retl(1);
    }
    else
    {
        _retl(0);
    }
    CCC_EPILOG();
}

//---------------------------------------------------------------------------
