
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

#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef _UNIX_
#include <io.h>
#endif

#include <db.h>
#include <mpool.h>
#include <swap.h>

//#define DEBUG
#define MAXPIN 32

static void   *pinned[MAXPIN];
static pgno_t  pageno[MAXPIN];


//---------------------------------------------------------------------------
MPOOL *mpool_open(int fd, int pagesize, int cryptflg)
{
    MPOOL *mp;

#ifdef _UNIX_
    struct stat sb;
    if( fstat(fd,&sb) || !S_ISREG(sb.st_mode) )
    {
        return (MPOOL*)0; //error
    }
#endif

    mp=(MPOOL*)malloc(sizeof(MPOOL));
    memset(mp,0,sizeof(MPOOL));
    mp->fd=fd;
    mp->pagesize=pagesize;
    mp->count=0;
    mp->cryptflg=cryptflg;

    return (MPOOL*)mp;
}


//---------------------------------------------------------------------------
int mpool_close(MPOOL *mp)
{
    free(mp);
    return 0;
}


//---------------------------------------------------------------------------
void mpool_dump(MPOOL *mp, void *page)
{
    int i,n,offs=0;
    for( i=0; i<mp->pagesize; )
    {
        printf("\n%02x ",offs);
        for( n=0; n<16; n++,i++ )
        {
            if( (n%4)==0 )
            {
                printf(" ");
            }
            printf("%02x ", 255&*(((char*)page)+i) );
            fflush(0);
        }
        offs+=16;
    }
    printf("\n");
}


//---------------------------------------------------------------------------
int mpool_count(MPOOL *mp, const char *msg)
{
    if( mp->count )
    {
        fprintf(stderr,"\nERROR: mpool_count %d %s\n", mp->count,msg );
        fflush(0);
        raise(SIGTERM);
        exit(1);
    }

    return mp->count;
}

//---------------------------------------------------------------------------
void *mpool_new(MPOOL *mp, pgno_t *pgnoaddr)
{
    char *buf;

    buf=(char*)malloc(mp->pagesize);
    memset(buf,0,mp->pagesize);
    *pgnoaddr=lseek(mp->fd,0,SEEK_END)/mp->pagesize;
    *(pgno_t*)buf=*pgnoaddr;

    int retcode=write(mp->fd,buf,mp->pagesize);

    mp->count++;

    #ifdef DEBUG
      printf("MPOOL-DEBUG-%d new %d\n",mp->fd,*pgnoaddr);fflush(0);
    #endif
    return buf;
}

//---------------------------------------------------------------------------
void *mpool_get(MPOOL *mp, pgno_t pgno)
{
    int rb;
    char *buf;

    if( pgno==0 )
    {
        return 0;
    }

    buf=(char*)malloc(mp->pagesize);

    int attempt=0;
    while(1)
    {
        memset(buf,0,mp->pagesize);
        lseek(mp->fd,((off_t)pgno)*mp->pagesize,SEEK_SET);
        rb=read(mp->fd,buf,mp->pagesize);

        if( rb!=mp->pagesize )
        {
            free(buf);
            return 0;
        }

        if( mp->cryptflg )
        {
            mpool_decrypt(mp,pgno,buf);
        }

        pgno_t code=*(pgno_t*)buf; //uint32
        if( mp->pgin )
        {
            M_32_SWAP(code);
        }

        if( code==pgno )
        {
            //ok, pgno egyezik
            break;
        }
        else if( code==CRCPG(buf,mp->pagesize) ) //disk byte order!
        {
            //ok, CRC egyezik
            //fprintf(stderr,"page verified: fd=%d pgno=%x crc=%x\n",mp->fd,pgno,code);
            break;
        }
        else if( ++attempt>10 )
        {
            fprintf(stderr,"\npage corrupt: fd=%d pgno=%x code=%x crc=%x\n", mp->fd, pgno, code, CRCPG(buf,mp->pagesize) );
            fflush(0);
            raise(SIGTERM);
            exit(1);
        }
    }

    if( mp->pgin )
    {
        (*mp->pgin)(buf);
    }
    *(pgno_t*)buf=pgno; //CRC helyett pgno

    mp->count++;

    #ifdef DEBUG
      printf("MPOOL-DEBUG-%d get %d(%08X)\n",mp->fd,pgno,code);fflush(0);
    #endif

    return buf;
}

//---------------------------------------------------------------------------
int mpool_put(MPOOL *mp, void *page, int dirty)
{
    pgno_t pgno=*(pgno_t*)page;
    pgno_t code=0; //crc

    if( dirty )
    {
        if( mp->pgout )
        {
            (*mp->pgout)(page);
        }
        code=CRCPG(page,mp->pagesize);  //disk byte order!
        if( mp->pgout )
        {
            M_32_SWAP(code);
        }
        *(pgno_t*)page=code;

        if( mp->cryptflg )
        {
            mpool_encrypt(mp,pgno,(char*)page);
        }

        lseek(mp->fd,((off_t)pgno)*mp->pagesize,SEEK_SET);
        int retcode=write(mp->fd,page,mp->pagesize);
        memset(page,'#',mp->pagesize);
    }
    else
    {
        memset(page,'?',mp->pagesize);
    }
    free(page);

    mp->count--;

    #ifdef DEBUG
      printf("MPOOL-DEBUG-%d put %d(%08x)\n",mp->fd,pgno,code);fflush(0);
    #endif

    return 0;
}

//---------------------------------------------------------------------------
