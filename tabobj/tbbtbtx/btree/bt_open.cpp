
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

#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef _UNIX_
#include <io.h>
#endif
 
#include <btree.h>

static void  header(BTREE*);

//---------------------------------------------------------------------------
BTREE *__bt_open(int fd, int psize, int create)
{
    BTREE *t=0;
    struct stat sb;
    int machine_lorder;

    // Allocate and initialize BTREE structure.

    t=(BTREE*)malloc(sizeof(BTREE));
    memset(t,0,sizeof(BTREE));

    F_CLR(t,B_NEEDSWAP);              // default=machine order

    t->bt_fd        = fd;             // -1 or a previously opened fd.
    t->bt_cmp       = __bt_defcmp;    // Lexicographic.
    t->bt_psize     = psize;          // 0 -> block size.
    t->bt_lockcount = 0;
    t->bt_dirtyflag = 0;
 
    if( t->bt_fd<0 )
    {
        fprintf(stderr,"FDESC:%d\n",errno);fflush(0);
        goto err;
    }
 
#ifdef _UNIX_
    if( fcntl(t->bt_fd,F_SETFD,1)==-1 ) //close-on-exec
    {
        fprintf(stderr,"FCNTL:%d\n",errno);fflush(0);
        goto err;
    }
#endif

    if( fstat(t->bt_fd,&sb) )
    {
        fprintf(stderr,"FSTAT:%d\n",errno);fflush(0);
        goto err;
    }
 
    if( !create && sb.st_size  ) 
    {
        if( __bt_header_read(t,0)!=RET_SUCCESS )
        {
            goto err;
        }

        if( t->magic!=BTREEMAGIC )
        {
            //forditott byte sorrend?
            
            if( F_ISSET(t,B_NEEDSWAP) )
            {
                F_CLR(t,B_NEEDSWAP); 
            }
            else
            {
                F_SET(t,B_NEEDSWAP); 
            }
            __bt_header_read(t,0); 

            if( t->magic!=BTREEMAGIC )
            {
                fprintf(stderr,"BTREEMAGIC\n");fflush(0);
                goto eftype;
            }
        }

        if( (GETVER(t)!=1) && (GETVER(t)!=2)  )
        {
            fprintf(stderr,"BTREEVERSION\n");fflush(0);
            goto eftype;
        }
 
        if( t->bt_psize<256 || t->bt_psize&(sizeof(indx_t)-1) )
        {
            fprintf(stderr,"MINPAGESIZE\n");fflush(0);
            goto eftype;
        }
    } 
    else if( create &&  sb.st_size==0 ) 
    {
        // Newly created file.
        // Set the page size to the best value for I/O to this file.

        if( t->bt_psize==0 ) 
        {
            #ifdef _UNIX_
              t->bt_psize=sb.st_blksize;
            #else
              t->bt_psize=4096;
            #endif
        }

        t->bt_free=P_INVALID;
        t->magic=BTREEMAGIC;
        SETVER(t,BTREEVERSION);
        char *pwenv=getenv("CCC_BTPASSWD");
        if(  pwenv!=0 && *pwenv!=0 )
        {
            SETENC(t,1); //titkositott
        }

        header(t); //create header page
    }
    else
    {
        goto err;
    }

    // Initialize pager. 
    if( (t->bt_mp= mpool_open(t->bt_fd,t->bt_psize,GETENC(t)))==NULL )
    {
        fprintf(stderr,"MPOOL:%d\n",errno);fflush(0);
        goto err;
    }
    
    t->bt_mp->pgin=F_ISSET(t,B_NEEDSWAP)?(void (*)(void*))__bt_swapin:0;
    t->bt_mp->pgout=F_ISSET(t,B_NEEDSWAP)?(void (*)(void*))__bt_swapout:0;
    
    //__bt_print_bthdr(t,"open");
    //__bt_print_free(t);
 
    mpool_count(t->bt_mp, "open");
    return t;

einval:    
    errno = EINVAL;
    fprintf(stderr,"EINVAL:%d\n",errno);fflush(0);
    goto err;

eftype:     
    errno = EINVAL;
    fprintf(stderr,"EFTYPE:%d\n",errno);fflush(0);
    goto err;

err:    
    fprintf(stderr,"ERROR:%d\n",errno);fflush(0);

    if( t )
    {
        if(t->bt_fd!=-1) 
        {
            close(t->bt_fd);
        }
        free(t);
    }

    return NULL;
}



//---------------------------------------------------------------------------
static void header(BTREE *t)  //create header
{    
    char *p;
    __bt_pagelock(t,0,1);
    t->bt_lockcount=1;
    p=(char*)malloc(t->bt_psize);
    memset(p,0,t->bt_psize);
    lseek(t->bt_fd,0,SEEK_SET);
    int retcode=write(t->bt_fd,p,t->bt_psize);
    __bt_header_write(t);
}
 
//---------------------------------------------------------------------------
int __bt_fd(BTREE *t) //file descriptor
{
    return  t->bt_fd;
}

//---------------------------------------------------------------------------
int __bt_pagesize(BTREE *t) 
{
    return  t->bt_psize;
}
 
//---------------------------------------------------------------------------




