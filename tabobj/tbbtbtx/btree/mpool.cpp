
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
 
//#define DEBUG
#define MAXPIN 32

static void   *pinned[MAXPIN];
static pgno_t  pageno[MAXPIN];


static void pin_ini();
static int pin_count();
static void pin_store(void*p,pgno_t x);
static void pin_drop(void*p,pgno_t x);
 
//---------------------------------------------------------------------------
static void pin_ini()
{
    int n;
    for(n=0; n<MAXPIN; n++)
    {
        pinned[n]=0;
        pageno[n]=0;
    }
}

static int pin_count()
{
    int count=0, n;
    for(n=0; n<MAXPIN; n++)
    {
        if( pinned[n] )
        {
            count++;
        }
    }
    return count;
}


static void pin_store(void*p,pgno_t x)
{
    int n;
    for(n=0; n<MAXPIN; n++)
    {
        if( pinned[n]==0 )
        {
            pinned[n]=p;
            pageno[n]=x;
            return;
        }
    }

    fprintf(stderr,"pin_store overflow\n");
    raise(SIGTERM);
    exit(1);
}
 
static void pin_drop(void*p,pgno_t x)
{
    int n;
    for(n=0; n<MAXPIN; n++)
    {
        if( pinned[n]==p )
        {
            if( x!=pageno[n] )
            {
                fprintf(stderr,"pin_drop pgno diff %d %d\n",x,pageno[n]);
                raise(SIGTERM);
                exit(1);
            }
            pinned[n]=0;
            pageno[n]=0; 
            return;
        }
    }

    fprintf(stderr,"pin_drop not found\n");
    raise(SIGTERM);
    exit(1);
}


//---------------------------------------------------------------------------
MPOOL *mpool_open(int fd, int pagesize)
{
    MPOOL *mp;

#ifdef _UNIX_
    struct stat sb;
    if( fstat(fd,&sb) || !S_ISREG(sb.st_mode) )
    {
        return (MPOOL*)0; //error
    }
#endif    
    
    pin_ini();

    mp=(MPOOL*)malloc(sizeof(MPOOL));
    memset(mp,0,sizeof(MPOOL));
    mp->fd=fd;
    mp->pagesize=pagesize;
    mp->count=0;

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
    int i,n; 
    for( i=0; i<mp->pagesize; )
    {
        printf("\n");
        for( n=0; n<16; n++,i++ )
        {
            printf("%02x ", 255&*(((char*)page)+i) );
            fflush(0); 
        }
    }
    printf("\n");
}

 
//---------------------------------------------------------------------------
int mpool_count(MPOOL *mp, const char *msg)
{
    if( mp->count ) 
    {
        fprintf(stderr,"ERROR: mpool_count %d %s\n", mp->count,msg );
        raise(SIGTERM);
        exit(1);
    }
    else if( pin_count() ) 
    {
        fprintf(stderr,"ERROR: pin_count %d %s\n", pin_count(),msg );
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

    0==write(mp->fd,buf,mp->pagesize);

    pin_store(buf,*pgnoaddr);
    mp->count++;

    #ifdef DEBUG
      printf("MPOOL-DEBUG new %d\n",*pgnoaddr);fflush(0);
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
    memset(buf,0,mp->pagesize);
    lseek(mp->fd,((off_t)pgno)*mp->pagesize,SEEK_SET);
    rb=read(mp->fd,buf,mp->pagesize);

    if( rb!=mp->pagesize )
    {
        free(buf);
        return 0;
    }
 
    if( mp->pgin )
    {
        (*mp->pgin)(buf);
    }
 
    pin_store(buf,pgno);
    mp->count++;

    #ifdef DEBUG
      printf("MPOOL-DEBUG get %d\n",pgno);fflush(0);
    #endif

    return buf; 
}

//---------------------------------------------------------------------------
int mpool_put(MPOOL *mp, void *page, int dirty)
{
    pgno_t pgno=*(pgno_t*)page;
    
    if( dirty )
    {
        lseek(mp->fd,((off_t)pgno)*mp->pagesize,SEEK_SET);
        if( mp->pgout )
        {
            (*mp->pgout)(page);
        }
        0==write(mp->fd,page,mp->pagesize);
        memset(page,'#',mp->pagesize);
    }
    else
    {
        memset(page,'?',mp->pagesize);
    }
    free(page);

    pin_drop(page,pgno);
    mp->count--;

    #ifdef DEBUG
      printf("MPOOL-DEBUG put %d(%d)\n",pgno,dirty);fflush(0);
    #endif

    return 0;
}

//---------------------------------------------------------------------------
